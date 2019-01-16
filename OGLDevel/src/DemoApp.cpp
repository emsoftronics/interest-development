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
#include "texture/texture2d.h"


class Demo : public Canvas
{
    private:
        Shader *mShader;
        Texture2D *mTexture;

    public:
        Demo (const char *title, int width, int height) : Canvas(title, width, height)
        {
           mShader = NULL;
           mTexture = NULL;
        }
        void draw(void);
        void loadShader(const char *vshader, const char *fshader, bool codebuffer = false)
        {
            mShader = new Shader(vshader, fshader, codebuffer);
            //glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
        }
        void loadTexture(const char *imagePath, GLboolean fliped = GL_FALSE)
        { mTexture = new Texture2D(imagePath, fliped);}
};
/*
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
*/
void Demo::draw()
{
   int ret = 0;
   GLfloat vVertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

   GLuint vIndices[] = {
        3,2,1,//1, 2, 3  // second triangle
        3,0,1, //
        //0, 1, 3, // first triangle
        //1, 2, 3  // second triangle
    };
   //ret = esGenSphere(100,0.5f, &vVertices, 0,0,&vIndices);
   //ret = esGenCube(1.0f, &vVertices, 0,0,&vIndices);
   // Set the viewport
   glViewport ( 0, 0, this->width, this->height );

   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   mTexture->bind((*mShader)("texture1"));
   // Use the program object
   glUseProgram ( mShader->ID);

   // Load the vertex data
   glVertexAttribPointer ( (*mShader)("aPos"), 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), vVertices);
   glEnableVertexAttribArray ( (*mShader)("aPos"));
   glVertexAttribPointer ( (*mShader)("aColor"), 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), vVertices + 3);
   glEnableVertexAttribArray ( (*mShader)("aColor"));
   glVertexAttribPointer ( (*mShader)("aTexCoord"), 2, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), vVertices + 6);
   glEnableVertexAttribArray ( (*mShader)("aTexCoord"));
   //printf("aPos = %d\n", (*mShader)("aPos"));
   //printf("aColor = %d\n", (*mShader)("aColor"));
//   printf("aTexCoord = %d\n", (*mShader)("aTexCoord"));

   //glDrawArrays ( GL_TRIANGLES, 0, 121 );
   glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, vIndices);
//   glFinish();
}

int main ( int argc, char *argv[] )
{

   Demo  demo("Hello Triangle", 600, 600);
   demo.loadShader("res/shaders/textureTest.vs", "res/shaders/textureTest.fs");
 //  demo.loadTexture("res/textures/container.jpg");
   demo.loadTexture("res/textures/awesomeface.png", GL_TRUE);
 // demo.loadTexture("res/textures/matrix.jpg", GL_TRUE);
 //  demo.loadTexture("res/textures/container2.png");

   demo.refreshForever();
   return 0;
}

