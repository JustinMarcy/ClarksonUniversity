#ifndef CIRCLE_H
#define CIRCLE_H 


#include "shape.h"


class Circle: public Shape {
 public:
  Circle();
  Circle(int radius);
  
  virtual double getArea() const;

 private:
  double radius;
};


#endif
