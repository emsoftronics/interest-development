/*
 * =====================================================================================
 *
 *       Filename:  canvas.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 14 January 2019 12:22:14  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <sys/time.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "canvas.h"

#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>



Canvas::Canvas(const char* title, GLint width, GLint height, Canvas::BufferType flags)
{
    EGLint attribList[] =
    {
       EGL_RED_SIZE,       5,
       EGL_GREEN_SIZE,     6,
       EGL_BLUE_SIZE,      5,
       EGL_ALPHA_SIZE,     (flags & Canvas::BufferType::WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
       EGL_DEPTH_SIZE,     (flags & Canvas::BufferType::WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
       EGL_STENCIL_SIZE,   (flags & Canvas::BufferType::WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
       EGL_SAMPLE_BUFFERS, (flags & Canvas::BufferType::WINDOW_MULTISAMPLE) ? 1 : 0,
       EGL_NONE
    };

    canvasCreated = false;
    this->width = width;
    this->height = height;

    if ( !createWindow (title) )
    {
      printf("%s: Creation of X11 window is failed!!\n", title);
      return;
    }


   if ( !createEGLContext ( this->hWnd,
                            &this->eglDisplay,
                            &this->eglContext,
                            &this->eglSurface,
                            attribList) )
   {
      printf("%s: Creation of EGL context for X11 window is failed!!\n", title);
      return;
   }
   canvasCreated = true;
}

void Canvas::handleKeyPress(unsigned char key)
{
    printf("Pressed key : %c\n", key);
}

void Canvas::update (float totaltime )
{
   if (totaltime > 5.0) printf("update something\n");
}

void Canvas::refreshOnce(void)
{
    update(0);
    draw();
    eglSwapBuffers(eglDisplay, eglSurface);
}

void Canvas::refreshForever(void)
{
    struct timeval t1, t2;
    struct timezone tz;
    float deltatime;
    float totaltime = 0.0f;
    unsigned int frames = 0;

    gettimeofday ( &t1 , &tz );

    while(userInterrupt() == GL_FALSE)
    {
        gettimeofday(&t2, &tz);
        deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
        t1 = t2;

        update(totaltime);
        draw();
        eglSwapBuffers(eglDisplay, eglSurface);

        totaltime += deltatime;
        frames++;
        if (totaltime >  2.0f)
        {
            printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n", frames, totaltime, frames/totaltime);
            totaltime -= 2.0f;
            frames = 0;
        }
    }
}

EGLBoolean Canvas::createWindow(const char *title)
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

    x_display = XOpenDisplay(NULL);
    if ( x_display == NULL )
    {
        return EGL_FALSE;
    }

    root = DefaultRootWindow((Display *)x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
    win = XCreateWindow(
               (Display *)x_display, root,
               0, 0, this->width, this->height, 0,
               CopyFromParent, InputOutput,
               CopyFromParent, CWEventMask,
               &swa );

    xattr.override_redirect = false;
    XChangeWindowAttributes ( (Display *)x_display, win, CWOverrideRedirect, &xattr );

    hints.input = true;
    hints.flags = InputHint;
    XSetWMHints((Display *)x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow ((Display *)x_display, win);
    XStoreName ((Display *)x_display, win, title);

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom ((Display *)x_display, "_NET_WM_STATE", false);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = false;
    XSendEvent (
       (Display *)x_display,
       DefaultRootWindow ( (Display *)x_display ),
       false,
       SubstructureNotifyMask,
       &xev );

    this->hWnd = (EGLNativeWindowType) win;
    return EGL_TRUE;
}

EGLBoolean Canvas::createEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
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
   display = eglGetDisplay((EGLNativeDisplayType)x_display);
   if ( display == EGL_NO_DISPLAY )
   {
      return EGL_FALSE;
   }

   // Initialize EGL
   if ( !eglInitialize(display, &majorVersion, &minorVersion) )
   {
      return EGL_FALSE;
   }

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
   surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
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

GLboolean Canvas::userInterrupt(void)
{
    XEvent xev;
    KeySym key;
    GLboolean userinterrupt = GL_FALSE;
    char text;

    // Pump all messages from X server. Keypresses are directed to keyfunc (if defined)
    while ( XPending ( (Display *)x_display ) )
    {
        XNextEvent( (Display *)x_display, &xev );
        if ( xev.type == KeyPress )
        {
            if (XLookupString(&xev.xkey,&text,1,&key,0)==1)
            {
                    handleKeyPress(text);
            }
        }
        if ( xev.type == DestroyNotify )
            userinterrupt = GL_TRUE;
    }
    return userinterrupt;
}

