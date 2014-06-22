#include <boost/filesystem/path.hpp>
#include "Mesh.h"
#include "window.h"

int main( int argc, char* argv[] )
{
  Window mainWindow( Rect<int>( 0, 0, 1600, 1000 ), "MeshViewer" );
  mainWindow.show( argc, argv );

  /*GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    LOG( glewGetErrorString( err ), DEBUG_LEVELS::LOW );
    return 0;
  }*/

  Mesh<int, float> mesh;
  boost::filesystem::path path( "trial.vts" );
  mesh.loadMeshVTS( path );

  return Fl::run();
}