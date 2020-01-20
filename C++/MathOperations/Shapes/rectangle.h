#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"


class rectangle: public Shape {

private:
 double L;
 double W;

 public:
  rectangle();
  rectangle(double length, double width);

  virtual double getArea() const;
};
#endif
