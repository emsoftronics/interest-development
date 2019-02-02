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
    EGLDisplay disp = EGL_NO_DISPLAY;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglGetDisplay, 1, sizeof(display_id) + 8);
    DCC_ADD_ARG(display_id, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(disp);
    DCC_END_CALL();
#endif
    return disp;
}

EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglInitialize, 3, sizeof(dpy) + sizeof(major) + sizeof(minor) + 2*sizeof(*major) +8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(major, 1);
    DCC_ADD_ARG(minor, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(major, sizeof(*major), 1);
    DCC_ADD_APTR_MEM(minor, sizeof(*minor), 2);
    DCC_RET_VAL(ret);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(major, sizeof(*major), 1);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(minor, sizeof(*minor), 2);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglTerminate, 1, sizeof(dpy) + 8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

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

EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI(EGLenum api)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglBindAPI, 1, sizeof(api) + 8);
    DCC_ADD_ARG(api, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLenum EGLAPIENTRY eglQueryAPI(void)
{
    EGLenum ret = -1;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglQueryAPI, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglWaitClient(void)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglWaitClient, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread(void)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglReleaseThread, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

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

EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext(void)
{
    EGLContext ret = EGL_NO_CONTEXT;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglGetCurrentContext, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface(EGLint readdraw)
{
    EGLSurface surf = EGL_NO_SURFACE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglGetCurrentSurface, 1, sizeof(readdraw) + 8);
    DCC_ADD_ARG(readdraw, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(surf);
    DCC_END_CALL();
#endif
    return surf;
}

EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay(void)
{
    EGLDisplay ret = EGL_NO_DISPLAY;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglGetCurrentDisplay, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext(EGLDisplay dpy, EGLContext ctx,
                           EGLint attribute, EGLint *value);

EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL(void)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglWaitGL, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative(EGLint engine)
{
    EGLBoolean ret = EGL_NO_SURFACE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglWaitNative, 1, sizeof(engine) + 8);
    DCC_ADD_ARG(engine, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers(EGLDisplay dpy, EGLSurface surface,
                          EGLNativePixmapType target);

/* Now, define eglGetProcAddress using the generic function ptr. type */
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY
       eglGetProcAddress(const char *procname);


