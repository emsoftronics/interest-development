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

EGLAPI const char * EGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name)
{
    static char buffer[64];
    int len = sizeof(buffer);
    buffer[0] = '\0';
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglQueryString, 4, sizeof(dpy) + sizeof(name) + sizeof(buffer) + sizeof(len) +  8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(name, 0);
    DCC_ADD_ARG(buffer, 1);
    DCC_ADD_ARG(len, 0);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(buffer, sizeof(buffer), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(buffer, sizeof(buffer), 2);
    DCC_END_CALL();
#endif
    return buffer;
}

EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs(EGLDisplay dpy, EGLConfig *configs,
                         EGLint config_size, EGLint *num_config)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglGetConfigs, 4, sizeof(dpy) + sizeof(configs) + sizeof(config_size)
    + sizeof(num_config) + sizeof(*num_config) + sizeof(*configs)*config_size +  8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(configs, 1);
    DCC_ADD_ARG(config_size, 0);
    DCC_ADD_ARG(num_config, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(configs, sizeof(*configs)*config_size, 1);
    DCC_ADD_APTR_MEM(num_config, sizeof(*num_config), 3);
    DCC_RET_VAL(ret);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(configs, sizeof(*configs)*config_size, 1);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(num_config, sizeof(*num_config), 3);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list,
                           EGLConfig *configs, EGLint config_size,
                           EGLint *num_config)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglChooseConfig, 5, sizeof(dpy) + sizeof(attrib_list)
    + sizeof(configs) + sizeof(config_size)
    + sizeof(num_config) + sizeof(*num_config) + sizeof(*configs)*config_size +  256);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(attrib_list, 1);
    DCC_ADD_ARG(configs, 1);
    DCC_ADD_ARG(config_size, 0);
    DCC_ADD_ARG(num_config, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(attrib_list, 240, 1);
    DCC_ADD_APTR_MEM(configs, sizeof(*configs)*config_size, 2);
    DCC_ADD_APTR_MEM(num_config, sizeof(*num_config), 4);
    DCC_RET_VAL(ret);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(configs, sizeof(*configs)*config_size, 2);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(num_config, sizeof(*num_config), 4);
    DCC_END_CALL();
#endif
    return ret;
}


EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config,
                              EGLint attribute, EGLint *value)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglGetConfigAttrib, 4, sizeof(dpy) + sizeof(config) + sizeof(attribute)
    + sizeof(value) + sizeof(*value) +  8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(config, 0);
    DCC_ADD_ARG(attribute, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, sizeof(*value), 3);
    DCC_RET_VAL(ret);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(value, sizeof(*value), 3);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
                                  EGLNativeWindowType win,
                                  const EGLint *attrib_list)
{
    EGLSurface surf = EGL_NO_SURFACE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglCreateWindowSurface, 4, sizeof(dpy) + sizeof(config)
    + sizeof(win) + sizeof(attrib_list) + 256);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(config, 0);
    DCC_ADD_ARG(win, 0);
    DCC_ADD_ARG(attrib_list, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(attrib_list, 240, 3);
    DCC_RET_VAL(surf);
    DCC_END_CALL();
#endif
    return surf;
}

EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config,
                                   const EGLint *attrib_list)
{
    EGLSurface surf = EGL_NO_SURFACE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglCreatePbufferSurface, 3, sizeof(dpy) + sizeof(config)
    + sizeof(attrib_list) + 256);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(config, 0);
    DCC_ADD_ARG(attrib_list, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(attrib_list, 240, 2);
    DCC_RET_VAL(surf);
    DCC_END_CALL();
#endif
    return surf;
}

EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config,
                                  EGLNativePixmapType pixmap,
                                  const EGLint *attrib_list)
{
    EGLSurface surf = EGL_NO_SURFACE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglCreatePixmapSurface, 4, sizeof(dpy) + sizeof(config)
    + sizeof(attrib_list) + 256);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(config, 0);
    DCC_ADD_ARG(pixmap, 0);
    DCC_ADD_ARG(attrib_list, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(attrib_list, 240, 3);
    DCC_RET_VAL(surf);
    DCC_END_CALL();
#endif
    return surf;
}

EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglDestroySurface, 2, sizeof(dpy) + sizeof(surface) +  8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(surface, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface(EGLDisplay dpy, EGLSurface surface,
                           EGLint attribute, EGLint *value)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglQuerySurface, 4, sizeof(dpy) + sizeof(surface) + sizeof(attribute)
    + sizeof(value) + sizeof(*value) +  8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(surface, 0);
    DCC_ADD_ARG(attribute, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, sizeof(*value), 3);
    DCC_RET_VAL(ret);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(value, sizeof(*value), 3);
    DCC_END_CALL();
#endif
    return ret;
}

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
              EGLConfig config, const EGLint *attrib_list)
{
    EGLSurface surf = EGL_NO_SURFACE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglCreatePbufferFromClientBuffer, 5, sizeof(dpy) + sizeof(buftype)
    + sizeof(buffer)  + sizeof(config)  + sizeof(attrib_list) + 256);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(buftype, 0);
    DCC_ADD_ARG(buffer, 0);
    DCC_ADD_ARG(config, 0);
    DCC_ADD_ARG(attrib_list, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(attrib_list, 240, 4);
    DCC_RET_VAL(surf);
    DCC_END_CALL();
#endif
    return surf;
}

EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface,
                            EGLint attribute, EGLint value)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglSurfaceAttrib, 4, sizeof(dpy) + sizeof(surface)
        + sizeof(attribute) + sizeof(value) + 8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(surface, 0);
    DCC_ADD_ARG(attribute, 0);
    DCC_ADD_ARG(value, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglBindTexImage, 3, sizeof(dpy) + sizeof(surface)
        + sizeof(buffer) + 8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(surface, 0);
    DCC_ADD_ARG(buffer, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglReleaseTexImage, 3, sizeof(dpy) + sizeof(surface)
        + sizeof(buffer) + 8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(surface, 0);
    DCC_ADD_ARG(buffer, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}


EGLAPI EGLBoolean EGLAPIENTRY eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglSwapInterval, 2, sizeof(dpy) + sizeof(interval) + 8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(interval, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config,
                            EGLContext share_context,
                            const EGLint *attrib_list)
{
    EGLContext ctx = EGL_NO_CONTEXT;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglCreateContext, 4, sizeof(dpy)
    + sizeof(config)  + sizeof(share_context)  + sizeof(attrib_list) + 256);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(config, 0);
    DCC_ADD_ARG(share_context, 0);
    DCC_ADD_ARG(attrib_list, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(attrib_list, 240, 3);
    DCC_RET_VAL(ctx);
    DCC_END_CALL();
#endif
    return ctx;
}

EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglDestroyContext, 2, sizeof(dpy) + sizeof(ctx) + 8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(ctx, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,
                          EGLSurface read, EGLContext ctx)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglMakeCurrent, 4, sizeof(dpy) + 2*sizeof(draw) + sizeof(ctx) + 8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(draw, 0);
    DCC_ADD_ARG(read, 0);
    DCC_ADD_ARG(ctx, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

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
                           EGLint attribute, EGLint *value)
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglQueryContext, 4, sizeof(dpy) + sizeof(ctx) + sizeof(attribute)
    + sizeof(value) + sizeof(*value) +  8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(ctx, 0);
    DCC_ADD_ARG(attribute, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, sizeof(*value), 3);
    DCC_RET_VAL(ret);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(value, sizeof(*value), 3);
    DCC_END_CALL();
#endif
    return ret;

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

EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglSwapBuffers, 2, sizeof(dpy) + sizeof(surface) +  8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(surface, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers(EGLDisplay dpy, EGLSurface surface,
                          EGLNativePixmapType target)
{
    EGLBoolean ret = EGL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(EGL_eglCopyBuffers, 3, sizeof(dpy) + sizeof(surface) + sizeof(target) +  8);
    DCC_ADD_ARG(dpy, 0);
    DCC_ADD_ARG(surface, 0);
    DCC_ADD_ARG(target, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

/* Now, define eglGetProcAddress using the generic function ptr. type */
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY
       eglGetProcAddress(const char *procname)
{
}


