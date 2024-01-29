/*Вивести текст на екран, прибравши зайві пробіли та слова, 
які дублюються (однакові і стоять поруч), вирівнявши текст по лівому краю.
Задати ширину вихідного абзацу*/

#include <bits/stdc++.h>

using namespace std;

struct tWord
{
    int st = -1;
    int fn = -1;
};

int findStartOfWord(string &str, int id)
{
    while(id < str.size() && str[id] == ' ')
    {
        str.erase(id, 1);
    }
    return id;

}
bool compareWord(string str, tWord first, tWord second)
{
    int len = second.fn - second.st + 1;
    if(first.fn - first.st + 1 != len) return false;

    int i = 0;
    while(i < len)
    {
        if(str[first.st + i] != str[second.st + i])
            return false;
        i++;
    }
    return true;
}
int main()
{
    if (!freopen("test.txt", "r", stdin))
    {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string str;
    bool clearWord = false, endLine = false, first = true;
    int sizeBuff = 0, written = 0;
    cin >> sizeBuff;

    getline(cin, str);
    while(getline(cin, str))
    {
        endLine = false;
        clearWord = false;
        tWord curr, prev;
        curr.st = findStartOfWord(str, 0);
        curr.fn =  str.find_first_of(' ') - 1;
        if(curr.fn < 0)
        {
            endLine = true;
            curr.fn = str.size() - 1;
        }

        if( curr.fn - curr.st < sizeBuff - written || (first && curr.fn - curr.st <= sizeBuff - written))
        {
            cout << str.substr(curr.st, curr.fn - curr.st + 1);
            written += curr.fn - curr.st + 1;
        }
        else
        {
            cout << "\n" << str.substr(curr.st, curr.fn - curr.st + 1);
            written = curr.fn - curr.st + 1;
        }
        while(curr.st >= 0 && !endLine)
        {
            if(!clearWord) prev = curr;
            curr.st = findStartOfWord(str, prev.fn + 2);
            curr.fn =  str.find_first_of(' ', curr.st) - 1;
            clearWord = false;
            if(curr.fn < 0)
            {
                endLine = true;
                curr.fn = str.size() - 1;
            }

            //cout << "/" << prev.st << " " << prev.fn << "->" << curr.st << " " << curr.fn << "/";
            if(compareWord(str, prev, curr))
            {
                str.erase(curr.st, curr.fn - curr.st + 1);
                clearWord = true;
            }


            if(!clearWord)
            {
                first = false;
                if( curr.fn - prev.fn <= sizeBuff - written)
                {
                    cout << str.substr(prev.fn + 1, curr.fn - prev.fn );
                    written += curr.fn - prev.fn;
                }
                else
                {
                    cout << "\n" << str.substr(curr.st, curr.fn - curr.st + 1);
                    written = curr.fn - curr.st + 1;
                }
            }

        }
        first = false;
    }
   // cout << written << "\n";
}
