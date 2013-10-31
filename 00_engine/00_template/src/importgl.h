/* San Angeles Observation OpenGL ES version example
 * Copyright 2004-2005 Jetro Lauha
 * All rights reserved.
 * Web: http://iki.fi/jetro/
 *
 * This source is free software; you can redistribute it and/or
 * modify it under the terms of EITHER:
 *   (1) The GNU Lesser General Public License as published by the Free
 *       Software Foundation; either version 2.1 of the License, or (at
 *       your option) any later version. The text of the GNU Lesser
 *       General Public License is included with this source in the
 *       file LICENSE-LGPL.txt.
 *   (2) The BSD-style license that is included with this source in
 *       the file LICENSE-BSD.txt.
 *
 * This source is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files
 * LICENSE-LGPL.txt and LICENSE-BSD.txt for more details.
 *
 * $Id: importgl.h,v 1.4 2005/02/24 20:29:33 tonic Exp $
 * $Revision: 1.4 $
 */

#ifndef IMPORTGL_H_INCLUDED
#define IMPORTGL_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ANDROID_NDK
 //Android - GL ES v1
 #include <GLES/gl.h>
#else
 //Win/Linux - GL
 #include <GL/gl.h>
#endif

/* Dynamically fetches pointers to the egl & gl functions.
 * Should be called once on application initialization.
 * Returns non-zero on success and 0 on failure.
 */
extern int importGLInit();

/* Frees the handle to egl & gl functions library.
 */
extern void importGLDeinit();

/* Use DISABLE_IMPORTGL if you want to link the OpenGL ES at
 * compile/link time and not import it dynamically runtime.
 */
#ifndef DISABLE_IMPORTGL


#ifndef IMPORTGL_API
#define IMPORTGL_API extern
#endif
#ifndef IMPORTGL_FNPTRINIT
#define IMPORTGL_FNPTRINIT
#endif

#define FNDEF(retType, funcName, args) IMPORTGL_API retType (*funcPtr_##funcName) args IMPORTGL_FNPTRINIT

FNDEF(void, glBlendFunc, (GLenum sfactor, GLenum dfactor));
FNDEF(void, glClear, (GLbitfield mask));
///FNDEF(void, glClearColorx, (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha));
FNDEF(void, glColor4x, (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha));
FNDEF(void, glColorPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
FNDEF(void, glDisable, (GLenum cap));
FNDEF(void, glDisableClientState, (GLenum array));
FNDEF(void, glDrawArrays, (GLenum mode, GLint first, GLsizei count));
FNDEF(void, glEnable, (GLenum cap));
FNDEF(void, glEnableClientState, (GLenum array));
FNDEF(void, glFrustumx, (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar));
FNDEF(GLenum, glGetError, (void));
FNDEF(void, glLightxv, (GLenum light, GLenum pname, const GLfixed *params));
FNDEF(void, glLoadIdentity, (void));
FNDEF(void, glMaterialx, (GLenum face, GLenum pname, GLfixed param));
FNDEF(void, glMaterialxv, (GLenum face, GLenum pname, const GLfixed *params));
FNDEF(void, glMatrixMode, (GLenum mode));
FNDEF(void, glMultMatrixx, (const GLfixed *m));
FNDEF(void, glNormalPointer, (GLenum type, GLsizei stride, const GLvoid *pointer));
FNDEF(void, glPopMatrix, (void));
FNDEF(void, glPushMatrix, (void));
FNDEF(void, glRotatex, (GLfixed angle, GLfixed x, GLfixed y, GLfixed z));
FNDEF(void, glScalex, (GLfixed x, GLfixed y, GLfixed z));
FNDEF(void, glShadeModel, (GLenum mode));
FNDEF(void, glTranslatex, (GLfixed x, GLfixed y, GLfixed z));
FNDEF(void, glVertexPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
FNDEF(void, glViewport, (GLint x, GLint y, GLsizei width, GLsizei height));


#undef FN
#define FNPTR(name) funcPtr_##name

#ifndef IMPORTGL_NO_FNPTR_DEFS

// Redirect egl* and gl* function calls to funcPtr_egl* and funcPtr_gl*.

#define glBlendFunc             FNPTR(glBlendFunc)
#define glClear                 FNPTR(glClear)
#define glClearColorx           FNPTR(glClearColorx)
#define glColor4x               FNPTR(glColor4x)
#define glColorPointer          FNPTR(glColorPointer)
#define glDisable               FNPTR(glDisable)
#define glDisableClientState    FNPTR(glDisableClientState)
#define glDrawArrays            FNPTR(glDrawArrays)
#define glEnable                FNPTR(glEnable)
#define glEnableClientState     FNPTR(glEnableClientState)
#define glFrustumx              FNPTR(glFrustumx)
#define glGetError              FNPTR(glGetError)
#define glLightxv               FNPTR(glLightxv)
#define glLoadIdentity          FNPTR(glLoadIdentity)
#define glMaterialx             FNPTR(glMaterialx)
#define glMaterialxv            FNPTR(glMaterialxv)
#define glMatrixMode            FNPTR(glMatrixMode)
#define glMultMatrixx           FNPTR(glMultMatrixx)
#define glNormalPointer         FNPTR(glNormalPointer)
#define glPopMatrix             FNPTR(glPopMatrix)
#define glPushMatrix            FNPTR(glPushMatrix)
#define glRotatex               FNPTR(glRotatex)
#define glScalex                FNPTR(glScalex)
#define glShadeModel            FNPTR(glShadeModel)
#define glTranslatex            FNPTR(glTranslatex)
#define glVertexPointer         FNPTR(glVertexPointer)
#define glViewport              FNPTR(glViewport)

#endif // !IMPORTGL_NO_FNPTR_DEFS


#endif // !DISABLE_IMPORTGL


#ifdef __cplusplus
}
#endif


#endif // !IMPORTGL_H_INCLUDED
