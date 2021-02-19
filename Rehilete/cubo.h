#ifndef CUBO_H
#define CUBO_H

class Cubo {
 public:
  Cubo(float l);
  void dibuja_figura(float angle);

 private:
  float cubo[8][3];
};

#endif  // CUBO_H
