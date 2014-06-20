#include "precomp.h"
#include <gl\GL.h>
#include "ViewportManager.h"

ViewportManager::ViewportManager()
{
  m_selectedViewport = -1;
  m_fShowingFullScreen = false;
  m_fShowingHelp = false;
}

void ViewportManager::addViewport( const Viewport& v )
{
  m_viewports.push_back( v );
  if ( m_selectedViewport == -1 )
  {
    selectViewport( 0 );
  }
}

int ViewportManager::getSelectedViewport() const throw()
{
  return m_selectedViewport;
}

void ViewportManager::selectViewport( int index ) throw()
{
  if ( index >= m_viewports.size() || m_viewports.size() < 0)
  {
    LOG( "ViewportManager::selectViewport incorrect viewport index", DEBUG_LEVELS::ERROR );
    if ( m_viewports.size() > 0 )
    {
      selectViewport( m_viewports.size() - 1 );
    }
    else
    {
      LOG( "ViewportManager::selectViewPort no viewports exist in viewport list", DEBUG_LEVELS::ERROR );
      return;
    }
  }

  //Track the selected viewport
  if ( m_selectedViewport != -1 )
  {
    m_viewports[m_selectedViewport].onDeselected();
  }
  m_selectedViewport = index;  
  m_viewports[m_selectedViewport].onSelected();
}

template< class T, class U >
void ViewportManager::registerMeshToViewport( Mesh<T,U> mesh, int viewportIndex ) throw()
{
  m_viewports[viewportIndex].registerMesh( mesh );
}

template< class T, class U >
void ViewportManager::unregisterMeshFromViewport( Mesh<T,U> m, int viewportIndex ) throw()
{
  m_viewports[viewportIndex].unregisterMesh(m);
}

void ViewportManager::draw() const throw()
{
  if ( m_fShowingFullScreen )
  {
    if ( m_selectedViewport != -1 )
    {
      m_viewports[m_selectedViewport].draw( m_fShowingFullScreen );
    }
  }
  else
  {
    std::for_each( m_viewports.cbegin(), m_viewports.cend(), std::bind2nd( draw, m_fShowingFullScreen ) );
  }
}

void ViewportManager::onMousePressed( int mouseX, int mouseY )
{
  int viewport = getViewportForMouse( mouseX, mouseY );
  selectViewport( viewport );
  if (m_selectedViewport != -1)
  {
    m_viewports[m_selectedViewport].onMousePressed( mouseX, mouseY );
  }
  else
  {
    LOG("No viewport currently selected", DEBUG_LEVELS::VERBOSE );
  }
}

void ViewportManager::onMouseDragged( int deltaX, int deltaY )
{
  if (m_selectedViewport != -1)
  {
    m_viewports[m_selectedViewport].onMouseDragged( deltaX, deltaY );
  }
  else
  {
    LOG( "No viewport currently selected", DEBUG_LEVELS::VERBOSE );
  }
}

void ViewportManager::onMouseMoved( int deltaX, int deltaY )
{
  if (m_selectedViewport != -1)
  {
    m_viewports[m_selectedViewport].onMouseMoved( deltaX, deltaY );
  }
  else
  {
    LOG( "No viewport currently selected", DEBUG_LEVELS::VERBOSE );
  }
}

void ViewportManager::onKeyReleased( char key )
{
  if (m_selectedViewport != -1)
  {
    m_viewports.get(m_selectedViewport).onKeyReleased();
  }
  else
  {
    LOG( "No viewport currently selected", DEBUG_LEVELS::VERBOSE );
  }
}

void ViewportManager::onKeyPressed( char key )
{
  if (key == '.')
  {
    if (m_selectedViewport != -1)
    {
      selectViewport( (m_selectedViewport + 1)%m_viewports.size() );
    }
  }
  if (key == '/')
  {
    m_fShowingFullScreen = !m_fShowingFullScreen;
  }

  //if (key == '!') {snapPicture();}

  if (m_selectedViewport != -1)
  {
    m_viewports[m_selectedViewport].onKeyPressed();
  }
}

int ViewportManager::getViewportForMouse( int mouseX, int mouseY ) const throw()
{
  if ( m_fShowingFullScreen )
  {
    return m_selectedViewport;
  }

  for (int i = 0; i < m_viewports.size(); i++)
  {
    if (m_viewports[i].containsPoint(mouseX, height - mouseY))
    {
      return i;
    }
  }
  LOG("Can't find viewport for mouse. Keeping same viewport!", DEBUG_LEVELS::VERBOSE );
  return m_selectedViewport;
}
