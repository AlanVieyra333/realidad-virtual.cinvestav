/** 
	Una malla en 1D de sistemas masa, resorte y amortiguador (MRA)

    |---*---*---*---|

	Fraga 11.11.2019 
**/
#include <qpainter.h>
#include <ctype.h>
#include <GL/glu.h>
#include "spring.h"

Spring::Spring( QWidget *parent )
		: QGLWidget( parent )
{
	// setMouseTracking( TRUE );

	timer = new QTimer( this );
	connect ( timer, SIGNAL(timeout()), this, SLOT(unPasoDeformacion()) );

	setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

	r.nodos = NODOS_BASE;	// 7, 13, 25
	delta = (NODOS_BASE - 1.0)/(r.nodos - 1.0);
	InicializaSistema( &r );
}

Spring::~Spring( )
{
	free( r.s );
}

void Spring::InicializaSistema( MRA2D *s )
{
	s->f = 0.2;
	s->k = 0.2;
	s->m = 0.01;
	s->b = 0.02667;

	s->dt = 1.0/30.0;

	s->k1 = 2.0 - s->dt*(s->k*s->dt + s->b)/s->m;
	s->k2 = 1.0 - s->dt*s->b/s->m;

	//s->nodo_actual = 0;

	int max_nodos = (NODOS_BASE*4) - 3;
	if(s->s == NULL)
		s->s = (MRA *)malloc( max_nodos * sizeof(MRA) );
	if( s->s == NULL ) {
		fprintf( stderr, "ERROR: no memory\n" );
		exit(1);
	} 
	// Inicializa vecinos:
	s->s[0].izq = -1;
	s->s[0].der =  1;
	for( int i=1; i<s->nodos-1; i++ ) {
		s->s[i].izq = i-1;
		s->s[i].der = i+1;
	}
	s->s[s->nodos-1].izq = s->nodos-2;
	s->s[s->nodos-1].der =  -1;

	// Inicializa posiciones:
	double d_nodo = 2.0 / (s->nodos + 1.0);
	for( int i=0; i<s->nodos; i++ ) {
		s->s[i].x0 = -1.0 + d_nodo*(i+1);
		s->s[i].y0 = 0.0;
		s->s[i].z0 = 0.0;
		s->s[i].x_1 = s->s[i].x = s->s[i].x1 = 0.0;
		s->s[i].y_1 = s->s[i].y = s->s[i].y1 = 0.0;
		s->s[i].z_1 = s->s[i].z = s->s[i].z1 = 0.0;
	}

	//double fx = s->f * cos(s->theta);
	//double fy = s->f * sin(s->theta);
	//double fz = s->f * 0.0;
	double fx = cos(s->theta2) * cos(s->theta);
	double fz = sin(s->theta2) * cos(s->theta);
	double fy = sin(s->theta);
	// Normalize
	double length = sqrt(fx*fx + fy*fy + fz*fz);
	fx /= length;
	fy /= length;
	fz /= length;
	// Aplicar fuerza
	fx *= s->f;
	fy *= s->f;
	fz *= s->f;

	// Aplicamos la fuerza al nodo s.nodo
	s->s[s->nodo_actual].k3x = ( fx * s->dt * s->dt)/s->m;
	s->s[s->nodo_actual].k3y = ( fy * s->dt * s->dt)/s->m;
	s->s[s->nodo_actual].k3z = ( fz * s->dt * s->dt)/s->m;
	
	// aplica_fuerza( s.nodo );
	// se aplican inializando las variales k3 de cada resorte
	replica_fuerza_a_la_derecha( s->nodo_actual, fx, fy, fz );
	replica_fuerza_a_la_izquierda( s->nodo_actual, fx, fy, fz );
}

void Spring::replica_fuerza_a_la_derecha( int n, double fx, double fy, double fz )
{
	int i = n + 1;
	double d = 0;

	while( i < r.nodos ){
		d += delta;
		double fx_aux = fx / pow(2.0, d);
		double fy_aux = fy / pow(2.0, d);
		double fz_aux = fz / pow(2.0, d);
		//printf("AUX: %lf %lf %lf\n", fx_aux, fy_aux, fz_aux);
		r.s[i].k3x = ( fx_aux * r.dt * r.dt)/r.m;
		r.s[i].k3y = ( fy_aux * r.dt * r.dt)/r.m;
		r.s[i].k3z = ( fz_aux * r.dt * r.dt)/r.m;
		i++;
	}
}

