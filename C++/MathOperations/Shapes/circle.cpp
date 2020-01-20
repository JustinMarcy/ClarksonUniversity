#include <math.h>
#include "circle.h"


Circle::Circle() : Shape("circle") {
  radius = 0;
}


Circle::Circle(int radius)  : Shape("circle")  {
  this->radius = radius;
}


double Circle::getArea() const {
  return M_PI*radius*radius;
}

