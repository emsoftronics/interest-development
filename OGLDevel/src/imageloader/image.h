/*
 * =====================================================================================
 *
 *       Filename:  image.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Sunday 13 January 2019 05:17:30  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__

#include "stb_image.h"
#include <cstdio>
#include <fstream>

class Image
{
    private:
        unsigned char *data;
        int width;
        int height;
        int channels;
        bool fliped;

    public:
        Image(const char *image_path, bool load_fliped = false) : data(NULL),
        width(0), height(0), channels(0), fliped(load_fliped)
        {
            loadImage(image_path, 0, load_fliped);
        }

        Image(const char *image_path, int desired_channels,
                bool load_fliped = false) : data(NULL), width(0), height(0),
        channels(0), fliped(load_fliped)
        {
            loadImage(image_path, desired_channels, load_fliped);
        }

        ~Image() { if(data != NULL)  stbi_image_free(data);}

        inline int getWidth() const { return width; }
        inline int getHeight() const { return height; }
        inline int getChannelCount() const { return channels; }
        inline unsigned char *getPixelizedData() const { return data; }
        inline bool isFliped() const { return fliped; }

    private:
        inline bool isFileExist(const char *path) {std::ifstream f(path); return f.good();}
        void loadImage(const char *image_path, int desired_channels, bool load_fliped)
        {
            if (isFileExist(image_path)) {
                stbi_set_flip_vertically_on_load(load_fliped);
                if (desired_channels <= 0) desired_channels = 0;
                else desired_channels %= 5;
                data = stbi_load(image_path, &width, &height, &channels, desired_channels);
                if (data == NULL) printf("%s: %s\n", image_path, stbi_failure_reason());
            }
            else {
                printf("%s : No such file or permission denied!!\n", image_path);
            }
        }
};

#endif /*  __IMAGELOADER_H__ */
