#include <QPushButton>
#include <QLabel>
#include <QLayout>

#ifndef PAINTER_H
#define PAINTER_H

#include "canvas.h"
#include "driver/SpaceMouseListener.h"

class Painter: public QWidget, public SpaceMouseListener
{
	Q_OBJECT
public:
    Painter( QWidget *parent=0 );
	void addShape(Figura*);
	void setEye(float, float, float);
	void setCenter(float, float, float);
	void setCenterDegree(float);
	void set_3dMouse(float tx, float ty, float tz, float rx, float ry, float rz);

	bool isSpaceMouseActive() override;
    void setSpaceMouseActive(bool value) override;
    void spaceMouseMovement(const int &TX, const int &TY, const int &TZ, const int &RX, const int &RY, const int &RZ) override;
    void spaceMouseButton(const int &id) override;
		
private slots:
	void newPosition( );

private:
	
	Canvas *canvas;
	QLabel *forceText, *textoAngulo, *textoAngulo2, *textoResolucion, *messpos, *visorMouse;
	QPushButton *quit, *myinit, *stop, *reset;
	QDoubleSpinBox *forceValue, *angulo, *angulo2;
	QSpinBox *resolucion;

	bool space_mouse_active = false;
};

#endif
