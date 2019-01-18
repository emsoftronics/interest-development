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
#include "vertex/vertex.h"
#include <unistd.h>

class Demo : public Canvas
{
    private:
        Shader *mShader;
        Texture2D *mTexture;
        Vertex *mVertex;

    public:
        Demo (const char *title, int width, int height) : Canvas(title, width, height)
        {
           mShader = NULL;
           mTexture = NULL;
           mVertex = NULL;
        }
        void draw(void);
        void update (float deltaTime );
        void loadShader(const char *vshader, const char *fshader, bool codebuffer = false)
        {
            mShader = new Shader(vshader, fshader, codebuffer);
            //glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
        }
        void loadTexture(const char *imagePath, GLboolean fliped = GL_FALSE)
        { mTexture = new Texture2D(imagePath, fliped);}

        void loadVertex(void)
        {
            /*
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
            */
            GLfloat *vVertices = NULL;
            GLfloat *texCoord = NULL;
            GLfloat *color = NULL;
            GLuint *vIndices = NULL;
            GLuint nv = esGenCube(1.0f, &vVertices, &color, &texCoord, &vIndices);
            mVertex = new Vertex( nv, vVertices, vIndices, nv, texCoord, color);
            free(vVertices);
            free(texCoord);
            free(color);
            free(vIndices);
        }
};

void Demo::update (float deltaTime )
{
   static GLfloat var = 0;
   static GLboolean flag = GL_FALSE;
   GLfloat v[] = {0.3f, -0.7f, 0.0f};
   v[0] += var;
   v[1] -= var;
   if (var < -0.5) flag = GL_FALSE;
   if (var > 0.5) flag = GL_TRUE;
   if (flag) var -= 0.01;
   else var += 0.01;
   //mVertex->updateVBO(8,3,v);
}

void Demo::draw()
{
    /*
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
    */
   //ret = esGenSphere(100,0.5f, &vVertices, 0,0,&vIndices);
   //ret = esGenCube(1.0f, &vVertices, 0,0,&vIndices);
   // Set the viewport
   glViewport ( 0, 0, this->width, this->height );

   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   mTexture->bind((*mShader)("texture1"));
   // Use the program object
   mShader->use();
/*
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
    */

   mVertex->attachVBO((*mShader)("aPos"), 0, 3);
   mVertex->attachVBO((*mShader)("aColor"), 5, 3);
   mVertex->attachVBO((*mShader)("aTexCoord"), 3, 2);
   mVertex->draw(GL_TRIANGLES);
}

int main ( int argc, char *argv[] )
{
   Demo  demo("Hello Triangle", 600, 600);
   demo.loadShader("res/shaders/textureTest.vs", "res/shaders/textureTest.fs");
 //  demo.loadTexture("res/textures/container.jpg");
   demo.loadTexture("res/textures/awesomeface.png", GL_TRUE);
 // demo.loadTexture("res/textures/matrix.jpg", GL_TRUE);
 //  demo.loadTexture("res/textures/container2.png");
   demo.loadVertex();

//   demo.refreshForever();
    demo.refreshOnce();
    sleep(5);
   return 0;
}

