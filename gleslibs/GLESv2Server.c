
#include "glesenum.h"
#include "vmcutil.h"
#include <stdlib.h>
#include <string.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

#define G_BF(_idx)          *((GLbitfield *)args[_idx])
#define G_BL(_idx)          *((GLboolean *)args[_idx])
#define G_EN(_idx)          *((GLenum *)args[_idx])
#define G_UI(_idx)          *((GLuint *)args[_idx])
#define G_FL(_idx)          *((GLfloat *)args[_idx])
#define G_CH(_idx)          *((GLchar *)args[_idx])
#define G_IN(_idx)          *((GLint *)args[_idx])
#define G_ST(_idx)          *((GLshort *)args[_idx])
#define G_US(_idx)          *((GLushort *)args[_idx])
#define G_SIP(_idx)          *((GLsizeiptr *)args[_idx])
#define G_SII(_idx)          *((GLsizei *)args[_idx])
#define G_IPT(_idx)          *((GLintptr *)args[_idx])
#define G_VPTR(_idx)        ((void *)args[_idx])

#ifdef EXTERNAL_EGL_PROFILE
extern void ep_get_window_resolution(EGLint *width, EGL *height);
extern void ep_get_display_major_minor(EGLint *major, EGL *minor);
extern void *ep_get_native_window(EGLDisplay *disp, EGLContext *ctx, EGLSurface *surf, EGLConfig *config);
extern void *ep_get_user_data(void);
#else
static void ep_get_window_resolution(EGLint *width, EGL *height)
{
    *width = 0;
    *height = 0;
}

static void ep_get_display_major_minor(EGLint *major, EGL *minor)
{
    *major = 0;
    *minor = 0;
}

static void *ep_get_native_window(EGLDisplay *disp, EGLContext *ctx, EGLSurface *surf, EGLConfig *config)
{
    *disp = EGL_NO_DISPLAY;
    *ctx = EGL_NO_CONTEXT;
    *surf = EGL_NO_SURFACE;
    *config = EGL_NONE;
    return NULL;
}

static void *ep_get_user_data(void) {return NULL;}

#endif

typedef struct {
        EGLint       width;
        EGLint       height;
        EGLint       major;
        EGLint       minor;
        EGLNativeWindowType  hWnd;
        EGLDisplay  eglDisplay;
        EGLContext  eglContext;
        EGLSurface  eglSurface;
        EGLConfig   eglConfig;
        void *user_data_ref;
        int initialized;
} egl_profile_t;

static egl_profile_t gs_egl_profile = {0};

static void init_egl_profile(void)
{
    gs_egl_profile.hWnd = (EGLNativeWindowType)ep_get_native_window(&gs_egl_profile.eglDisplay,
        &gs_egl_profile.eglContext, &gs_egl_profile.eglSurface, &gs_egl_profile.eglConfig);\
     ep_get_display_major_minor(&gs_egl_profile.major, &gs_egl_profile.minor);
     ep_get_window_resolution(&gs_egl_profile.width, &gs_egl_profile.height);
     user_data_ref = ep_get_user_data();
    if (gs_egl_profile.eglDisplay == EGL_NO_DISPLAY) gs_egl_profile.initialized = 0;
    else gs_egl_profile.initialized = 1;
}

