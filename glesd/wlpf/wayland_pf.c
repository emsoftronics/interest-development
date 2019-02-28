/*
 * =====================================================================================
 *
 *       Filename:  wayland_pf.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Saturday 09 February 2019 02:24:47  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */


//#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <signal.h>

#include <linux/input.h>

#include <wayland-client.h>
#include <wayland-egl.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <sys/types.h>
#include <unistd.h>
#include "ivi-application-client-protocol.h"
#define IVI_SURFACE_ID 9000

#include "weston-egl-ext.h"
#include "weston_platform.h"

#ifndef EGL_EXT_swap_buffers_with_damage
#define EGL_EXT_swap_buffers_with_damage 1
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)(EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#endif

#ifndef EGL_EXT_buffer_age
#define EGL_EXT_buffer_age 1
#define EGL_BUFFER_AGE_EXT          0x313D
#endif

struct window;
struct seat;

struct display {
    struct wl_display *display;
    struct wl_registry *registry;
    struct wl_compositor *compositor;
    struct wl_seat *seat;
    struct wl_shm *shm;
    struct {
        EGLDisplay dpy;
        EGLContext ctx;
        EGLConfig conf;
        EGLint major;
        EGLint minor;
    } egl;
    struct window *window;
    struct ivi_application *ivi_application;

    PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC swap_buffers_with_damage;
};

struct geometry {
    int width, height;
};

struct window {
    struct display *display;
    struct geometry geometry, window_size;

    uint32_t benchmark_time, frames;
    struct wl_egl_window *native;
    struct wl_surface *surface;
    struct ivi_surface *ivi_surface;
    EGLSurface egl_surface;
    struct wl_callback *callback;
    int opaque, buffer_size, frame_sync;
};


static void
init_egl(struct display *display, struct window *window)
{
    static const EGLint context_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    const char *extensions;

    EGLint config_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_ALPHA_SIZE, 1,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLint n, count, i, size;
    EGLConfig *configs;
    EGLBoolean ret;

    if (window->opaque || window->buffer_size == 16)
        config_attribs[9] = 0;

    display->egl.dpy =
        weston_platform_get_egl_display(EGL_PLATFORM_WAYLAND_KHR,
                        display->display, NULL);
    assert(display->egl.dpy);

    ret = eglInitialize(display->egl.dpy, &display->egl.major, &display->egl.minor);
    assert(ret == EGL_TRUE);
    ret = eglBindAPI(EGL_OPENGL_ES_API);
    assert(ret == EGL_TRUE);

    if (!eglGetConfigs(display->egl.dpy, NULL, 0, &count) || count < 1)
        assert(0);

    configs = calloc(count, sizeof *configs);
    assert(configs);

    ret = eglChooseConfig(display->egl.dpy, config_attribs,
                  configs, count, &n);
    assert(ret && n >= 1);

    for (i = 0; i < n; i++) {
        eglGetConfigAttrib(display->egl.dpy,
                   configs[i], EGL_BUFFER_SIZE, &size);
        if (window->buffer_size == size) {
            display->egl.conf = configs[i];
            break;
        }
    }
    free(configs);
    if (display->egl.conf == NULL) {
        fprintf(stderr, "did not find config with buffer size %d\n",
            window->buffer_size);
        exit(EXIT_FAILURE);
    }

    display->egl.ctx = eglCreateContext(display->egl.dpy,
                        display->egl.conf,
                        EGL_NO_CONTEXT, context_attribs);
    assert(display->egl.ctx);

    display->swap_buffers_with_damage = NULL;
    extensions = eglQueryString(display->egl.dpy, EGL_EXTENSIONS);
    if (extensions &&
        strstr(extensions, "EGL_EXT_swap_buffers_with_damage") &&
        strstr(extensions, "EGL_EXT_buffer_age"))
        display->swap_buffers_with_damage =
            (PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)
            eglGetProcAddress("eglSwapBuffersWithDamageEXT");

    if (display->swap_buffers_with_damage)
        printf("has EGL_EXT_buffer_age and EGL_EXT_swap_buffers_with_damage\n");

}

static void
fini_egl(struct display *display)
{
    eglTerminate(display->egl.dpy);
    eglReleaseThread();
}


static void
handle_ivi_surface_configure(void *data, struct ivi_surface *ivi_surface,
                             int32_t width, int32_t height)
{
    struct window *window = data;

    wl_egl_window_resize(window->native, width, height, 0, 0);

    window->geometry.width = width;
    window->geometry.height = height;
    window->window_size = window->geometry;
}

static const struct ivi_surface_listener ivi_surface_listener = {
    handle_ivi_surface_configure,
};


static void
create_ivi_surface(struct window *window, struct display *display)
{
    uint32_t id_ivisurf = IVI_SURFACE_ID + (uint32_t)getpid();
    char *option = NULL;
    char *end;

    option = getenv("QT_IVI_SURFACE_ID");
    if (!option) option = getenv("IVI_CLIENT_SURFACE_ID");

    if (option) id_ivisurf = strtol(option, &end, 0);
    window->ivi_surface =
        ivi_application_surface_create(display->ivi_application,
                           id_ivisurf, window->surface);

    if (window->ivi_surface == NULL) {
        fprintf(stderr, "Failed to create ivi_client_surface\n");
        abort();
    }

    ivi_surface_add_listener(window->ivi_surface,
                 &ivi_surface_listener, window);
}

static void
create_surface(struct window *window)
{
    struct display *display = window->display;
    EGLBoolean ret;

    window->surface = wl_compositor_create_surface(display->compositor);

    window->native =
        wl_egl_window_create(window->surface,
                     window->geometry.width,
                     window->geometry.height);
    window->egl_surface =
        weston_platform_create_egl_surface(display->egl.dpy,
                           display->egl.conf,
                           window->native, NULL);


    if (display->ivi_application ) {
        create_ivi_surface(window, display);
    } else {
        assert(0);
    }

    ret = eglMakeCurrent(window->display->egl.dpy, window->egl_surface,
                 window->egl_surface, window->display->egl.ctx);
    assert(ret == EGL_TRUE);

    if (!window->frame_sync)
        eglSwapInterval(display->egl.dpy, 0);
}

static void
destroy_surface(struct window *window)
{
    /* Required, otherwise segfault in egl_dri2.c: dri2_make_current()
     * on eglReleaseThread(). */
    eglMakeCurrent(window->display->egl.dpy, EGL_NO_SURFACE, EGL_NO_SURFACE,
               EGL_NO_CONTEXT);

    eglDestroySurface(window->display->egl.dpy, window->egl_surface);
    wl_egl_window_destroy(window->native);

    if (window->display->ivi_application)
        ivi_surface_destroy(window->ivi_surface);
    wl_surface_destroy(window->surface);

    if (window->callback)
        wl_callback_destroy(window->callback);
}

static void
seat_handle_capabilities(void *data, struct wl_seat *seat,
             enum wl_seat_capability caps)
{
}

static const struct wl_seat_listener seat_listener = {
    seat_handle_capabilities,
};

static void
registry_handle_global(void *data, struct wl_registry *registry,
               uint32_t name, const char *interface, uint32_t version)
{
    struct display *d = data;
    if (strcmp(interface, "wl_compositor") == 0) {
        d->compositor =
            wl_registry_bind(registry, name,
                     &wl_compositor_interface, 1);
    } else if (strcmp(interface, "wl_seat") == 0) {
        d->seat = wl_registry_bind(registry, name,
                       &wl_seat_interface, 1);
        wl_seat_add_listener(d->seat, &seat_listener, d);
    } else if (strcmp(interface, "wl_shm") == 0) {
        d->shm = wl_registry_bind(registry, name,
                      &wl_shm_interface, 1);
    } else if (strcmp(interface, "ivi_application") == 0) {
        d->ivi_application =
            wl_registry_bind(registry, name,
                     &ivi_application_interface, 1);
    }
}

static void
registry_handle_global_remove(void *data, struct wl_registry *registry,
                  uint32_t name)
{
}

static const struct wl_registry_listener registry_listener = {
    registry_handle_global,
    registry_handle_global_remove
};

static int get_screen_resolution(int screen_id, EGLint *width, EGLint *height)
{
    unsigned int* screenIDs = NULL;
    unsigned int numberOfScreens = 0;
    unsigned int reqId = 0;
    int ret = -1;

    if ((!width) || (!height))  goto ResError;
    if (screen_id < 0) screen_id = 0;
    *width = 0; *height = 0;

    if (ilm_init() != 0) {
        printf("ilm_init failed\n");
        goto ResError;
    }

    if (ilm_getScreenIDs(&numberOfScreens, &screenIDs) != 0) {
        printf("ilm_getScreenIDs failed!!\n");
        goto ResError;
    }
    else {
        if(((int)numberOfScreens == 0) || (screen_id >= (int)numberOfScreens)) {
            goto ResError;
        }
        reqId = screenIDs[screen_id];
    }

    if (ilm_getScreenResolution(reqId, width, height) != 0) {
        printf("ilm_getScreenResolution failed\n");
        goto ResError;
    }
    ret = 0;
ResError:
    if (screenIDs) free(screenIDs);
    ilm_destroy();
    return ret;
}

#if 0
static GLuint
create_shader(const char *source, GLenum shader_type)
{
    GLuint shader;
    GLint status;

    shader = glCreateShader(shader_type);
    assert(shader != 0);

    glShaderSource(shader, 1, (const char **) &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char log[1000];
        GLsizei len;
        glGetShaderInfoLog(shader, 1000, &len, log);
        fprintf(stderr, "Error: compiling %s: %*s\n",
            shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment",
            len, log);
        exit(1);
    }

    return shader;
}

static const char *vert_shader_text =
    "uniform mat4 rotation;\n"
    "attribute vec4 pos;\n"
    "attribute vec4 color;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "  gl_Position = rotation * pos;\n"
    "  v_color = color;\n"
    "}\n";

static const char *frag_shader_text =
    "precision mediump float;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "  gl_FragColor = v_color;\n"
    "}\n";

static void
init_gl(void)
{
    GLuint frag, vert;
    GLuint program;
    GLint status;

    frag = create_shader(frag_shader_text, GL_FRAGMENT_SHADER);
    vert = create_shader(vert_shader_text, GL_VERTEX_SHADER);

    program = glCreateProgram();
    glAttachShader(program, frag);
    glAttachShader(program, vert);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        char log[1000];
        GLsizei len;
        glGetProgramInfoLog(program, 1000, &len, log);
        fprintf(stderr, "Error: linking:\n%*s\n", len, log);
        exit(1);
    }

    glUseProgram(program);

    glBindAttribLocation(program, 0, "pos");
    glBindAttribLocation(program, 1, "color");
    glLinkProgram(program);

   //rotation_uniform =
   //     glGetUniformLocation(program, "rotation");
}


