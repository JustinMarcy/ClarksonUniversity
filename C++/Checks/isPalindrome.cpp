#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

bool isPalindrome(string word);

  int main ()
{
  string input;
  cout<<"please enter a word or phrase: "<<endl;
  cin>>input;
  if (isPalindrome(input))
    {
      cout<<input<<" is a palindrome"<<endl;
    }
  else 
    {
      cout<<input<<" is not a palindrome"<<endl;
    }
  return 0;
}
bool isPalindrome(string word)
{
  for(int i = 0; i <= word.length()-1; i++)
{
    if(word[i] != word[word.length()-1-i])
    {
      return false;
    }
    else
    {
      return true;
    }
 }
}
// References: https://stackoverflow.com/questions/39822811/c-palindrome-function
