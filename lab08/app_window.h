
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

# include <gsim/gs_color.h>
# include <gsim/gs_array.h>
# include <gsim/gs_vec.h>
# include "ogl_tools.h"
# include "glut_window.h"
# include "so_axis.h"
# include "so_poly.h"
# include "so_line.h"
# include "so_lineshape.h"

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
    // OpenGL shaders and programs:
	 GlShader _flatvsh, _flatfsh, _linevsh, _linefsh;
	 GlProgram _prog, _lineprog;

    // My scene objects:
    SoAxis _axis;
    SoPoly _poly;
	SoLine _line;
	SoLineShape _lineShape;

    // App data:
    enum MenuEv { evOption0, evOption1 };
	enum CurveType { None, Lagrange, Bezier};

    float _rotx, _roty; // scene transformation data
    GsVec _trans;       // scene transformation data
    GsMat _str;         // scene transformation

    GsVec _eye, _center, _up; // camera data
    GsMat _cam;               // camera transformation
    float _aspect, _znear, _zfar, _fovy; // perspective projection data
    GsMat _proj;              // projection transformation
    GsMat _spr;               // final scene projection _spr=_cam*_proj

    float _pickprec;
    bool _viewaxis;
    bool _oktodrag;
    int _w, _h;
	bool _updated;
	CurveType _curveType;
	bool _autoUpdate3D;
	int _segments;
	bool _forcedUpdate;

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void initPrograms ();
    GsVec2 windowToScene ( const GsVec2& v );
    GsVec rayXYintercept ( const GsVec2& v );

   private : // functions derived from the base class
    virtual void glutMenu ( int m );
    virtual void glutKeyboard ( unsigned char key, int x, int y );
    virtual void glutSpecial ( int key, int x, int y );
    virtual void glutMouse ( int b, int s, int x, int y );
    virtual void glutMotion ( int x, int y );
    virtual void glutDisplay ();
    virtual void glutReshape ( int w, int h );
 };

#endif // APP_WINDOW_H