static void fcall_handler(int fid, int argc, void **args, void *ret, uint32_t *retsize)
{
    static void *vertex_buffer = NULL;

    if (!gs_egl_profile.initialized) init_egl_profile();

    switch (fid) {
        case EGL_eglGetError:
             *((EGLint *)ret) = eglGetError(); *retsize = sizeof(EGLint);
            break;
        case EGL_eglGetDisplay:
//            EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id);
             *((EGLDisplay *)ret) = gs_egl_profile.eglDisplay; *retsize = sizeof(EGLDisplay);
            break;
        case EGL_eglInitialize:
//            EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor);
            *((EGLint *)args[1]) = gs_egl_profile.major;
            *((EGLint *)args[2]) = gs_egl_profile.minor;
            *((EGLBoolean *)ret) = (gs_egl_profile.initialized)? EGL_TRUE :EGL_FALSE; *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglTerminate:
//            EGLAPI EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy);
            *((EGLBoolean *)ret) = EGL_TRUE; *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglQueryString:
//            EGLAPI const char * EGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name);
            ret = eglQueryString(gs_egl_profile.eglDisplay, *((EGLint *)args[1])); *retsize = sizeof(ret);
            memcpy(args[2], ret, *((int *)args[3]));
            break;
        case EGL_eglGetProcAddress:
//            EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress(const char *procname);
            *((long *) ret) = (long)eglGetProcAddress((const char *)args[0]); *retsize = sizeof(long);
            break;
        case EGL_eglGetConfigs:
            *((EGLBoolean *)ret) = eglGetConfigs(gs_egl_profile.eglDisplay, (EGLConfig *)args[1],
                         *((EGLint*)args[2]), (EGLint *)args[3]);
            *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglChooseConfig:
            *((EGLBoolean *)ret) = eglChooseConfig(gs_egl_profile.eglDisplay, (const EGLint *)args[1],
                           (EGLConfig *)args[2], *((EGLint*)args[3]),
                           (EGLint *)args[4]);
            *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglGetConfigAttrib:
            *((EGLBoolean *)ret) = eglGetConfigAttrib(gs_egl_profile.eglDisplay, *((EGLConfig *)args[1]),
                              *((EGLint *)args[2]), (EGLint *)args[3]);
            *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglCreateWindowSurface:
//            EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
//                                  EGLNativeWindowType win,
//                                  const EGLint *attrib_list);
            *((EGLSurface *)ret) = gs_egl_profile.eglSurface; *retsize = sizeof(EGLSurface);
            break;
        case EGL_eglCreatePixmapSurface:
//            EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config,
//                                  EGLNativePixmapType pixmap,
//                                  const EGLint *attrib_list);
            *((EGLSurface *)ret) = gs_egl_profile.eglSurface; *retsize = sizeof(EGLSurface);
            break;
        case EGL_eglCreatePbufferSurface:
//            EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config,
//                                   const EGLint *attrib_list);
            *((EGLSurface *)ret) = gs_egl_profile.eglSurface; *retsize = sizeof(EGLSurface);
            break;
        case EGL_eglDestroySurface:
//            EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface);
            *((EGLBoolean *)ret) = (gs_egl_profile.initialized)? EGL_TRUE :EGL_FALSE; *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglQuerySurface:
//            EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface(EGLDisplay dpy, EGLSurface surface,
//                           EGLint attribute, EGLint *value);
            *((EGLBoolean *)ret) = eglQuerySurface(gs_egl_profile.eglDisplay, gs_egl_profile.eglSurface,
                *((EGLint *)args[2]), (EGLint *)args[3]); *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglCreateContext:
//            EGLAPI EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config,
//                            EGLContext share_context,
//                            const EGLint *attrib_list);
            *((EGLContext *)ret) = gs_egl_profile.eglContext; *retsize = sizeof(EGLContext);
            break;
        case EGL_eglDestroyContext:
//            EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
            *((EGLBoolean *)ret) = (gs_egl_profile.initialized)? EGL_TRUE :EGL_FALSE; *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglMakeCurrent:
//            EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,
//                          EGLSurface read, EGLContext ctx);
            *((EGLBoolean *)ret) = (gs_egl_profile.initialized)? EGL_TRUE :EGL_FALSE; *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglGetCurrentContext:
//            EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext(void);
            *((EGLContext *)ret) = gs_egl_profile.eglContext; *retsize = sizeof(EGLContext);
            break;
        case EGL_eglGetCurrentSurface:
//            EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface(EGLint readdraw);
            *((EGLSurface *)ret) = gs_egl_profile.eglSurface; *retsize = sizeof(EGLSurface);
            break;
        case EGL_eglGetCurrentDisplay:
//            EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay(void);
            *((EGLDisplay *)ret) = gs_egl_profile.eglDisplay; *retsize = sizeof(EGLDisplay);
            break;
        case EGL_eglQueryContext:
//            EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext(EGLDisplay dpy, EGLContext ctx,
//                           EGLint attribute, EGLint *value);
             *((EGLBoolean *)ret) = eglQueryContext(gs_egl_profile.eglDisplay, gs_egl_profile.eglContext,
                *((EGLint *)args[2]), (EGLint *)args[3]); *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglWaitGL:
            *((EGLBoolean *)ret) = eglWaitGL(); *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglWaitNative:
            *((EGLBoolean *)ret) = eglWaitNative(*((EGLint *)args[0])); *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglSwapBuffers:
//            EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
            *((EGLBoolean *)ret) = eglSwapBuffers(gs_egl_profile.eglDisplay, gs_egl_profile.eglSurface);
             *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglCopyBuffers:
            *((EGLBoolean *)ret) = eglCopyBuffers(gs_egl_profile.eglDisplay, gs_egl_profile.eglSurface,
                          *((EGLNativePixmapType*)args[2]));
             *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglSwapInterval:
            *((EGLBoolean *)ret) = eglSwapInterval(gs_egl_profile.eglDisplay, *((EGLint *)args[1]));
             *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglSurfaceAttrib:
             *((EGLBoolean *)ret) = eglSurfaceAttrib(gs_egl_profile.eglDisplay, gs_egl_profile.eglSurface,
                            *((EGLint*)args[2]), *((EGLint*)args[3]));
             *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglBindTexImage:
            *((EGLBoolean *)ret) = eglBindTexImage(gs_egl_profile.eglDisplay, gs_egl_profile.eglSurface,
                *((EGLint*)args[2]));
             *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglReleaseTexImage:
            *((EGLBoolean *)ret) = eglReleaseTexImage(gs_egl_profile.eglDisplay, gs_egl_profile.eglSurface,
                *((EGLint*)args[2]));
             *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglCreatePbufferFromClientBuffer:
//            EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferFromClientBuffer(
//              EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer,
//              EGLConfig config, const EGLint *attrib_list);
            *((EGLSurface *)ret) = gs_egl_profile.eglSurface; *retsize = sizeof(EGLSurface);
            break;
        case EGL_eglBindAPI:
            *((EGLBoolean *)ret) = eglBindAPI(*((EGLenum*)args[0]));
            *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglQueryAPI:
            *((EGLenum *)ret) = eglQueryAPI();
            *retsize = sizeof(EGLenum);
            break;
        case EGL_eglWaitClient:
            *((EGLBoolean *)ret) = eglWaitClient();
            *retsize = sizeof(EGLBoolean);
            break;
        case EGL_eglReleaseThread:
            *((EGLBoolean *)ret) = eglReleaseThread();
            *retsize = sizeof(EGLBoolean);
            break;
        /*************GLESv2 function cases ***************************/
        case GLESv2_glActiveTexture:
            glActiveTexture (G_EN(0));
            break;
        case GLESv2_glAttachShader:
            glAttachShader (G_UI(0), G_UI(1));
            break;
        case GLESv2_glBindAttribLocation:
            glBindAttribLocation (G_UI(0), G_UI(1), (const GLchar *)G_VPTR(2));
            break;
        case GLESv2_glBindBuffer:
            glBindBuffer (G_EN(0), G_UI(1));
            break;
        case GLESv2_glBindFramebuffer:
            glBindFramebuffer (G_EN(0), G_UI(1));
            break;
        case GLESv2_glBindRenderbuffer:
            glBindRenderbuffer (G_EN(0), G_UI(1));
            break;
        case GLESv2_glBindTexture:
            glBindTexture (G_EN(0), G_UI(1));
            break;
        case GLESv2_glBlendColor:
            glBlendColor (G_FL(0), G_FL(1), G_FL(2), G_FL(3));
            break;
        case GLESv2_glBlendEquation:
            glBlendEquation (G_EN(0));
            break;
        case GLESv2_glBlendEquationSeparate:
            glBlendEquationSeparate (G_EN(0), G_EN(1));
            break;
        case GLESv2_glBlendFunc:
            glBlendFunc (G_EN(0), G_EN(1));
            break;
        case GLESv2_glBlendFuncSeparate:
            glBlendFuncSeparate (G_EN(0), G_EN(1), G_EN(2), G_EN(3));
            break;
        case GLESv2_glBufferData:
            glBufferData (G_EN(0), G_SIP(1), (const void *)G_VPTR(2), G_EN(3));
            break;
        case GLESv2_glBufferSubData:
            glBufferSubData (G_EN(0), G_IPT(1), G_SIP(2), (const void *)G_VPTR(3));
            break;
        case GLESv2_glCheckFramebufferStatus:
            *((GLenum *)ret) = glCheckFramebufferStatus (G_EN(0)); *retsize = sizeof(GLenum);
            break;
        case GLESv2_glClear:
            glClear (G_BF(0));
            break;
        case GLESv2_glClearColor:
            glClearColor (G_FL(0), G_FL(1), G_FL(2), G_FL(3));
            break;
        case GLESv2_glClearDepthf:
            glClearDepthf (G_FL(0));
            break;
        case GLESv2_glClearStencil:
            glClearStencil (G_IN(0));
            break;
        case GLESv2_glColorMask:
            glColorMask (G_BL(0), G_BL(1), G_BL(2), G_BL(3));
            break;
        case GLESv2_glCompileShader:
            glCompileShader (G_UI(0));
            break;
        case GLESv2_glCompressedTexImage2D:
            glCompressedTexImage2D (G_EN(0), G_IN(1), G_EN(2), G_SII(3), G_SII(4), G_IN(5),
                    G_SII(6), (const void *)G_VPTR(7));
            break;
        case GLESv2_glCompressedTexSubImage2D:
            glCompressedTexSubImage2D (G_EN(0), G_IN(1), G_IN(2), G_IN(3), G_SII(4), G_SII(5),
                    G_EN(6), G_SII(7), (const void *)G_VPTR(8));
            break;
        case GLESv2_glCopyTexImage2D:
            glCopyTexImage2D (G_EN(0), G_IN(1), G_EN(2), G_IN(3), G_IN(4), G_SII(5), G_SII(6), G_IN(7));
            break;
        case GLESv2_glCopyTexSubImage2D:
            glCopyTexSubImage2D (G_EN(0), G_IN(1), G_IN(2), G_IN(3), G_IN(4), G_IN(5), G_SII(6), G_SII(7));
            break;
        case GLESv2_glCreateProgram:
            *((GLuint *)ret) = glCreateProgram (); *retsize = sizeof(GLuint);
            break;
        case GLESv2_glCreateShader:
            *((GLuint *)ret) = glCreateShader (G_EN(0)); *retsize = sizeof(GLuint);
            break;
        case GLESv2_glCullFace:
            glCullFace (G_EN(0));
            break;
        case GLESv2_glDeleteBuffers:
            glDeleteBuffers (G_SII(0), (const GLuint *)G_VPTR(1));
            break;
        case GLESv2_glDeleteFramebuffers:
            glDeleteFramebuffers (G_SII(0), (const GLuint *)G_VPTR(1));
            break;
        case GLESv2_glDeleteProgram:
            glDeleteProgram (G_UI(0));
            break;
        case GLESv2_glDeleteRenderbuffers:
            glDeleteRenderbuffers (G_SII(0), (const GLuint *)G_VPTR(1));
            break;
        case GLESv2_glDeleteShader:
            glDeleteShader (G_UI(0));
            break;
        case GLESv2_glDeleteTextures:
            glDeleteTextures (G_SII(0), (const GLuint *)G_VPTR(1));
            break;
        case GLESv2_glDepthFunc:
            glDepthFunc (G_EN(0));
            break;
        case GLESv2_glDepthMask:
            glDepthMask (G_BL(0));
            break;
        case GLESv2_glDepthRangef:
            glDepthRangef (G_FL(0), G_FL(1));
            break;
        case GLESv2_glDetachShader:
            glDetachShader (G_UI(0), G_UI(1));
            break;
        case GLESv2_glDisable:
            glDisable (G_EN(0));
            break;
        case GLESv2_glDisableVertexAttribArray:
            glDisableVertexAttribArray (G_UI(0));
            break;
        case GLESv2_glDrawArrays:
            glDrawArrays (G_EN(0), G_IN(1), G_SII(2));
            if (vertex_buffer) {free(vertex_buffer); vertex_buffer = NULL;}
            break;
        case GLESv2_glDrawElements:
            glDrawElements (G_EN(0), G_SII(1), G_EN(2), (const void *)G_VPTR(3));
            if (vertex_buffer) {free(vertex_buffer); vertex_buffer = NULL;}
            break;
        case GLESv2_glEnable:
            glEnable (G_EN(0));
            break;
        case GLESv2_glEnableVertexAttribArray:
            glEnableVertexAttribArray (G_UI(0));
            break;
        case GLESv2_glFinish:
            glFinish ();
            break;
        case GLESv2_glFlush:
            glFlush ();
            break;
        case GLESv2_glFramebufferRenderbuffer:
            glFramebufferRenderbuffer (G_EN(0), G_EN(1), G_EN(2), G_UI(3));
            break;
        case GLESv2_glFramebufferTexture2D:
            glFramebufferTexture2D (G_EN(0), G_EN(1), G_EN(2), G_UI(3), G_IN(4));
            break;
        case GLESv2_glFrontFace:
            glFrontFace (G_EN(0));
            break;
        case GLESv2_glGenBuffers:
            glGenBuffers (G_SII(0), (GLuint *)G_VPTR(1));
            break;
        case GLESv2_glGenerateMipmap:
            glGenerateMipmap (G_EN(0));
            break;
        case GLESv2_glGenFramebuffers:
            glGenFramebuffers (G_SII(0), (GLuint *)G_VPTR(1));
            break;
        case GLESv2_glGenRenderbuffers:
            glGenRenderbuffers (G_SII(0), (GLuint *)G_VPTR(1));
            break;
        case GLESv2_glGenTextures:
            glGenTextures (G_SII(0), (GLuint *)G_VPTR(1));
            break;
        case GLESv2_glGetActiveAttrib:
            glGetActiveAttrib (G_UI(0), G_UI(1), G_SII(2), (GLsizei *)G_VPTR(3),
                    (GLint *)G_VPTR(4), (GLenum *)G_VPTR(5), (GLchar *)G_VPTR(6));
            break;
        case GLESv2_glGetActiveUniform:
            glGetActiveUniform (G_UI(0), G_UI(1), G_SII(2), (GLsizei *)G_VPTR(3),
                    (GLint *)G_VPTR(4), (GLenum *)G_VPTR(5), (GLchar *)G_VPTR(6));
            break;
        case GLESv2_glGetAttachedShaders:
            glGetAttachedShaders (G_UI(0), G_SII(1), (GLsizei *)G_VPTR(2), (GLuint *)G_VPTR(3));
            break;
        case GLESv2_glGetAttribLocation:
            *((GLint *)ret) = glGetAttribLocation (G_UI(0), (const GLchar *)G_VPTR(1)); *retsize = sizeof(GLint);
            break;
        case GLESv2_glGetBooleanv:
            glGetBooleanv (G_EN(0), (GLboolean *)G_VPTR(1));
            break;
        case GLESv2_glGetBufferParameteriv:
            glGetBufferParameteriv (G_EN(0), G_EN(1), (GLint *)G_VPTR(2));
            break;
        case GLESv2_glGetError:
            *((GLenum *)ret) = glGetError (); *retsize = sizeof(GLenum);
            break;
        case GLESv2_glGetFloatv:
            glGetFloatv (G_EN(0), (GLfloat *)G_VPTR(1));
            break;
        case GLESv2_glGetFramebufferAttachmentParameteriv:
            glGetFramebufferAttachmentParameteriv (G_EN(0), G_EN(1), G_EN(2), (GLint *)G_VPTR(3));
            break;
        case GLESv2_glGetIntegerv:
            glGetIntegerv (G_EN(0), (GLint *)G_VPTR(1));
            break;
        case GLESv2_glGetProgramiv:
            glGetProgramiv (G_UI(0), G_EN(1), (GLint *)G_VPTR(2));
            break;
        case GLESv2_glGetProgramInfoLog:
            glGetProgramInfoLog (G_UI(0), G_SII(1), (GLsizei *)G_VPTR(2), (GLchar *)G_VPTR(3));
            break;
        case GLESv2_glGetRenderbufferParameteriv:
            glGetRenderbufferParameteriv (G_EN(0), G_EN(1), (GLint *)G_VPTR(2));
            break;
        case GLESv2_glGetShaderiv:
            glGetShaderiv (G_UI(0), G_EN(1), (GLint *)G_VPTR(2));
            break;
        case GLESv2_glGetShaderInfoLog:
            glGetShaderInfoLog (G_UI(0), G_SII(1), (GLsizei *)G_VPTR(2), (GLchar *)G_VPTR(3));
            break;
        case GLESv2_glGetShaderPrecisionFormat:
            glGetShaderPrecisionFormat (G_EN(0), G_EN(1), (GLint *)G_VPTR(2), (GLint *)G_VPTR(3));
            break;
        case GLESv2_glGetShaderSource:
            glGetShaderSource (G_UI(0), G_SII(1), (GLsizei *)G_VPTR(2), (GLchar *)G_VPTR(3));
            break;
        case GLESv2_glGetString:
            strncpy((char *)G_VPTR(2), (char *)glGetString (G_EN(0)), G_SII(1));
            break;
        case GLESv2_glGetTexParameterfv:
            glGetTexParameterfv (G_EN(0), G_EN(1), (GLfloat *)G_VPTR(2));
            break;
        case GLESv2_glGetTexParameteriv:
            glGetTexParameteriv (G_EN(0), G_EN(1), (GLint *)G_VPTR(2));
            break;
        case GLESv2_glGetUniformfv:
            glGetUniformfv (G_UI(0), G_IN(1), (GLfloat *)G_VPTR(2));
            break;
        case GLESv2_glGetUniformiv:
            glGetUniformiv (G_UI(0), G_IN(1), (GLint *)G_VPTR(2));
            break;
        case GLESv2_glGetUniformLocation:
            *((GLint *)ret) = glGetUniformLocation (G_UI(0), (const GLchar *)G_VPTR(1)); *retsize = sizeof(GLint);
            break;
        case GLESv2_glGetVertexAttribfv:
            glGetVertexAttribfv (G_UI(0), G_EN(1), (GLfloat *)G_VPTR(2));
            break;
        case GLESv2_glGetVertexAttribiv:
            glGetVertexAttribiv (G_UI(0), G_EN(1), (GLint *)G_VPTR(2));
            break;
        case GLESv2_glGetVertexAttribPointerv:
            glGetVertexAttribPointerv (G_UI(0), G_EN(1), (void **)G_VPTR(2));
            break;
        case GLESv2_glHint:
            glHint (G_EN(0), G_EN(1));
            break;
        case GLESv2_glIsBuffer:
            *((GLboolean *)ret) = glIsBuffer (G_UI(0)); *retsize = sizeof(GLboolean);
            break;
        case GLESv2_glIsEnabled:
            *((GLboolean *)ret) = glIsEnabled (G_EN(0)); *retsize = sizeof(GLboolean);
            break;
        case GLESv2_glIsFramebuffer:
            *((GLboolean *)ret) = glIsFramebuffer (G_UI(0)); *retsize = sizeof(GLboolean);
            break;
        case GLESv2_glIsProgram:
            *((GLboolean *)ret) = glIsProgram (G_UI(0)); *retsize = sizeof(GLboolean);
            break;
        case GLESv2_glIsRenderbuffer:
            *((GLboolean *)ret) = glIsRenderbuffer (G_UI(0)); *retsize = sizeof(GLboolean);
            break;
        case GLESv2_glIsShader:
            *((GLboolean *)ret) = glIsShader (G_UI(0)); *retsize = sizeof(GLboolean);
            break;
        case GLESv2_glIsTexture:
            *((GLboolean *)ret) = glIsTexture (G_UI(0)); *retsize = sizeof(GLboolean);
            break;
        case GLESv2_glLineWidth:
            glLineWidth (G_FL(0));
            break;
        case GLESv2_glLinkProgram:
            glLinkProgram (G_UI(0));
            break;
        case GLESv2_glPixelStorei:
            glPixelStorei (G_EN(0), G_IN(1));
            break;
        case GLESv2_glPolygonOffset:
            glPolygonOffset (G_FL(0), G_FL(1));
            break;
        case GLESv2_glReadPixels:
            glReadPixels (G_IN(0), G_IN(1), G_SII(2), G_SII(3), G_EN(4), G_EN(5), (void *)G_VPTR(6));
            break;
        case GLESv2_glReleaseShaderCompiler:
            glReleaseShaderCompiler ();
            break;
        case GLESv2_glRenderbufferStorage:
            glRenderbufferStorage (G_EN(0), G_EN(1), G_SII(2), G_SII(3));
            break;
        case GLESv2_glSampleCoverage:
            glSampleCoverage (G_FL(0), G_BL(1));
            break;
        case GLESv2_glScissor:
            glScissor (G_IN(0), G_IN(1), G_SII(2), G_SII(3));
            break;
        case GLESv2_glShaderBinary:
            glShaderBinary (G_SII(0), (const GLuint *)G_VPTR(1), G_EN(2), (const void *)G_VPTR(3), G_SII(4));
            break;
        case GLESv2_glShaderSource:
            glShaderSource (G_UI(0), G_SII(1), (const GLchar *const*)G_VPTR(2), (const GLint *)G_VPTR(3));
            break;
        case GLESv2_glStencilFunc:
            glStencilFunc (G_EN(0), G_IN(1), G_UI(2));
            break;
        case GLESv2_glStencilFuncSeparate:
            glStencilFuncSeparate (G_EN(0), G_EN(1), G_IN(2), G_UI(3));
            break;
        case GLESv2_glStencilMask:
            glStencilMask (G_UI(0));
            break;
        case GLESv2_glStencilMaskSeparate:
            glStencilMaskSeparate (G_EN(0), G_UI(1));
            break;
        case GLESv2_glStencilOp:
            glStencilOp (G_EN(0), G_EN(1), G_EN(2));
            break;
        case GLESv2_glStencilOpSeparate:
            glStencilOpSeparate (G_EN(0), G_EN(1), G_EN(2), G_EN(3));
            break;
        case GLESv2_glTexImage2D:
            glTexImage2D (G_EN(0), G_IN(1), G_IN(2), G_SII(3), G_SII(4), G_IN(5),
                    G_EN(6), G_EN(7), (const void *)G_VPTR(8));
            break;
        case GLESv2_glTexParameterf:
            glTexParameterf (G_EN(0), G_EN(1), G_FL(2));
            break;
        case GLESv2_glTexParameterfv:
            glTexParameterfv (G_EN(0), G_EN(1), (const GLfloat *)G_VPTR(2));
            break;
        case GLESv2_glTexParameteri:
            glTexParameteri (G_EN(0), G_EN(1), G_IN(2));
            break;
        case GLESv2_glTexParameteriv:
            glTexParameteriv (G_EN(0), G_EN(1), (const GLint *)G_VPTR(2));
            break;
        case GLESv2_glTexSubImage2D:
            glTexSubImage2D (G_EN(0), G_IN(1), G_IN(2), G_IN(3), G_SII(4), G_SII(5),
                    G_EN(6), G_EN(7), (const void *)G_VPTR(8));
            break;
        case GLESv2_glUniform1f:
            glUniform1f (G_IN(0), G_FL(1));
            break;
        case GLESv2_glUniform1fv:
            glUniform1fv (G_IN(0), G_SII(1), (const GLfloat *)G_VPTR(2));
            break;
        case GLESv2_glUniform1i:
            glUniform1i (G_IN(0), G_IN(1));
            break;
        case GLESv2_glUniform1iv:
            glUniform1iv (G_IN(0), G_SII(1), (const GLint *)G_VPTR(2));
            break;
        case GLESv2_glUniform2f:
            glUniform2f (G_IN(0), G_FL(1), G_FL(2));
            break;
        case GLESv2_glUniform2fv:
            glUniform2fv (G_IN(0), G_SII(1), (const GLfloat *)G_VPTR(2));
            break;
        case GLESv2_glUniform2i:
            glUniform2i (G_IN(0), G_IN(1), G_IN(2));
            break;
        case GLESv2_glUniform2iv:
            glUniform2iv (G_IN(0), G_SII(1), (const GLint *)G_VPTR(2));
            break;
        case GLESv2_glUniform3f:
            glUniform3f (G_IN(0), G_FL(1), G_FL(2), G_FL(3));
            break;
        case GLESv2_glUniform3fv:
            glUniform3fv (G_IN(0), G_SII(1), (const GLfloat *)G_VPTR(2));
            break;
        case GLESv2_glUniform3i:
            glUniform3i (G_IN(0), G_IN(1), G_IN(2), G_IN(3));
            break;
        case GLESv2_glUniform3iv:
            glUniform3iv (G_IN(0), G_SII(1), (const GLint *)G_VPTR(2));
            break;
        case GLESv2_glUniform4f:
            glUniform4f (G_IN(0), G_SII(1), G_FL(2), G_FL(3), G_FL(4));
            break;
        case GLESv2_glUniform4fv:
            glUniform4fv (G_IN(0), G_SII(1), (const GLfloat *)G_VPTR(2));
            break;
        case GLESv2_glUniform4i:
            glUniform4i (G_IN(0), G_IN(1), G_IN(2), G_IN(3), G_IN(4));
            break;
        case GLESv2_glUniform4iv:
            glUniform4iv (G_IN(0), G_SII(1), (const GLint *)G_VPTR(2));
            break;
        case GLESv2_glUniformMatrix2fv:
            glUniformMatrix2fv (G_IN(0), G_SII(1), G_BL(2), (const GLfloat *)G_VPTR(3));
            break;
        case GLESv2_glUniformMatrix3fv:
            glUniformMatrix3fv (G_IN(0), G_SII(1), G_BL(2), (const GLfloat *)G_VPTR(3));
            break;
        case GLESv2_glUniformMatrix4fv:
            glUniformMatrix4fv (G_IN(0), G_SII(1), G_BL(2), (const GLfloat *)G_VPTR(3));
            break;
        case GLESv2_glUseProgram:
            glUseProgram (G_UI(0));
            break;
        case GLESv2_glValidateProgram:
            glValidateProgram (G_UI(0));
            break;
        case GLESv2_glVertexAttrib1f:
            glVertexAttrib1f (G_UI(0), G_FL(1));
            break;
        case GLESv2_glVertexAttrib1fv:
            glVertexAttrib1fv (G_UI(0), (const GLfloat *)G_VPTR(1));
            break;
        case GLESv2_glVertexAttrib2f:
            glVertexAttrib2f (G_UI(0), G_FL(1), G_FL(2));
            break;
        case GLESv2_glVertexAttrib2fv:
            glVertexAttrib2fv (G_UI(0), (const GLfloat *)G_VPTR(1));
            break;
        case GLESv2_glVertexAttrib3f:
            glVertexAttrib3f (G_UI(0), G_FL(1), G_FL(2), G_FL(3));
            break;
        case GLESv2_glVertexAttrib3fv:
            glVertexAttrib3fv (G_UI(0), (const GLfloat *)G_VPTR(1));
            break;
        case GLESv2_glVertexAttrib4f:
            glVertexAttrib4f (G_UI(0), G_FL(1), G_FL(2), G_FL(3), G_FL(4));
            break;
        case GLESv2_glVertexAttrib4fv:
            glVertexAttrib4fv (G_UI(0), (const GLfloat *)G_VPTR(1));
            break;
        case GLESv2_glVertexAttribPointer:
            {
                void *tptr = G_VPTR(5);
                if ((long)tptr > 256) {
                    if (vertex_buffer == NULL) vertex_buffer = malloc(4<<10);
                    if (vertex_buffer) memcpy(vertex_buffer, tptr, 4<<10);
                    tptr = vertex_buffer;
                }
                glVertexAttribPointer (G_UI(0), G_IN(1), G_EN(2), G_BL(3), G_SII(4), (const void *)tptr);
            }
            break;
        case GLESv2_glViewport:
            glViewport (G_IN(0), G_IN(1), G_SII(2), G_SII(3));
            break;
    }
}



int main (int argc, char **argv)
{
#ifdef DEFAULT_FCALL_SERVER
    RUN_DEFAULT_FCALL_SERVER(fcall_handler);
#endif
    return 0;
}
