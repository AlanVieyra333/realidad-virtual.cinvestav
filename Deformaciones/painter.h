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
		void set_3dMouse(short rx, short ry);
		
private slots:
	void newPosition( );

private:
	
	Canvas *canvas;
	QLabel *forceText, *textoAngulo, *textoAngulo2, *textoResolucion, *messpos, *visorMouse;
	QPushButton *quit, *myinit, *stop, *reset;
	QDoubleSpinBox *forceValue, *angulo, *angulo2;
	QSpinBox *resolucion;
};

#endif
