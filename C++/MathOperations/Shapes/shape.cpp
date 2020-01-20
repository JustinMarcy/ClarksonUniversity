#include<string>
#include<ostream>
#include "shape.h"

using std::string;
using std::ostream;
using std::endl;

Shape::Shape() {
  name = "";
}


Shape::Shape(string nameOfShape) {
  name = nameOfShape;
}

string Shape::getName() const {
  return name;
}

void Shape::setName(string nn) {
  name = nn;
}

ostream& operator<<(ostream& os, const Shape& shp) {
  os << "It is a "<<shp.getName()<<" with area "<<shp.getArea()<<"."<<endl;
  return os;   
}

