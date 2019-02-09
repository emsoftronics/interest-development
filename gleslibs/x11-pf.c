#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
//#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>

#define X11_WIN_WIDTH   600
#define X11_WIN_HEIGHT  600
#define X11_WIN_TITLE  "Server Render Screen"


typedef struct {
        EGLint       major;
        EGLint       minor;
        EGLint       width;
        EGLint       height;
        EGLNativeWindowType  hWnd;
        EGLDisplay  eglDisplay;
        EGLContext  eglContext;
        EGLSurface  eglSurface;
        Display *x_display;
} x11_pf_t;

static x11_pf_t xpf = {
    .major = 0,
    .minor = 0,
    .width = X11_WIN_WIDTH,
    .height = X11_WIN_HEIGHT,
    .hWnd = 0,
    .eglDisplay = EGL_NO_DISPLAY,
    .eglContext = EGL_NO_CONTEXT,
    .eglSurface = EGL_NO_SURFACE,
    .x_display = NULL
};

static EGLBoolean createWindow(const char *title)
{
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    //EGLConfig ecfg;
    //EGLint num_config;
    Window win;

    /*
     * X11 native display initialization
     */

    xpf.x_display = XOpenDisplay(NULL);
    if ( xpf.x_display == NULL )
    {
        return EGL_FALSE;
    }

    root = DefaultRootWindow(xpf.x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
    win = XCreateWindow(
               xpf.x_display, root,
               0, 0, xpf.width, xpf.height, 0,
               CopyFromParent, InputOutput,
               CopyFromParent, CWEventMask,
               &swa );

    xattr.override_redirect = EGL_FALSE;
    XChangeWindowAttributes ( xpf.x_display, win, CWOverrideRedirect, &xattr );

    hints.input = EGL_FALSE;
    hints.flags = InputHint;
    XSetWMHints(xpf.x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow (xpf.x_display, win);
    XStoreName (xpf.x_display, win, title);

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom (xpf.x_display, "_NET_WM_STATE", EGL_FALSE);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = EGL_FALSE;
    XSendEvent (
       xpf.x_display,
       DefaultRootWindow ( xpf.x_display ),
       EGL_FALSE,
       SubstructureNotifyMask,
       &xev );

    xpf.hWnd = (EGLNativeWindowType) win;
    return EGL_TRUE;
}

static EGLBoolean createEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
                              EGLContext* eglContext, EGLSurface* eglSurface,
                              EGLint attribList[])
{
 EGLint numConfigs;
   EGLint majorVersion;
   EGLint minorVersion;
   EGLDisplay display;
   EGLContext context;
   EGLSurface surface;
   EGLConfig config;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

   // Get Display
   display = eglGetDisplay((EGLNativeDisplayType)xpf.x_display);
   if ( display == EGL_NO_DISPLAY )
   {
      return EGL_FALSE;
   }

   // Initialize EGL
   if ( !eglInitialize(display, &majorVersion, &minorVersion) )
   {
      return EGL_FALSE;
   }
   xpf.major = majorVersion;
   xpf.minor = minorVersion;
   // Get configs
   if ( !eglGetConfigs(display, NULL, 0, &numConfigs) )
   {
      return EGL_FALSE;
   }

   // Choose config
   if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
   {
      return EGL_FALSE;
   }

   // Create a surface
   surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)xpf.hWnd, NULL);
   if ( surface == EGL_NO_SURFACE )
   {
      return EGL_FALSE;
   }

   // Create a GL context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
   if ( context == EGL_NO_CONTEXT )
   {
      return EGL_FALSE;
   }

   // Make the context current
   if ( !eglMakeCurrent(display, surface, surface, context) )
   {
      return EGL_FALSE;
   }

   *eglDisplay = display;
   *eglSurface = surface;
   *eglContext = context;
   return EGL_TRUE;
}

static void init_x11_pf(void)
{
    int flags = 0;
    EGLint attribList[] =
    {
       EGL_RED_SIZE,       5,
       EGL_GREEN_SIZE,     6,
       EGL_BLUE_SIZE,      5,
       EGL_ALPHA_SIZE,     (flags & 1) ? 8 : EGL_DONT_CARE,
       EGL_DEPTH_SIZE,     (flags & 2) ? 8 : EGL_DONT_CARE,
       EGL_STENCIL_SIZE,   (flags & 3) ? 8 : EGL_DONT_CARE,
       EGL_SAMPLE_BUFFERS, (flags & 4) ? 1 : 0,
       EGL_NONE
    };

    if ( !createWindow (X11_WIN_TITLE) )
    {
      printf("%s: Creation of X11 window is failed!!\n", X11_WIN_TITLE);
      return;
    }


   if ( !createEGLContext ( xpf.hWnd,
                            &xpf.eglDisplay,
                            &xpf.eglContext,
                            &xpf.eglSurface,
                            attribList) )
   {
      printf("%s: Creation of EGL context for X11 window is failed!!\n", X11_WIN_TITLE);
      return;
   }
}

#ifdef EXTERNAL_EGL_PROFILE

void ep_get_window_resolution(EGLint *width, EGLint *height)
{
    *width = xpf.width;
    *height = xpf.height;
}
void ep_get_display_major_minor(EGLint *major, EGLint *minor)
{
    *major = xpf.major;
    *minor = xpf.minor;
}

void *ep_get_native_window(EGLDisplay *disp, EGLContext *ctx, EGLSurface *surf, EGLConfig *config)
{
    init_x11_pf();
    *disp = xpf.eglDisplay;
    *ctx = xpf.eglContext;
    *surf = xpf.eglSurface;
    *config = 1;
    return xpf.hWnd;
}

void *ep_get_user_data(void)
{
    return NULL;
}

EGLBoolean ep_SwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    return eglSwapBuffers(dpy, surface);
}

void ep_destroy_native_window(void)
{
    //TODO
}

#endif
