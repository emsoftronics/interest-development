/*
 * =====================================================================================
 *
 *       Filename:  glesenum.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Friday 25 January 2019 01:30:14  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish22@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __GLESENUM_H__
#define __GLESENUM_H__
#define GL_STRLEN(s) (((s)==NULL)?0:strlen(s))

typedef enum {
GLESv2_glActiveTexture = 0x200,
GLESv2_glBindBuffer,
GLESv2_glBindTexture,
GLESv2_glBlendFunc,
GLESv2_glBufferData,
GLESv2_glBufferSubData,
GLESv2_glClear,
GLESv2_glClearColor,
GLESv2_glClearDepthf,
GLESv2_glClearStencil,
GLESv2_glColorMask,
GLESv2_glCompressedTexImage2D,
GLESv2_glCompressedTexSubImage2D,
GLESv2_glCopyTexImage2D,
GLESv2_glCopyTexSubImage2D,
GLESv2_glCullFace,
GLESv2_glDeleteBuffers,
GLESv2_glDeleteTextures,
GLESv2_glDepthFunc,
GLESv2_glDepthMask,
GLESv2_glDepthRangef,
GLESv2_glDisable,
GLESv2_glDrawArrays,
GLESv2_glDrawElements,
GLESv2_glEnable,
GLESv2_glFinish,
GLESv2_glFlush,
GLESv2_glFrontFace,
GLESv2_glGenBuffers,
GLESv2_glGenTextures,
GLESv2_glGetBooleanv,
GLESv2_glGetBufferParameteriv,
GLESv2_glGetError,
GLESv2_glGetFloatv,
GLESv2_glGetIntegerv,
GLESv2_glGetString,
GLESv2_glGetTexParameterfv,
GLESv2_glGetTexParameteriv,
GLESv2_glHint,
GLESv2_glIsBuffer,
GLESv2_glIsEnabled,
GLESv2_glIsTexture,
GLESv2_glLineWidth,
GLESv2_glPixelStorei,
GLESv2_glPolygonOffset,
GLESv2_glReadPixels,
GLESv2_glSampleCoverage,
GLESv2_glScissor,
GLESv2_glStencilFunc,
GLESv2_glStencilMask,
GLESv2_glStencilOp,
GLESv2_glTexImage2D,
GLESv2_glTexParameterf,
GLESv2_glTexParameterfv,
GLESv2_glTexParameteri,
GLESv2_glTexParameteriv,
GLESv2_glTexSubImage2D,
GLESv2_glViewport,
/***********Different functions from GLESv1 ********************* */
GLESv2_glAttachShader,
GLESv2_glBindAttribLocation,
GLESv2_glBindFramebuffer,
GLESv2_glBindRenderbuffer,
GLESv2_glBlendColor,
GLESv2_glBlendEquation,
GLESv2_glBlendEquationSeparate,
GLESv2_glBlendFuncSeparate,
GLESv2_glCheckFramebufferStatus,
GLESv2_glCompileShader,
GLESv2_glCreateProgram,
GLESv2_glCreateShader,
GLESv2_glDeleteFramebuffers,
GLESv2_glDeleteProgram,
GLESv2_glDeleteRenderbuffers,
GLESv2_glDeleteShader,
GLESv2_glDetachShader,
GLESv2_glDisableVertexAttribArray,
GLESv2_glEnableVertexAttribArray,
GLESv2_glFramebufferRenderbuffer,
GLESv2_glFramebufferTexture2D,
GLESv2_glGenerateMipmap,
GLESv2_glGenFramebuffers,
GLESv2_glGenRenderbuffers,
GLESv2_glGetActiveAttrib,
GLESv2_glGetActiveUniform,
GLESv2_glGetAttachedShaders,
GLESv2_glGetAttribLocation,
GLESv2_glGetFramebufferAttachmentParameteriv,
GLESv2_glGetProgramInfoLog,
GLESv2_glGetProgramiv,
GLESv2_glGetRenderbufferParameteriv,
GLESv2_glGetShaderInfoLog,
GLESv2_glGetShaderiv,
GLESv2_glGetShaderPrecisionFormat,
GLESv2_glGetShaderSource,
GLESv2_glGetUniformfv,
GLESv2_glGetUniformiv,
GLESv2_glGetUniformLocation,
GLESv2_glGetVertexAttribfv,
GLESv2_glGetVertexAttribiv,
GLESv2_glGetVertexAttribPointerv,
GLESv2_glIsFramebuffer,
GLESv2_glIsProgram,
GLESv2_glIsRenderbuffer,
GLESv2_glIsShader,
GLESv2_glLinkProgram,
GLESv2_glReleaseShaderCompiler,
GLESv2_glRenderbufferStorage,
GLESv2_glShaderBinary,
GLESv2_glShaderSource,
GLESv2_glStencilFuncSeparate,
GLESv2_glStencilMaskSeparate,
GLESv2_glStencilOpSeparate,
GLESv2_glUniform1f,
GLESv2_glUniform1fv,
GLESv2_glUniform1i,
GLESv2_glUniform1iv,
GLESv2_glUniform2f,
GLESv2_glUniform2fv,
GLESv2_glUniform2i,
GLESv2_glUniform2iv,
GLESv2_glUniform3f,
GLESv2_glUniform3fv,
GLESv2_glUniform3i,
GLESv2_glUniform3iv,
GLESv2_glUniform4f,
GLESv2_glUniform4fv,
GLESv2_glUniform4i,
GLESv2_glUniform4iv,
GLESv2_glUniformMatrix2fv,
GLESv2_glUniformMatrix3fv,
GLESv2_glUniformMatrix4fv,
GLESv2_glUseProgram,
GLESv2_glValidateProgram,
GLESv2_glVertexAttrib1f,
GLESv2_glVertexAttrib1fv,
GLESv2_glVertexAttrib2f,
GLESv2_glVertexAttrib2fv,
GLESv2_glVertexAttrib3f,
GLESv2_glVertexAttrib3fv,
GLESv2_glVertexAttrib4f,
GLESv2_glVertexAttrib4fv,
GLESv2_glVertexAttribPointer
} gles2_t;


