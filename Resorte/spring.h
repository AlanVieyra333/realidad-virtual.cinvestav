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

#define NODOS_BASE 7

class Spring: public QGLWidget
{
	Q_OBJECT  // Debe incluirse para usar se�ales/ranuras de Qt
public:
	Spring( QWidget *parent=0 );
	~Spring( );

	void createSpring( void );
	void muestraResorte( void );
	QSizePolicy sizePolicy() const;
	void replica_fuerza_a_la_izquierda( int i, double fx, double fy, double fz );
	void replica_fuerza_a_la_derecha( int i, double fx, double fy, double fz );

public slots:
	void poneResolucion(int val) {
		int val_anterior;
		if (r.nodos == NODOS_BASE)
		{
			val_anterior = 1;
		} else if (r.nodos == (NODOS_BASE*2) - 1)
		{
			val_anterior = 2;
		} else {
			val_anterior = 3;
		}
		
		switch (val)
		{
		case 1:
			r.nodos = NODOS_BASE;
			if (val_anterior == 2)
				r.nodo_actual = r.nodo_actual/2;
			else if (val_anterior == 3)
				r.nodo_actual = r.nodo_actual/4;
			break;
		case 2:
			r.nodos = (NODOS_BASE*2) - 1;
			if (val_anterior == 1)
				r.nodo_actual = r.nodo_actual*2;
			else if (val_anterior == 3)
				r.nodo_actual = r.nodo_actual/2;
			break;
		case 3:
			r.nodos = (NODOS_BASE*4) - 3;
			if (val_anterior == 1)
				r.nodo_actual = r.nodo_actual*4;
			else if (val_anterior == 2)
				r.nodo_actual = r.nodo_actual*2;
			break;
		default:
			break;
		}

		delta = (NODOS_BASE - 1.0) / (r.nodos - 1.0);
		InicializaSistema(&r);
	}
	void poneNodo( int val ) {
		if(val < r.nodos)
			r.nodo_actual = val;
		updateGL();
	}
	void resetea( void ) {
		timer->stop( );
		updateGL();
	}
	void deforma( void ) { 
		//double fx = r.f * cos(r.theta);
		//double fy = r.f * sin(r.theta);
		double fx = cos(r.theta2) * cos(r.theta);
		double fz = sin(r.theta2) * cos(r.theta); 
		double fy = sin(r.theta);

		//printf("%lf %lf\n", r.theta, r.theta2);
		//printf("%lf %lf %lf\n", fx, fy, fz);
		// Normalize
		double length = sqrt(fx*fx + fy*fy + fz*fz);
		fx /= length;
		fy /= length;
		fz /= length;
		//printf("%lf\n", length);
		// Aplicar fuerza
		fx *= r.f;
		fy *= r.f;
		fz *= r.f;
		//printf("%lf %lf %lf\n", fx, fy, fz);

		// Aplicamos la fuerza al nodo s.nodo
		r.s[r.nodo_actual].k3x = ( fx * r.dt * r.dt)/r.m;
		r.s[r.nodo_actual].k3y = ( fy * r.dt * r.dt)/r.m;
		r.s[r.nodo_actual].k3z = ( fz * r.dt * r.dt)/r.m;

		// aplica_fuerza( s.nodo );
		// se aplican inializando las variales k3 de cada resorte
		replica_fuerza_a_la_derecha( r.nodo_actual, fx, fy, fz );
		replica_fuerza_a_la_izquierda( r.nodo_actual, fx, fy, fz );

		timer->start( 33 );
	}
	void quitaFuerza( void ) { 
		//r.f = 0.0;
		for( int i=0; i<r.nodos; i++ ) {
			r.s[i].k3x = r.s[i].k3y = r.s[i].k3z = 0.0;
		}
	}
	void poneFuerza( double fuerza ) { 
		r.f = fuerza;
		// fprintf( stderr, "f = %lf\n", r.f );
	}
	void poneAngulo( double a ) { 
		r.theta = a * M_PI/180.0;
	}
	void poneAngulo2( double a ) { 
		r.theta2 = a * M_PI/180.0;
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
	typedef struct mra {
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
	typedef struct mra2d {
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
	MRA2D r;
	void setRy(short ry);
	void applyForce();
};


#endif // SPRING_H
