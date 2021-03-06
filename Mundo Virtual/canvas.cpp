#include "canvas.h"
#include <qpainter.h>
#include <OpenGL/glu.h>
#include <math.h>

using namespace std;

Canvas::Canvas( QWidget *parent )
		: QGLWidget( parent )
{
	signo = 1;	

	setFocusPolicy( Qt::StrongFocus);

	timer = new QTimer( this );
	connect ( timer, SIGNAL(timeout()), this, SLOT(timerDone()) );

	xrot = yrot = 0;
	angle = 0;

	setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}

void Canvas::timerDone( )
{
	angle += 3.0*signo;

	if ( angle >= 360.0 ) angle = 0.0;
	if ( angle <= -360.0 ) angle = 0.0;
	
	updateGL( );
}

void Canvas::mouseMoveEvent( QMouseEvent * e )
{
	QPoint c = e->pos( );

	xmouse = c.x( );
	ymouse = c.y( );
	if ( xmouse>=0 && ymouse>=0 )  emit changePos ( );

	yrot = (float)xmouse*360.f/(float)windowWidth - 180.f;
	xrot = (float)ymouse*360.f/(float)windowHeight - 180.f;

	updateGL( );
}

void Canvas::keyPressEvent ( QKeyEvent * e )
{
	switch ( e->key() ) {
		case '+':   
			signo = 1;
			break;
		case '-':  
			signo = -1;
			break;
		case 16777234:	// Left
			centerDegree -= 2.0;
			updateGL( );
			break;
		case 16777236:	// Right
			centerDegree += 2.0;
			updateGL( );
			break;
		case 16777235:	// Up
			eye[1] += 0.1;
			center[1] += 0.1;
			updateGL( );
			break;
		case 16777237:	// Down
			eye[1] -= 0.1;
			center[1] -= 0.1;
			updateGL( );
			break;
		case 16777220:  // Intro - Walk
			eye[0] = eye[0] + 0.1 * cos(centerDegree * M_PI / 180.0);
			eye[2] = eye[2] + 0.1 * sin(centerDegree * M_PI / 180.0);

			center[0] = center[0] + 0.1 * cos(centerDegree * M_PI / 180.0);
			center[2] = center[2] + 0.1 * sin(centerDegree * M_PI / 180.0);
			updateGL( );
			break;
		case 16777219:  // Delete - Walk reverse
			eye[0] = eye[0] - 0.1 * cos(centerDegree * M_PI / 180.0);
			eye[2] = eye[2] - 0.1 * sin(centerDegree * M_PI / 180.0);

			center[0] = center[0] - 0.1 * cos(centerDegree * M_PI / 180.0);
			center[2] = center[2] - 0.1 * sin(centerDegree * M_PI / 180.0);
			updateGL( );
			break;
	}
}

//
// This method puts the initial coordinates each time window is resized
//
void Canvas::resizeGL( int l, int a )
{
	float aspect=(float)l/(float)a;

	windowWidth = l;
	windowHeight = a;

	glViewport (0, 0, (GLsizei) l, (GLsizei) a);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	// gluPerspective( 24.0, aspect,  1.0, 10.0);
	gluPerspective( 24.0, aspect,  6.0, 10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();			 /* clear the matrix */

	emit changeSize ( );
}

QSizePolicy Canvas::sizePolicy() const
{
	return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}

void Canvas::initializeGL( ) 
{
	glClearColor ( 0.8, 0.8, 0.8, 0.0);	// Background to a grey tone

	/* initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glEnable (GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();			 /* clear the matrix */
}

void Canvas::paintGL(void)
{
	/** Clear all pixels **/
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix( );

	center[0] = eye[0] + centerRadio * cos(centerDegree * M_PI / 180.0);
	center[2] = eye[2] + centerRadio * sin(centerDegree * M_PI / 180.0);

	gluLookAt(
		eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0.0, 1.0, 0.0
	); 

	glRotatef (yrot, 0.0, 1.0, 0.0);
	glRotatef (xrot, 1.0, 0.0, 0.0);

	/* Paint shapes */
	for (auto&& figura : figuras) figura->dibuja_figura(angle);
	
	glPopMatrix( );
}

void Canvas::addShape(Figura *figura) {
	figuras.push_back(figura);
}

void Canvas::setEye(float x, float y, float z) {
	eye[0] = x;
	eye[1] = y;
	eye[2] = z;

	eyeO[0] = x;
	eyeO[1] = y;
	eyeO[2] = z;
}

void Canvas::setCenterDegree(float degree) {
  centerDegree = degree;

	centerDegreeO = degree;
}
