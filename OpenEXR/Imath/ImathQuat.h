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



#ifndef INCLUDED_IMATHQUAT_H
#define INCLUDED_IMATHQUAT_H

//----------------------------------------------------------------------
//
//	template class Quat<T>
//
//	"Quaternions came from Hamilton ... and have been an unmixed
//	evil to those who have touched them in any way. Vector is a
//	useless survival ... and has never been of the slightest use
//	to any creature."
//
//	    - Lord Kelvin
//
//	This class implements the quaternion numerical type -- you
//      will probably want to use this class to represent orientations
//	in R3 and to convert between various euler angle reps. You
//	should probably use Imath::Euler<> for that.
//
//----------------------------------------------------------------------

#include <ImathExc.h>
#include <ImathMatrix.h>

#include <iostream>


namespace Imath {

template <class T>
class Quat;

template<class T>
Quat<T> slerp(const Quat<T> &q1,const Quat<T> &q2, T t);

template<class T>
Quat<T> squad(const Quat<T> &q1,const Quat<T> &q2, 
	      const Quat<T> &qa,const Quat<T> &qb, T t);

template<class T>
void intermediate(const Quat<T> &q0, const Quat<T> &q1, 
		     const Quat<T> &q2, const Quat<T> &q3,
		     Quat<T> &qa, Quat<T> &qb);

template <class T>
class Quat
{
  public:

    T			    r;	    // real part
    Vec3<T>		    v;	    // imaginary vector

    //-----------------------------------------------------
    //	Constructors - default constructor is identity quat
    //-----------------------------------------------------

    Quat()			    : r(1), v(0,0,0) {}
    Quat( const Quat<T>& q)	    : r(q.r), v(q.v) {}
    Quat( T s, T i, T j, T k )	    : r(s), v(i,j,k) {}
    Quat( T s, Vec3<T> d ) 	    : r(s), v(d) {}

    //------------------------------------------------
    //	Basic Algebra - Operators and Methods
    //  The operator return values are *NOT* normalized
    //
    //  operator^ is 4D dot product
    //  operator/ uses the inverse() quaternion
    //	operator~ is conjugate -- if (S+V) is quat then
    //		  the conjugate (S+V)* == (S-V)
    //
    //  some operators (*,/,*=,/=) treat the quat as
    //	a 4D vector when one of the operands is scalar
    //------------------------------------------------

    const Quat<T>&	    operator=	(const Quat<T>&);
    const Quat<T>&	    operator*=	(const Quat<T>&);
    const Quat<T>&	    operator*=	(T);
    const Quat<T>&	    operator/=	(const Quat<T>&);
    const Quat<T>&	    operator/=	(T);
    const Quat<T>&	    operator+=	(const Quat<T>&);
    const Quat<T>&	    operator-=	(const Quat<T>&);
    T&			    operator[]	(int index);	// as 4D vector
    T			    operator[]	(int index) const;

//  friend Quat<T>	    operator*	(const Quat<T>&,const Quat<T>&);
//  friend Quat<T>	    operator*	(const Quat<T>&,T);
//  friend Quat<T>	    operator*	(T,const Quat<T>&);
//  friend Quat<T>	    operator/	(const Quat<T>&,const Quat<T>&);
//  friend Quat<T>	    operator/	(const Quat<T>&,T);
//  friend Quat<T>	    operator+	(const Quat<T>&,const Quat<T>&);
//  friend Quat<T>	    operator-	(const Quat<T>&,const Quat<T>&);
//  friend T		    operator^	(const Quat<T>&,const Quat<T>&);
//  friend Quat<T>	    operator-	(const Quat<T>&);
//  friend Quat<T>	    operator~	(const Quat<T>&);   // conjugate

//  friend Matrix33<T>	    operator*	(const Quat<T>&,const Matrix33<T>&);
//  friend Matrix33<T>	    operator*	(const Matrix33<T>&,const Quat<T>&);

//  friend std::ostream&    operator<<	(std::ostream &,const Quat<T>&);

    static Quat<T>	    identity()	{ return Quat<T>(); }

    Quat<T>&		    invert();		    // this -> 1 / this
    Quat<T>		    inverse() const;
    Quat<T>&		    normalize();	    // returns this
    Quat<T>		    normalized() const;
    T			    length() const;	    // in R4

    //-----------------------
    //	Interpolation
    //-----------------------

//  friend Quat<T>	    slerp(const Quat<T>&,const Quat<T>&,T t);

    //-----------------------
    //	Rotation conversion
    //-----------------------

