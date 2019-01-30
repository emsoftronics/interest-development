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

GL_APICALL void GL_APIENTRY glActiveTexture (GLenum texture)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glActiveTexture, 1, sizeof(texture));
    DCC_ADD_ARG(texture, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glAttachShader (GLuint program, GLuint shader)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glAttachShader, 2, sizeof(program)+sizeof(shader));
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(shader, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, const GLchar *name)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBindAttribLocation, 3, sizeof(program)+sizeof(index)+sizeof(name)+GL_STRLEN(name)+1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(name, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(name, GL_STRLEN(name)+1, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBindBuffer, 2, sizeof(target)+sizeof(buffer));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(buffer, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBindFramebuffer, 2, sizeof(target)+sizeof(framebuffer));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(framebuffer, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBindRenderbuffer, 2, sizeof(target)+sizeof(renderbuffer));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(renderbuffer, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glBindTexture (GLenum target, GLuint texture)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBindTexture, 2, sizeof(target)+sizeof(texture));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(texture, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBlendColor, 4, 4*sizeof(red));
    DCC_ADD_ARG(red, 0);
    DCC_ADD_ARG(green, 0);
    DCC_ADD_ARG(blue, 0);
    DCC_ADD_ARG(alpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBlendEquation (GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBlendEquation, 1, sizeof(mode));
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBlendEquationSeparate, 2, sizeof(modeRGB)+sizeof(modeAlpha));
    DCC_ADD_ARG(modeRGB, 0);
    DCC_ADD_ARG(modeAlpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBlendFunc, 2, sizeof(sfactor)+sizeof(dfactor));
    DCC_ADD_ARG(sfactor, 0);
    DCC_ADD_ARG(dfactor, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB,
    GLenum sfactorAlpha, GLenum dfactorAlpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBlendFuncSeparate, 4, 4*sizeof(sfactorRGB));
    DCC_ADD_ARG(sfactorRGB, 0);
    DCC_ADD_ARG(dfactorRGB, 0);
    DCC_ADD_ARG(sfactorAlpha, 0);
    DCC_ADD_ARG(dfactorAlpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const void *data, GLenum usage)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glBufferData, 4, sizeof(target) + sizeof(size) + sizeof(data) + sizeof(usage) + size + 1);
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
    DCC_START_CALL(GLESv2_glBufferSubData, 4, sizeof(target) + sizeof(offset) + sizeof(size) + sizeof(data) + size + 1);
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

GL_APICALL GLenum GL_APIENTRY glCheckFramebufferStatus (GLenum target)
{
    GLenum ret = -1;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glCheckFramebufferStatus, 1, sizeof(target));
    DCC_ADD_ARG(target, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
   return ret;
}

