#include<iostream>
#include<string.h>
using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr<<"usage: weirdOp a_string"<<endl;
    return 1;
  }
  int slen = strlen(argv[1]);
  char* str = new char[slen];
  int x = slen-1;
  string org=argv[1];
  for (int i=0; i < slen; i++)
    {
      str[x]= org[i];
      x--;
    }
  cout<< str <<endl;
}
