
# include <iostream>
# include "ogl_tools.h"
# include "app_window.h"

//==========================================================================
// Main routine
//==========================================================================
int main ( int argc, char** argv )
 {
   // Init freeglut library
   glutInit ( &argc, argv );
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

// Fallback to OpenGL 3.3 on Linux (fine for this lab)
#if !(defined WIN32)   
   glutInitContextVersion (3, 3);
#endif

   glutInitContextProfile ( GLUT_CORE_PROFILE );
 
   // Now create the window of your application:
   AppWindow* w = new AppWindow ( "CSE-170 Support Code", 300, 300, 600, 600 );

   // Finally start the main loop:
   w->run ();
}