void Spring::replica_fuerza_a_la_izquierda( int n, double fx, double fy, double fz )
{
	int i = n - 1;
	double d = 0;

	while( i >= 0 ){
		d += delta;
		double fx_aux = fx / pow(2.0, d);
		double fy_aux = fy / pow(2.0, d);
		double fz_aux = fz / pow(2.0, d);
		r.s[i].k3x = ( fx_aux * r.dt * r.dt)/r.m;
		r.s[i].k3y = ( fy_aux * r.dt * r.dt)/r.m;
		r.s[i].k3z = ( fz_aux * r.dt * r.dt)/r.m;
		i--;
	}
}

//
// This method puts the initial coordinates each time window is resized
//
void Spring::resizeGL( int w, int h )
{
	float aspect=(float)w/(float)h;

	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	if( w <= h )
		glOrtho( -1.0, 1.0, -1.0/aspect, 1.0/aspect, -1.0, 1.0);
	else
		glOrtho( -1.0*aspect, 1.0*aspect, -1.0, 1.0, -1.0, 1.0);
}

void Spring::paintGL( void )
{
	/** Clear all pixels **/
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();			 /* clear the matrix */

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	static double center[] = {0.0, 0.0, 0.0};
	static double eye[] = {0.25, 0.25, 0.25};

	gluLookAt(
		eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0.0, 1.0, 0.0
	);

	glLineWidth( 4.0 );
	glPointSize( 8.0 );
	muestraResorte(  );

	// swapBuffers( );
}

void Spring::initializeGL( ) 
{
	glClearColor ( 0.8, 0.8, 0.8, 0.0);	// Background to a grey tone

	/* initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glEnable (GL_DEPTH_TEST);

}

void Spring::muestraResorte(  )
{  
	glBegin( GL_LINE_STRIP );
		glColor3f( 1.0, 0.0, 0.0);

		glVertex3d( -0.99, 0.0, 0.0 );
		for( int i = 0; i<r.nodos; i++) { 
			double x1 = r.s[i].x0 + r.s[i].x1;
			double y1 = r.s[i].y0 + r.s[i].y1;
			double z1 = r.s[i].z0 + r.s[i].z1;

			glVertex3d( x1, y1, z1 );
		}
		glVertex3d(  0.99, 0.0, 0.0 );
	glEnd(  );
	glBegin( GL_POINTS );
		glColor3f( 0.0, 0.0, 1.0 );
		double x1 = r.s[r.nodo_actual].x0 + r.s[r.nodo_actual].x1;
		double y1 = r.s[r.nodo_actual].y0 + r.s[r.nodo_actual].y1;
		double z1 = r.s[r.nodo_actual].z0 + r.s[r.nodo_actual].z1;
		glVertex3d( x1, y1, z1 );

		glVertex3d( -0.99, 0.0, 0.01 );
		glVertex3d(  0.99, 0.0, 0.01 );
	glEnd(  );
}


void Spring::unPasoDeformacion( void )
{
	for( int i=0; i<r.nodos; i++ ) { 
		r.s[i].x1 = r.k1 * r.s[i].x - r.k2 * r.s[i].x_1 + r.s[i].k3x;
		r.s[i].x_1 = r.s[i].x;
		r.s[i].x   = r.s[i].x1;

		r.s[i].y1 = r.k1 * r.s[i].y - r.k2 * r.s[i].y_1 + r.s[i].k3y;
		r.s[i].y_1 = r.s[i].y;
		r.s[i].y   = r.s[i].y1;

		r.s[i].z1 = r.k1 * r.s[i].z - r.k2 * r.s[i].z_1 + r.s[i].k3z;
		r.s[i].z_1 = r.s[i].z;
		r.s[i].z   = r.s[i].z1;
	}

	updateGL();
}
	