typedef enum {
GLESv1_glActiveTexture = 0x100,
GLESv1_glBindBuffer,
GLESv1_glBindTexture,
GLESv1_glBlendFunc,
GLESv1_glBufferData,
GLESv1_glBufferSubData,
GLESv1_glClear,
GLESv1_glClearColor,
GLESv1_glClearDepthf,
GLESv1_glClearStencil,
GLESv1_glColorMask,
GLESv1_glCompressedTexImage2D,
GLESv1_glCompressedTexSubImage2D,
GLESv1_glCopyTexImage2D,
GLESv1_glCopyTexSubImage2D,
GLESv1_glCullFace,
GLESv1_glDeleteBuffers,
GLESv1_glDeleteTextures,
GLESv1_glDepthFunc,
GLESv1_glDepthMask,
GLESv1_glDepthRangef,
GLESv1_glDisable,
GLESv1_glDrawArrays,
GLESv1_glDrawElements,
GLESv1_glEnable,
GLESv1_glFinish,
GLESv1_glFlush,
GLESv1_glFrontFace,
GLESv1_glGenBuffers,
GLESv1_glGenTextures,
GLESv1_glGetBooleanv,
GLESv1_glGetBufferParameteriv,
GLESv1_glGetError,
GLESv1_glGetFloatv,
GLESv1_glGetIntegerv,
GLESv1_glGetString,
GLESv1_glGetTexParameterfv,
GLESv1_glGetTexParameteriv,
GLESv1_glHint,
GLESv1_glIsBuffer,
GLESv1_glIsEnabled,
GLESv1_glIsTexture,
GLESv1_glLineWidth,
GLESv1_glPixelStorei,
GLESv1_glPolygonOffset,
GLESv1_glReadPixels,
GLESv1_glSampleCoverage,
GLESv1_glScissor,
GLESv1_glStencilFunc,
GLESv1_glStencilMask,
GLESv1_glStencilOp,
GLESv1_glTexImage2D,
GLESv1_glTexParameterf,
GLESv1_glTexParameterfv,
GLESv1_glTexParameteri,
GLESv1_glTexParameteriv,
GLESv1_glTexSubImage2D,
GLESv1_glViewport,
/****** Different functions which are not resembling with GLESv2 *********/
GLESv1_glAlphaFunc,
GLESv1_glAlphaFuncx,
GLESv1_glClearColorx,
GLESv1_glClearDepthx,
GLESv1_glClientActiveTexture,
GLESv1_glClipPlanef,
GLESv1_glClipPlanex,
GLESv1_glColor4f,
GLESv1_glColor4ub,
GLESv1_glColor4x,
GLESv1_glColorPointer,
GLESv1_glDepthRangex,
GLESv1_glDisableClientState,
GLESv1_glEnableClientState,
GLESv1_glFogf,
GLESv1_glFogfv,
GLESv1_glFogx,
GLESv1_glFogxv,
GLESv1_glFrustumf,
GLESv1_glFrustumx,
GLESv1_glGetClipPlanef,
GLESv1_glGetClipPlanex,
GLESv1_glGetFixedv,
GLESv1_glGetLightfv,
GLESv1_glGetLightxv,
GLESv1_glGetMaterialfv,
GLESv1_glGetMaterialxv,
GLESv1_glGetPointerv,
GLESv1_glGetTexEnvfv,
GLESv1_glGetTexEnviv,
GLESv1_glGetTexEnvxv,
GLESv1_glGetTexParameterxv,
GLESv1_glLightf,
GLESv1_glLightfv,
GLESv1_glLightModelf,
GLESv1_glLightModelfv,
GLESv1_glLightModelx,
GLESv1_glLightModelxv,
GLESv1_glLightx,
GLESv1_glLightxv,
GLESv1_glLineWidthx,
GLESv1_glLoadIdentity,
GLESv1_glLoadMatrixf,
GLESv1_glLoadMatrixx,
GLESv1_glLogicOp,
GLESv1_glMaterialf,
GLESv1_glMaterialfv,
GLESv1_glMaterialx,
GLESv1_glMaterialxv,
GLESv1_glMatrixMode,
GLESv1_glMultiTexCoord4f,
GLESv1_glMultiTexCoord4x,
GLESv1_glMultMatrixf,
GLESv1_glMultMatrixx,
GLESv1_glNormal3f,
GLESv1_glNormal3x,
GLESv1_glNormalPointer,
GLESv1_glOrthof,
GLESv1_glOrthox,
GLESv1_glPointParameterf,
GLESv1_glPointParameterfv,
GLESv1_glPointParameterx,
GLESv1_glPointParameterxv,
GLESv1_glPointSize,
GLESv1_glPointSizePointerOES,
GLESv1_glPointSizex,
GLESv1_glPolygonOffsetx,
GLESv1_glPopMatrix,
GLESv1_glPushMatrix,
GLESv1_glRotatef,
GLESv1_glRotatex,
GLESv1_glSampleCoveragex,
GLESv1_glScalef,
GLESv1_glScalex,
GLESv1_glShadeModel,
GLESv1_glTexCoordPointer,
GLESv1_glTexEnvf,
GLESv1_glTexEnvfv,
GLESv1_glTexEnvi,
GLESv1_glTexEnviv,
GLESv1_glTexEnvx,
GLESv1_glTexEnvxv,
GLESv1_glTexParameterx,
GLESv1_glTexParameterxv,
GLESv1_glTranslatef,
GLESv1_glTranslatex,
GLESv1_glVertexPointer
} gles1_t;


static inline int gles_sizeof(int type)
{
    switch(type&0xf)
    {
        case 0x0:   return sizeof(signed char);
        case 0x1:   return sizeof(unsigned char);
        case 0x2:   return sizeof(short);
        case 0x3:   return sizeof(unsigned short);
        case 0x4:   return sizeof(int);
        case 0x5:   return sizeof(unsigned int);
        case 0x6:   return sizeof(float);
        default:    return sizeof(void *);
    }
    return 0;
}

static inline int gles_pixel_channels(int format, int type)
{
    switch (type) {
        case 8363:
        case 8033:
        case 8034: return 2;
        break;
    }

    switch(format) {
        case 0x8284:
        case 0x8285:
        case 0x1801:
        case 0x1802:
        case 0x1902:
        case 0x1903:
        case 0x1904:
        case 0x1905:
        case 0x1906: return 1;
            break;
        case 0x84f9:
        case 0x8227: return 2;
            break;
        case 0x80e0:
        case 0x1907: return 3;
            break;
        default: return 4;
    }
    return 4;
}


#endif /* __GLESENUM_H__ */
