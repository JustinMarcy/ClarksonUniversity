#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;


int main()
{
  int n;
  cout<<"Please enter a sample size n: ";
  cin>>n;
  if (n<1) {
    cout<<"ERROR: sample size most be at least 1"<<endl;
  }

  int count = 0;
  int Mpref[n][n];
  int Wpref[n][n];
  for (int i=0; i<n; i++) {
      for(int j=0; j<n; j++){
        Mpref[i][j]=j;
        Wpref[i][j]=j;
        //cout<<Mpref[i][j];
        //cout<<Wpref[i][j];
        count++;
        if (count % n+1 == 1) {
          cout<<"\n";
        }
      }
    }
   srand(time(NULL));
   for(int i=0; i<n; i++)
   {
     random_shuffle(&Mpref[i][0], &Mpref[i][0]+n);
   }
   for(int i=0; i<n; i++)
   {
     random_shuffle(&Wpref[i][0], &Wpref[i][0]+n);
   }
   std::cout << "Men's preference"<<endl;
   for(int i=0; i<n; ++i)
      {
        for(int j=0; j<n; ++j)
        std::cout << Mpref[i][j] << ' ';
        std::cout << '\n';
        }
    std::cout << "\nWomen's preference"<<endl;
    for(int i=0; i<n; ++i)
        {
          for(int j=0; j<n; ++j)
          std::cout << Wpref[i][j] << ' ';
          std::cout << '\n';
        }
    int isManFree[n];
    int isWomFree[n];
    for (int i = 0; i<n; i++){
    isManFree[i] = 0;
    isWomFree[i] = 0;
    }
    int i=0;
    int j=0;
  //  while(isManFree[i]=0)
  //  {
  //    if (isWomFree(Mpref[i][j])=0)
  //    {
  //      cout<<"MATCH!: "<<"Man "<<[i]<<" matched with woman "<<Mpref[i][j]<<endl;
  //    }
  //  }
    return(0);
}
//References:
//http://www.cplusplus.com/reference/algorithm/random_shuffle/
//https://stackoverflow.com/questions/12858734/c-implementation-of-gale-shapley-algorithm
