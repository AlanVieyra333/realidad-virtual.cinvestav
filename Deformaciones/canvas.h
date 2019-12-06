#ifndef CANVAS_H
#define CANVAS_H

#include <QtOpenGL>
#include <QTimer>
#include <vector>

#include "figuras/figura.h"

using namespace std;

class Canvas : public QGLWidget
{
	Q_OBJECT // must include this if you use Qt signals/slots
public:
	Canvas(QWidget *parent = 0);
	~Canvas();
	QSizePolicy sizePolicy() const;
	void getPosition(int *x, int *y)
	{
		*x = xmouse;
		*y = ymouse;
	}
	void getSize(int *w, int *h)
	{
		*w = windowWidth;
		*h = windowHeight;
	}
	void set_3dMouse(float tx, float ty, float tz, float rx, float ry, float rz);

public slots:
	void timerDone(void);
	void initscreen(void);
	void stop(void);
	void reset(void);

	void addShape(Figura*);
	void setEye(float, float, float);
	void setCenter(float, float, float);
	void setCenterDegree(float);
	void set_force(double val);
	void set_angle_alpha(double val);
	void set_angle_beta(double val);
	void set_resolution(int val);
	

signals:
	void changePos();	// called when mouse is moved
	void changeSize(); // called when windows is resized

protected:
	void initializeGL(void);
	void resizeGL(int w, int h);
	void paintGL(void);
	void mouseMoveEvent(QMouseEvent *);
	void keyPressEvent(QKeyEvent *e);

private:
	QTimer *timer;

	int windowWidth, windowHeight; // canvas width and height

	float yrot, xrot; // Encene rotation

	int xmouse, ymouse; // Mouse pointer coordinates
	vector<float> eye = {0.0, 0.0, 0.0};
	vector<float> eyeO = {0.0, 0.0, 0.0};
	vector<float> center = {0.0, 0.0, 0.0};
	vector<float> centerO = {0.0, 0.0, 0.0};
	float centerDegreeO = -90, centerDegree = -90.0;	// Z negative
	float centerRadio = 10;
	float force, alpha, beta;

	/* Figures */
	vector<Figura*> shapes;
	void* data_shape = NULL;

	void set_v_force(float force, float alpha, float beta);
};

#endif // CANVAS_H
