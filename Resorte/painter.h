#ifndef PAINTER_H
#define PAINTER_H

#include "spring.h"


class Painter: public QWidget
{
	Q_OBJECT
public:
    Painter( QWidget *parent=0 );

private slots:
	void doRemove(  ) {
		//forceValue -> setValue( 0.0 );
		emit sendRemove( );
	}

signals:
	void sendRemove( );

private:
	Spring * spring;
	QPushButton *quit, *reset, *apply, *remove;
	QLabel *forceText, *textoAngulo, *textoAngulo2, *textoNodo, *textoResolucion;
	QDoubleSpinBox *forceValue, *angulo, *angulo2;
	QSpinBox *nodo, *resolucion;
};

#endif
