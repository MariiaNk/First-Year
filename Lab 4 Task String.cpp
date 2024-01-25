/* Реалізувати перетворення рядка, що складається з {0,1} у код Грея і навпаки */

#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    char line[1000], ansLine[1000];
    int option, code[1000], lenArr = 0;

    cout << "Choose option: [to code Grey] - 1 or [from code Grey] - 2:\n";
    cin >> option;

    // ç á³íàðíîãî êîäó â êîä ãðåÿ
    if(option == 1)
    {
        cout << "Input binary code:\n";
        cin >> line;

        ansLine[0] = line[0];
        for (int i = 1; i < strlen(line); i++)
        {
             ansLine[i] = (line[i] - '0') ^ (line[i-1] - '0') + '0';
             //cout <<line[i] << "^" << line[i-1] << "  " << temp << "\n";
        }
    }
    // ç êîäó Ãðåÿ â á³íàðíèé êîä
    else if(option == 2)
    {
        cout << "Input grey code:\n";
        cin >> line;

        ansLine[0] = line[0];
        for (int i = 1; i < strlen(line); i++)
            ansLine[i] = (line[i] - '0') ^ ( ansLine[i - 1] - '0') + '0';
    }
    else
    {
        cout << "Error\n\n";
        main();
        return 0;
    }
    cout << "Answer\n" << ansLine;
    return 0;

}

/*
5


Input: 1 101
Output: 100

Input: 1 1110
Output: 1001


*/
