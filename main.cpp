#include <boost/filesystem/path.hpp>
#include "Mesh.h"
#include "ViewportManager.h"
#include "FL/Fl.H"

int main( int argc, char* argv[] )
{
  std::unique_ptr< Mesh<int, float> > pMesh( new Mesh<int, float>() );
  boost::filesystem::path path( "trial.vts" );
  pMesh->loadMeshVTS( path );

  ViewportManager viewportManager( Rect<int>( 0, 0, 1600, 1000 ) );
  std::unique_ptr< IInteractableMesh > pMeshBase( std::move( pMesh ) );
  std::unique_ptr< Viewport > pViewport( new Viewport() );
  pViewport->registerMesh( pMeshBase );
  viewportManager.addViewport( pViewport );

  return Fl::run();
}