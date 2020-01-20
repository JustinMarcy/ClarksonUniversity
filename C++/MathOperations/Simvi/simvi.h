#include<iostream>
#include<cstdlib>

using namespace std;

class simvi {
private:
  int* data;
  unsigned int numvals;
  unsigned int capacity;
  

public:
  simvi();

  simvi(int sz);

  simvi(const simvi& orig);
 
  int get_capacity() const;

  int current_size() const;

  void insert(int dt);

  //get: 0 to numvals-1
  int get(int loc) const;

  void set(int nval, unsigned loc);

  void print(string vname);
  
  int& operator[](int index);

  simvi& operator=(const simvi& orig);
};


	     

