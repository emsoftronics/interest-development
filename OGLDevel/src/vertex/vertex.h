/*
 * =====================================================================================
 *
 *       Filename:  vertex.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Thursday 17 January 2019 12:50:10  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __VERTEX_H__
#define __VERTEX_H__
#include <GLES2/gl2.h>

class Vertex
{
    private:
        GLuint VBO_ID;
        GLuint EBO_ID;
        GLuint Stride;
        GLuint VBOLength;
        GLuint EBOLength;

    public:
        Vertex(GLfloat *vbuffer, GLuint stride, GLuint vlength, GLuint *ebuffer = NULL,
                GLuint elength = 0) : Stride(stride), VBOLength(vlength), EBOLength(elength)
        {
            glGenBuffers(1, &this->VBO_ID);
            if (ebuffer) glGenBuffers(1, &this->EBO_ID);
            else EBO_ID = (GLuint)(-1);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
            glBufferData(GL_ARRAY_BUFFER, VBOLength*sizeof(GLfloat), vbuffer, GL_STATIC_DRAW);
            if (ebuffer) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOLength*sizeof(GLuint), ebuffer, GL_STATIC_DRAW);
            }
            else EBOLength = 0;
        }

        Vertex(GLuint vertex_count, GLfloat *v3Dbuffer, GLuint *ebuffer = NULL,
                GLuint elength = 0, GLfloat *v2Dtexbuf = NULL, GLfloat *v3Dbuf1 = NULL,
                GLfloat *v3Dbuf2 = NULL) : EBOLength(elength)
        {
            glGenBuffers(1, &this->VBO_ID);
            if (ebuffer) glGenBuffers(1, &this->EBO_ID);
            else EBO_ID = (GLuint)(-1);
            VBOLength = vertex_count*3;
            VBOLength += (v2Dtexbuf) ? (2*vertex_count) : 0;
            VBOLength += (v3Dbuf1) ? (3*vertex_count) : 0;
            VBOLength += (v3Dbuf2) ? (3*vertex_count) : 0;
            Stride = 3 + ((v2Dtexbuf) ? 2 : 0) + ((v3Dbuf1) ? 3 : 0) + ((v3Dbuf1) ? 3 : 0);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
            glBufferData(GL_ARRAY_BUFFER, VBOLength*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
            for (int i = 0; i < (int)vertex_count; i++) {
                glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)(i*Stride*sizeof(GLfloat)),
                        (GLsizeiptr)(3*sizeof(GLfloat)), &v3Dbuffer[i*3]);
                if (v2Dtexbuf) {
                    glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)((3+i*Stride)*sizeof(GLfloat)),
                            (GLsizeiptr)(2*sizeof(GLfloat)), &v2Dtexbuf[i*2]);
                }

                if (v3Dbuf1) {
                    glBufferSubData(GL_ARRAY_BUFFER,
                            (GLintptr)((3 + ((v2Dtexbuf) ? 2 : 0) + i*Stride)*sizeof(GLfloat)),
                            (GLsizeiptr)(3*sizeof(GLfloat)), &v3Dbuf1[i*3]);
                }

                if (v3Dbuf2) {
                    glBufferSubData(GL_ARRAY_BUFFER,
                            (GLintptr)((3 + ((v2Dtexbuf) ? 2 : 0) + ((v3Dbuf1) ? 3 : 0) + i*Stride)*sizeof(GLfloat)),
                            (GLsizeiptr)(3*sizeof(GLfloat)), &v3Dbuf2[i*3]);
                }
            }

            if (ebuffer) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOLength*sizeof(GLuint), ebuffer, GL_STATIC_DRAW);
            }
            else EBOLength = 0;
        }

        ~Vertex(void) {
            glDeleteBuffers(1, &this->VBO_ID);
            if (EBOLength) glDeleteBuffers(1, &this->EBO_ID);
        }

        inline void updateVBO(GLuint start_index, GLuint update_element_count, GLfloat *vbuffer)
        {
            if ((int)VBOLength - (int)start_index - (int)update_element_count < 0 ) return;
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
            glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)(start_index*sizeof(GLfloat)),
                    (GLsizeiptr)(update_element_count* sizeof(GLfloat)), vbuffer);
        }

        inline void updateEBO(GLuint start_index, GLuint update_element_count, GLuint *vbuffer)
        {
            if ((int)EBOLength - (int)start_index - (int)update_element_count < 0 ) return;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (GLintptr)(start_index*sizeof(GLuint)),
                    (GLsizeiptr)(update_element_count* sizeof(GLuint)), vbuffer);
        }

        inline GLuint getVBO(void) const {return VBO_ID;}
        inline GLuint getEBO(void) const {return EBO_ID;}
        inline GLuint getVBOLength(void) const {return VBOLength;}
        inline GLuint getEBOLength(void) const {return EBOLength;}
        inline GLboolean isEBOEnabled(void) const {return (GLboolean)EBOLength;}
        inline void attachVBO(GLuint attrib_locvar_id, GLuint offset, GLuint ecount = 3)
        {
            glVertexAttribPointer(attrib_locvar_id, ecount, GL_FLOAT, GL_FALSE,
                    Stride*sizeof(GLfloat), (void *)(offset*sizeof(GLfloat)));
            glEnableVertexAttribArray(attrib_locvar_id);
        }
        inline void detachVBO(GLuint attrib_locvar_id) { glDisableVertexAttribArray(attrib_locvar_id); }
        inline void bind(void)
        {
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
            if (EBOLength) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
        }

        inline void draw(GLuint primitive = GL_TRIANGLE_STRIP, GLuint start_index = 0, GLuint index_drawable_count = 0)
        {
            bind();
            if (EBOLength) glDrawElements(primitive,
                    (index_drawable_count)? index_drawable_count:EBOLength,
                    GL_UNSIGNED_INT, (void *)(start_index*sizeof(GLuint)));
            else glDrawArrays(primitive, start_index,
                    (index_drawable_count)?index_drawable_count:(VBOLength/Stride));
        }
};

#endif /* __VERTEX_H__ */
