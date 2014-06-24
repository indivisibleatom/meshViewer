#include "precomp.h"
#include "Viewport.h"
#include <GL/glew.h>
#include <GL/GLU.h>
#include <boost/iterator/indirect_iterator.hpp>

Viewport::Viewport() : m_eye( 0.0f, 0.0f, 100.0f ), m_up( 0.0f, 1.0f, 0.0f ), m_lookAt( 0.0f, 0.0f, 0.0f )
{
  for ( int i = 0; i < 3; i++ )
  {
    Vector<float> vector( 0.0f , 0.0f, 0.0f );
    vector.set( i, 1.0f );
    m_axes.push_back( vector );
  }
}

void Viewport::registerMesh( std::unique_ptr< IInteractableMesh >& mesh ) throw()
{
  m_meshes.push_back( std::move( mesh ) );
}

void Viewport::init()
{
  std::for_each( boost::make_indirect_iterator( m_meshes.cbegin() ), boost::make_indirect_iterator( m_meshes.cend() ), std::mem_fn( &IInteractableMesh::init ) );
}

void Viewport::draw( bool fDrawingFullScreen ) const throw() 
{
  glClearColor( 1.0, 1.0, 1.0, 1.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt( m_eye.x(), m_eye.y(), m_eye.z(), m_lookAt.x(), m_lookAt.y(), m_lookAt.z(), m_up.x(), m_up.y(), m_up.z() );

  glMatrixMode(GL_MODELVIEW);
  std::for_each( boost::make_indirect_iterator( m_meshes.cbegin() ), boost::make_indirect_iterator( m_meshes.cend() ), std::mem_fn( &IInteractableMesh::draw ) );
}

void Viewport::onMouseDragged( int deltaX, int deltaY )
{
  if ( m_pViewportHost->isKeyPressed( 'z' ) )
  {
    m_eye = Point<float>(m_eye, -float(deltaY), m_axes[2] );
  }
  else if ( m_pViewportHost->isKeyPressed( 'x' ) )
  {
    m_eye = Point<float>(m_eye, -float(deltaY), m_axes[2] );
    m_up = Vector<float>( m_up, -(PI*float(deltaX))/1600, m_axes[0], m_axes[1] );
  }
}