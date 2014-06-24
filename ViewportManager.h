#ifndef _VIEWPORTMANAGER_H_
#define _VIEWPORTMANAGER_H_

#include "ViewportHost.h"
#include "Viewport.h"
#include "Mesh.h"
#include "Rect.h"

class ViewportManager : public IViewport
{
private:
  std::unique_ptr<IViewportHost> m_pViewportHost;
  std::vector< std::unique_ptr< Viewport > > m_pViewports;
  int m_selectedViewport;
  bool m_fShowingFullScreen;
  Rect<int> m_rect;
  Point<int> m_previousMousePosition;

public:
  ViewportManager( const Rect<int>& rect );

  void init() override;
  const Rect<int>& getRect() const throw() { return m_rect; }

  void addViewport( std::unique_ptr< Viewport >& viewport );
  int getSelectedViewport() const throw();
  void selectViewport( int index ) throw();
  template< class T, class U > void registerMeshToViewport( Mesh<T,U> mesh, int viewportIndex ) throw();
  template< class T, class U > void unregisterMeshFromViewport( Mesh<T,U> mesh, int viewportIndex ) throw();

  void draw() const throw() override;

  void onMousePressed( int mouseX, int mouseY );
  void onMouseReleased( int mouseX, int mouseY );
  void onMouseDragged( int deltaX, int deltaY );
  void onMouseMoved( int deltaX, int deltaY );
  void onKeyReleased( int ch );
  void onKeyPressed( int ch );

private:
  int getViewportForMouse( int mouseX, int mouseY ) const throw();
};

#endif//_VIEWPORTMANAGER_H_