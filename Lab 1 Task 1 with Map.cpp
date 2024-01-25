/*Знайти період десяткового дробу*/

#include <bits/stdc++.h>

using namespace std;

string findPeriod(int a, int b)
{
    a = (a % b) * 10;

    map <int, int> prePeriod;
    string period;
    int position = 0;
    period.clear();

    while(a != 0)
    {
        //cout << period << " " << position << "[" << a << "]\n";
        if (prePeriod.find(a) != prePeriod.end())
            return period.substr(0, prePeriod[a]) + "(" + period.substr(prePeriod[a]) + ")";

        prePeriod[a] = position;

        period += a / b + '0';
        a = (a % b) * 10;
        position++;

    }

    if (period.empty()) return "0";
    return period;

}
int main()
{
    int a, b;
    cin >> a >> b;
    cout << findPeriod(a, b) << "\n";
}
