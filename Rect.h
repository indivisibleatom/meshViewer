#ifndef _RECT_H_
#define _RECT_H_

template <class T>
class Rect
{
private:
  T m_x;
  T m_y;
  T m_width;
  T m_height;
public:
  Rect( int x, int y, int width, int height ) throw() : m_x( x ), m_y( y ), m_width( width ), m_height( height ) {}
  T x() const throw() { return m_x; }
  T y() const throw() { return m_y; }
  T width() const throw() { return m_width; }
  T height() const throw() { return m_height; }
};

#endif//_RECT_H_