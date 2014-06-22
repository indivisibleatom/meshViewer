#include <boost/filesystem/path.hpp>
#include "Mesh.h"
#include "window.h"

int main( int argc, char* argv[] )
{
  Mesh<int, float> mesh;
  boost::filesystem::path path( "trial.vts" );
  mesh.loadMeshVTS( path );
  mesh.initMesh();
  mesh.draw();

  Window mainWindow( Rect<int>( 0, 0, 1600, 1000 ), "MeshViewer" );
  mainWindow.show( argc, argv );
  return Fl::run();
}