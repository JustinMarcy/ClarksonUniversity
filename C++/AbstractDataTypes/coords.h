#ifndef COORDS_H
#define COORDS_H
#include<iostream>
#include<cstdlib>
using namespace std;

namespace coords {
class rect_coords;
class polar_coords;

class rect_coords
{
private:
  double x;
  double y;

public:
  rect_coords();
  rect_coords(double a, double b);
  polar_coord::toPolar();
  void print(string name);
};


class polar_coords
{
private:
  double r;
  double theta;
  bool isOrg;

public:
  polar_coords();
  polar_coords(const polar_coords& origin);
  polar_coords(bool check, double radius, double angle);
  rect_coords toRectangular();
  polar_coords& operator=(cosnt polar_coords& origin);
  void print(string name);

};
}
#endif
