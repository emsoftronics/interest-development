/*
 * =====================================================================================
 *
 *       Filename:  GLESv2.c
 *
 *    Description:
 *
 *        Version:  2.0
 *        Created:  Friday 25 January 2019 02:10:07  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include <string.h>
#include "glesenum.h"
#include "vmcutil.h"
#include <GLES/gl.h>

#ifdef GL_APICALL
#undef GL_APICALL
#endif
#define GL_APICALL

#ifdef GL_APIENTRY
#undef GL_APIENTRY
#endif
#define GL_APIENTRY

GL_APICALL void GL_APIENTRY glActiveTexture (GLenum texture)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glActiveTexture, 1, sizeof(texture));
    DCC_ADD_ARG(texture, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glAlphaFunc (GLenum func, GLclampf ref)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glAlphaFunc, 2, sizeof(func)+sizeof(ref));
    DCC_ADD_ARG(func, 0);
    DCC_ADD_ARG(ref, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glAlphaFuncx (GLenum func, GLclampx ref)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glAlphaFuncx, 2, sizeof(func)+sizeof(ref));
    DCC_ADD_ARG(func, 0);
    DCC_ADD_ARG(ref, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glBindBuffer, 2, sizeof(target)+sizeof(buffer));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(buffer, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClearColorx, 4, 4*sizeof(red));
    DCC_ADD_ARG(red, 0);
    DCC_ADD_ARG(green, 0);
    DCC_ADD_ARG(blue, 0);
    DCC_ADD_ARG(alpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClearDepthx (GLclampx depth)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClearDepthx, 1, sizeof(depth));
    DCC_ADD_ARG(depth, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glBindTexture (GLenum target, GLuint texture)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glBindTexture, 2, sizeof(target)+sizeof(texture));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(texture, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClientActiveTexture (GLenum texture)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClientActiveTexture, 1, sizeof(texture));
    DCC_ADD_ARG(texture, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClipPlanef (GLenum plane, const GLfloat *equation)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClipPlanef, 2, sizeof(plane) + sizeof(equation) + 4*sizeof(*equation));
    DCC_ADD_ARG(plane, 0);
    DCC_ADD_ARG(equation, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(equation, 4*sizeof(*equation), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClipPlanex (GLenum plane, const GLfixed *equation)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClipPlanex, 2, sizeof(plane) + sizeof(equation) + 4*sizeof(*equation));
    DCC_ADD_ARG(plane, 0);
    DCC_ADD_ARG(equation, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(equation, 4*sizeof(*equation), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glBlendFunc, 2, sizeof(sfactor)+sizeof(dfactor));
    DCC_ADD_ARG(sfactor, 0);
    DCC_ADD_ARG(dfactor, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glColor4f, 4, 4*sizeof(red));
    DCC_ADD_ARG(red, 0);
    DCC_ADD_ARG(green, 0);
    DCC_ADD_ARG(blue, 0);
    DCC_ADD_ARG(alpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const void *data, GLenum usage)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glBufferData, 4, sizeof(target) + sizeof(size) + sizeof(data) + sizeof(usage) + size + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(size, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ADD_ARG(usage, 0);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, size + 1, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glBufferSubData, 4, sizeof(target) + sizeof(offset) + sizeof(size) + sizeof(data) + size + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(offset, 0);
    DCC_ADD_ARG(size, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, size + 1, 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glColor4ub, 4, 4*sizeof(red));
    DCC_ADD_ARG(red, 0);
    DCC_ADD_ARG(green, 0);
    DCC_ADD_ARG(blue, 0);
    DCC_ADD_ARG(alpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClear (GLbitfield mask)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClear, 1, sizeof(mask));
    DCC_ADD_ARG(mask, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClearColor, 4, 4*sizeof(red));
    DCC_ADD_ARG(red, 0);
    DCC_ADD_ARG(green, 0);
    DCC_ADD_ARG(blue, 0);
    DCC_ADD_ARG(alpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClearDepthf (GLfloat d)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClearDepthf, 1, sizeof(d));
    DCC_ADD_ARG(d, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClearStencil (GLint s)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glClearStencil, 1, sizeof(s));
    DCC_ADD_ARG(s, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glColorMask, 4, 4*sizeof(red));
    DCC_ADD_ARG(red, 0);
    DCC_ADD_ARG(green, 0);
    DCC_ADD_ARG(blue, 0);
    DCC_ADD_ARG(alpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glColor4x, 4, 4*sizeof(red));
    DCC_ADD_ARG(red, 0);
    DCC_ADD_ARG(green, 0);
    DCC_ADD_ARG(blue, 0);
    DCC_ADD_ARG(alpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat,
    GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glCompressedTexImage2D, 8, sizeof(target) + sizeof(level) + sizeof(internalformat)
    + sizeof(width) + sizeof(height) + sizeof(border) + sizeof(imageSize) + sizeof(data) + imageSize + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(level, 0);
    DCC_ADD_ARG(internalformat, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ADD_ARG(border, 0);
    DCC_ADD_ARG(imageSize, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, imageSize + 1, 7);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset,
    GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glCompressedTexSubImage2D, 9, sizeof(target) + sizeof(level) + sizeof(xoffset) + sizeof(yoffset)
    + sizeof(width) + sizeof(height) + sizeof(format) + sizeof(imageSize) + sizeof(data) + imageSize + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(level, 0);
    DCC_ADD_ARG(xoffset, 0);
    DCC_ADD_ARG(yoffset, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ADD_ARG(format, 0);
    DCC_ADD_ARG(imageSize, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, imageSize + 1, 8);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat,
    GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glCopyTexImage2D, 8, sizeof(target) + sizeof(level) + sizeof(internalformat)
    + sizeof(x) + sizeof(y) + sizeof(width) + sizeof(height) + sizeof(border));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(level, 0);
    DCC_ADD_ARG(internalformat, 0);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ADD_ARG(border, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset,
    GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glCopyTexSubImage2D, 8, sizeof(target) + sizeof(level) + sizeof(xoffset)
    + sizeof(yoffset) + sizeof(x) + sizeof(y) + sizeof(width) + sizeof(height));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(level, 0);
    DCC_ADD_ARG(xoffset, 0);
    DCC_ADD_ARG(yoffset, 0);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glColorPointer, 4, sizeof(size) + sizeof(type) + sizeof(stride) + sizeof(pointer) + 1024);
    DCC_ADD_ARG(size, 0);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(stride, 0);
    DCC_ADD_ARG(pointer, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pointer, 1000, 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDepthRangex (GLclampx zNear, GLclampx zFar)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDepthRangex, 2, sizeof(zNear) + sizeof(zFar));
    DCC_ADD_ARG(zNear, 0);
    DCC_ADD_ARG(zFar, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glCullFace (GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glCullFace, 1, sizeof(mode));
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint *buffers)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDeleteBuffers, 2, sizeof(n) + sizeof(buffers) + (n+1)*sizeof(*buffers));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(buffers, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(buffers, (n+1)*sizeof(*buffers), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDisableClientState (GLenum array)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDisableClientState, 1, sizeof(array));
    DCC_ADD_ARG(array, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glEnableClientState (GLenum array)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glEnableClientState, 1, sizeof(array));
    DCC_ADD_ARG(array, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFogf (GLenum pname, GLfloat param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFogf, 2, sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFogfv (GLenum pname, const GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFogfv, 2, sizeof(pname) + sizeof(params) + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDeleteTextures, 2, sizeof(n) + sizeof(textures) + (n+1)*sizeof(*textures));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(textures, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(textures, (n+1)*sizeof(*textures), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDepthFunc (GLenum func)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDepthFunc, 1, sizeof(func));
    DCC_ADD_ARG(func, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDepthMask (GLboolean flag)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDepthMask, 1, sizeof(flag));
    DCC_ADD_ARG(flag, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDepthRangef (GLfloat n, GLfloat f)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDepthRangef, 2, sizeof(n) + sizeof(f));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(f, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFogx (GLenum pname, GLfixed param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFogx, 2, sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDisable (GLenum cap)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDisable, 1, sizeof(cap));
    DCC_ADD_ARG(cap, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFogxv (GLenum pname, const GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFogxv, 2, sizeof(pname) + sizeof(params) + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDrawArrays, 3, sizeof(mode) + sizeof(first) + sizeof(count));
    DCC_ADD_ARG(mode, 0);
    DCC_ADD_ARG(first, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glDrawElements, 4, sizeof(mode) + sizeof(count) + sizeof(type) + sizeof(indices)
        + (count + 1)*gles_sizeof(type));
    DCC_ADD_ARG(mode, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(indices, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(indices, (count + 1)*gles_sizeof(type), 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glEnable (GLenum cap)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glEnable, 1, sizeof(cap));
    DCC_ADD_ARG(cap, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFrustumf, 6, 6*sizeof(left));
    DCC_ADD_ARG(left, 0);
    DCC_ADD_ARG(right, 0);
    DCC_ADD_ARG(bottom, 0);
    DCC_ADD_ARG(top, 0);
    DCC_ADD_ARG(zNear, 0);
    DCC_ADD_ARG(zFar, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFinish (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFinish, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFlush (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFlush, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFrustumx, 6, 6*sizeof(left));
    DCC_ADD_ARG(left, 0);
    DCC_ADD_ARG(right, 0);
    DCC_ADD_ARG(bottom, 0);
    DCC_ADD_ARG(top, 0);
    DCC_ADD_ARG(zNear, 0);
    DCC_ADD_ARG(zFar, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetClipPlanef (GLenum pname, GLfloat eqn[4])
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetClipPlanef, 2, sizeof(pname) + sizeof(GLfloat)*4 +4);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(eqn, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(eqn, sizeof(GLfloat)*4, 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(eqn, sizeof(GLfloat)*4, 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFrontFace (GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glFrontFace, 1, sizeof(mode));
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGenBuffers, 2, sizeof(n) + sizeof(buffers) + (n+1)*sizeof(*buffers));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(buffers, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(buffers, (n+1)*sizeof(*buffers), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(buffers, n*sizeof(*buffers), 1);
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glGetClipPlanex (GLenum pname, GLfixed eqn[4])
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetClipPlanex, 2, sizeof(pname) + sizeof(GLfixed)*4 +4);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(eqn, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(eqn, sizeof(GLfixed)*4, 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(eqn, sizeof(GLfixed)*4, 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetFixedv, 2, sizeof(pname) + sizeof(params) + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetLightfv, 3, sizeof(light) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(light, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGenTextures, 2, sizeof(n) + sizeof(textures) + (n+1)*sizeof(*textures));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(textures, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(textures, (n+1)*sizeof(*textures), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(textures, n*sizeof(*textures), 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetLightxv, 3, sizeof(light) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(light, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetMaterialfv, 3, sizeof(face) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetMaterialxv, 3, sizeof(face) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetPointerv (GLenum pname, GLvoid **params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetPointerv, 2, sizeof(pname) + sizeof(params)
        + 50*sizeof(*params) + 4);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(*params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(*params, 50*sizeof(*params), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(*params, 50*sizeof(*params), 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetBooleanv, 2, sizeof(pname) + sizeof(data) + sizeof(*data) + 1);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, sizeof(*data), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(data, sizeof(*data), 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetBufferParameteriv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL GLenum GL_APIENTRY glGetError (void)
{
    GLenum ret = 0;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetError, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL void GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetFloatv, 2, sizeof(pname) + sizeof(data) + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, 500, 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(data, 500, 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetTexEnvfv, 3, sizeof(env) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(env, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetIntegerv (GLenum pname, GLint *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetIntegerv, 2, sizeof(pname) + sizeof(data) + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, 500, 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(data, 500, 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetTexEnvxv, 3, sizeof(env) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(env, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetTexEnviv (GLenum env, GLenum pname, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetTexEnviv, 3, sizeof(env) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(env, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetTexParameterxv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLightfv (GLenum light, GLenum pname, const GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLightfv, 3, sizeof(light) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(light, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLightf, 3, sizeof(light) + sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(light, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLightModelf (GLenum pname, GLfloat param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLightModelf, 3, sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLightModelfv (GLenum pname, const GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLightModelfv, 3, sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 1);
    DCC_END_CALL();
#endif
}


GL_APICALL const GLubyte *GL_APIENTRY glGetString (GLenum name)
{
    static GLubyte retstr[64] = {0};
    GLubyte *buf = retstr;
    GLsizei bufSize = sizeof(retstr);
    memset(retstr, 0, bufSize);
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetString, 3, sizeof(name) + sizeof(void *)
    + sizeof(bufSize) + bufSize + 1);
    DCC_ADD_ARG(name, 0);
    DCC_ADD_ARG(bufSize, 0);
    DCC_ADD_ARG(buf, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(buf, bufSize + 1, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(buf, bufSize, 2);
    DCC_END_CALL();
#endif
    return retstr;
}

GL_APICALL void GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetTexParameterfv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glGetTexParameteriv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLightModelx (GLenum pname, GLfixed param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLightModelx, 3, sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLightModelxv (GLenum pname, const GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLightModelxv, 3, sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 1);
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLightx, 3, sizeof(light) + sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(light, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glLightxv (GLenum light, GLenum pname, const GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLightxv, 3, sizeof(light) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(light, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLineWidthx (GLfixed width)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLineWidthx, 1, sizeof(width));
    DCC_ADD_ARG(width, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLoadIdentity (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLoadIdentity, 0,0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glHint (GLenum target, GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glHint, 2, sizeof(target) + sizeof(mode) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL GLboolean GL_APIENTRY glIsBuffer (GLuint buffer)
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glIsBuffer, 1, sizeof(buffer) + 1);
    DCC_ADD_ARG(buffer, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap)
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glIsEnabled, 1, sizeof(cap) + 1);
    DCC_ADD_ARG(cap, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL void GL_APIENTRY glLoadMatrixf (const GLfloat *m)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLoadMatrixf, 1, sizeof(m) + sizeof(*m)*16 + 16);
    DCC_ADD_ARG(m, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(m, sizeof(*m)*16, 0);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glLoadMatrixx (const GLfixed *m)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLoadMatrixx, 1, sizeof(m) + sizeof(*m)*16 + 16);
    DCC_ADD_ARG(m, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(m, sizeof(*m)*16, 0);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLogicOp (GLenum opcode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLogicOp, 1, sizeof(opcode) + 1);
    DCC_ADD_ARG(opcode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMaterialf, 3, sizeof(face) + sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture)
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glIsTexture, 1, sizeof(texture) + 1);
    DCC_ADD_ARG(texture, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL void GL_APIENTRY glLineWidth (GLfloat width)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glLineWidth, 1, sizeof(width) + 1);
    DCC_ADD_ARG(width, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, const GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMaterialfv, 3, sizeof(face) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPixelStorei (GLenum pname, GLint param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPixelStorei, 2, sizeof(pname) + sizeof(param) + 1);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPolygonOffset, 2, sizeof(factor) + sizeof(units) + 1);
    DCC_ADD_ARG(factor, 0);
    DCC_ADD_ARG(units, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height,
    GLenum format, GLenum type, void *pixels)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glReadPixels, 7, sizeof(x) + sizeof(y) + sizeof(width) + sizeof(height)
        + sizeof(format) + sizeof(type) + sizeof(pixels) + gles_pixel_channels(format, type)*width*height + 16);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ADD_ARG(format, 0);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(pixels, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pixels, gles_pixel_channels(format, type)*width*height + 16, 6);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(pixels, gles_pixel_channels(format, type)*width*height + 8, 6);
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMaterialx, 3, sizeof(face) + sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, const GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMaterialxv, 3, sizeof(face) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glSampleCoverage (GLfloat value, GLboolean invert)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glSampleCoverage, 2, sizeof(value) + sizeof(invert) + 1);
    DCC_ADD_ARG(value, 0);
    DCC_ADD_ARG(invert, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glScissor, 4, sizeof(x) + sizeof(y)
        + sizeof(width) + sizeof(height) + 1);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glMatrixMode (GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMatrixMode, 1, sizeof(mode));
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMultiTexCoord4f, 5, sizeof(target) + sizeof(s)*4);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(s, 0);
    DCC_ADD_ARG(t, 0);
    DCC_ADD_ARG(r, 0);
    DCC_ADD_ARG(q, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glStencilFunc, 3, sizeof(func) + sizeof(ref) + sizeof(mask) + 1);
    DCC_ADD_ARG(func, 0);
    DCC_ADD_ARG(ref, 0);
    DCC_ADD_ARG(mask, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMultiTexCoord4x, 5, sizeof(target) + sizeof(s)*4);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(s, 0);
    DCC_ADD_ARG(t, 0);
    DCC_ADD_ARG(r, 0);
    DCC_ADD_ARG(q, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glStencilMask (GLuint mask)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glStencilMask, 3, sizeof(mask) + 1);
    DCC_ADD_ARG(mask, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glMultMatrixf (const GLfloat *m)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMultMatrixf, 1, sizeof(m) + sizeof(*m)*16 + 16);
    DCC_ADD_ARG(m, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(m, sizeof(*m)*16, 0);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glStencilOp, 3, sizeof(fail) + sizeof(zfail) + sizeof(zpass) + 1);
    DCC_ADD_ARG(fail, 0);
    DCC_ADD_ARG(zfail, 0);
    DCC_ADD_ARG(zpass, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glMultMatrixx (const GLfixed *m)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glMultMatrixx, 1, sizeof(m) + sizeof(*m)*16 + 16);
    DCC_ADD_ARG(m, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(m, sizeof(*m)*16, 0);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width,
    GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexImage2D, 9, sizeof(target) + sizeof(level) + sizeof(internalformat)
        + sizeof(width) + sizeof(height) + sizeof(border) + sizeof(format) + sizeof(type)
        + sizeof(pixels) + gles_pixel_channels(format, type)*width*height + 16);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(level, 0);
    DCC_ADD_ARG(internalformat, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ADD_ARG(border, 0);
    DCC_ADD_ARG(format, 0);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(pixels, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pixels, gles_pixel_channels(format, type)*width*height+16, 8);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexParameterf, 3, sizeof(target) + sizeof(pname) + sizeof(param) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexParameterfv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexParameteri, 3, sizeof(target) + sizeof(pname) + sizeof(param) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexParameteriv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexSubImage2D, 9, sizeof(target) + sizeof(level) + sizeof(xoffset)
        + sizeof(yoffset)  + sizeof(width) + sizeof(height) + sizeof(format) + sizeof(type)
        + sizeof(pixels) + gles_pixel_channels(format, type)*width*height + 16);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(level, 0);
    DCC_ADD_ARG(xoffset, 0);
    DCC_ADD_ARG(yoffset, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ADD_ARG(format, 0);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(pixels, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pixels, gles_pixel_channels(format, type)*width*height+16, 8);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glNormal3f, 3, sizeof(nx)*3);
    DCC_ADD_ARG(nx, 0);
    DCC_ADD_ARG(ny, 0);
    DCC_ADD_ARG(nz, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glNormal3x, 3, sizeof(nx)*3);
    DCC_ADD_ARG(nx, 0);
    DCC_ADD_ARG(ny, 0);
    DCC_ADD_ARG(nz, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glNormalPointer, 3, sizeof(type) + sizeof(stride) + sizeof(pointer) + 1024);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(stride, 0);
    DCC_ADD_ARG(pointer, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pointer, 1000, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glOrthof, 6, 6*sizeof(left));
    DCC_ADD_ARG(left, 0);
    DCC_ADD_ARG(right, 0);
    DCC_ADD_ARG(bottom, 0);
    DCC_ADD_ARG(top, 0);
    DCC_ADD_ARG(zNear, 0);
    DCC_ADD_ARG(zFar, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glOrthox, 6, 6*sizeof(left));
    DCC_ADD_ARG(left, 0);
    DCC_ADD_ARG(right, 0);
    DCC_ADD_ARG(bottom, 0);
    DCC_ADD_ARG(top, 0);
    DCC_ADD_ARG(zNear, 0);
    DCC_ADD_ARG(zFar, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPointParameterf (GLenum pname, GLfloat param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPointParameterf, 2, sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPointParameterfv (GLenum pname, const GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPointParameterfv, 2, sizeof(pname) + sizeof(params) + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPointParameterx (GLenum pname, GLfixed param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPointParameterx, 2, sizeof(pname) + sizeof(param));
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPointParameterxv (GLenum pname, const GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPointParameterxv, 2, sizeof(pname) + sizeof(params) + 512);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPointSize (GLfloat size)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPointSize, 1, sizeof(size));
    DCC_ADD_ARG(size, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

/* GL_OES_point_size_array */
GL_APICALL void GL_APIENTRY glPointSizePointerOES (GLenum type, GLsizei stride, const GLvoid *pointer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPointSizePointerOES, 3, sizeof(type) + sizeof(stride) + sizeof(pointer) + 1024);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(stride, 0);
    DCC_ADD_ARG(pointer, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pointer, 1000, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPointSizex (GLfixed size)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPointSizex, 1, sizeof(size));
    DCC_ADD_ARG(size, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glPolygonOffsetx (GLfixed factor, GLfixed units)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPolygonOffsetx, 2, 2*sizeof(factor) + 4);
    DCC_ADD_ARG(factor, 0);
    DCC_ADD_ARG(units, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPopMatrix (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPopMatrix, 0, 1);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPushMatrix (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glPushMatrix, 0, 1);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glRotatef, 4, 4*sizeof(angle) + 4);
    DCC_ADD_ARG(angle, 0);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(z, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glRotatex, 4, 4*sizeof(angle) + 4);
    DCC_ADD_ARG(angle, 0);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(z, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glSampleCoveragex (GLclampx value, GLboolean invert)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glSampleCoveragex, 2, sizeof(value) + sizeof(invert));
    DCC_ADD_ARG(value, 0);
    DCC_ADD_ARG(invert, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glScalef, 3, 3*sizeof(x) + 4);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(z, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glScalex, 3, 3*sizeof(x) + 4);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(z, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glShadeModel (GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glShadeModel, 1, sizeof(mode) + 4);
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexCoordPointer, 4, sizeof(size) + sizeof(type) + sizeof(stride) + sizeof(pointer) + 1024);
    DCC_ADD_ARG(size, 0);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(stride, 0);
    DCC_ADD_ARG(pointer, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pointer, 1000, 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexEnvf, 3, sizeof(target) + sizeof(pname) + sizeof(param) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexEnvfv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexEnvi, 3, sizeof(target) + sizeof(pname) + sizeof(param) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexEnviv (GLenum target, GLenum pname, const GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexEnviv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glTexEnvx (GLenum target, GLenum pname, GLfixed param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexEnvx, 3, sizeof(target) + sizeof(pname) + sizeof(param) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexEnvxv (GLenum target, GLenum pname, const GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexEnvxv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glTexParameterx (GLenum target, GLenum pname, GLfixed param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexParameterx, 3, sizeof(target) + sizeof(pname) + sizeof(param) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(param, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glTexParameterxv (GLenum target, GLenum pname, const GLfixed *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTexParameterxv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + 512);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, 500, 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, 500, 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glViewport, 4, 2*sizeof(x) + 2*sizeof(width) + 1);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTranslatef, 3, 3*sizeof(x) + 1);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(z, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glTranslatex, 3, 3*sizeof(x) + 1);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(z, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv1_glVertexPointer, 4, sizeof(size) + sizeof(type) + sizeof(stride) + sizeof(pointer) + 1024);
    DCC_ADD_ARG(size, 0);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(stride, 0);
    DCC_ADD_ARG(pointer, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pointer, 1000, 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

