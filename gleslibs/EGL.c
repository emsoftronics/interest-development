#include <EGL/egl.h>
#include "vmcutil.h"
#include "glesenum.h"

EGLAPI EGLint EGLAPIENTRY eglGetError(void)
{
    EGLint ret = -1;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglGetError, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id)
{
}

EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy);

EGLAPI const char * EGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name);

EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs(EGLDisplay dpy, EGLConfig *configs,
                         EGLint config_size, EGLint *num_config);
EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list,
                           EGLConfig *configs, EGLint config_size,
                           EGLint *num_config);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config,
                              EGLint attribute, EGLint *value);

EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
                                  EGLNativeWindowType win,
                                  const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config,
                                   const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config,
                                  EGLNativePixmapType pixmap,
                                  const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface(EGLDisplay dpy, EGLSurface surface,
                           EGLint attribute, EGLint *value);

EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI(EGLenum api);
EGLAPI EGLenum EGLAPIENTRY eglQueryAPI(void);

EGLAPI EGLBoolean EGLAPIENTRY eglWaitClient(void);

EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread(void);

EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferFromClientBuffer(
              EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer,
              EGLConfig config, const EGLint *attrib_list);

EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface,
                            EGLint attribute, EGLint value);
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);


EGLAPI EGLBoolean EGLAPIENTRY eglSwapInterval(EGLDisplay dpy, EGLint interval);

EGLAPI EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config,
                            EGLContext share_context,
                            const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,
                          EGLSurface read, EGLContext ctx);

EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext(void);
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface(EGLint readdraw);
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay(void);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext(EGLDisplay dpy, EGLContext ctx,
                           EGLint attribute, EGLint *value);

EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL(void);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative(EGLint engine);
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers(EGLDisplay dpy, EGLSurface surface,
                          EGLNativePixmapType target);

/* Now, define eglGetProcAddress using the generic function ptr. type */
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY
       eglGetProcAddress(const char *procname);


