#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "Mesh.h"

class Viewport
{
private:
  std::vector< std::unique_ptr< IInteractableMesh > > m_meshes;

public:
  Viewport( Viewport&& other ) : m_meshes( std::move( other.m_meshes ) ) { }
  Viewport( const Viewport&& other ) : m_meshes( std::move( other.m_meshes ) ) { }

  void onSelected() {}
  void onDeselected() {}
  template < class T, class U > void registerMesh( std::unique_ptr< IInteractableMesh >& mesh );

  void draw( bool fDrawingFullScreen = false ) const throw();

  void onMousePressed( int mouseX, int mouseY ) {}
  void onMouseDragged( int deltaX, int deltaY ) {}
  void onMouseMoved( int deltaX, int deltaY ) {}
  void onKeyReleased( char ch ) {}
  void onKeyPressed( char ch ) {}

  bool containsPoint(int x, int y) const throw() { return false; }
};

#endif//_VIEWPORT_H_