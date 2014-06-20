#if 0
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
    for ( std::vector<Viewport>::const_iterator iter = m_viewports.cbegin(); iter != m_viewports.cend(); ++iter )
    {
      iter->draw( m_fShowingFullScreen );
    }
  }
  if ( m_fShowingHelp )
  {
    camera();
    glViewport(0,0,width,height);
    writeHelp();
  }
}

void ViewportManager::onMousePressed()
{
  int viewport = getViewportForMouse( mouseX, mouseY );
  selectViewport( viewport );
  if (m_selectedViewport != -1)
  {
    m_viewports.get(m_selectedViewport).onMousePressed();
  }
  else
  {
  }
}

void onMouseDragged()
{
  if (m_selectedViewport != -1)
  {
    m_viewports.get(m_selectedViewport).onMouseDragged();
  }
  else
  {
    if (DEBUG && DEBUG_MODE >= LOW)
    {
      print ("ViewportManager::onMouseDragged - no viewport currently selected");
    }
  }
}

void onMouseMoved()
{
  if (m_selectedViewport != -1)
  {
    m_viewports.get(m_selectedViewport).onMouseMoved();
  }
  else
  {
    if (DEBUG && DEBUG_MODE >= LOW)
    {
      print ("ViewportManager::onMouseMoved - no viewport currently selected");
    }
  }
}

void onKeyReleased()
{
  if (m_selectedViewport != -1)
  {
    m_viewports.get(m_selectedViewport).onKeyReleased();
  }
  else
  {
    if (DEBUG && DEBUG_MODE >= LOW)
    {
      print ("ViewportManager::onMouseDragged - no viewport currently selected");
    }
  }
}

void onKeyPressed()
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
  if (key == 'H')
  {
    m_fShowingHelp = !m_fShowingHelp;
  }

  if (key == '!') {snapPicture();}
  
  if (m_selectedViewport != -1)
  {
    m_viewports.get(m_selectedViewport).onKeyPressed();
  }    
}

private int getViewportForMouse( int mouseX, int mouseY )
{
  if ( m_fShowingFullScreen )
  {
    return m_selectedViewport;
  }
  for (int i = 0; i < m_viewports.size(); i++)
  {
    if (m_viewports.get(i).containsPoint(mouseX, height - mouseY))
    {
      return i;
    }
  }
  if ( DEBUG && DEBUG_MODE >= LOW )
  {
    print ("ViewportManager::getViewportForMouse : can't find viewport for mouse. Keeping same viewport!");
  }
  return m_selectedViewport;
}
#endif