/**
	A example for drawing crated primitives

	Fraga 11/09/2000
**/

#include <QApplication>
#include <vector>

#include "painter.h"

#include "utils/color.h"
#include "figuras/cubo.h"

void addShapes(Painter *);

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    Painter w;

    w.setGeometry( 100, 100, 1000, 540 );		//355 );
    addShapes(&w);
    w.setEye(20.0, 2.0, -5.0);
    w.setCenterDegree(135);

    w.show();         // Show widget
    return a.exec();  // go!
}

/*	Add shapes into canvas	*/
void addShapes(Painter *w) {
	vector<float> v1, v2;
    
    // Piso
    v1 = {0,0,0};
    v2 = {v1[0] + (float) 15.0, v1[1] + (float) 0.5, v1[2] + (float) 8.0};
	w->addShape(new Cubo(v1, v2, Color.Gray));
    // Tabla
    v1 = {v1[0] + (float) 0.0, v1[1] + (float) 0.5, v1[2] + (float) 0.0};
	v2 = {v1[0] + (float) 3.0, v1[1] + (float) 0.5, v1[2] + (float) 8.0};
	w->addShape(new Cubo(v1, v2, Color.Wine));
    // Obstaculo 1
	v1 = {v1[0] + (float) 3.5, v1[1] + (float) 0.0, v1[2] + (float) 0.0};
	v2 = {v1[0] + (float) 3.0, v1[1] + (float) 1.0, v1[2] + (float) 3.0};
	w->addShape(new Cubo(v1, v2, Color.Brown));
    // Obstaculo 2
	v1 = {v1[0] + (float) 4.0, v1[1] + (float) 0.0, v1[2] + (float) 0.0};
	v2 = {v1[0] + (float) 2.0, v1[1] + (float) 3.0, v1[2] + (float) 2.0};
	w->addShape(new Cubo(v1, v2, Color.Brown));
    // Obstaculo 3
	v1 = {v1[0] - (float) 4.0, v1[1] + (float) 0.0, v1[2] + (float) 5.0};
	v2 = {v1[0] + (float) 3.0, v1[1] + (float) 2.0, v1[2] + (float) 3.0};
	w->addShape(new Cubo(v1, v2, Color.Brown));
    // Obstaculo 4
	v1 = {v1[0] + (float) 4.0, v1[1] + (float) 0.0, v1[2] + (float) 0.0};
	v2 = {v1[0] + (float) 3.0, v1[1] + (float) 1.0, v1[2] + (float) 3.0};
	w->addShape(new Cubo(v1, v2, Color.Brown));
    // Obstaculo 5
	v1 = {v1[0] + (float) 4.0, v1[1] + (float) 0.0, v1[2] + (float) 0.0};
	v2 = {v1[0] + (float) 3.0, v1[1] + (float) 2.0, v1[2] + (float) 3.0};
	w->addShape(new Cubo(v1, v2, Color.Brown));

    // Obstaculo n
	//v1 = {v1[0] + (float) 0.0, v1[1] + (float) 0.0, v1[2] + (float) 0.0};
	//v2 = {v1[0] + (float) 0.0, v1[1] + (float) 0.0, v1[2] + (float) 0.0};
	//w->addShape(new Cubo(v1, v2, Color.Brown));
}
