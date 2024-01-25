// Пошук простих дільників факторіалу n!
// Ex: 10! = {{2,8},{3,4},{5,2},{7,1}}

#include <bits/stdc++.h>

using namespace std;


bool IsPrime(int n)
{
    if(n % 2 == 0) return false;
    for(int i = 3; i <= sqrt(n); i+=2)
    {
        if(n % i== 0) return false;
    }
    return true;
}


int main()
{
    int n;
    cout << "Input n: ";
    cin >> n;
    if (n == 1)
    {
        cout << "One is prime";
        return 0;
    }
    cout << "Factorization of factorial " << n << "!: ";


    int CntDiv = 0, Div = 2, TempStage = Div;
    if( n > 1)
    {
        while(TempStage <= n)
        {
            CntDiv += n/TempStage;
            TempStage *= Div;
        }
        cout << "{" << Div << "," << CntDiv << "}";
    }

    for(int Div = 3; Div <= n; Div+=2)
    {
        if(IsPrime(Div))
        {
            CntDiv = 0, TempStage = Div;
            while(TempStage <= n)
            {
                CntDiv += n/TempStage;
                TempStage *= Div;
            }
            cout << ",{" << Div << "," << CntDiv << "}";
        }
    }
}
