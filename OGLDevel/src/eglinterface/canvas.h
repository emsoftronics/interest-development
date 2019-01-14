/*
 * =====================================================================================
 *
 *       Filename:  canvas.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Sunday 13 January 2019 11:36:06  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__
#include <GLES2/gl2.h>
#include <EGL/egl.h>

class Canvas
{
    protected:
//        void*       userData;
        GLint       width;
        GLint       height;
        EGLNativeWindowType  hWnd;
        EGLDisplay  eglDisplay;
        EGLContext  eglContext;
        EGLSurface  eglSurface;
        bool canvasCreated;
        void *x_display;

    public:
        enum BufferType {
            WINDOW_RGB          = 0,
            WINDOW_ALPHA        = 1,
            WINDOW_DEPTH        = 2,
            WINDOW_STENCIL      = 3,
            WINDOW_MULTISAMPLE  = 4
        };

        Canvas(const char* title, GLint width, GLint height, BufferType flags = WINDOW_RGB);
        void refreshOnce(void);
        void refreshForever(void);
        virtual void handleKeyPress(unsigned char key);
        virtual void update (float deltaTime );
        virtual void draw (void) = 0;

    protected:
        EGLBoolean createWindow(const char *title);
        EGLBoolean createEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
                              EGLContext* eglContext, EGLSurface* eglSurface,
                              EGLint attribList[]);
        GLboolean userInterrupt(void);
};

#endif /*__CANVAS_H__ */
