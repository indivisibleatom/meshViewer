//#include <gl\GL.h>
//#include <gl\glut.h>
#include <boost/filesystem/path.hpp>
#include "Mesh.h"

int main( int argc, char* argv[] )
{
  Mesh<int, float> mesh;
  boost::filesystem::path path( "trial.vts" );
  mesh.loadMeshVTS( path );
  /*glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(1600, 1000);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Mesh viewer");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;*/
}