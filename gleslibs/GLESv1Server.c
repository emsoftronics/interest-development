
#include "glesenum.h"
#include "vmcutil.h"
#include <GLES/gl.h>

static void fcall_handler(int fid, int argc, void **args, void*ret, uint32_t *retsize)
{
    switch (fid) {
        case GLESv1_glAlphaFunc:
            void glAlphaFunc (GLenum func, GLclampf ref);
            break;
        case GLESv1_glClearColor:
            void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
            break;
        case GLESv1_glClearDepthf:
            void glClearDepthf (GLclampf depth);
            break;
        case GLESv1_glClipPlanef:
            void glClipPlanef (GLenum plane, const GLfloat *equation);
            break;
        case GLESv1_glColor4f:
            void glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
            break;
        case GLESv1_glDepthRangef:
            void glDepthRangef (GLclampf zNear, GLclampf zFar);
            break;
        case GLESv1_glFogf:
            void glFogf (GLenum pname, GLfloat param);
            break;
        case GLESv1_glFogfv:
            void glFogfv (GLenum pname, const GLfloat *params);
            break;
        case GLESv1_glFrustumf:
            void glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
            break;
        case GLESv1_glGetClipPlanef:
            void glGetClipPlanef (GLenum pname, GLfloat eqn[4]);
            break;
        case GLESv1_glGetFloatv:
            void glGetFloatv (GLenum pname, GLfloat *params);
            break;
        case GLESv1_glGetLightfv:
            void glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
            break;
        case GLESv1_glGetMaterialfv:
            void glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
            break;
        case GLESv1_glGetTexEnvfv:
            void glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params);
            break;
        case GLESv1_glGetTexParameterfv:
            void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
            break;
        case GLESv1_glLightModelf:
            void glLightModelf (GLenum pname, GLfloat param);
            break;
        case GLESv1_glLightModelfv:
            void glLightModelfv (GLenum pname, const GLfloat *params);
            break;
        case GLESv1_glLightf:
            void glLightf (GLenum light, GLenum pname, GLfloat param);
            break;
        case GLESv1_glLightfv:
            void glLightfv (GLenum light, GLenum pname, const GLfloat *params);
            break;
        case GLESv1_glLineWidth:
            void glLineWidth (GLfloat width);
            break;
        case GLESv1_glLoadMatrixf:
            void glLoadMatrixf (const GLfloat *m);
            break;
        case GLESv1_glMaterialf:
            void glMaterialf (GLenum face, GLenum pname, GLfloat param);
            break;
        case GLESv1_glMaterialfv:
            void glMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
            break;
        case GLESv1_glMultMatrixf:
            void glMultMatrixf (const GLfloat *m);
            break;
        case GLESv1_glMultiTexCoord4f:
            void glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
            break;
        case GLESv1_glNormal3f:
            void glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
            break;
        case GLESv1_glOrthof:
            void glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
            break;
        case GLESv1_glPointParameterf:
            void glPointParameterf (GLenum pname, GLfloat param);
            break;
        case GLESv1_glPointParameterfv:
            void glPointParameterfv (GLenum pname, const GLfloat *params);
            break;
        case GLESv1_glPointSize:
            void glPointSize (GLfloat size);
            break;
        case GLESv1_glPolygonOffset:
            void glPolygonOffset (GLfloat factor, GLfloat units);
            break;
        case GLESv1_glRotatef:
            void glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
            break;
        case GLESv1_glScalef:
            void glScalef (GLfloat x, GLfloat y, GLfloat z);
            break;
        case GLESv1_glTexEnvf:
            void glTexEnvf (GLenum target, GLenum pname, GLfloat param);
            break;
        case GLESv1_glTexEnvfv:
            void glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params);
            break;
        case GLESv1_glTexParameterf:
            void glTexParameterf (GLenum target, GLenum pname, GLfloat param);
            break;
        case GLESv1_glTexParameterfv:
            void glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
            break;
        case GLESv1_glTranslatef:
            void glTranslatef (GLfloat x, GLfloat y, GLfloat z);
            break;
        case GLESv1_glActiveTexture:
            void glActiveTexture (GLenum texture);
            break;
        case GLESv1_glAlphaFuncx:
            void glAlphaFuncx (GLenum func, GLclampx ref);
            break;
        case GLESv1_glBindBuffer:
            void glBindBuffer (GLenum target, GLuint buffer);
            break;
        case GLESv1_glBindTexture:
            void glBindTexture (GLenum target, GLuint texture);
            break;
        case GLESv1_glBlendFunc:
            void glBlendFunc (GLenum sfactor, GLenum dfactor);
            break;
        case GLESv1_glBufferData:
            void glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
            break;
        case GLESv1_glBufferSubData:
            void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
            break;
        case GLESv1_glClear:
            void glClear (GLbitfield mask);
            break;
        case GLESv1_glClearColorx:
            void glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
            break;
        case GLESv1_glClearDepthx:
            void glClearDepthx (GLclampx depth);
            break;
        case GLESv1_glClearStencil:
            void glClearStencil (GLint s);
            break;
        case GLESv1_glClientActiveTexture:
            void glClientActiveTexture (GLenum texture);
            break;
        case GLESv1_glClipPlanex:
            void glClipPlanex (GLenum plane, const GLfixed *equation);
            break;
        case GLESv1_glColor4ub:
            void glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
            break;
        case GLESv1_glColor4x:
            void glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
            break;
        case GLESv1_glColorMask:
            void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
            break;
        case GLESv1_glColorPointer:
            void glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
            break;
        case GLESv1_glCompressedTexImage2D:
            void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
            break;
        case GLESv1_glCompressedTexSubImage2D:
            void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
            break;
        case GLESv1_glCopyTexImage2D:
            void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
            break;
        case GLESv1_glCopyTexSubImage2D:
            void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
            break;
        case GLESv1_glCullFace:
            void glCullFace (GLenum mode);
            break;
        case GLESv1_glDeleteBuffers:
            void glDeleteBuffers (GLsizei n, const GLuint *buffers);
            break;
        case GLESv1_glDeleteTextures:
            void glDeleteTextures (GLsizei n, const GLuint *textures);
            break;
        case GLESv1_glDepthFunc:
            void glDepthFunc (GLenum func);
            break;
        case GLESv1_glDepthMask:
            void glDepthMask (GLboolean flag);
            break;
        case GLESv1_glDepthRangex:
            void glDepthRangex (GLclampx zNear, GLclampx zFar);
            break;
        case GLESv1_glDisable:
            void glDisable (GLenum cap);
            break;
        case GLESv1_glDisableClientState:
            void glDisableClientState (GLenum array);
            break;
        case GLESv1_glDrawArrays:
            void glDrawArrays (GLenum mode, GLint first, GLsizei count);
            break;
        case GLESv1_glDrawElements:
            void glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
            break;
        case GLESv1_glEnable:
            void glEnable (GLenum cap);
            break;
        case GLESv1_glEnableClientState:
            void glEnableClientState (GLenum array);
            break;
        case GLESv1_glFinish:
            void glFinish (void);
            break;
        case GLESv1_glFlush:
            void glFlush (void);
            break;
        case GLESv1_glFogx:
            void glFogx (GLenum pname, GLfixed param);
            break;
        case GLESv1_glFogxv:
            void glFogxv (GLenum pname, const GLfixed *params);
            break;
        case GLESv1_glFrontFace:
            void glFrontFace (GLenum mode);
            break;
        case GLESv1_glFrustumx:
            void glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
            break;
        case GLESv1_glGetBooleanv:
            void glGetBooleanv (GLenum pname, GLboolean *params);
            break;
        case GLESv1_glGetBufferParameteriv:
            void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
            break;
        case GLESv1_glGetClipPlanex:
            void glGetClipPlanex (GLenum pname, GLfixed eqn[4]);
            break;
        case GLESv1_glGenBuffers:
            void glGenBuffers (GLsizei n, GLuint *buffers);
            break;
        case GLESv1_glGenTextures:
            void glGenTextures (GLsizei n, GLuint *textures);
            break;
        case GLESv1_glGetError:
            GLenum glGetError (void);
            break;
        case GLESv1_glGetFixedv:
            void glGetFixedv (GLenum pname, GLfixed *params);
            break;
        case GLESv1_glGetIntegerv:
            void glGetIntegerv (GLenum pname, GLint *params);
            break;
        case GLESv1_glGetLightxv:
            void glGetLightxv (GLenum light, GLenum pname, GLfixed *params);
            break;
        case GLESv1_glGetMaterialxv:
            void glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params);
            break;
        case GLESv1_glGetPointerv:
            void glGetPointerv (GLenum pname, GLvoid **params);
            break;
        case GLESv1_*:
            const * GL_APIENTRY glGetString (GLenum name);
            break;
        case GLESv1_glGetTexEnviv:
            void glGetTexEnviv (GLenum env, GLenum pname, GLint *params);
            break;
        case GLESv1_glGetTexEnvxv:
            void glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params);
            break;
        case GLESv1_glGetTexParameteriv:
            void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
            break;
        case GLESv1_glGetTexParameterxv:
            void glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params);
            break;
        case GLESv1_glHint:
            void glHint (GLenum target, GLenum mode);
            break;
        case GLESv1_glIsBuffer:
            GLboolean glIsBuffer (GLuint buffer);
            break;
        case GLESv1_glIsEnabled:
            GLboolean glIsEnabled (GLenum cap);
            break;
        case GLESv1_glIsTexture:
            GLboolean glIsTexture (GLuint texture);
            break;
        case GLESv1_glLightModelx:
            void glLightModelx (GLenum pname, GLfixed param);
            break;
        case GLESv1_glLightModelxv:
            void glLightModelxv (GLenum pname, const GLfixed *params);
            break;
        case GLESv1_glLightx:
            void glLightx (GLenum light, GLenum pname, GLfixed param);
            break;
        case GLESv1_glLightxv:
            void glLightxv (GLenum light, GLenum pname, const GLfixed *params);
            break;
        case GLESv1_glLineWidthx:
            void glLineWidthx (GLfixed width);
            break;
        case GLESv1_glLoadIdentity:
            void glLoadIdentity (void);
            break;
        case GLESv1_glLoadMatrixx:
            void glLoadMatrixx (const GLfixed *m);
            break;
        case GLESv1_glLogicOp:
            void glLogicOp (GLenum opcode);
            break;
        case GLESv1_glMaterialx:
            void glMaterialx (GLenum face, GLenum pname, GLfixed param);
            break;
        case GLESv1_glMaterialxv:
            void glMaterialxv (GLenum face, GLenum pname, const GLfixed *params);
            break;
        case GLESv1_glMatrixMode:
            void glMatrixMode (GLenum mode);
            break;
        case GLESv1_glMultMatrixx:
            void glMultMatrixx (const GLfixed *m);
            break;
        case GLESv1_glMultiTexCoord4x:
            void glMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
            break;
        case GLESv1_glNormal3x:
            void glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
            break;
        case GLESv1_glNormalPointer:
            void glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
            break;
        case GLESv1_glOrthox:
            void glOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
            break;
        case GLESv1_glPixelStorei:
            void glPixelStorei (GLenum pname, GLint param);
            break;
        case GLESv1_glPointParameterx:
            void glPointParameterx (GLenum pname, GLfixed param);
            break;
        case GLESv1_glPointParameterxv:
            void glPointParameterxv (GLenum pname, const GLfixed *params);
            break;
        case GLESv1_glPointSizex:
            void glPointSizex (GLfixed size);
            break;
        case GLESv1_glPolygonOffsetx:
            void glPolygonOffsetx (GLfixed factor, GLfixed units);
            break;
        case GLESv1_glPopMatrix:
            void glPopMatrix (void);
            break;
        case GLESv1_glPushMatrix:
            void glPushMatrix (void);
            break;
        case GLESv1_glReadPixels:
            void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
            break;
        case GLESv1_glRotatex:
            void glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
            break;
        case GLESv1_glSampleCoverage:
            void glSampleCoverage (GLclampf value, GLboolean invert);
            break;
        case GLESv1_glSampleCoveragex:
            void glSampleCoveragex (GLclampx value, GLboolean invert);
            break;
        case GLESv1_glScalex:
            void glScalex (GLfixed x, GLfixed y, GLfixed z);
            break;
        case GLESv1_glScissor:
            void glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
            break;
        case GLESv1_glShadeModel:
            void glShadeModel (GLenum mode);
            break;
        case GLESv1_glStencilFunc:
            void glStencilFunc (GLenum func, GLint ref, GLuint mask);
            break;
        case GLESv1_glStencilMask:
            void glStencilMask (GLuint mask);
            break;
        case GLESv1_glStencilOp:
            void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
            break;
        case GLESv1_glTexCoordPointer:
            void glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
            break;
        case GLESv1_glTexEnvi:
            void glTexEnvi (GLenum target, GLenum pname, GLint param);
            break;
        case GLESv1_glTexEnvx:
            void glTexEnvx (GLenum target, GLenum pname, GLfixed param);
            break;
        case GLESv1_glTexEnviv:
            void glTexEnviv (GLenum target, GLenum pname, const GLint *params);
            break;
        case GLESv1_glTexEnvxv:
            void glTexEnvxv (GLenum target, GLenum pname, const GLfixed *params);
            break;
        case GLESv1_glTexImage2D:
            void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
            break;
        case GLESv1_glTexParameteri:
            void glTexParameteri (GLenum target, GLenum pname, GLint param);
            break;
        case GLESv1_glTexParameterx:
            void glTexParameterx (GLenum target, GLenum pname, GLfixed param);
            break;
        case GLESv1_glTexParameteriv:
            void glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
            break;
        case GLESv1_glTexParameterxv:
            void glTexParameterxv (GLenum target, GLenum pname, const GLfixed *params);
            break;
        case GLESv1_glTexSubImage2D:
            void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
            break;
        case GLESv1_glTranslatex:
            void glTranslatex (GLfixed x, GLfixed y, GLfixed z);
            break;
        case GLESv1_glVertexPointer:
            void glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
            break;
        case GLESv1_glViewport:
            void glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
            break;
    }
}
