#ifndef _POINT_H_
#define _POINT_H_

template <class T>
class Point
{
private:
  T m_x;
  T m_y;
  T m_z;

public:
  Point() {}

  Point( T x, T y, T z ) throw() : m_x( x ), m_y( y ), m_z( z ) {}

  Point& set( T x, T y, T z ) throw() 
  {
    m_x = x;
    m_y = y;
    m_z = z;
    return *this;
  }

  Point& set( const Point& other ) throw() 
  { 
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    return *this;
  }

  Point& set( int index, T value ) throw() 
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
};

#endif//_POINT_H_