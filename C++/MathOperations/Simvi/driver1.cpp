#include<iostream>
#include<cstdlib>
#include<iostream>
#include "simvi.h"

using namespace std;

  ostream& operator<<(ostream& os, const simvi& x) {
    for (int i = 0; i < x.current_size(); i++) {
      os<<x.get(i)<<" ";
    }
    cout<<"["<<x.current_size()<<" out of max "<<x.get_capacity()<<"]";
    os<<endl;
    return os;
  }


int main(void) {
  simvi e1;
  //simvi e11(40);

  e1.insert(4);
  e1.insert(77);
  e1.insert(-90);
  e1.insert(100);
  e1.insert(655);
  e1.insert(666);
  e1.insert(99);
  //e1.print("e1");
  

  //cout<<e1.current_size()<<endl;
  e1.set(888, e1.current_size()-1);
  //e1.print("e1");
  
  simvi e2 = e1;

  
  e1.print("e1");
  cout<<"e2: "<<e2;
  
  e2.set(-333, 0);
  //e2.set(20, 100); //check error message


  cout<<"e1: "<<e1;
  cout<<"e2: "<<e2;
  
  // e1.print("e1");
  //e2.print("e2");


  //access operator  
  // cout<<"2nd element of e1: "<<e1.get(1)<<endl;
  // cout<<"2nd element of e1: "<<e1[1]<<endl;
  int tmp1 = e1[2];
  // cout<<"tmp1: "<<tmp1<<endl;
  e1[2] = 555;

  // cout<<endl<<endl<<"test regular assignemnt: "<<endl;
  simvi e3(20);
  e3.insert(100);
  e3.insert(-1);
  cout<<"e3: "<<e3<<endl;
  

  e2 = e3;
  cout<<"[copied e3 into e2]"<<endl;
  cout<<"e3: "<<e3<<endl;
  cout<<"e2: "<<e2<<endl;
  
  
  
  e2.set(50, 0);
  cout<<"set e2[0] to 50."<<endl;
  cout<<"e3: "<<e3<<endl;
  cout<<"e2: "<<e2<<endl;

  //e2.get(500);
  //e2.set(6, 500); //enable this to get error

  //e2 = (e3 = e1);
  //cout<<"e1: "<<e1<<endl;
  //cout<<"e2: "<<e2<<endl;
  //cout<<"e3: "<<e3<<endl;
  // cout<<"main: "<<&e2<<endl;
  
  
    
  
  // for (int i = 0; i < e2.current_size(); i++) {
  //   cout<<"e2 at "<<i<<": "<<e2.get(i)<<endl;
  // }

  return 0;
}

