#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;

int Matching(int n,int Mpref[n][n],int Wpref[n][n]);

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
        int*match=Matching(n,Mpref,Wpref);
        for(int i=0;i<n;i++)
        {
            cout<<"Match: "<<*(match+i)+1<<" ";    // output: matching result
        }
        delete [] match;
        return(0);
}


bool isOneFree(int n,bool* state)    // test if there's at least one man Free.
{
    for(int i=0;i<n;i++)
    {
        if(*(state+i)==true)
        {
          return true;
        }
    }
    return false;
}

int Matching(int n,int Mpref[n][n],int Wpref[n][n]) // numbers, priority lists of males and females.
{
    bool isManFree[n],isWomanFree[n],isManProposed[n][n];   // to represent matching states.
    int *match = new int[n];   // index-value(man-woman) pair

    for(int i=0;i<n;i++)    // initialize values.
    {
        isManFree[i]=true;
        isWomanFree[i]=true;
        for(int j=0;j<n;j++){   isManProposed[i][j]=false;    }
        match[i]=-1;
    }

    while(isOneFree(n,isManFree))   // all matching coMprefleted if it returns false.
    {
        int indexM;
        for(int i=0;i<n;i++)
        {
            if(isManFree[i]==true)  { indexM=i; break; }    // we'll try matching this guy with a girl!
        }

        int indexWo;
        for(int i=0;i<n;i++)
        {
            int w=Mpref[indexM][i];
            if(isManProposed[indexM][w]==false)  { indexWo=w;   break;}  // current priority
        }
        isManProposed[indexM][indexWo]=true;

        if(isWomanFree[indexWo])
        {
            isManFree[indexM]=false;
            isWomanFree[indexWo]=false;
            match[indexM]=indexWo; // they're engaged!
        }
        else    // she's engaged to someone already.
        {
            int indexRival; // find the coMprefetitor's index.
            for(int i=0;i<n;i++)
            {
                if(match[i]==indexWo){ indexRival=i;    break; }
            }

            int pM,pRival;
            for(int i=0;i<n;i++)
            {
                if(Wpref[indexWo][i]==indexM)  pM=i;
                if(Wpref[indexWo][i]==indexRival)  pRival=i;
            }
            if(pM<pRival)   // the girl's decision
            {
                isManFree[indexM]=false;
                isManFree[indexRival]=true;
                isWomanFree[indexWo]=false;
                match[indexM]=indexWo;  // change the match
            }
        }
    }
    return match;
}
