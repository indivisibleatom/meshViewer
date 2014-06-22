#include "precomp.h"
#include "window.h"

Window::Window( const Rect<int>& rect, const std::string& name ) : Fl_Gl_Window( rect.x(), rect.y(), rect.width(), rect.height(), name.c_str() ),
                                                                                 m_viewportManager( rect )
{
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
  }
  m_viewportManager.draw();
}

int Window::handle( int evnt )
{
  switch ( evnt )
  {
  case FL_PUSH:
    break;
  case FL_DRAG:
    break;
  case FL_RELEASE:
    break;
  case FL_FOCUS:
  case FL_UNFOCUS:
    break;
  case FL_KEYBOARD:
    break;
  default:
    return Fl_Gl_Window::handle( evnt );
  }
  return 1;
}