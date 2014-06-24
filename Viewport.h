#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "ViewportHost.h"
#include "Mesh.h"

class Viewport
{
private:
  std::vector< std::unique_ptr< IInteractableMesh > > m_meshes;
  
  //Camera parameters
  Point<float> m_eye;
  Point<float> m_lookAt;
  Vector<float> m_up;
  const IViewportHost* m_pViewportHost;

  std::vector< Vector<float> > m_axes;

public:
  Viewport( Viewport&& other ) : m_meshes( std::move( other.m_meshes ) ) , m_pViewportHost( nullptr ) {}

  Viewport();
  void init();

  void setHost( const IViewportHost* pViewportHost ) throw() { m_pViewportHost = pViewportHost; }

  void onSelected() {}
  void onDeselected() {}
  void registerMesh( std::unique_ptr< IInteractableMesh >& mesh );

  void draw( bool fDrawingFullScreen = false ) const throw();

  void onMousePressed( int mouseX, int mouseY ) {}
  void onMouseDragged( int deltaX, int deltaY );
  void onMouseMoved( int deltaX, int deltaY ) {}
  void onKeyReleased( int ch ) {}
  void onKeyPressed( int ch ) {}

  bool containsPoint(int x, int y) const throw() { return false; }
};

#endif//_VIEWPORT_H_