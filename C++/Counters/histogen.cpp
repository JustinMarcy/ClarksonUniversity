#include<iostream>
#include<string>
#include<cmath>
#include<sstream>
using namespace std;
int main ()
  {
    string text = "Representatives from Google and its parent company Alphabet\
eagerly discussed how the company can play a greater role in \
reducing misleading information online, several Davos attendees \
involved in and briefed on these conversations told Quartz. A \
notification system, perhaps via an optional extension for \
Google's Chrome browser, was an idea that these people said was \
broached more than once. Such a browser-based system controlled by \
Google could alert users on Facebook's or Twitter's websites when \
they're seeing or sharing a link deemed to be false or \
untrustworthy. Right now, this appears to be merely an idea \
company executives are discussing, not a product in development.";
    cout<<"\n\n--------- word frequency histogram ----------"<<endl;
    istringstream iss(text);
    string word;
    while(iss >> word)
      {
	string::size_type start = 0;
	int occurrences = 0;
       	while ((start = text.find(word, start)) !=string::npos)
	  {
	  ++occurrences;
	  start += word.length(); 
	  }
	cout<<word<<" "<<occurrences<<endl;
      }
  return 0;
  }
 
