#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "Mesh.h"

class Viewport
{
public:
  void onSelected() {}
  void onDeselected() {}
  template < class T, class U > void registerMesh( Mesh<T,U> mesh ) {}

  void draw( bool fDrawingFullScreen = false ) const throw() {}

  void onMousePressed( int mouseX, int mouseY ) {}
  void onMouseDragged( int deltaX, int deltaY ) {}
  void onMouseMoved( int deltaX, int deltaY ) {}
  void onKeyReleased( char ch ) {}
  void onKeyPressed( char ch ) {}

  bool containsPoint(int x, int y) const throw() { return false; }
};

#endif//_VIEWPORT_H_