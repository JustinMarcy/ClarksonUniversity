#include <iostream>
using namespace std;

bool Availible(int n,bool* preference); //Function to check if man/woman is availible

int* Matching(int n, int**MP, int**WP) // numbers, priority lists of males and females.
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

    while(Availible(n,isManFree))   // all matching completed if it returns false.
    {
        int indexM;
        for(int i=0;i<n;i++)
        {
            if(isManFree[i]==true)  { indexM=i; break; }    // we'll try matching this guy with a girl!
        }

        int indexWo;
        for(int i=0;i<n;i++)
        {
            int w=MP[indexM][i];
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
            int indexRival; // find the competitor's index.
            for(int i=0;i<n;i++)
            {
                if(match[i]==indexWo){ indexRival=i;    break; }
            }

            int pM,pRival;
            for(int i=0;i<n;i++)
            {
                if(WP[indexWo][i]==indexM)  pM=i;
                if(WP[indexWo][i]==indexRival)  pRival=i;
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

int main()
{
    int n;
    cout<<"please enter sample size"<<endl;
    cin>>n;
    int**MP,**WP;
    MP=new int*[n];
    for(int i=0;i<n;i++)    // a lot of inputs
    {
        MP[i]=new int[n];
        for(int j=0;j<n;j++)
        {
            cout<<"please enter men's preference"<<endl;
            cin>>MP[i][j];
        }
    }
    WP=new int*[n];
    for(int i=0;i<n;i++)
    {
        WP[i]=new int[n];
        for(int j=0;j<n;j++)
        {
            cout<<"please enter the woman's preference"<<endl;
            cin>>WP[i][j];
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            MP[i][j]--; // inputs are 1~n, get indexes 0~n-1
            WP[i][j]--;
        }
    }
    int*match=Matching(n,MP,WP);
    for(int i=0;i<n;i++)
    {
        cout<<"Match: "<<*(match+i)+1<<" ";    // output: matching result
    }
    delete [] match;
    return 0;
}

bool Availible(int n, bool* preference) //Function to check if man/women is availible
{
    int i=0;
    while(i<n)
    {
        if(*(preference+i)==true)
        {
          return (true);
        }
        i++;
    }
    return false;
}
