#include<iostream>
#include<cstdlib>
#include "simvi.h"

using namespace std;

const int INITIAL_SZ = 5;
const int INCREMENT = 20;

simvi::simvi() {
    data = new int[INITIAL_SZ];
    capacity = INITIAL_SZ;
    numvals = 0;
  }

 simvi::simvi(int sz) {
    data = new int[sz];
    capacity = sz;
    numvals = 0;
  }

  simvi::simvi(const simvi& orig) {
    numvals = orig.numvals;
    capacity = orig.capacity;
    
    data = new int[orig.capacity];

    for (int i = 0; i < orig.numvals; i++) {
      data[i] = orig.data[i];
    }
  }

 
  int simvi::get_capacity() const {
    return capacity;
  }

  int simvi::current_size() const {
    //numvals = 10;
    return numvals;
  }

  void simvi::insert(int dt) {
    if (numvals == capacity) {
      int* x = new int[capacity+INCREMENT];

      for (int i = 0; i < numvals; i++) {
	x[i] = data[i];
      }
      delete[] data;
      data = x;
      capacity += INCREMENT;
    }
    data[numvals++] = dt;
  }

  //get: 0 to numvals-1
  int simvi::get(int loc) const {
    if (loc >= numvals) {
      cout<<"ERROR: simvi.get: OUT OF BOUNDS"<<endl;
      exit(1);
    }

    //data[0] = -111; //works, but why? (data is not being changed, but heap memory is)
    //data = new int[1000]; //err, as expected (const function)
    //numvals = 200; //err, as expected  (const function)
    
    return data[loc];
  }

  void simvi::set(int nval, unsigned loc) {
    if (loc > numvals) {
      cerr<<"ERROR: simvi.set: TOO FEW ELEMENTS"<<endl;
      exit(1);
    }
    data[loc] = nval;
  }


  void simvi::print(string vname) {
    cout<<vname<<": ";
    for (int i = 0; i < current_size(); i++) {
      cout<<get(i)<<" ";
    }
    cout<<endl;
  }
  
  int& simvi::operator[](int index) {
    return data[index];
  }

  simvi& simvi::operator=(const simvi& orig) {
    delete[] data;
    int* x = new int[orig.capacity];
    capacity = orig.capacity;
    numvals = orig.numvals;

    for (int i = 0; i < orig.numvals; i++) {
      x[i] = orig.data[i];
    }
    data = x;

    //return SOMETHING;
    cout<<"assignOverl: "<<this<<endl;
    return *this;
  }




 

	     

