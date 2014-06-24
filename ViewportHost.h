#ifndef _VIEWPORTHOST_H_
#define _VIEWPORTHOST_H_

#include "Rect.h"

//ViewportHost interface
class IViewportHost
{
public:
  virtual ~IViewportHost() = 0 {}
  virtual bool isKeyPressed( int key ) const throw() = 0;
};

//Viewport interface
class IViewport
{
public:
  virtual ~IViewport() = 0 {}
  virtual const Rect<int>& getRect() const throw() = 0;

  virtual void init() = 0;
  virtual void draw() const throw() = 0;
  virtual void onMousePressed( int mouseX, int mouseY ) = 0;
  virtual void onMouseReleased( int mouseX, int mouseY ) = 0;
  virtual void onMouseDragged( int deltaX, int deltaY ) = 0;
  virtual void onMouseMoved( int deltaX, int deltaY ) = 0;
  virtual void onKeyReleased( int key ) = 0;
  virtual void onKeyPressed( int key ) = 0;
};

void createViewportHost( std::unique_ptr< IViewportHost >& pViewportHost, IViewport* pViewport );

#endif//_VIEWPORTHOST_H_