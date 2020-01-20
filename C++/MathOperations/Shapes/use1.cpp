#include <iostream>
#include <ostream>
#include "circle.h"
#include "rectangle.h"

using std::cout;
using std::endl;


int main(void) {
  Circle c1(30);
  cout<<"area of c1: "<<c1.getArea()<<endl;
  cout<<c1<<endl;

  Rectangle r1(2, 8.9);
  cout<<"area of r1: "<<r1.getArea()<<endl;
  cout<<r1<<endl;

  Rectangle r2(5.9);
  cout<<"area of r2: "<<r2.getArea()<<endl;
  cout<<r2;

  //abstract type Shape can't be instantiated
  //Shape s1;
  

  return 0;
}

