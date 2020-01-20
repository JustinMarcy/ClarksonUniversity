#include <iostream>
#include <cstring>
using namespace std;
int* multiply(int* , int* , int m, int n);
int main()
{
      cout<<"\n***PLEASE ENTER YOUR FIRST POLYNOMIAL***"<<endl;
      int HP1;
      cout<<"Enter the highest degree: "<<endl;
      cin>>HP1;
      if (HP1<0)
        {
          cout<<"Cannot input a negative power"<<endl;
          return (-1);
        }
      int size1=HP1+1;
      int coeffs1[size1];
      cout<<"Please enter the coefficients to each monomial\n"<<endl;
      for(int i=0;i<size1;i++)
        {
          cout<<"Enter coefficient of monomial a("<<i<<"):"<<endl;
          cin>>coeffs1[i];
        }
      cout<<"Coefficients of 1st polynomial: (";
      for (int i=0; i<size1; i++)
        {
          if (i==size1-1)
            {
              cout<<coeffs1[i]<<")"<<endl;
            }
          else
            {
              cout<<coeffs1[i]<<", ";
            }
        }
        cout<<"\n***PLEASE ENTER YOUR SECOND POLYNOMIAL*** "<<endl;
        int HP2;
        cout<<"Enter the highest degree: "<<endl;
        cin>>HP2;
        if (HP2<0)
          {
            cout<<"Cannot input a negative power"<<endl;
            return (-1);
          }
        int size2=HP2+1;
        int coeffs2[size2];
        cout<<"Please enter the coefficients to each monomial\n"<<endl;
        for(int i=0;i<size2;i++)
          {
            cout<<"Enter coefficient of monomial a("<<i<<"):"<<endl;
            cin>>coeffs2[i];
          }
      cout<<"Coefficients of 2nd polynomial: (";
      for (int i=0; i<size2; i++)
        {
          if (i==size2-1)
            {
              cout<<coeffs2[i]<<")"<<endl;
            }
          else
            {
              cout<<coeffs2[i]<<", ";
            }
        }
        int n=sizeof(coeffs2)/sizeof(*coeffs2);
        int m=sizeof(coeffs1)/sizeof(*coeffs1);
        int *prod = multiply(coeffs1, coeffs2, m, n);
        cout<<"Coefficients of product polynomial: (";
        for (int i=0; i<m+n-1; i++)
          {
            if (i==m+n-2)
              {
                cout<<prod[i]<<")"<<endl;
              }
            else
              {
                cout<<prod[i]<<", ";
              }
          }
return (0);
}

int *multiply(int A[], int B[], int m, int n)
{
   int *prod = new int[m+n-1];
   for (int i = 0; i<m+n-1; i++)    // Initialize the product array
     prod[i] = 0;
   for (int i=0; i<m; i++)
   {
     for (int j=0; j<n; j++)
         prod[i+j] += A[i]*B[j];
   }

   return prod;
}
//References:
//https://stackoverflow.com/questions/5636070/zero-an-array-in-c-code
//https://www.geeksforgeeks.org/multiply-two-polynomials-2/
