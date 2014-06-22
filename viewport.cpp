#include "precomp.h"
#include "Viewport.h"
#include <boost/iterator/indirect_iterator.hpp>

template <class T, class U>
void Viewport::registerMesh( std::unique_ptr< IInteractableMesh >& mesh ) throw()
{
  m_meshes.push_back( std::move( mesh ) );
}

void Viewport::draw( bool fDrawingFullScreen ) const throw() 
{
  std::for_each( boost::make_indirect_iterator( m_meshes.cbegin() ), boost::make_indirect_iterator( m_meshes.cend() ), std::mem_fn( &IInteractableMesh::draw ) );
  /*for ( auto iter = m_meshes.begin(); iter != m_meshes.end(); iter++ )
  {
    (*iter)->draw();
  }*/
}
