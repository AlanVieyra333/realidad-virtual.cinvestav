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
			public : Canvas(QWidget *parent = 0);
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

public slots:
	void timerDone(void);
	void initscreen(void)
	{
		timer->start(17);
		// timer->start(500);
	}
	void stop(void)
	{
		timer->stop();
	}

	void reset(void)
	{
		angle = 0;
		xrot = yrot = 0;

		eye[0] = eyeO[0]; eye[1] = eyeO[1]; eye[2] = eyeO[2];
		centerDegree = centerDegreeO;
		center[1] = 1.5;
		updateGL( );
	}

	void addShape(Figura*);
	void setEye(float, float, float);
	void setCenter(float, float, float);
	void setCenterDegree(float);

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

	float angle;
	int signo;
	int xmouse, ymouse; // Mouse pointer coordinates
	vector<float> eye = {0.0, 0.0, 0.0};
	vector<float> eyeO = {0.0, 0.0, 0.0};
	vector<float> center = {0.0, 0.0, 0.0};
	float centerDegreeO = -90, centerDegree = -90.0;	// Z negative
	float centerRadio = 10;

	/* Figures */
	vector<Figura*> figuras;
};

#endif // CANVAS_H
