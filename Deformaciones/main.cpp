/**
	A example for drawing crated primitives

	Fraga 11/09/2000
**/

#include <QApplication>
#include <vector>

#include "painter.h"

#include "figuras/mesh.h"

void addShapes(Painter *);

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    Painter w;

    w.setGeometry( 100, 100, 1000, 540 );		//355 );
    addShapes(&w);
    w.setEye(2.1, 5.2, 4.0);
    w.setCenter(0.0, 0.0, 0.0);
    //w.setCenterDegree(-90);

    w.show();         // Show widget
    return a.exec();  // go!
}

/*	Add shapes into canvas	*/
void addShapes(Painter *w) {
	vector<float> v1, v2;
    
    // Malla
    v1 = {-1.0, 0.0, -1.0};
    v2 = {v1[0] + 2, v1[1], v1[2] + 2};
    w->addShape(new Mesh(v1, v2));
}
