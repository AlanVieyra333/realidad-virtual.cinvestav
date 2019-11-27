#include <QPushButton>
#include <QLabel>
#include <QLayout>

#ifndef PAINTER_H
#define PAINTER_H

#include "canvas.h"

class Painter: public QWidget
{
	Q_OBJECT
public:
    Painter( QWidget *parent=0 );
		void addShape(Figura*);
		void setEye(float, float, float);
		void setCenter(float, float, float);
		void setCenterDegree(float);
		
private slots:
	void newPosition( );
	void newSize( );

private:
	
	Canvas *canvas;
	QLabel *messpos;
	QLabel *messize;
	QLabel *visorMouse;
	QLabel *visorTama;
	QPushButton *quit, *myinit, *stop, *reset;
};

#endif
