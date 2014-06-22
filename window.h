#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GL/glew.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include "Rect.h"
#include "ViewportManager.h"

class Window : public Fl_Gl_Window
{
private:
  ViewportManager m_viewportManager;

public:
  Window( const Rect<int>& rect, const std::string& name );
  void draw();
  int handle( int );
};

#endif//_WINDOW_H_