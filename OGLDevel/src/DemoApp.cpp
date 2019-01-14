/*
 * =====================================================================================
 *
 *       Filename:  DemoApp.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 14 January 2019 01:47:25  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "eglinterface/canvas.h"
#include "common/esUtil.h"
#include "shader/shader.h"

class Demo : public Canvas
{
    private:
        static const char *vshader;
        static const char *fshader;
        Shader *mShader;

    public:
        Demo (const char *title, int width, int height) : Canvas(title, width, height)
        {
           mShader = new Shader(vshader, fshader, true);
           glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
        }
        void draw(void);
};

const char *Demo::vshader =
      "attribute vec4 vPosition;    \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = vPosition;  \n"
      "}                            \n";

const char *Demo::fshader =
      "precision mediump float;\n"
      "void main()                                  \n"
      "{                                            \n"
      "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
      "}                                            \n";

void Demo::draw()
{
   int ret = 0;
   GLfloat *vVertices = NULL;
   GLuint *vIndices = NULL;
   //ret = esGenSphere(100,0.5f, &vVertices, 0,0,&vIndices);
   ret = esGenCube(1.0f, &vVertices, 0,0,&vIndices);
   // Set the viewport
   glViewport ( 0, 0, this->width, this->height );

   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( mShader->ID);

   // Load the vertex data
   glVertexAttribPointer ( (*mShader)("vPosition"), 3, GL_FLOAT, GL_FALSE, 0, vVertices );
   glEnableVertexAttribArray ( (*mShader)("vPosition") );

   //glDrawArrays ( GL_TRIANGLES, 0, 121 );
   glDrawElements( GL_TRIANGLE_STRIP, ret, GL_UNSIGNED_SHORT, vIndices);
//   glFinish();
   free(vVertices);
   free(vIndices);
}

int main ( int argc, char *argv[] )
{

   Demo  demo("Hello Triangle", 600, 600);

   demo.refreshForever();
   return 0;
}
