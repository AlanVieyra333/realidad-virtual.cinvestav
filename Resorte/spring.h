/**
	Definiciones para un programa
	para deformar un simple sistema resorte-masa-amortiguador en 2D
	(este programa usa primivitas de OpenGL y  Qt v. 4)

	Fraga  8/12/2010
	Fraga 28/01/2012
**/
#ifndef SPRING_H
#define SPRING_H

#include <QWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QDoubleSpinBox>
#include <math.h>

#define BASE_NODES 7
#define RESOLUTION_LEVEL 3
#define MAX_NODES (((BASE_NODES>>1) << RESOLUTION_LEVEL) + 1)		// 25  -> 7 nodos y resolucion 3

class Spring: public QGLWidget
{
	Q_OBJECT  // Debe incluirse para usar se�ales/ranuras de Qt
public:
	Spring( QWidget *parent=0 );
	~Spring( );

	void createSpring( void );
	void muestraResorte( void );
	void muestraMalla( void );
	QSizePolicy sizePolicy() const;
	void replica_fuerza_a_la_izquierda( int i, double fx, double fy, double fz );
	void replica_fuerza_a_la_derecha( int i, double fx, double fy, double fz );

public slots:
	void poneResolucion(int val) {
		int val_anterior;
		if (mra2d.nodos == BASE_NODES)
		{
			val_anterior = 1;
		} else if (mra2d.nodos == (BASE_NODES*2) - 1)
		{
			val_anterior = 2;
		} else {
			val_anterior = 3;
		}
		
		switch (val)
		{
		case 1:
			mra2d.nodos = BASE_NODES;
			if (val_anterior == 2)
				mra2d.nodo_actual = mra2d.nodo_actual/2;
			else if (val_anterior == 3)
				mra2d.nodo_actual = mra2d.nodo_actual/4;
			break;
		case 2:
			mra2d.nodos = (BASE_NODES*2) - 1;
			if (val_anterior == 1)
				mra2d.nodo_actual = mra2d.nodo_actual*2;
			else if (val_anterior == 3)
				mra2d.nodo_actual = mra2d.nodo_actual/2;
			break;
		case 3:
			mra2d.nodos = (BASE_NODES*4) - 3;
			if (val_anterior == 1)
				mra2d.nodo_actual = mra2d.nodo_actual*4;
			else if (val_anterior == 2)
				mra2d.nodo_actual = mra2d.nodo_actual*2;
			break;
		default:
			break;
		}

		delta = (BASE_NODES - 1.0) / (mra2d.nodos - 1.0);
		InicializaSistema(&mra2d);
	}
	void poneNodo( int val ) {
		if(val < mra2d.nodos)
			mra2d.nodo_actual = val;
		updateGL();
	}
	void resetea( void ) {
		timer->stop( );
		updateGL();
	}
	void deforma( void ) { 
		//double fx = mra2d.f * cos(mra2d.theta);
		//double fy = mra2d.f * sin(mra2d.theta);
		double fx = cos(mra2d.theta2) * cos(mra2d.theta);
		double fz = sin(mra2d.theta2) * cos(mra2d.theta); 
		double fy = sin(mra2d.theta);

		//printf("%lf %lf\n", mra2d.theta, mra2d.theta2);
		//printf("%lf %lf %lf\n", fx, fy, fz);
		// Normalize
		double length = sqrt(fx*fx + fy*fy + fz*fz);
		fx /= length;
		fy /= length;
		fz /= length;
		//printf("%lf\n", length);
		// Aplicar fuerza
		fx *= mra2d.f;
		fy *= mra2d.f;
		fz *= mra2d.f;
		//printf("%lf %lf %lf\n", fx, fy, fz);

		// Aplicamos la fuerza al nodo s.nodo
		mra2d.s[mra2d.nodo_actual].k3x = ( fx * mra2d.dt * mra2d.dt)/mra2d.m;
		mra2d.s[mra2d.nodo_actual].k3y = ( fy * mra2d.dt * mra2d.dt)/mra2d.m;
		mra2d.s[mra2d.nodo_actual].k3z = ( fz * mra2d.dt * mra2d.dt)/mra2d.m;

		// aplica_fuerza( s.nodo );
		// se aplican inializando las variales k3 de cada resorte
		replica_fuerza_a_la_derecha( mra2d.nodo_actual, fx, fy, fz );
		replica_fuerza_a_la_izquierda( mra2d.nodo_actual, fx, fy, fz );

		timer->start( 33 );
	}
	void quitaFuerza( void ) { 
		//mra2d.f = 0.0;
		for( int i=0; i<mra2d.nodos; i++ ) {
			mra2d.s[i].k3x = mra2d.s[i].k3y = mra2d.s[i].k3z = 0.0;
		}
	}
	void poneFuerza( double fuerza ) { 
		mra2d.f = fuerza;
		// fprintf( stderr, "f = %lf\n", mra2d.f );
	}
	void poneAngulo( double a ) { 
		mra2d.theta = a * M_PI/180.0;
	}
	void poneAngulo2( double a ) { 
		mra2d.theta2 = a * M_PI/180.0;
	}
	void unPasoDeformacion( void );

protected:
	void initializeGL( void );
	void resizeGL( int w, int h );
	void paintGL( void );
 
 
private:
	QTimer *timer;

	int windowWidth, windowHeight;   // canvas width and height

	float yrot, xrot;  // Encene rotation

	double angle;

	// Una estructura para almacenar el estado de un nodo.
	// Este es un sistema MRA con otro resorte extra solo con kint
	typedef struct _MRA {
		double x0;
		double x_1, x, x1;
		double k3x;

		double y0;
		double y_1, y, y1;
		double k3y;

		double z0;
		double z_1, z, z1;
		double k3z;

		int izq;
		int der;
	} MRA;

	// Resorte en dos dimensiones
	typedef struct _MRA2D {
		double k, m, b;
		double dt;  // Delta i inicial: dt = 0.0333333333;
		double k1, k2;

		// La fuerza aplicada:
		double f, theta = 0, theta2 = 0;
		int nodo_actual = 0;

		MRA *s = NULL;
		int nodos;
	} MRA2D;

	 
	double delta = 1.0;

public:
	void InicializaSistema( MRA2D *s );
	MRA2D mra2d;
	void setRy(short ry);
	void applyForce();
};


#endif // SPRING_H
