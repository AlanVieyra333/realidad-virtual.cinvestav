#ifndef CANVAS_H
#define CANVAS_H

#include <QtOpenGL>
#include <QTimer>

#include "cubo.h"
#include "rehilete.h"

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

	/* Figures */
	Cubo *cubo;
	Rehilete *rehilete;
};

#endif // CANVAS_H
