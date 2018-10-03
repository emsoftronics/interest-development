/*
 * =====================================================================================
 *
 *       Filename:  Display.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Saturday 14 October 2017 06:11:16  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

class Display {
    private:
        struct fb_fix_screeninfo finfo;
        struct fb_var_screeninfo vinfo;
        int fd;
        void *base_addr;
        unsigned long int buffer_size;
        unsigned long int page_size;
        unsigned int page_count;
        unsigned int current_page;
        void *render_bffer;


    public:
        union Pixel {
            struct {
                unsigned char blue;
                unsigned char green;
                unsigned char red;
                unsigned char alpha;
            } subcolor;
            unsigned int color;
        };

        Display(int disp_node, int page_count);
        ~Display(void);

        int SetPixel(int x, int y, Pixel *pixel_in);
        int GetPixel(int x, int y, Pixel *pixel_out);



}
