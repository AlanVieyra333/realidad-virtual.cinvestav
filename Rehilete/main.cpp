#include <QApplication>

#include "painter.h"

int main(int argc, char **argv) {
  QApplication a(argc, argv);

  Painter w;

  w.setGeometry(100, 100, 500, 360);  // 355 );

  w.show();         // Show widget
  return a.exec();  // go!
}
