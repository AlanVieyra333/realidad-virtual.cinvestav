#include "canvas.h"
#include <qpainter.h>
#include <math.h>

#include "utils/data_shape.h"
#include "utils/geom_func.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/glu.h>
#elif defined __linux__
    #include <GL/glu.h>
#endif

using namespace std;

Canvas::Canvas( QWidget *parent )
		: QGLWidget( parent )
{
	signo = 1;	

	setFocusPolicy( Qt::StrongFocus);

	timer = new QTimer( this );
	connect ( timer, SIGNAL(timeout()), this, SLOT(timerDone()) );

	xrot = yrot = 0;

	setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

	// Init datatype of data shape.
	dataMesh* data_mesh = (dataMesh*) malloc(sizeof(dataMesh));
	data_mesh->apply_force = false;
	data_mesh->v_force[0] = 0; data_mesh->v_force[1] = 0.2; data_mesh->v_force[2] = 0;
	data_mesh->resolution = 1;
	data_mesh->mouse3d_x = 0;
	data_mesh->mouse3d_y = 0;
	data_shape = (void *) data_mesh;
}

Canvas::~Canvas() {
	free(data_shape);
}

void Canvas::timerDone( )
{
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
			//setCenterDegree(centerDegree - 2.0);
			eye[0] -= 0.1;
			updateGL( );
			break;
		case 16777236:	// Right
			//setCenterDegree(centerDegree + 2.0);
			eye[0] += 0.1;
			updateGL( );
			break;
		case 16777235:	// Up
			eye[1] += 0.1;
			//center[1] += 0.1;
			updateGL( );
			break;
		case 16777237:	// Down
			eye[1] -= 0.1;
			//center[1] -= 0.1;
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

	timer->start(1000 * 1 / 30);
}

void Canvas::paintGL(void)
{
	/** Clear all pixels **/
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix( );

	gluLookAt(
		eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0.0, 1.0, 0.0
	); 

	glLineWidth( 4.0 );
	glPointSize( 8.0 );

	glRotatef (yrot, 0.0, 1.0, 0.0);
	glRotatef (xrot, 1.0, 0.0, 0.0);

	/* Paint shapes */
	for (auto&& shape : shapes) shape->dibuja_figura(data_shape);
	
	glPopMatrix( );
}

void Canvas::addShape(Figura *shape) {
	shapes.push_back(shape);
}

void Canvas::setEye(float x, float y, float z) {
	eye[0] = x;
	eye[1] = y;
	eye[2] = z;

	eyeO[0] = x;
	eyeO[1] = y;
	eyeO[2] = z;
}

void Canvas::setCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;

	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void Canvas::setCenterDegree(float degree) {
    centerDegree = degree;

	if(centerDegreeO == 0)
		centerDegreeO = degree;

	center[0] = eye[0] + centerRadio * cos(centerDegree * M_PI / 180.0);
	center[2] = eye[2] + centerRadio * sin(centerDegree * M_PI / 180.0);
}

void Canvas::initscreen(void) {
	((dataMesh*) data_shape)->apply_force = true;
}

void Canvas::stop(void) {
	((dataMesh*) data_shape)->apply_force = false;
}

void Canvas::reset(void) {
	((dataMesh*) data_shape)->apply_force = false;
	xrot = yrot = 0;

	eye[0] = eyeO[0]; eye[1] = eyeO[1]; eye[2] = eyeO[2];
	centerDegree = centerDegreeO;
	center[0] = centerO[0]; center[1] = centerO[1]; center[2] = centerO[2];

	//timer->stop( );
	updateGL( );
}

/*	#########################################################	*/

void Canvas::set_resolution(int val) {
	((dataMesh*) data_shape)->resolution = val;
}

void Canvas::set_v_force(float force, float alpha, float beta) {
	this->force = force;
	this->alpha = alpha;
	this->beta = beta;
	vector<float> v_force_tmp = to_vector_force(force, alpha, beta);
	((dataMesh*) data_shape)->v_force[0] = v_force_tmp[0];
	((dataMesh*) data_shape)->v_force[1] = v_force_tmp[1];
	((dataMesh*) data_shape)->v_force[2] = v_force_tmp[2];
}

void Canvas::set_force(double force) {
	set_v_force(force, alpha, beta);
}

void Canvas::set_angle_alpha(double alpha) {
	set_v_force(force, alpha, beta);
}

void Canvas::set_angle_beta(double beta) {
	set_v_force(force, alpha, beta);
}

void Canvas::set_3dMouse(short rx, short ry) {
	((dataMesh*) data_shape)->mouse3d_x = rx;
	((dataMesh*) data_shape)->mouse3d_y = ry;
}