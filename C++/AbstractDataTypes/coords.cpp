#include<iostream>
#include<cmath>
#include"coords.h"
rect_coords::rect_coords()
{
  x=0;
  y=0;
}
rect_coords::rect_coords(double a, double b)
{
  x=a;
  y=b;
}

rect_coords polar_coords::toRectangular()
{
  x= r*cos(theta);
  y= r*sin(theta);
}

void print(string name)
{

}

polar_coords rect_coords::toPolar()
{
  r=sqrt(x^2+y^2);
  theta= arctan(y/x);
}
polar_coords()
{

}

polar_coords(const polar_coords& origin)
{
  origin.r=0;
  origin.theta=(M_PI/6);
}
polar_coords(bool check, double radius, double angle)
{
  check=isOrg;
  radius=r;
  angle=theta;
}

void print()
{

}
