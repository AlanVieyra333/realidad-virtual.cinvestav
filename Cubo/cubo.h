/**
	Definitions for "hola" program
	(this use OpenGL primitives and Qt)

	Fraga 19/09/2001
	Fraga 18/09/2017
**/
#ifndef CUBO_H
#define CUBO_H

#include <QWidget>
#include <QtOpenGL>
#include <QTimer>

class Cubo: public QGLWidget
{
	Q_OBJECT  // must include this if you use Qt signals/slots
public:
	Cubo( QWidget *parent=0 );
	QSizePolicy sizePolicy() const;
	void getPosition ( int *x, int *y ) { *x = xmouse; *y = ymouse; }
	void getSize ( int *w, int *h ) { 
		*w = windowWidth; *h = windowHeight; 
	}
	void initCarasColor( void );
    void crea_cubo( float l, float cubo[][3] );
    void dibuja_cubo( float cubo[][3] );

public slots:
	void timerDone( void );
	void initscreen( void ) { 
		timer->start( 17 );
		// timer->start(500);
	}
	void stop( void ) {
		timer->stop( );
 	} 

signals:
	void changePos( ); // called when mouse is moved
	void changeSize( ); // called when windows is resized
 
protected:
	void initializeGL( void );
	void resizeGL( int w, int h );
	void paintGL( void );
	void mouseMoveEvent( QMouseEvent * );
	void keyPressEvent ( QKeyEvent * e );
	// void mousePressEvent( QMouseEvent * );
 
 
private:
	QTimer *timer;

	int windowWidth, windowHeight;   // canvas width and height

	float yrot, xrot;  // Encene rotation

	float angle;
	int signo;
	int xmouse, ymouse;  // Mouse pointer coordinates

	// Una instacia de un cubo se almacena aquí:
	float cubo1[8][3];
};


#endif // CUBO_H
