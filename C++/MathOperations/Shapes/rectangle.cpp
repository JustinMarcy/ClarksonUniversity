#include"rectangle.h"
#include<cmath>


rectangle::rectangle() : Shape("rectangle") {
  L = 0;
  W = 0;
}

rectangle::rectangle() : Shape("rectangle") {
  this->L = L;
  this->W = W;
}

double rectangle::getArea() const {
  return L*W;
}
