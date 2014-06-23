#include <boost/filesystem/path.hpp>
#include "Mesh.h"
#include "window.h"

int main( int argc, char* argv[] )
{
  Window mainWindow( Rect<int>( 0, 0, 1600, 1000 ), "MeshViewer" );
  mainWindow.show( argc, argv );

  std::unique_ptr< Mesh<int, float> > pMesh( new Mesh<int, float>() );
  boost::filesystem::path path( "trial.vts" );
  pMesh->loadMeshVTS( path );
  std::unique_ptr< IInteractableMesh > pMeshBase( std::move( pMesh ) );

  std::unique_ptr< Viewport > pViewport( new Viewport() );
  pViewport->registerMesh( pMeshBase );

  mainWindow.getViewportManager().addViewport( pViewport );

  return Fl::run();
}