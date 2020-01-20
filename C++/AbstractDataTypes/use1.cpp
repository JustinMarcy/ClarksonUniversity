//note: (0, 0.523599 rad) is our polar origin as is PI/6 (approx.)

#include <iostream>
#include "coords.h"
#include <cmath>

using std::endl;
using std::cout;

using coords::rect_coords;
using coords::polar_coords;

int main(void) {
  cout<<"--- Test 1 --- "<<endl;
  rect_coords rdef;
  rdef.print("rdef");
  cout<<endl;
   

  cout<<"--- Test 2 --- "<<endl;
  rect_coords r1(40, 22);  
  r1.print("r1");
  polar_coords r1p = r1.toPolar();
  r1p.print("r1p");
  cout<<endl;

  cout<<"--- Test 3 --- "<<endl;
  polar_coords p2last(false, 45.6508, 0.502843);
  p2last.print("p2last");
  rect_coords p2last_r = p2last.toRectangular();
  p2last_r.print("p2last_r");
  cout<<endl;

  cout<<"--- Test 4 --- "<<endl;
  rect_coords wr1(-10, 120);
  wr1.print("wr1");
  cout<<endl;

  cout<<"--- Test 5 --- "<<endl;
  polar_coords pdef;
  pdef.print("pdef");
  rect_coords pdefr = pdef.toRectangular();
  pdefr.print("pdefr");
  cout<<endl;

  cout<<"--- Test 6 --- "<<endl;
  polar_coords p1(false, 100, 20); //false means this point is not the polar origin
  p1.print("p1");
  polar_coords p2(p1);
  p2.print("p2");
  cout<<endl;
  
  cout<<"--- Test 7 --- "<<endl;
  polar_coords p3(false, 25, M_PI/3); 
  p3.print("p3");
  p1 = p3;
  cout<<"{{p1 = p3}}"<<endl;
  p1.print("p1");
  rect_coords p1_r = p1.toRectangular();
  p1_r.print("p1_r");
  cout<<endl;
  
  cout<<"--- Test 8 --- "<<endl;
  polar_coords p4(true, 0, M_PI/3); //the polar origin; r=0; angle will be ignored in favor a fixed value (see problem statement)
  p4.print("p4");
  rect_coords p4r = p4.toRectangular();
  p4r.print("p4r");
  cout<<endl;
     
  cout<<"--- Test 9 --- "<<endl;
  rect_coords r5(0, 0);
  r5.print("r5");
  polar_coords r5p = r5.toPolar();
  r5p.print("r5p");
  //cout<<endl;

  return 0;
}
