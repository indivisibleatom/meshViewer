#ifndef _VIEWPORTMANAGER_H_
#define _VIEWPORTMANAGER_H_

#include "Viewport.h"
#include "Mesh.h"
#include "Rect.h"

class ViewportManager
{
private:
  std::vector<Viewport> m_viewports;
  int m_selectedViewport;
  bool m_fShowingFullScreen;
  Rect<int> m_rect;

public:
  ViewportManager( const Rect<int>& rect );
  void addViewport( const Viewport& v );
  int getSelectedViewport() const throw();
  void selectViewport( int index ) throw();
  template< class T, class U > void registerMeshToViewport( Mesh<T,U> mesh, int viewportIndex ) throw();
  template< class T, class U > void unregisterMeshFromViewport( Mesh<T,U> mesh, int viewportIndex ) throw();

  void draw() const throw();

  void onMousePressed( int mouseX, int mouseY );
  void onMouseDragged( int deltaX, int deltaY );
  void onMouseMoved( int deltaX, int deltaY );
  void onKeyReleased( char ch );
  void onKeyPressed( char ch );

private:
  int getViewportForMouse( int mouseX, int mouseY ) const throw();
};

#endif//_VIEWPORTMANAGER_H_