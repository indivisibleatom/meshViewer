#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GL/glew.h>
#include <FL/Fl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include "Rect.h"
#include "ViewportHost.h"

class Window : public Fl_Gl_Window, public IViewportHost
{
private:
  IViewport* m_pViewport;

public:
  Window( IViewport* pViewport, const std::string& name );

  bool isKeyPressed( int key ) const throw() override;

  void draw();
  int handle( int );
};

#endif//_WINDOW_H_