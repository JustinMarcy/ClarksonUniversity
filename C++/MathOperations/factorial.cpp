#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

int factorial(int x);

int main(int argc, char** argv )
{
    if (argc > 2)
     {
     cout<<"usage: factorial <positive_integer>"<<endl;
     return 1;
     }
    int num = atoi(argv[1]);
    if (num <0)
     {
     cout<<"usage: factorial <positive_integer>"<<endl;
     return 1;
     }
  cout<<"factorial("<<num<<") = "<<factorial(num)<<endl;
  return 0;
}

int factorial(int x)
{
  if (x == 0)
    {
    return 0;
    }
  else if (x == 1)
    {
      return 1;
    }
  else if (x > 1)
    {
      return x* factorial(x-1);
    }
}
