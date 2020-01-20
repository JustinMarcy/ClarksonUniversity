#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

string  generate(string x, string y);

int main()
{
  string firstname;
  string lastname;
  ifstream infile;
  ofstream outfile;
  infile.open("employeeNames.txt");
  outfile.open("employeesXMLData.xml");
  if (!infile)
    {
      cout<<"Error: could not open input file";
      return(1);
    } 
  infile>>firstname>>lastname;
  while (!infile.eof())
    {           
      outfile<<"<person>"<<endl;
      outfile<<"<firstname>"<<firstname<<"</firstname>"<<endl;
      outfile<<"<lastname>"<<lastname<<"</lastname>"<<endl;
      outfile<<"<email>"<<generate(firstname, lastname)<<"</email>"<<endl;
      outfile<<"</person> \n"<<endl;
      infile>>firstname>>lastname;
    }
  return(0);
}

string generate(string x, string y)
{
  string addressF = x.substr(0,1);
  string addressL = y.substr(0,6);
  string at = "@company.com";
  string email = addressF + addressL + at;
  for (int i=0; email[i]; i++) email[i] = tolower(email[i]);
  return email;
}
