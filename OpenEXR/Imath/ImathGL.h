///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2002, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////


#ifndef INCLUDED_IMATHGL_H
#define INCLUDED_IMATHGL_H

#include <GL/gl.h>

#include <ImathVec.h>
#include <ImathMatrix.h>

inline void glVertex    ( const Imath::V3f &v ) { glVertex3f(v.x,v.y,v.z);   }
inline void glVertex    ( const Imath::V2f &v ) { glVertex2f(v.x,v.y);       }
inline void glNormal    ( const Imath::V3f &n ) { glNormal3f(n.x,n.y,n.z);   }
inline void glColor     ( const Imath::V3f &c ) { glColor3f(c.x,c.y,c.z);    }
inline void glTranslate ( const Imath::V3f &t ) { glTranslatef(t.x,t.y,t.z); }

inline void glTexCoord( const Imath::V2f &t )
{
    glTexCoord2f(t.x,t.y);
#ifndef PLATFORM_IRIX
    glMultiTexCoord2f(GL_TEXTURE1, t.x, t.y);
#endif
}

inline void glDisableTexture()
{
#ifndef PLATFORM_IRIX
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0);
#endif
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

inline void 
glMultMatrix( const Imath::M44f& m ) 
{ 
    glMultMatrixf( (GLfloat*)m[0] ); 
}

inline void 
glMultMatrix( const Imath::M44f* m ) 
{ 
    glMultMatrixf( (GLfloat*)(*m)[0] ); 
}

inline void 
glLoadMatrix( const Imath::M44f& m ) 
{ 
    glLoadMatrixf( (GLfloat*)m[0] ); 
}

inline void 
glLoadMatrix( const Imath::M44f* m ) 
{ 
    glLoadMatrixf( (GLfloat*)(*m)[0] ); 
}



#endif
