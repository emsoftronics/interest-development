/*
 * =====================================================================================
 *
 *       Filename:  texture2d.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 14 January 2019 10:44:43  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__
#include <GLES2/gl2.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
    private:
        // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
        GLuint ID;
        // Texture image dimensions
        GLuint Width, Height; // Width and height of loaded image in pixels
        // Texture Format
        GLuint Internal_Format; // Format of texture object
        // Texture configuration
        GLuint Wrap_S; // Wrapping mode on S axis
        GLuint Wrap_T; // Wrapping mode on T axis
        GLboolean imageTexture;
        GLboolean Fliped;

    public:
        // Constructor (sets default texture modes)
        Texture2D(GLuint width, GLuint height, GLuint internalFormat = GL_RGB,
            GLuint wrap_S = GL_CLAMP_TO_EDGE, GLuint wrap_T = GL_CLAMP_TO_EDGE);

        Texture2D(const char *imagePath, GLboolean fliped = GL_FALSE, GLuint internalFormat = GL_RGB,
            GLuint wrap_S = GL_CLAMP_TO_EDGE, GLuint wrap_T = GL_CLAMP_TO_EDGE);
        inline GLuint getID(void) const { return ID;}
        inline GLuint getWidth(void) const { return Width;}
        inline GLuint getHeight(void) const { return Height;}
        inline GLuint getInternalFormat(void) const { return Internal_Format;}
        inline GLboolean isImageTexture(void) const { return imageTexture;}
        inline GLboolean isFliped(void) const { return Fliped;}
        inline void bind(GLuint tex_varloc_id = 0) const {
            glActiveTexture(GL_TEXTURE0 + tex_varloc_id);
            glBindTexture(GL_TEXTURE_2D, this->ID);
        }

        ~Texture2D(void)
        { glBindTexture(GL_TEXTURE_2D, 0);
          glDeleteTextures(1, &this->ID);
        }
};

#endif
