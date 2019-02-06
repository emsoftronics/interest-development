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
#include "geometry/geometry.h"
#include <unistd.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Demo : public Canvas
{
    private:
        Shader *mShader;
        Texture2D *mTexture;
        Vertex *mVertex;
        glm::mat4 uTranslate;
        glm::mat4 uScale;
        glm::mat4 uRotate;
        glm::mat4 uView;
        glm::mat4 uProjection;

    public:
        Demo (const char *title, int width, int height) : Canvas(title, width, height)
        {
           mShader = NULL;
           mTexture = NULL;
           mVertex = NULL;
           uTranslate = glm::mat4(1.0);
           uScale = glm::mat4(1.0);
           uRotate = glm::mat4(1.0);
           uProjection = glm::ortho(-(float)width*0.5f, (float)width*0.5f,
                   -(float)height*0.5f, (float)height*0.5f, 10.0f, 1000.0f);
            //uProjection = glm::perspective(glm::radians(15.0f), (float)width / (float)height, 0.1f, 1000.0f) * uProjection;
           uView = glm::lookAt(/*cameraPos*/ glm::vec3(0.0, 0.0, -10.0f),
                   /*cameraPos*/glm::vec3(0.0, 0.0, -10.0f) + /*cameraFront*/glm::vec3(-0.0, 0.0, -1.0f),
                   /*cameraUp*/ glm::vec3(0.0, 1.0, 0.0f));
        }
        void draw(void);
        void update (float totalTime );
        void loadShader(const char *vshader, const char *fshader, bool codebuffer = false)
        {
            mShader = new Shader(vshader, fshader, codebuffer);
            //glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
        }
        void loadTexture(const char *imagePath, GLboolean fliped = GL_FALSE)
        { mTexture = new Texture2D(imagePath, fliped, GL_RGB, GL_REPEAT, GL_REPEAT);}

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
            /*
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
            */
            mVertex = Geometry::loadCube();
            //mVertex = Geometry::loadTriangle();
            //mVertex = Geometry::loadSquare();
        }
};

void Demo::update (float totalTime )
{
    static int i = 0;
    if (totalTime > 1.9) i = 0;
    else printf("\r%04d***", i++);
#if 1
    //uScale = glm::scale(glm::mat4(1.0),  glm::vec3(100.0));
    uRotate = glm::rotate(uRotate, glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //uTranslate[4] = glm::vec4(0.0, 0.0, -0.5, 1.0);
//    uTranslate = glm::translate(glm::mat4(1.0),  glm::vec3(0.0, 0.0, -300.0));

    uView = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    uProjection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
#else
    uView = glm::mat4(1.0f);
    uProjection = glm::mat4(1.0f);
#endif
}

void Demo::draw()
{

   //int ret = 0;
   GLfloat vVertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

   GLuint vIndices[] = {
        3,2,1,//1, 2, 3  // second triangle
        3,0,1 //
        //0, 1, 3, // first triangle
        //1, 2, 3  // second triangle
    };

   //ret = esGenSphere(100,0.5f, &vVertices, 0,0,&vIndices);
   //ret = esGenCube(1.0f, &vVertices, 0,0,&vIndices);
   // Set the viewport

   glViewport ( 0, 0, this->width, this->height );
   // Clear the color buffer
   //glDepthRangef(0.1f, 1000.0f);
   //glDepthFunc(GL_LESS);
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //mShader->setInt("texture1", 10);
   //mTexture->bind(10);
   mTexture->bind((*mShader)("texture1"));
   // Use the program object
   mShader->use();
   mShader->setMat4("uTranslate", uTranslate);
   mShader->setMat4("uScale", uScale);
   mShader->setMat4("uRotate", uRotate);
   mShader->setMat4("uProjection", uProjection);
   mShader->setMat4("uView", uView);

#if 0
   glVertexAttrib3f((*mShader)("aColor"), 1.0f, 0.5f, 0.5f);
   mVertex->attachVBO((*mShader)("aPosition"), 0, 3);
   //mVertex->attachVBO((*mShader)("aColor"), 5, 3);
   mVertex->attachVBO((*mShader)("aTexCoord"), 6, 2);
   mVertex->draw(GL_TRIANGLES);
#else
 // Load the vertex data
   glVertexAttribPointer ( (*mShader)("aPosition"), 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), vVertices);
   glEnableVertexAttribArray ( (*mShader)("aPosition"));
   glVertexAttribPointer ( (*mShader)("aColor"), 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), vVertices + 3);
   glEnableVertexAttribArray ( (*mShader)("aColor"));
   glVertexAttribPointer ( (*mShader)("aTexCoord"), 2, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), vVertices + 6);
   glEnableVertexAttribArray ( (*mShader)("aTexCoord"));
   glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, vIndices);
   //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#endif
   glFinish();
}

int main ( int argc, char *argv[] )
{
   Demo  demo("Hello Triangle", 600, 600);
   demo.loadShader("res/shaders/textureTest.vs", "res/shaders/textureTest.fs");
//   glEnable(GL_DEPTH_TEST);
//   demo.loadTexture("res/textures/container.jpg");
   demo.loadTexture("res/textures/awesomeface.png", GL_TRUE);
 // demo.loadTexture("res/textures/matrix.jpg", GL_TRUE);
 //  demo.loadTexture("res/textures/container2.png");
//   demo.loadVertex();

   demo.refreshForever();
   demo.refreshOnce();
    //sleep(5);
   return 0;
}

