#include "precomp.h"
#include "ViewportManager.h"

ViewportManager::ViewportManager( const Rect<int>& rect ) : m_selectedViewport( -1 ), m_fShowingFullScreen( false ),
                                                            m_rect( rect ), m_previousMousePosition( -1, -1, 0 )
{
  createViewportHost( m_pViewportHost, this );
}

void ViewportManager::init()
{
  std::for_each( m_pViewports.cbegin(), m_pViewports.cend(), std::mem_fn( &Viewport::init ) );
}

void ViewportManager::addViewport( std::unique_ptr< Viewport >& viewport )
{
  viewport->setHost( m_pViewportHost.get() );
  m_pViewports.push_back( std::move( viewport ) );
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
  if ( index >= m_pViewports.size() || m_pViewports.size() < 0)
  {
    LOG( "ViewportManager::selectViewport incorrect viewport index", DEBUG_LEVELS::HIGH );
    if ( m_pViewports.size() > 0 )
    {
      selectViewport( m_pViewports.size() - 1 );
    }
    else
    {
      LOG( "ViewportManager::selectViewPort no viewports exist in viewport list", DEBUG_LEVELS::HIGH );
      return;
    }
  }

  //Track the selected viewport
  if ( m_selectedViewport != -1 )
  {
    m_pViewports[m_selectedViewport]->onDeselected();
  }
  m_selectedViewport = index;  
  m_pViewports[m_selectedViewport]->onSelected();
}

template< class T, class U >
void ViewportManager::registerMeshToViewport( Mesh<T,U> mesh, int viewportIndex ) throw()
{
  m_pViewports[viewportIndex].registerMesh( mesh );
}

template< class T, class U >
void ViewportManager::unregisterMeshFromViewport( Mesh<T,U> mesh, int viewportIndex ) throw()
{
  m_pViewports[viewportIndex].unregisterMesh( mesh );
}

void ViewportManager::draw() const throw()
{
  if ( m_fShowingFullScreen )
  {
    if ( m_selectedViewport != -1 )
    {
      m_pViewports[m_selectedViewport]->draw( m_fShowingFullScreen );
    }
  }
  else
  {
    std::for_each( m_pViewports.cbegin(), m_pViewports.cend(), std::bind( &Viewport::draw, std::placeholders::_1, m_fShowingFullScreen ) );
  }
}

void ViewportManager::onMousePressed( int mouseX, int mouseY )
{
  m_previousMousePosition.set( mouseX, mouseY, 0 );

  int viewport = getViewportForMouse( mouseX, mouseY );
  selectViewport( viewport );
  if (m_selectedViewport != -1)
  {
    m_pViewports[m_selectedViewport]->onMousePressed( mouseX, mouseY );
  }
  else
  {
    LOG("No viewport currently selected", DEBUG_LEVELS::VERBOSE );
  }
}

void ViewportManager::onMouseReleased( int /*mouseX*/, int /*mouseY*/ )
{
  m_previousMousePosition.set( -1, -1, 0 );
}

void ViewportManager::onMouseDragged( int mouseX, int mouseY )
{
  if ( m_previousMousePosition.x() != -1 )
  {
    int deltaX = mouseX - m_previousMousePosition.x();
    int deltaY = mouseY - m_previousMousePosition.y();

    if (m_selectedViewport != -1)
    {
      m_pViewports[m_selectedViewport]->onMouseDragged( deltaX, deltaY );
    }
    else
    {
      LOG( "No viewport currently selected", DEBUG_LEVELS::VERBOSE );
    }
  }
  m_previousMousePosition.set( mouseX, mouseY, 0 );
}

void ViewportManager::onMouseMoved( int deltaX, int deltaY )
{
  if (m_selectedViewport != -1)
  {
    m_pViewports[m_selectedViewport]->onMouseMoved( deltaX, deltaY );
  }
  else
  {
    LOG( "No viewport currently selected", DEBUG_LEVELS::VERBOSE );
  }
}

void ViewportManager::onKeyReleased( int key )
{
  if (m_selectedViewport != -1)
  {
    m_pViewports[m_selectedViewport]->onKeyReleased( key );
  }
  else
  {
    LOG( "No viewport currently selected", DEBUG_LEVELS::VERBOSE );
  }
}

void ViewportManager::onKeyPressed( int key )
{
  if (key == '.')
  {
    if (m_selectedViewport != -1)
    {
      selectViewport( (m_selectedViewport + 1)%m_pViewports.size() );
    }
  }
  if (key == '/')
  {
    m_fShowingFullScreen = !m_fShowingFullScreen;
  }

  //if (key == '!') {snapPicture();}

  if (m_selectedViewport != -1)
  {
    m_pViewports[m_selectedViewport]->onKeyPressed( key );
  }
}

int ViewportManager::getViewportForMouse( int mouseX, int mouseY ) const throw()
{
  if ( m_fShowingFullScreen )
  {
    return m_selectedViewport;
  }

  for (int i = 0; i < m_pViewports.size(); i++)
  {
    if (m_pViewports[i]->containsPoint(mouseX, m_rect.y() - mouseY))
    {
      return i;
    }
  }
  LOG("Can't find viewport for mouse. Keeping same viewport!", DEBUG_LEVELS::VERBOSE );
  return m_selectedViewport;
}
