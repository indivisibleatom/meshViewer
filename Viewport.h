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

  bool containsPoint(int x, int y) const throw() {}
}

#endif//_VIEWPORT_H_