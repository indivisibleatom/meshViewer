#include "precomp.h"
#include "ViewportHost.h"
#include "window.h"

void createViewportHost( std::unique_ptr< IViewportHost >& pViewportHost, IViewport* pViewport )
{
  std::unique_ptr< Window > pWindow( new Window( pViewport, "MeshViewer" ) );
  pWindow->show();
  pViewportHost = std::move( pWindow );
}

Window::Window( IViewport* pViewport, const std::string& name ) : Fl_Gl_Window( pViewport->getRect().x(), pViewport->getRect().y(), 
                                                                                pViewport->getRect().width(), pViewport->getRect().height(), name.c_str() ),
                                                                  m_pViewport( pViewport )
{
}

bool Window::isKeyPressed( int key ) const throw()
{
  return Fl::event_key( key );
}

void Window::draw()
{
  if ( !valid() )
  {
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      LOG( glewGetErrorString( err ), DEBUG_LEVELS::LOW );
      return ;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 60.0 , 1.0, 0.1 , 1000.0 );
    m_pViewport->init();
  }
  m_pViewport->draw();
}

int Window::handle( int evnt )
{
  switch ( evnt )
  {
  case FL_PUSH: m_pViewport->onMousePressed( Fl::event_x(), Fl::event_y() );
    break;
  case FL_MOVE: m_pViewport->onMouseMoved( Fl::event_x(), Fl::event_y() );
    break;
  case FL_DRAG: m_pViewport->onMouseDragged( Fl::event_x(), Fl::event_y() );
    redraw();
    break;
  case FL_RELEASE: m_pViewport->onMouseReleased( Fl::event_x(), Fl::event_y() );
    break;
  case FL_FOCUS:
  case FL_UNFOCUS: 
    break;
  case FL_KEYDOWN: m_pViewport->onKeyReleased( Fl::event_key() );
    break;
  case FL_KEYUP: m_pViewport->onKeyPressed( Fl::event_key() );
    break;
  default:
    return Fl_Gl_Window::handle( evnt );
  }
  return 1;
}
