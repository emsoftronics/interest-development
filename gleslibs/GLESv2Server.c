
#include "glesenum.h"
#include "vmcutil.h"
#include <GLES2/gl2.h>

#define G_EN(_idx)          *((GLenum *)args[_idx])
#define G_UI(_idx)          *((GLuint *)args[_idx])
#define G_FL(_idx)          *((GLfloat *)args[_idx])
#define G_CH(_idx)          *((GLchar *)args[_idx])
#define G_IN(_idx)          *((GLint *)args[_idx])
#define G_ST(_idx)          *((GLshort *)args[_idx])
#define G_US(_idx)          *((GLushort *)args[_idx])
#define G_SIP(_idx)          *((GLsizeiptr *)args[_idx])
#define G_SII(_idx)          *((GLsizei *)args[_idx])
#define G_IPT(_idx)          *((GLintptr *)args[_idx])

static void fcall_handler(int fid, int argc, void **args, void*ret, uint32_t *retsize)
{
    switch (fid) {
        case GLESv2_glActiveTexture:
            glActiveTexture (G_EN(0));
            break;
        case GLESv2_glAttachShader:
            glAttachShader (G_UI(0), G_UI(1));
            break;
        case GLESv2_glBindAttribLocation:
            void glBindAttribLocation (GLuint program, GLuint index, const GLchar *name);
            break;
        case GLESv2_glBindBuffer:
            void glBindBuffer (GLenum target, GLuint buffer);
            break;
        case GLESv2_glBindFramebuffer:
            void glBindFramebuffer (GLenum target, GLuint framebuffer);
            break;
        case GLESv2_glBindRenderbuffer:
            void glBindRenderbuffer (GLenum target, GLuint renderbuffer);
            break;
        case GLESv2_glBindTexture:
            void glBindTexture (GLenum target, GLuint texture);
            break;
        case GLESv2_glBlendColor:
            void glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
            break;
        case GLESv2_glBlendEquation:
            void glBlendEquation (GLenum mode);
            break;
        case GLESv2_glBlendEquationSeparate:
            void glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
            break;
        case GLESv2_glBlendFunc:
            void glBlendFunc (GLenum sfactor, GLenum dfactor);
            break;
        case GLESv2_glBlendFuncSeparate:
            void glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
            break;
        case GLESv2_glBufferData:
            void glBufferData (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
            break;
        case GLESv2_glBufferSubData:
            void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
            break;
        case GLESv2_glCheckFramebufferStatus:
            GLenum glCheckFramebufferStatus (GLenum target);
            break;
        case GLESv2_glClear:
            void glClear (GLbitfield mask);
            break;
        case GLESv2_glClearColor:
            void glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
            break;
        case GLESv2_glClearDepthf:
            void glClearDepthf (GLfloat d);
            break;
        case GLESv2_glClearStencil:
            void glClearStencil (GLint s);
            break;
        case GLESv2_glColorMask:
            void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
            break;
        case GLESv2_glCompileShader:
            void glCompileShader (GLuint shader);
            break;
        case GLESv2_glCompressedTexImage2D:
            void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
            break;
        case GLESv2_glCompressedTexSubImage2D:
            void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
            break;
        case GLESv2_glCopyTexImage2D:
            void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
            break;
        case GLESv2_glCopyTexSubImage2D:
            void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
            break;
        case GLESv2_glCreateProgram:
            GLuint glCreateProgram (void);
            break;
        case GLESv2_glCreateShader:
            GLuint glCreateShader (GLenum type);
            break;
        case GLESv2_glCullFace:
            void glCullFace (GLenum mode);
            break;
        case GLESv2_glDeleteBuffers:
            void glDeleteBuffers (GLsizei n, const GLuint *buffers);
            break;
        case GLESv2_glDeleteFramebuffers:
            void glDeleteFramebuffers (GLsizei n, const GLuint *framebuffers);
            break;
        case GLESv2_glDeleteProgram:
            void glDeleteProgram (GLuint program);
            break;
        case GLESv2_glDeleteRenderbuffers:
            void glDeleteRenderbuffers (GLsizei n, const GLuint *renderbuffers);
            break;
        case GLESv2_glDeleteShader:
            void glDeleteShader (GLuint shader);
            break;
        case GLESv2_glDeleteTextures:
            void glDeleteTextures (GLsizei n, const GLuint *textures);
            break;
        case GLESv2_glDepthFunc:
            void glDepthFunc (GLenum func);
            break;
        case GLESv2_glDepthMask:
            void glDepthMask (GLboolean flag);
            break;
        case GLESv2_glDepthRangef:
            void glDepthRangef (GLfloat n, GLfloat f);
            break;
        case GLESv2_glDetachShader:
            void glDetachShader (GLuint program, GLuint shader);
            break;
        case GLESv2_glDisable:
            void glDisable (GLenum cap);
            break;
        case GLESv2_glDisableVertexAttribArray:
            void glDisableVertexAttribArray (GLuint index);
            break;
        case GLESv2_glDrawArrays:
            void glDrawArrays (GLenum mode, GLint first, GLsizei count);
            break;
        case GLESv2_glDrawElements:
            void glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices);
            break;
        case GLESv2_glEnable:
            void glEnable (GLenum cap);
            break;
        case GLESv2_glEnableVertexAttribArray:
            void glEnableVertexAttribArray (GLuint index);
            break;
        case GLESv2_glFinish:
            void glFinish (void);
            break;
        case GLESv2_glFlush:
            void glFlush (void);
            break;
        case GLESv2_glFramebufferRenderbuffer:
            void glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
            break;
        case GLESv2_glFramebufferTexture2D:
            void glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
            break;
        case GLESv2_glFrontFace:
            void glFrontFace (GLenum mode);
            break;
        case GLESv2_glGenBuffers:
            void glGenBuffers (GLsizei n, GLuint *buffers);
            break;
        case GLESv2_glGenerateMipmap:
            void glGenerateMipmap (GLenum target);
            break;
        case GLESv2_glGenFramebuffers:
            void glGenFramebuffers (GLsizei n, GLuint *framebuffers);
            break;
        case GLESv2_glGenRenderbuffers:
            void glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
            break;
        case GLESv2_glGenTextures:
            void glGenTextures (GLsizei n, GLuint *textures);
            break;
        case GLESv2_glGetActiveAttrib:
            void glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
            break;
        case GLESv2_glGetActiveUniform:
            void glGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
            break;
        case GLESv2_glGetAttachedShaders:
            void glGetAttachedShaders (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
            break;
        case GLESv2_glGetAttribLocation:
            GLint glGetAttribLocation (GLuint program, const GLchar *name);
            break;
        case GLESv2_glGetBooleanv:
            void glGetBooleanv (GLenum pname, GLboolean *data);
            break;
        case GLESv2_glGetBufferParameteriv:
            void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
            break;
        case GLESv2_glGetError:
            GLenum glGetError (void);
            break;
        case GLESv2_glGetFloatv:
            void glGetFloatv (GLenum pname, GLfloat *data);
            break;
        case GLESv2_glGetFramebufferAttachmentParameteriv:
            void glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
            break;
        case GLESv2_glGetIntegerv:
            void glGetIntegerv (GLenum pname, GLint *data);
            break;
        case GLESv2_glGetProgramiv:
            void glGetProgramiv (GLuint program, GLenum pname, GLint *params);
            break;
        case GLESv2_glGetProgramInfoLog:
            void glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
            break;
        case GLESv2_glGetRenderbufferParameteriv:
            void glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
            break;
        case GLESv2_glGetShaderiv:
            void glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
            break;
        case GLESv2_glGetShaderInfoLog:
            void glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
            break;
        case GLESv2_glGetShaderPrecisionFormat:
            void glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
            break;
        case GLESv2_glGetShaderSource:
            void glGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
            break;
        case GLESv2_*GL_APIENTRY:
            const *GL_APIENTRY glGetString (GLenum name);
            break;
        case GLESv2_glGetTexParameterfv:
            void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
            break;
        case GLESv2_glGetTexParameteriv:
            void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
            break;
        case GLESv2_glGetUniformfv:
            void glGetUniformfv (GLuint program, GLint location, GLfloat *params);
            break;
        case GLESv2_glGetUniformiv:
            void glGetUniformiv (GLuint program, GLint location, GLint *params);
            break;
        case GLESv2_glGetUniformLocation:
            GLint glGetUniformLocation (GLuint program, const GLchar *name);
            break;
        case GLESv2_glGetVertexAttribfv:
            void glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params);
            break;
        case GLESv2_glGetVertexAttribiv:
            void glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params);
            break;
        case GLESv2_glGetVertexAttribPointerv:
            void glGetVertexAttribPointerv (GLuint index, GLenum pname, void **pointer);
            break;
        case GLESv2_glHint:
            void glHint (GLenum target, GLenum mode);
            break;
        case GLESv2_glIsBuffer:
            GLboolean glIsBuffer (GLuint buffer);
            break;
        case GLESv2_glIsEnabled:
            GLboolean glIsEnabled (GLenum cap);
            break;
        case GLESv2_glIsFramebuffer:
            GLboolean glIsFramebuffer (GLuint framebuffer);
            break;
        case GLESv2_glIsProgram:
            GLboolean glIsProgram (GLuint program);
            break;
        case GLESv2_glIsRenderbuffer:
            GLboolean glIsRenderbuffer (GLuint renderbuffer);
            break;
        case GLESv2_glIsShader:
            GLboolean glIsShader (GLuint shader);
            break;
        case GLESv2_glIsTexture:
            GLboolean glIsTexture (GLuint texture);
            break;
        case GLESv2_glLineWidth:
            void glLineWidth (GLfloat width);
            break;
        case GLESv2_glLinkProgram:
            void glLinkProgram (GLuint program);
            break;
        case GLESv2_glPixelStorei:
            void glPixelStorei (GLenum pname, GLint param);
            break;
        case GLESv2_glPolygonOffset:
            void glPolygonOffset (GLfloat factor, GLfloat units);
            break;
        case GLESv2_glReadPixels:
            void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
            break;
        case GLESv2_glReleaseShaderCompiler:
            void glReleaseShaderCompiler (void);
            break;
        case GLESv2_glRenderbufferStorage:
            void glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
            break;
        case GLESv2_glSampleCoverage:
            void glSampleCoverage (GLfloat value, GLboolean invert);
            break;
        case GLESv2_glScissor:
            void glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
            break;
        case GLESv2_glShaderBinary:
            void glShaderBinary (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
            break;
        case GLESv2_glShaderSource:
            void glShaderSource (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
            break;
        case GLESv2_glStencilFunc:
            void glStencilFunc (GLenum func, GLint ref, GLuint mask);
            break;
        case GLESv2_glStencilFuncSeparate:
            void glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
            break;
        case GLESv2_glStencilMask:
            void glStencilMask (GLuint mask);
            break;
        case GLESv2_glStencilMaskSeparate:
            void glStencilMaskSeparate (GLenum face, GLuint mask);
            break;
        case GLESv2_glStencilOp:
            void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
            break;
        case GLESv2_glStencilOpSeparate:
            void glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
            break;
        case GLESv2_glTexImage2D:
            void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
            break;
        case GLESv2_glTexParameterf:
            void glTexParameterf (GLenum target, GLenum pname, GLfloat param);
            break;
        case GLESv2_glTexParameterfv:
            void glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
            break;
        case GLESv2_glTexParameteri:
            void glTexParameteri (GLenum target, GLenum pname, GLint param);
            break;
        case GLESv2_glTexParameteriv:
            void glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
            break;
        case GLESv2_glTexSubImage2D:
            void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
            break;
        case GLESv2_glUniform1f:
            void glUniform1f (GLint location, GLfloat v0);
            break;
        case GLESv2_glUniform1fv:
            void glUniform1fv (GLint location, GLsizei count, const GLfloat *value);
            break;
        case GLESv2_glUniform1i:
            void glUniform1i (GLint location, GLint v0);
            break;
        case GLESv2_glUniform1iv:
            void glUniform1iv (GLint location, GLsizei count, const GLint *value);
            break;
        case GLESv2_glUniform2f:
            void glUniform2f (GLint location, GLfloat v0, GLfloat v1);
            break;
        case GLESv2_glUniform2fv:
            void glUniform2fv (GLint location, GLsizei count, const GLfloat *value);
            break;
        case GLESv2_glUniform2i:
            void glUniform2i (GLint location, GLint v0, GLint v1);
            break;
        case GLESv2_glUniform2iv:
            void glUniform2iv (GLint location, GLsizei count, const GLint *value);
            break;
        case GLESv2_glUniform3f:
            void glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
            break;
        case GLESv2_glUniform3fv:
            void glUniform3fv (GLint location, GLsizei count, const GLfloat *value);
            break;
        case GLESv2_glUniform3i:
            void glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
            break;
        case GLESv2_glUniform3iv:
            void glUniform3iv (GLint location, GLsizei count, const GLint *value);
            break;
        case GLESv2_glUniform4f:
            void glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
            break;
        case GLESv2_glUniform4fv:
            void glUniform4fv (GLint location, GLsizei count, const GLfloat *value);
            break;
        case GLESv2_glUniform4i:
            void glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
            break;
        case GLESv2_glUniform4iv:
            void glUniform4iv (GLint location, GLsizei count, const GLint *value);
            break;
        case GLESv2_glUniformMatrix2fv:
            void glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
            break;
        case GLESv2_glUniformMatrix3fv:
            void glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
            break;
        case GLESv2_glUniformMatrix4fv:
            void glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
            break;
        case GLESv2_glUseProgram:
            void glUseProgram (GLuint program);
            break;
        case GLESv2_glValidateProgram:
            void glValidateProgram (GLuint program);
            break;
        case GLESv2_glVertexAttrib1f:
            void glVertexAttrib1f (GLuint index, GLfloat x);
            break;
        case GLESv2_glVertexAttrib1fv:
            void glVertexAttrib1fv (GLuint index, const GLfloat *v);
            break;
        case GLESv2_glVertexAttrib2f:
            void glVertexAttrib2f (GLuint index, GLfloat x, GLfloat y);
            break;
        case GLESv2_glVertexAttrib2fv:
            void glVertexAttrib2fv (GLuint index, const GLfloat *v);
            break;
        case GLESv2_glVertexAttrib3f:
            void glVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z);
            break;
        case GLESv2_glVertexAttrib3fv:
            void glVertexAttrib3fv (GLuint index, const GLfloat *v);
            break;
        case GLESv2_glVertexAttrib4f:
            void glVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
            break;
        case GLESv2_glVertexAttrib4fv:
            void glVertexAttrib4fv (GLuint index, const GLfloat *v);
            break;
        case GLESv2_glVertexAttribPointer:
            void glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
            break;
        case GLESv2_glViewport:
            void glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
            break;
    }
}