    Quat<T>&		    setAxisAngle(const Vec3<T>& axis, T radians);
    Quat<T>&		    setRotation(const Vec3<T>& fromDirection,
					const Vec3<T>& toDirection);

    T		            angle() const;
    Vec3<T> 		    axis() const;

    Matrix33<T>		    toMatrix33() const;
    Matrix44<T>		    toMatrix44() const;

    Quat<T>                 log() const;
    Quat<T>                 exp() const;
};


//--------------------
// Convenient typedefs
//--------------------

typedef Quat<float>	Quatf;
typedef Quat<double>	Quatd;


//---------------
// Implementation
//---------------

template<class T>
inline const Quat<T>& Quat<T>::operator= (const Quat<T>& q)
{
    r = q.r;
    v = q.v;
    return *this;
}

template<class T>
inline const Quat<T>& Quat<T>::operator*= (const Quat<T>& q)
{
    T rtmp = r * q.r - (v ^ q.v);
    v = r * q.v + v * q.r + v % q.v;
    r = rtmp;
    return *this;
}

template<class T>
inline const Quat<T>& Quat<T>::operator*= (T t)
{
    r *= t;
    v *= t;
    return *this;
}

template<class T>
inline const Quat<T>& Quat<T>::operator/= (const Quat<T>& q)
{
    *this = *this * q.inverse();
    return *this;
}

template<class T>
inline const Quat<T>& Quat<T>::operator/= (T t)
{
    r /= t;
    v /= t;
    return *this;
}

template<class T>
inline const Quat<T>& Quat<T>::operator+= (const Quat<T>& q)
{
    r += q.r;
    v += q.v;
    return *this;
}

template<class T>
inline const Quat<T>& Quat<T>::operator-= (const Quat<T>& q)
{
    r -= q.r;
    v -= q.v;
    return *this;
}
template<class T>
inline T& Quat<T>::operator[] (int index)
{
    return index ? v[index-1] : r;
}

template<class T>
inline T Quat<T>::operator[] (int index) const
{
    return index ? v[index-1] : r;
}

template<class T>
inline T operator^ (const Quat<T>& q1,const Quat<T>& q2)
{
    return q1.r * q2.r + (q1.v ^ q2.v);
}

template <class T>
inline T Quat<T>::length() const
{
    return Math<T>::sqrt( r * r + (v ^ v) );
}

template <class T>
inline Quat<T>& Quat<T>::normalize()
{
    if ( T l = length() ) { r /= l; v /= l; }
    else { r = 1; v = 0; }
    return *this;
}

template <class T>
inline Quat<T> Quat<T>::normalized() const
{
    if ( T l = length() ) return Quat( r / l, v / l );
    return Quat();
}

template<class T>
inline Quat<T> Quat<T>::inverse() const
{
    // 1    Q*
    // - = ----   where Q* is conjugate (operator~)
    // Q   Q* Q   and (Q* Q) == Q ^ Q (4D dot)

    T qdot = *this ^ *this;
    return Quat( r / qdot, -v / qdot );
}

template<class T>
inline Quat<T>& Quat<T>::invert()
{
    T qdot = (*this) ^ (*this);
    r /= qdot;
    v = -v / qdot;
    return *this;
}

template<class T>
Quat<T> slerp(const Quat<T> &q1,const Quat<T> &q2, T t)
{
    //
    // Spherical linear interpolation.
    // This routine is more advanced than the routine in
    // SbRotation. Given two quaternions q1 and q2, there
    // are two possible arcs along which one can move,
    // corresponding to alternative starting directions.
    // This routine chooses the shorter arc for the 
    // interpolation of q1 and q2, which is more desirable.
    //

    T qdot	    = q1 ^ q2;
    const T epsilon = .0001;
    Quat<T> result;
    T s1,s2;

    Quat<T> q1b = q1;

    if ( qdot < 0 )
    {
	// If q1 and q2 are more than 90 degrees apart,
	// flip q1 - this gives us the shorter arc.
	// 
	qdot = -qdot;
	q1b.v = -q1.v;
	q1b.r = -q1.r;
    }

    if ((1 - qdot) > epsilon )
    {
	T omega = Math<T>::acos(qdot);
	T sinom = Math<T>::sin(omega);
	s1	    = Math<T>::sin((1.0 - t) * omega) / sinom;
	s2	    = Math<T>::sin(t * omega) / sinom;
    }
    else
    {
	// If q1 and q2 are very close together, do 
	// simple linear interpolation:
	// 
	s1	= 1.0 - t;
	s2	= t;
    }

    result = s1 * q1b + s2 * q2;

    return result;
}

template<class T>
Quat<T> squad(const Quat<T> &q0, const Quat<T> &q1,
	      const Quat<T> &q2, const Quat<T> &q3,
	      T t)
{
    // Spherical Cubic Spline Interpolation -
    // from Advanced Animation and Rendering
    // Techniques by Watt and Watt, Page 366:
    // A spherical curve is constructed using three
    // spherical linear interpolations of a quadrangle
    // of unit quaternions: q1, qa, qb, q2.
    // Given a set of quaternion keys: q0, q1, q2, q3,
    // this routine does the interpolation between
    // q1 and q2 by constructing two intermediate
    // quaternions: qa and qb. The qa and qb are 
    // computed by the intermediate function to 
    // guarantee the continuity of tangents across
    // adjacent cubic segments. 
    // 
    // The q1 q2 is the cubic segment being interpolated. 
    // The q0 is from the previous adjacent segment and q3 is 
    // from the next adjacent segment. The q0 and q3 are used
    // in computing qa and qb.
    // 
    Quat<T> qa, qb;
    intermediate(q0, q1, q2, q3, qa, qb);
    Quat<T> r1 = slerp(q1, q2, t);
    Quat<T> r2 = slerp(qa, qb, t);
    Quat<T> result = slerp(r1, r2, 2*t*(1-t));
    return result;
}

template<class T>
void intermediate(const Quat<T> &q0, const Quat<T> &q1, 
		  const Quat<T> &q2, const Quat<T> &q3,
		  Quat<T> &qa, Quat<T> &qb)
{
    // From advanced Animation and Rendering
    // Techniques by Watt and Watt, Page 366:
    // computing the inner quadrangle 
    // points (qa and qb) to guarantee tangent
    // continuity.
    // 
    Quat<T> q1inv = q1.inverse();
    Quat<T> c1 = q1inv*q2;
    Quat<T> c2 = q1inv*q0;
    Quat<T> c3 = (T) 0.25 * (c2.log() - c1.log());
    qa = q1 * c3.exp();

    Quat<T> q2inv = q2.inverse();
    Quat<T> c4 = q2inv*q3;
    Quat<T> c5 = q2inv*q1;
    Quat<T> c6 = (T) 0.25 * (c5.log() - c4.log());
    qb = q2 * c6.exp();
}

template <class T>
inline Quat<T> Quat<T>::log() const
{
    // For unit quaternion, from Advanced Animation and 
    // Rendering Techniques by Watt and Watt, Page 366:
    //
    Quat<T> result;
    result.r = 0;
    result.v = v;
    const T epsilon = .0001;

    double theta = acos(r);
    if( theta > epsilon )
    {
	result.v.x = v.x*theta;
	result.v.y = v.y*theta;
	result.v.z = v.z*theta;
    }
    return result;
}

template <class T>
inline Quat<T> Quat<T>::exp() const
{
    // For pure quaternion (zero scalar part):
    // from Advanced Animation and Rendering
    // Techniques by Watt and Watt, Page 366:
    //
    Quat<T> result;
    double theta = v.length();
    const T epsilon = .0001;

    result.r = cos(theta);
    result.v = v;
    if( sin(theta) > epsilon)
    {
	result.v.x = sin(theta)*v.x;
	result.v.y = sin(theta)*v.y;
	result.v.z = sin(theta)*v.z;
    }
    return result;
}

template <class T>
inline T Quat<T>::angle() const
{
    return 2.0*Math<T>::acos(r);
}

template <class T>
inline Vec3<T> Quat<T>::axis() const
{
    return v.normalized();
}

template <class T>
inline Quat<T>& Quat<T>::setAxisAngle(const Vec3<T>& axis, T radians)
{
    r = Math<T>::cos(radians/2);
    v = axis.normalized() * Math<T>::sin(radians/2);
    return *this;
}


template <class T>
Quat<T>&
Quat<T>::setRotation(const Vec3<T>& from, const Vec3<T>& to)
{
    //
    // Ported from SbRotation
    //

    T cost = from.dot(to) / Math<T>::sqrt(from.dot(from) * to.dot(to));

    // check for degeneracies
    if (cost > 0.99999)
    {
	//
	// Vectors are parallel.
	//

	r = 1.0;
	v = 0;
    }
    else if (cost < -0.99999)
    {
	//
	// Vectors are opposite. Find an axis to rotate around,
	// which should be perpendicular to the original axis.
	//

	Vec3<T> frm = from.normalized();
	v = frm.cross(Vec3<T>(1, 0, 0));
	if (v.length() < 0.00001)
	    v   = frm.cross(Vec3<T>(0, 1, 0));
	r = 0;
	v.normalize();
    }
    else
    {
	//
	// Use half-angle formulae:
	// cos^2 t = ( 1 + cos (2t) ) / 2
	// w part is cosine of half the rotation angle
	//

	r = Math<T>::sqrt(0.5 * (1.0 + cost));

	//
	// sin^2 t = ( 1 - cos (2t) ) / 2
	// Do the normalization of the axis vector at the same time so
	// we only call sqrt once.
	//

	v = from.cross(to);
	v *= Math<T>::sqrt((0.5 * (1.0 - cost))/(v.dot(v)));
    }

    return *this;
}

template<class T>
Matrix33<T> Quat<T>::toMatrix33() const
{
    return Matrix33<T>(1. - 2.0 * (v.y * v.y + v.z * v.z),
			    2.0 * (v.x * v.y + v.z * r),
			    2.0 * (v.z * v.x - v.y * r),

			    2.0 * (v.x * v.y - v.z * r),
		       1. - 2.0 * (v.z * v.z + v.x * v.x),
			    2.0 * (v.y * v.z + v.x * r),

			    2.0 * (v.z * v.x + v.y * r),
			    2.0 * (v.y * v.z - v.x * r),
		       1. - 2.0 * (v.y * v.y + v.x * v.x));
}

template<class T>
Matrix44<T> Quat<T>::toMatrix44() const
{
    return Matrix44<T>(1. - 2.0 * (v.y * v.y + v.z * v.z),
			    2.0 * (v.x * v.y + v.z * r),
			    2.0 * (v.z * v.x - v.y * r),
			    0.,
			    2.0 * (v.x * v.y - v.z * r),
		       1. - 2.0 * (v.z * v.z + v.x * v.x),
			    2.0 * (v.y * v.z + v.x * r),
			    0.,
			    2.0 * (v.z * v.x + v.y * r),
			    2.0 * (v.y * v.z - v.x * r),
		       1. - 2.0 * (v.y * v.y + v.x * v.x),
			    0.,
			    0.,
			    0.,
			    0.,
			    1.0 );
}


template<class T>
inline Matrix33<T> operator* (const Matrix33<T> &M, const Quat<T> &q)
{
    return M * q.toMatrix33();
}

template<class T>
inline Matrix33<T> operator* (const Quat<T> &q, const Matrix33<T> &M)
{
    return q.toMatrix33() * M;
}

template<class T>
std::ostream& operator<< (std::ostream &o, const Quat<T> &q)
{
    return o << "(" << q.r
	     << " " << q.v.x
	     << " " << q.v.y
	     << " " << q.v.z
	     << ")";

}

template<class T>
inline Quat<T> operator* (const Quat<T>& q1, const Quat<T>& q2)
{
    // (S1+V1) (S2+V2) = S1 S2 - V1.V2 + S1 V2 + V1 S2 + V1 x V2
    return Quat<T>( q1.r * q2.r - (q1.v ^ q2.v),
		    q1.r * q2.v + q1.v * q2.r + q1.v % q2.v );
}

template<class T>
inline Quat<T> operator/ (const Quat<T>& q1, const Quat<T>& q2)
{
    return q1 * q2.inverse();
}

template<class T>
inline Quat<T> operator/ (const Quat<T>& q,T t)
{
    return Quat<T>(q.r/t,q.v/t);
}

template<class T>
inline Quat<T> operator* (const Quat<T>& q,T t)
{
    return Quat<T>(q.r*t,q.v*t);
}

template<class T>
inline Quat<T> operator* (T t, const Quat<T>& q)
{
    return Quat<T>(q.r*t,q.v*t);
}

template<class T>
inline Quat<T> operator+ (const Quat<T>& q1, const Quat<T>& q2)
{
    return Quat<T>( q1.r + q2.r, q1.v + q2.v );
}

template<class T>
inline Quat<T> operator- (const Quat<T>& q1, const Quat<T>& q2)
{
    return Quat<T>( q1.r - q2.r, q1.v - q2.v );
}

template<class T>
inline Quat<T> operator~ (const Quat<T>& q)
{
    return Quat<T>( q.r, -q.v );	// conjugate: (S+V)* = S-V
}

template<class T>
inline Quat<T> operator- (const Quat<T>& q)
{
    return Quat<T>( -q.r, -q.v );
}


} // namespace Imath

#endif