static void
redraw(void *data, struct wl_callback *callback, uint32_t time)
{
    struct window *window = data;
    struct display *display = window->display;
    static const GLfloat verts[3][2] = {
        { -0.5, -0.5 },
        {  0.5, -0.5 },
        {  0,    0.5 }
    };
    static const GLfloat colors[3][3] = {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    };
    GLfloat angle;
    GLfloat rotation[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };
    static const uint32_t speed_div = 5, benchmark_interval = 5;
    struct wl_region *region;
    EGLint rect[4];
    EGLint buffer_age = 0;
    struct timeval tv;

    assert(window->callback == callback);
    window->callback = NULL;

    if (callback)
        wl_callback_destroy(callback);

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (window->frames == 0)
        window->benchmark_time = time;
    if (time - window->benchmark_time > (benchmark_interval * 1000)) {
        printf("%d frames in %d seconds: %f fps\n",
               window->frames,
               benchmark_interval,
               (float) window->frames / benchmark_interval);
        window->benchmark_time = time;
        window->frames = 0;
    }

    angle = (time / speed_div) % 360 * M_PI / 180.0;
    rotation[0][0] =  cos(angle);
    rotation[0][2] =  sin(angle);
    rotation[2][0] = -sin(angle);
    rotation[2][2] =  cos(angle);

    if (display->swap_buffers_with_damage)
        eglQuerySurface(display->egl.dpy, window->egl_surface,
                EGL_BUFFER_AGE_EXT, &buffer_age);

    glViewport(0, 0, window->geometry.width, window->geometry.height);

    glUniformMatrix4fv(window->gl.rotation_uniform, 1, GL_FALSE,
               (GLfloat *) rotation);

    glClearColor(0.0, 0.0, 0.0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    glVertexAttribPointer(window->gl.pos, 2, GL_FLOAT, GL_FALSE, 0, verts);
    glVertexAttribPointer(window->gl.col, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(window->gl.pos);
    glEnableVertexAttribArray(window->gl.col);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(window->gl.pos);
    glDisableVertexAttribArray(window->gl.col);

    usleep(window->delay);

    if (window->opaque || window->fullscreen) {
        region = wl_compositor_create_region(window->display->compositor);
        wl_region_add(region, 0, 0,
                  window->geometry.width,
                  window->geometry.height);
        wl_surface_set_opaque_region(window->surface, region);
        wl_region_destroy(region);
    } else {
        wl_surface_set_opaque_region(window->surface, NULL);
    }

    if (display->swap_buffers_with_damage && buffer_age > 0) {
        rect[0] = window->geometry.width / 4 - 1;
        rect[1] = window->geometry.height / 4 - 1;
        rect[2] = window->geometry.width / 2 + 2;
        rect[3] = window->geometry.height / 2 + 2;
        display->swap_buffers_with_damage(display->egl.dpy,
                          window->egl_surface,
                          rect, 1);
    } else {
        eglSwapBuffers(display->egl.dpy, window->egl_surface);
    }
    window->frames++;
}
#endif

static EGLBoolean create_region(struct window *window)
{
    struct wl_region *region;
    struct display *display = window->display;
    region = wl_compositor_create_region(window->display->compositor);
    wl_region_add(region, 0, 0, window->geometry.width, window->geometry.height);
    wl_surface_set_opaque_region(window->surface, region);
    wl_region_destroy(region);
    return eglSwapBuffers(display->egl.dpy, window->egl_surface);
}

static struct display display = { 0 };
static struct window  window  = { 0 };

static int init_wayland_platform(void)
{
    window.display = &display;
    display.window = &window;
    if (get_screen_resolution(0, &window.geometry.width, &window.geometry.height) < 0) {
        window.geometry.width  = 600;
        window.geometry.height = 600;
    }
    window.window_size = window.geometry;
    window.buffer_size = 32;
    window.frame_sync = 1;

    display.display = wl_display_connect(NULL);
    if (display.display <= 0) {
        perror("wl_display_connect");
        return -1;
    }

    display.registry = wl_display_get_registry(display.display);
    wl_registry_add_listener(display.registry,
                 &registry_listener, &display);

    wl_display_dispatch(display.display);

    init_egl(&display, &window);
    create_surface(&window);
    wl_display_roundtrip(display.display);
    create_region(&window);
    printf("%s:%dx%d\n", __func__, window.geometry.width, window.geometry.height);
    wl_display_dispatch_pending(display.display);
    printf("%s:Successfully initialized wayland platform\n", __func__);
    return 0;
}


static void exit_wayaland_platform(void)
{
    destroy_surface(&window);
    fini_egl(&display);

    if (display.ivi_application)
        ivi_application_destroy(display.ivi_application);

    if (display.compositor)
        wl_compositor_destroy(display.compositor);

    wl_registry_destroy(display.registry);
    wl_display_flush(display.display);
    wl_display_disconnect(display.display);
}


#ifdef EXTERNAL_EGL_PROFILE

void ep_get_window_resolution(EGLint *width, EGLint *height)
{
    *width = window.geometry.width;
    *height = window.geometry.height;
}
void ep_get_display_major_minor(EGLint *major, EGLint *minor)
{
    *major = display.egl.major;
    *minor = display.egl.minor;
}

void *ep_get_native_window(EGLDisplay *disp, EGLContext *ctx, EGLSurface *surf, EGLConfig *config)
{
    if (init_wayland_platform() < 0) return NULL;
    *disp = display.egl.dpy;
    *ctx = display.egl.ctx;
    *surf = window.egl_surface;
    *config = display.egl.conf;
    return window.native;
}

EGLBoolean ep_SwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    //EGLBoolean ret = eglSwapBuffers(dpy, surface);
    EGLBoolean ret = create_region(&window);
    wl_display_dispatch_pending(display.display);
    return ret;
}

void *ep_get_user_data(void)
{
    return &window;
}

void ep_destroy_native_window(void)
{
    exit_wayaland_platform();
}
#endif