GL_APICALL void GL_APIENTRY glClear (GLbitfield mask)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glClear, 1, sizeof(mask));
    DCC_ADD_ARG(mask, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glClearColor, 4, 4*sizeof(red));
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
    DCC_START_CALL(GLESv2_glClearDepthf, 1, sizeof(d));
    DCC_ADD_ARG(d, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glClearStencil (GLint s)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glClearStencil, 1, sizeof(s));
    DCC_ADD_ARG(s, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glColorMask, 4, 4*sizeof(red));
    DCC_ADD_ARG(red, 0);
    DCC_ADD_ARG(green, 0);
    DCC_ADD_ARG(blue, 0);
    DCC_ADD_ARG(alpha, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glCompileShader (GLuint shader)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glCompileShader, 1, sizeof(shader));
    DCC_ADD_ARG(shader, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat,
    GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glCompressedTexImage2D, 8, sizeof(target) + sizeof(level) + sizeof(internalformat)
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
    DCC_START_CALL(GLESv2_glCompressedTexSubImage2D, 9, sizeof(target) + sizeof(level) + sizeof(xoffset) + sizeof(yoffset)
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
    DCC_START_CALL(GLESv2_glCopyTexImage2D, 8, sizeof(target) + sizeof(level) + sizeof(internalformat)
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
    DCC_START_CALL(GLESv2_glCopyTexSubImage2D, 8, sizeof(target) + sizeof(level) + sizeof(xoffset)
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

GL_APICALL GLuint GL_APIENTRY glCreateProgram (void)
{
    GLuint ret = (GLuint)(-1);
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glCreateProgram, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type)
{
    GLuint ret = (GLuint)(-1);
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glCreateShader, 1, sizeof(type));
    DCC_ADD_ARG(type, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL void GL_APIENTRY glCullFace (GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glCullFace, 1, sizeof(mode));
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint *buffers)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDeleteBuffers, 2, sizeof(n) + sizeof(buffers) + (n+1)*sizeof(*buffers));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(buffers, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(buffers, (n+1)*sizeof(*buffers), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDeleteFramebuffers (GLsizei n, const GLuint *framebuffers)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDeleteFramebuffers, 2, sizeof(n) + sizeof(framebuffers) + (n+1)*sizeof(*framebuffers));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(framebuffers, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(framebuffers, (n+1)*sizeof(*framebuffers), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDeleteProgram (GLuint program)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDeleteProgram, 1, sizeof(program));
    DCC_ADD_ARG(program, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDeleteRenderbuffers (GLsizei n, const GLuint *renderbuffers)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDeleteRenderbuffers, 2, sizeof(n) + sizeof(renderbuffers) + (n+1)*sizeof(*renderbuffers));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(renderbuffers, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(renderbuffers, (n+1)*sizeof(*renderbuffers), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDeleteShader (GLuint shader)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDeleteShader, 1, sizeof(shader));
    DCC_ADD_ARG(shader, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDeleteTextures, 2, sizeof(n) + sizeof(textures) + (n+1)*sizeof(*textures));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(textures, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(renderbuffers, (n+1)*sizeof(*textures), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDepthFunc (GLenum func)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDepthFunc, 1, sizeof(func));
    DCC_ADD_ARG(func, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDepthMask (GLboolean flag)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDepthMask, 1, sizeof(flag));
    DCC_ADD_ARG(flag, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDepthRangef (GLfloat n, GLfloat f)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDepthRangef, 2, sizeof(n), sizeof(f));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(f, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDetachShader (GLuint program, GLuint shader)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDetachShader, 2, sizeof(program), sizeof(shader));
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(shader, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDisable (GLenum cap)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDisable, 1, sizeof(cap));
    DCC_ADD_ARG(cap, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDisableVertexAttribArray (GLuint index)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDisableVertexAttribArray, 1, sizeof(index));
    DCC_ADD_ARG(index, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glDrawArrays, 3, sizeof(mode), sizeof(first), sizeof(count));
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
    DCC_START_CALL(GLESv2_glDrawElements, 4, sizeof(mode) + sizeof(count) + sizeof(type) + sizeof(indices)
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
    DCC_START_CALL(GLESv2_glEnable, 1, sizeof(cap));
    DCC_ADD_ARG(cap, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glEnableVertexAttribArray (GLuint index)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glEnableVertexAttribArray, 1, sizeof(index));
    DCC_ADD_ARG(index, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFinish (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glFinish, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFlush (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glFlush, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment,
GLenum renderbuffertarget, GLuint renderbuffer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glFramebufferRenderbuffer, 4, sizeof(target) + sizeof(attachment)
        + sizeof(renderbuffertarget) + sizeof(renderbuffer));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(attachment, 0);
    DCC_ADD_ARG(renderbuffertarget, 0);
    DCC_ADD_ARG(renderbuffer, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment,
    GLenum textarget, GLuint texture, GLint level)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glFramebufferTexture2D, 5, sizeof(target) + sizeof(attachment)
        + sizeof(textarget) + sizeof(texture) + sizeof(level));
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(attachment, 0);
    DCC_ADD_ARG(textarget, 0);
    DCC_ADD_ARG(texture, 0);
    DCC_ADD_ARG(level, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glFrontFace (GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glFrontFace, 1, sizeof(mode));
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGenBuffers, 2, sizeof(n) + sizeof(buffers) + (n+1)*sizeof(*buffers));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(buffers, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(buffers, (n+1)*sizeof(*buffers), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(buffers, n*sizeof(*buffers), 1);
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glGenerateMipmap (GLenum target)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGenerateMipmap, 1, sizeof(target));
    DCC_ADD_ARG(target, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGenFramebuffers, 2, sizeof(n) + sizeof(framebuffers) + (n+1)*sizeof(*framebuffers));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(framebuffers, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(framebuffers, (n+1)*sizeof(*framebuffers), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(framebuffers, n*sizeof(*framebuffers), 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGenRenderbuffers, 2, sizeof(n) + sizeof(renderbuffers) + (n+1)*sizeof(*renderbuffers));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(renderbuffers, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(renderbuffers, (n+1)*sizeof(*renderbuffers), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(renderbuffers, n*sizeof(*renderbuffers), 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGenTextures, 2, sizeof(n) + sizeof(textures) + (n+1)*sizeof(*textures));
    DCC_ADD_ARG(n, 0);
    DCC_ADD_ARG(textures, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(textures, (n+1)*sizeof(*textures), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(textures, n*sizeof(*textures), 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize,
    GLsizei *length, GLint *size, GLenum *type, GLchar *name)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetActiveAttrib, 7, sizeof(program) + sizeof(index) + sizeof(bufSize)
        + sizeof(*length) + sizeof(*size) + sizeof(*type) + 4*sizeof(name) + bufSize + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(bufSize, 0);
    DCC_ADD_ARG(length, 1);
    DCC_ADD_ARG(size, 1);
    DCC_ADD_ARG(type, 1);
    DCC_ADD_ARG(name, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(length, sizeof(*length), 3);
    DCC_ADD_APTR_MEM(size, sizeof(*size), 4);
    DCC_ADD_APTR_MEM(type, sizeof(*type), 5);
    DCC_ADD_APTR_MEM(name, bufSize + 1, 6);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(length, sizeof(*length), 3);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(size, sizeof(*size), 4);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(type, sizeof(*type), 5);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(name, bufSize, 6);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize,
    GLsizei *length, GLint *size, GLenum *type, GLchar *name)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetActiveUniform, 7, sizeof(program) + sizeof(index) + sizeof(bufSize)
        + sizeof(*length) + sizeof(*size) + sizeof(*type) + 4*sizeof(name) + bufSize + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(bufSize, 0);
    DCC_ADD_ARG(length, 1);
    DCC_ADD_ARG(size, 1);
    DCC_ADD_ARG(type, 1);
    DCC_ADD_ARG(name, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(length, sizeof(*length), 3);
    DCC_ADD_APTR_MEM(size, sizeof(*size), 4);
    DCC_ADD_APTR_MEM(type, sizeof(*type), 5);
    DCC_ADD_APTR_MEM(name, bufSize + 1, 6);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(length, sizeof(*length), 3);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(size, sizeof(*size), 4);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(type, sizeof(*type), 5);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(name, bufSize, 6);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetAttachedShaders, 4, sizeof(program) + sizeof(maxCount) + sizeof(*count)
        + sizeof(*shaders) + 2*sizeof(void *) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(maxCount, 0);
    DCC_ADD_ARG(count, 1);
    DCC_ADD_ARG(shaders, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(count, sizeof(*count), 2);
    DCC_ADD_APTR_MEM(shaders, maxCount*sizeof(*shaders), 3);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(count, sizeof(*count), 2);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(shaders, maxCount*sizeof(*shaders), 3);
    DCC_END_CALL();
#endif
}

GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint program, const GLchar *name)
{
    GLint ret = (GLint)(-1);
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetAttribLocation, 2, sizeof(program) + sizeof(name) + GL_STRLEN(name) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(name, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(name, GL_STRLEN(name) + 1, 1);
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL void GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetBooleanv, 2, sizeof(pname) + sizeof(data) + sizeof(*data) + 1);
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
    DCC_START_CALL(GLESv2_glGetBufferParameteriv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL GLenum GL_APIENTRY glGetError (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetError, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetFloatv, 2, sizeof(pname) + sizeof(data) + sizeof(*data) + 1);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, sizeof(*data), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(data, sizeof(*data), 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target,
    GLenum attachment, GLenum pname, GLint *params);
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetFramebufferAttachmentParameteriv, 4, sizeof(target) + sizeof(attachment)
        + sizeof(pname) + sizeof(params) + sizeof(*params) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(attachment, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 3);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 3);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetIntegerv (GLenum pname, GLint *data)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetIntegerv, 2, sizeof(pname) + sizeof(data) + sizeof(*data) + 1);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(data, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(data, sizeof(*data), 1);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(data, sizeof(*data), 1);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetProgramiv, 3, sizeof(program) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufSize,
    GLsizei *length, GLchar *infoLog)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetProgramInfoLog, 4, sizeof(program) + sizeof(bufSize) + sizeof(*length)
        + sizeof(*infoLog) + 2*sizeof(void *) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(bufSize, 0);
    DCC_ADD_ARG(length, 1);
    DCC_ADD_ARG(infoLog, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(length, sizeof(*length), 2);
    DCC_ADD_APTR_MEM(infoLog, bufSize + 1, 3);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(length, sizeof(*length), 2);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(infoLog, bufSize + 1, 3);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetRenderbufferParameteriv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetShaderiv, 3, sizeof(shader) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(shader, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufSize,
    GLsizei *length, GLchar *infoLog)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetShaderInfoLog, 4, sizeof(shader) + sizeof(bufSize) + sizeof(*length)
        + sizeof(*infoLog) + 2*sizeof(void *) + 1);
    DCC_ADD_ARG(shader, 0);
    DCC_ADD_ARG(bufSize, 0);
    DCC_ADD_ARG(length, 1);
    DCC_ADD_ARG(infoLog, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(length, sizeof(*length), 2);
    DCC_ADD_APTR_MEM(infoLog, bufSize + 1, 3);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(length, sizeof(*length), 2);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(infoLog, bufSize + 1, 3);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype,
    GLint *range, GLint *precision)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetShaderPrecisionFormat, 4, sizeof(shadertype) + sizeof(precisiontype)
    + 2*sizeof(range) + 2*sizeof(*precision) + 1);
    DCC_ADD_ARG(shadertype, 0);
    DCC_ADD_ARG(precisiontype, 0);
    DCC_ADD_ARG(range, 1);
    DCC_ADD_ARG(precision, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(range, sizeof(*range), 2);
    DCC_ADD_APTR_MEM(precision, sizeof(*precision), 3);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(range, sizeof(*range), 2);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(precision, sizeof(*precision), 3);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetShaderSource, 4, sizeof(shader) + sizeof(bufSize)
    + sizeof(*length) + 2*sizeof(void*) + bufSize + 1);
    DCC_ADD_ARG(shader, 0);
    DCC_ADD_ARG(bufSize, 0);
    DCC_ADD_ARG(length, 1);
    DCC_ADD_ARG(source, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(length, sizeof(*length), 2);
    DCC_ADD_APTR_MEM(source, bufSize + 1, 3);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(length, sizeof(*length), 2);
    DCC_UPDATE_NON_CONST_PTR_ON_RET(source, bufSize, 3);
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
    DCC_START_CALL(GLESv2_glGetString, 3, sizeof(name) + sizeof(void *)
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
    DCC_START_CALL(GLESv2_glGetTexParameterfv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetTexParameteriv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetUniformfv, 3, sizeof(program) + sizeof(location) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetUniformiv, 3, sizeof(program) + sizeof(location) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}


GL_APICALL GLint GL_APIENTRY glGetUniformLocation (GLuint program, const GLchar *name)
{
    GLint ret = (GLint)(-1);
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetUniformLocation, 2, sizeof(program) + sizeof(name) + GL_STRLEN(name) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ADD_ARG(name, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(name, GL_STRLEN(name) + 1, 1);
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}


GL_APICALL void GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetVertexAttribfv, 3, sizeof(index) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetVertexAttribiv, 3, sizeof(index) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, void **pointer);
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glGetVertexAttribPointerv, 3, sizeof(index) + sizeof(pname) + 2*sizeof(void*) + 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(pointer, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pointer, sizeof(*pointer), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(pointer, sizeof(*pointer), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glHint (GLenum target, GLenum mode)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glHint, 2, sizeof(target) + sizeof(mode) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(mode, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL GLboolean GL_APIENTRY glIsBuffer (GLuint buffer);
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glIsBuffer, 1, sizeof(buffer) + 1);
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
    DCC_START_CALL(GLESv2_glIsEnabled, 1, sizeof(cap) + 1);
    DCC_ADD_ARG(cap, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer)
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glIsFramebuffer, 1, sizeof(framebuffer) + 1);
    DCC_ADD_ARG(framebuffer, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}


GL_APICALL GLboolean GL_APIENTRY glIsProgram (GLuint program)
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glIsProgram, 1, sizeof(program) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer)
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glIsRenderbuffer, 1, sizeof(renderbuffer) + 1);
    DCC_ADD_ARG(renderbuffer, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader)
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glIsShader, 1, sizeof(shader) + 1);
    DCC_ADD_ARG(shader, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture)
{
    GLboolean ret = GL_FALSE;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glIsTexture, 1, sizeof(texture) + 1);
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
    DCC_START_CALL(GLESv2_glLineWidth, 1, sizeof(width) + 1);
    DCC_ADD_ARG(width, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glLinkProgram (GLuint program)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glLinkProgram, 1, sizeof(program) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glPixelStorei (GLenum pname, GLint param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glPixelStorei, 2, sizeof(pname) + sizeof(param) + 1);
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
    DCC_START_CALL(GLESv2_glPolygonOffset, 2, sizeof(factor) + sizeof(units) + 1);
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
    DCC_START_CALL(GLESv2_glReadPixels, 7, sizeof(x) + sizeof(y) + sizeof(width) + sizeof(height)
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


GL_APICALL void GL_APIENTRY glReleaseShaderCompiler (void)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glReleaseShaderCompiler, 0, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glRenderbufferStorage, 4, sizeof(target) + sizeof(internalformat)
        + sizeof(width) + sizeof(height) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(internalformat, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glSampleCoverage (GLfloat value, GLboolean invert)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glSampleCoverage, 2, sizeof(value) + sizeof(invert) + 1);
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
    DCC_START_CALL(GLESv2_glScissor, 4, sizeof(x) + sizeof(y)
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

GL_APICALL void GL_APIENTRY glShaderBinary (GLsizei count, const GLuint *shaders,
    GLenum binaryformat, const void *binary, GLsizei length)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glShaderBinary, 5, sizeof(count) + sizeof(shaders) + sizeof(binaryformat)
        + sizeof(binary) + sizeof(length) + count*sizeof(*shaders) + length + 1);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(shaders, 1);
    DCC_ADD_ARG(binaryformat, 0);
    DCC_ADD_ARG(binary, 1);
    DCC_ADD_ARG(length, 0);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(shaders, count*sizeof(*shaders), 1);
    DCC_ADD_APTR_MEM(binary, length, 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glShaderSource (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glShaderSource, 4, sizeof(shader) + sizeof(count) + sizeof(string)
        + sizeof(length) + count*(sizeof(*length) + sizeof(string) + 80) +  1);
    DCC_ADD_ARG(shader, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(string, 2);
    DCC_ADD_ARG(length, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(length, count*sizeof(*length), 3);
    DCC_ADD_MEM_ARR(string, count, length, 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glStencilFunc, 3, sizeof(func) + sizeof(ref) + sizeof(mask) + 1);
    DCC_ADD_ARG(func, 0);
    DCC_ADD_ARG(ref, 0);
    DCC_ADD_ARG(mask, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glStencilFuncSeparate, 4, sizeof(face) + sizeof(func) + sizeof(ref) + sizeof(mask) + 1);
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(func, 0);
    DCC_ADD_ARG(ref, 0);
    DCC_ADD_ARG(mask, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glStencilMask (GLuint mask)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glStencilMask, 3, sizeof(mask) + 1);
    DCC_ADD_ARG(mask, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glStencilMaskSeparate, 2, sizeof(face) + sizeof(mask) + 1);
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(mask, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glStencilOp, 3, sizeof(fail) + sizeof(zfail) + sizeof(zpass) + 1);
    DCC_ADD_ARG(fail, 0);
    DCC_ADD_ARG(zfail, 0);
    DCC_ADD_ARG(zpass, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glStencilOpSeparate, 4, sizeof(face) + sizeof(sfail) + sizeof(dpfail)
        + sizeof(dppass) + 1);
    DCC_ADD_ARG(face, 0);
    DCC_ADD_ARG(sfail, 0);
    DCC_ADD_ARG(dpfail, 0);
    DCC_ADD_ARG(dppass, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width,
    GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glTexImage2D, 9, sizeof(target) + sizeof(level) + sizeof(internalformat)
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
    DCC_START_CALL(GLESv2_glTexParameterf, 3, sizeof(target) + sizeof(pname) + sizeof(param) + 1);
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
    DCC_START_CALL(GLESv2_glTexParameterfv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glTexParameteri, 3, sizeof(target) + sizeof(pname) + sizeof(param) + 1);
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
    DCC_START_CALL(GLESv2_glTexParameteriv, 3, sizeof(target) + sizeof(pname) + sizeof(params)
        + sizeof(*params) + 1);
    DCC_ADD_ARG(target, 0);
    DCC_ADD_ARG(pname, 0);
    DCC_ADD_ARG(params, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(params, sizeof(*params), 2);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(params, sizeof(*params), 2);
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glTexSubImage2D, 9, sizeof(target) + sizeof(level) + sizeof(xoffset)
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


GL_APICALL void GL_APIENTRY glUniform1f (GLint location, GLfloat v0)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform1f, 2, sizeof(location) + sizeof(v0) + 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(v0, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform1fv (GLint location, GLsizei count, const GLfloat *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform1fv, 3, sizeof(location) + sizeof(count) + sizeof(value)
        + count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, count*sizeof(*value), 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform1i (GLint location, GLint v0)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform1i, 2, sizeof(location) + sizeof(v0) + 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(v0, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform1iv (GLint location, GLsizei count, const GLint *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform1iv, 3, sizeof(location) + sizeof(count) + sizeof(value)
        + count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, count*sizeof(*value), 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform2f, 3, sizeof(location) + 2*sizeof(v0) + 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(v0, 0);
    DCC_ADD_ARG(v1, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform2fv (GLint location, GLsizei count, const GLfloat *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform2fv, 3, sizeof(location) + sizeof(count) + sizeof(value)
        + 2*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 2*count*sizeof(*value), 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform2i, 3, sizeof(location) + 2*sizeof(v0) + 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(v0, 0);
    DCC_ADD_ARG(v1, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform2iv (GLint location, GLsizei count, const GLint *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform2iv, 3, sizeof(location) + sizeof(count) + sizeof(value)
        + 2*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 2*count*sizeof(*value), 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform3f, 4, sizeof(location) + 3*sizeof(v0) + 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(v0, 0);
    DCC_ADD_ARG(v1, 0);
    DCC_ADD_ARG(v2, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform3fv (GLint location, GLsizei count, const GLfloat *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform3fv, 3, sizeof(location) + sizeof(count) + sizeof(value)
        + 3*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 3*count*sizeof(*value), 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform3i, 4, sizeof(location) + 3*sizeof(v0) + 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(v0, 0);
    DCC_ADD_ARG(v1, 0);
    DCC_ADD_ARG(v2, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform3iv (GLint location, GLsizei count, const GLint *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform3iv, 3, sizeof(location) + sizeof(count) + sizeof(value)
        + 3*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 3*count*sizeof(*value), 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform4f, 5, sizeof(location) + 4*sizeof(v0) + 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(v0, 0);
    DCC_ADD_ARG(v1, 0);
    DCC_ADD_ARG(v2, 0);
    DCC_ADD_ARG(v3, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform4fv (GLint location, GLsizei count, const GLfloat *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform4fv, 3, sizeof(location) + sizeof(count) + sizeof(value)
        + 4*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 4*count*sizeof(*value), 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform4i, 5, sizeof(location) + 4*sizeof(v0) + 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(v0, 0);
    DCC_ADD_ARG(v1, 0);
    DCC_ADD_ARG(v2, 0);
    DCC_ADD_ARG(v3, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniform4iv (GLint location, GLsizei count, const GLint *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniform4iv, 3, sizeof(location) + sizeof(count) + sizeof(value)
        + 4*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 4*count*sizeof(*value), 2);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniformMatrix2fv, 4, sizeof(location) + sizeof(count)
        + sizeof(transpose) + sizeof(value) + 2*2*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(transpose, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 2*2*count*sizeof(*value), 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniformMatrix3fv, 4, sizeof(location) + sizeof(count)
        + sizeof(transpose) + sizeof(value) + 3*3*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(transpose, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 3*3*count*sizeof(*value), 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUniformMatrix4fv, 4, sizeof(location) + sizeof(count)
        + sizeof(transpose) + sizeof(value) + 4*4*count*sizeof(*value)+ 1);
    DCC_ADD_ARG(location, 0);
    DCC_ADD_ARG(count, 0);
    DCC_ADD_ARG(transpose, 0);
    DCC_ADD_ARG(value, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(value, 4*4*count*sizeof(*value), 3);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glUseProgram (GLuint program)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glUseProgram, 1, sizeof(program) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glValidateProgram (GLuint program)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glValidateProgram, 1, sizeof(program) + 1);
    DCC_ADD_ARG(program, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glVertexAttrib1f (GLuint index, GLfloat x)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttrib1f, 2, sizeof(index) + sizeof(x) + 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(x, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glVertexAttrib1fv (GLuint index, const GLfloat *v)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttrib1fv, 2, sizeof(index) + sizeof(v) + sizeof(*v)+ 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(v, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(v, sizeof(*v), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glVertexAttrib2f (GLuint index, GLfloat x, GLfloat y)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttrib2f, 3, sizeof(index) + 2*sizeof(x) + 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glVertexAttrib2fv (GLuint index, const GLfloat *v)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttrib2fv, 2, sizeof(index) + sizeof(v) + 2*sizeof(*v)+ 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(v, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(v, 2*sizeof(*v), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttrib3f, 4, sizeof(index) + 3*sizeof(x) + 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(z, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glVertexAttrib3fv (GLuint index, const GLfloat *v)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttrib3fv, 2, sizeof(index) + sizeof(v) + 3*sizeof(*v)+ 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(v, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(v, 3*sizeof(*v), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttrib4f, 5, sizeof(index) + 4*sizeof(x) + 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(z, 0);
    DCC_ADD_ARG(w, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glVertexAttrib4fv (GLuint index, const GLfloat *v)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttrib4fv, 2, sizeof(index) + sizeof(v) + 4*sizeof(*v)+ 1);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(v, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(v, 4*sizeof(*v), 1);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


GL_APICALL void GL_APIENTRY glVertexAttribPointer (GLuint index, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, const void *pointer)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glVertexAttribPointer, 6, sizeof(index) + sizeof(size) + sizeof(type)
        + sizeof(normalized) + sizeof(stride) + sizeof(pointer)
        + (((long)pointer < 256)?0:(4<<10)) + 16);
    DCC_ADD_ARG(index, 0);
    DCC_ADD_ARG(size, 0);
    DCC_ADD_ARG(type, 0);
    DCC_ADD_ARG(normalized, 0);
    DCC_ADD_ARG(stride, 0);
    DCC_ADD_ARG(pointer, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(pointer, (((long)pointer < 256)?0:(4<<10)), 5);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

GL_APICALL void GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(GLESv2_glViewport, 4, 2*sizeof(x) + 2*sizeof(width) + 1);
    DCC_ADD_ARG(x, 0);
    DCC_ADD_ARG(y, 0);
    DCC_ADD_ARG(width, 0);
    DCC_ADD_ARG(height, 0);
    DCC_ARG_OVER();
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}


