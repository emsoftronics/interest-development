/*
 * =====================================================================================
 *
 *       Filename:  texture2d.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 14 January 2019 11:33:24  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "texture2d.h"
#include "imageloader/image.h"
#include <cstring>

Texture2D::Texture2D(GLuint width, GLuint height, GLuint internalFormat, GLuint wrap_S, GLuint wrap_T)
{
    glGenTextures(1, &this->ID);
    this->Width = width;
    this->Height = height;
    this->Internal_Format = internalFormat;
    this->Wrap_S = wrap_S;
    this->Wrap_T = wrap_T;
    this->imageTexture = GL_FALSE;
    this->Fliped = GL_FALSE;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Internal_Format, GL_UNSIGNED_BYTE, NULL);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(const char *imagePath, GLboolean fliped, GLuint internalFormat, GLuint wrap_S, GLuint wrap_T)
{
    glGenTextures(1, &this->ID);
    this->Internal_Format = internalFormat;
    this->Wrap_S = wrap_S;
    this->Wrap_T = wrap_T;
    this->Fliped = fliped;
    glBindTexture(GL_TEXTURE_2D, this->ID);
    GLuint imageformat = GL_RGB;
    Image image(imagePath, (bool)fliped);
    if (image.getPixelizedData() == NULL) {
        this->Width = 400;
        this->Height = 400;
        this->imageTexture = GL_FALSE;
        printf("%s: failed to load image!!\n", imagePath);
    }
    else {
        this->Width = image.getWidth();
        this->Height = image.getHeight();
        this->imageTexture = GL_TRUE;
        imageformat = (image.getChannelCount() == 4) ? GL_RGBA : GL_RGB;
        this->Internal_Format = imageformat;//(image.getChannelCount() < 4) ? imageformat : this->Internal_Format;
        printf("%s: Resolution = %dx%d and channels = %d\n", imagePath, Width, Height, image.getChannelCount());
    }
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, Width, Height, 0,
            imageformat, GL_UNSIGNED_BYTE, image.getPixelizedData());
    glGenerateMipmap(GL_TEXTURE_2D);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

