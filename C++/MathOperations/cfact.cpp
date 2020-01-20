#include<iostream>
#include<cmath>
//References: www.programiz.com/cpp-programming/examples/factors-number
int main()
{
  int n;
  int i;
  std::cout<<"Enter a number greater than 1: "<<std::endl;
  std::cin>>n;
  if (n<1)
    {
      std::cout<<"Could not understand input, please try again \n"<<std::endl;
      return 0;
    }
  std::cout<<"Factors of "<<n<<" are "<<std::endl;
  for(i=1;i<=n;i++)
    {
      if(n % i ==0)
	std::cout<<i<<" "<<std::endl;
    } 
  return 0;
}
