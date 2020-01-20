#ifndef SHAPE_H
#define SHAPE_H

#include<string>
#include<ostream>

using std::string;
using std::ostream;

class Shape {
private:
  string name;

 public:
  Shape();
  Shape(string name);
  string getName() const;
  void setName(string);
  virtual double getArea() const = 0;
  friend ostream& operator<<(ostream& os, const Shape& shp);
};


#endif
