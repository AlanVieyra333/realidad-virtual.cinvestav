#ifndef COLOR_H
#define COLOR_H

struct _Color
{
  float Red[3] = {1.0, 0.0, 0.0};
  float Green[3] = {0.0, 1.0, 0.0};
  float Blue[3] = {0.0, 0.0, 1.0};
  float Yellow[3] = {1.0, 1.0, 0.0};
  float White[3] = {1.0, 1.0, 1.0};
  float Purple[3] = {1.0, 0.0, 1.0};
  float Brown[3] = {0.545, 0.365, 0.18};
  float Wine[3] = {0.4471, 0.1843, 0.2157};
  float Gray[3] = {0.5, 0.5, 0.5};
} Color;

#endif // COLOR_H