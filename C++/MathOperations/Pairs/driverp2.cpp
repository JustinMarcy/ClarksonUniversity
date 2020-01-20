#include <iostream>
#include "pair.h"



int main(void) {
  BTPair<long> ap1(50, 22000);
  ap1.print();


  BTPair<char> ap2('f', 'b');
  ap2.print();

  BTPair<double> ap3(0.44, 8.230821);
  ap3.print();

  return 0;
}
