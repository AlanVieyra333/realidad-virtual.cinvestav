/** 
	A "hello" program in Qt
	that use OpenGL drawing primitives
	File: quad.cpp

	Fraga 19/09/2001
**/
#include <qpainter.h>
#include <ctype.h>
#include "cubo.h"
#include <GL/glu.h>

Cubo::Cubo( QWidget *parent )
		: QGLWidget( parent )
//  : QGLWidget( QGLFormat( QGL::SingleBuffer|QGL::NoDepthBuffer ), parent )
{
	signo = 1;	

	// setMouseTracking( TRUE );

	// setFocusPolicy( QWidget::StrongFocus);
	setFocusPolicy( Qt::StrongFocus);

	timer = new QTimer( this );
	connect ( timer, SIGNAL(timeout()), this, SLOT(timerDone()) );

	xrot = yrot = 0;
	angle = 0;

	setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	crea_cubo( 1.0, cubo1 );
}


void Cubo::timerDone( )
{
	angle += 3.0*signo;

	if ( angle >= 360.0 ) angle = 0.0;
	if ( angle <= -360.0 ) angle = 0.0;
	
	updateGL( );
}

void Cubo::mouseMoveEvent( QMouseEvent * e )
{
	QPoint c = e->pos( );

	xmouse = c.x( );
	ymouse = c.y( );
	if ( xmouse>=0 && ymouse>=0 )  emit changePos ( );

	yrot = (float)xmouse*360.f/(float)windowWidth - 180.f;
	xrot = (float)ymouse*360.f/(float)windowHeight - 180.f;

	updateGL( );
}

void Cubo::keyPressEvent ( QKeyEvent * e )
{
	switch ( e->key() ) {
		case '+':   
			signo = 1;
			break;
		case '-':  
			signo = -1;
			break;
	}
}

//
// This method puts the initial coordinates each time window is resized
//
void Cubo::resizeGL( int l, int a )
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

QSizePolicy Cubo::sizePolicy() const
{
	return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}

void Cubo::paintGL(void)
{
	/** Clear all pixels **/
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix( );
	gluLookAt( 0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ); 

	glRotatef (yrot, 0.0, 1.0, 0.0);
	glRotatef (xrot, 1.0, 0.0, 0.0);

	glRotatef(-45.00, 0.0, 1.0, 0.0 );
	glRotatef( 35.26, 0.0, 0.0, 1.0 );
	glRotatef( angle, 1.0, 0.0, 0.0 );
	glRotatef(-35.26, 0.0, 0.0, 1.0 );
	glRotatef( 45.00, 0.0, 1.0, 0.0 );
	dibuja_cubo( cubo1 );
	glPopMatrix( );

	// swapBuffers( );
}

void Cubo::initializeGL( ) 
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


void Cubo::crea_cubo( float l, float cubo[][3] )
{
	cubo[0][0] = l; cubo[0][1] = l; cubo[0][2] = l;
	cubo[1][0] = l; cubo[1][1] = l; cubo[1][2] = 0;
	cubo[2][0] = 0; cubo[2][1] = l; cubo[2][2] = 0;
	cubo[3][0] = 0; cubo[3][1] = l; cubo[3][2] = l;

	cubo[4][0] = l; cubo[4][1] = 0; cubo[4][2] = l;
	cubo[5][0] = l; cubo[5][1] = 0; cubo[5][2] = 0;
	cubo[6][0] = 0; cubo[6][1] = 0; cubo[6][2] = 0;
	cubo[7][0] = 0; cubo[7][1] = 0; cubo[7][2] = l;
}


void Cubo::dibuja_cubo( float cubo[][3] ) 
{
	static float Mcolores[6][3] = {
		{1.0,0.0,0.0}, // rojo
		{0.0,1.0,0.0}, // verde
		{0.0,0.0,1.0}, // azul
		{1.0,1.0,0.0}, // amarillo
		{1.0,1.0,1.0}, // blanca
		{1.0,0.0,1.0} };  // magenta

	static int Mcaras[6][4] = {
		{ 0, 1, 2, 3},
		{ 4, 7, 6, 5},
		{ 0, 4, 5, 1},
		{ 1, 2, 6, 5},
		{ 2, 6, 7, 3},
		{ 0, 3, 7, 4} };

	int i;

	glBegin( GL_QUADS );
	for( i=0; i<6; i++ ) {
		glColor3fv( &Mcolores[i][0] );
		glVertex3fv( &cubo[ Mcaras[i][0] ][0] );
		glVertex3fv( &cubo[ Mcaras[i][1] ][0] );
		glVertex3fv( &cubo[ Mcaras[i][2] ][0] );
		glVertex3fv( &cubo[ Mcaras[i][3] ][0] );
	}
	glEnd( );
}
