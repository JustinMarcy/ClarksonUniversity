#include<iostream>
#include<climits>
#include<cmath>
#include<exception>

using namespace std;

int safesum (int n1, int n2);

int main()
{
  try {
    cout<<safesum(3, 9000)<<endl;   
    cout<<safesum(2147483600, 100)<<endl; 
  } catch (int SumTooLargeForInt){
    cerr<<"main: Caught SumTooLargeForInt exception"<<endl;
 } 
 cout<<safesum(34412, 100000)<<endl; 
 cout<<safesum(2147483000, 5000)<<endl;
 return(0);
}

int safesum (int n1, int n2)
{   
  int sum;
  sum=n1+n2;
  if (sum > INT_MAX || sum <0) {
    throw (1);
  }
  else {
  return(sum);
  }
}
