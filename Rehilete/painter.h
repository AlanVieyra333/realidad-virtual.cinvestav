#include <QLabel>
#include <QLayout>
#include <QPushButton>

#ifndef PAINTER_H
#define PAINTER_H

#include "canvas.h"

class Painter : public QWidget {
  Q_OBJECT
 public:
  Painter(QWidget *parent = 0);

 private slots:
  void newPosition();
  void newSize();

 private:
  Canvas *canvas;
  QLabel *messpos;
  QLabel *messize;
  QLabel *visorMouse;
  QLabel *visorTama;
  QPushButton *myinit, *stop;
};

#endif
