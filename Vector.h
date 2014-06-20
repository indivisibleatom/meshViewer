#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>

template <class T>
class Vector
{
private:
  T m_x;
  T m_y;
  T m_z;

public:
  Vector() {}
  Vector( T x, T y, T z ) throw() : m_x( x ), m_y( y ), m_z( z ) {}
  
  Vector& set( T x, T y, T z ) throw() 
  {
    m_x = x;
    m_y = y;
    m_z = z;
    return *this;
  }

  Vector& set( const Vector& other ) throw() 
  { 
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    return *this;
  }
  Vector& set( int index, T value ) throw() 
  {
    switch ( index )
    {
    case 0: m_x = value;
      break;
    case 1: m_y = value;
      break;
    case 2: m_z = value;
      break;
    }
    return *this;
  }

  Vector& add( const Vector& other ) throw() 
  {
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
  }
  
  Vector& add( float scale, const Vector& other ) throw() {
    m_x += scale*other.m_x;
    m_y += scale*other.m_y;
    m_z += scale*other.m_z; 
    return *this;
  }

  Vector& sub( const Vector& other ) throw() 
  {
    m_x-=other.m_x;
    m_y-=other.m_y;
    m_z-=other.m_z;
    return *this;
  }

  Vector& mul( T f ) throw()
  {
    m_x*=f;
    m_y*=f;
    m_z*=f;
    return *this;
  }

  Vector& div( T f )
  {
    float recip = 1/f;
    return mul( recip );
  }

  Vector& rev() throw()
  {
    m_x=-m_x;
    m_y=-m_y;
    m_z=-m_z;
    return *this;
  }

  T norm() throw()
  {
    return( sqrt( m_x*m_x + m_y*m_y + m_z*m_z ) );
  }

  Vector& normalize() throw()
  {
    float n=norm();
    if ( n>0.000001 )
    {
      div( n );
    }
    return *this;
  }
}

#endif//_VECTOR_H_