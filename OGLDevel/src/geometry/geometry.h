/*
 * =====================================================================================
 *
 *       Filename:  geometry.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Saturday 19 January 2019 01:30:36  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <GLES2/gl2.h>
#include "vertex/vertex.h"

class Geometry
{
    public:
        static Vertex *loadTriangle(void);
        static Vertex *loadSquare(void);
//        static Vertex *loadPolygon(GLuint side_count);
        static Vertex *loadCube(void);

    private:
  //      static float *generatePolygonVertices(GLuint side_count);
};

#endif /* __GEOMETRY_H__ */
