/*Знайти період десяткового дробу*/
#include <iostream>

using namespace std;

int main()
{
    int num1, num2;
    cout << "Input a and b: ";
    cin >> num1 >> num2;
    int prePeriod[num2];

    int intPart = num1/num2;
    num1 %= num2;

    string result;
    for (int i = 0; i < num2; i++)
        prePeriod[i] = -1;


    while (num1 != 0 && prePeriod[num1] == -1)
    {
        prePeriod[num1] = result.size();
        num1 *= 10;
        result += num1 / num2 + '0';
        num1 %= num2;
    }


    if (prePeriod[num1] != -1)
    {
        cout << "Fraction: "  << intPart << '.' << result.substr(0, prePeriod[num1]) + "(" + result.substr(prePeriod[num1]) + ")\n";
        cout << "Period: " << result.substr(prePeriod[num1]) << "\n";
    }
    else if (result.empty())
        cout << "Integer" << intPart << "\nPeriod: 0\n";
    else cout << "Fraction without period -> fraction: " << intPart << '.' << result << "\nPeriod: 0\n";

    return 0;
}
