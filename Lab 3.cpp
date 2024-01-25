//Методом градієнтного спуску визначити екстремум однозначної функції.

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x)
{
    return sin(x);
}

double df(double (*fun)(double), double a, double step)
{
    return (fun(a + step) - fun(a)) / step;
}

int main()
{
    setlocale (LC_CTYPE, "ukr");

    double const_epsilon = 0.001, step_df = 0.01;
    double current_x;
    cin >> current_x;

    double temp_x = current_x, pohidna = df(f, current_x, step_df);
    while(pohidna > 0.00011)
    {
        current_x = current_x - const_epsilon * pohidna;
        //cout << current_x << ' ' << pohidna << "\n";

        pohidna =  df(f, current_x, step_df);
    }


    cout << "Id min value x = " << fixed << setprecision(5) << current_x << "\n";
    cout << "Min value: f(x) = " << fixed << setprecision(5) << f(current_x) << "\n";

    //cout << "\nCheck print: " << current_x * current_x << "\n";

    return 0;
}
