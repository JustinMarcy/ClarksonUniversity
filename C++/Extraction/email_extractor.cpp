#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
  ifstream infile;
  ofstream outfile;
  string str;
  infile.open("file.dat");
  outfile.open("addr.tmp");
  if (!infile)
    {
      cout<<"Error: could not open input file";
      return(1);
    }   
  while(!infile.eof())
    {
      infile>>str;
      if (str.find('@')<str.length())
	{
	  cout<<str<<endl;
	  outfile<<str<<endl;
	}
    }
  infile.close();
  outfile.close();
  cout<<"Process complete"<<endl;
  return(0);
}
