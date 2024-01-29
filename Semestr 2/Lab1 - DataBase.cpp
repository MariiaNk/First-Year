#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <stack>

using namespace std;
struct tDate
{
    int day;
    int month;
    int year;

    friend std::istream & operator>>(istream &is, tDate& p)
    {
        return is >> p.day >> p.month >> p.year;
    }
    friend std::ostream & operator<<(ostream &os, tDate& p)
    {
        return os << p.day << "." << p.month << "." << p.year ;
    }

    bool isValidDate() const
    {
        if (month < 1 || month > 12) return false;
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) daysInMonth[2] = 29;
        if (day < 1 || day > daysInMonth[month]) return false;
        if (year < 1900 || year > 2100) return false;
        return true;
    }


};
struct tTime
{
    int hours;
    int minutes;
    friend std::istream & operator>>(istream &is, tTime& p)
    {
        return is >> p.hours >> p.minutes;
    }
    friend std::ostream & operator<<(ostream &os, tTime& p)
    {
        return os << p.hours << ":" << p.minutes ;
    }
    bool isValidTime() const
    {
        if(minutes > 60 || minutes < 0) return false;
        if(hours > 23 || hours < 0) return false;
        return true;
    }

};
struct tGoods
{

    int id;
    char name[1000];
    char measure[1000];
    int cnt; //кількість товару
    tDate date; // дата виробництва
    tTime time; // час виробництва в хвилинах
    tDate expirationDate; //термін придатності
};


tGoods convertInputData (char *buffer)
{
    tGoods buffGood;
    buffGood.id = atoi(strtok(buffer, " "));
    char *subBuff = strtok(NULL, " ");
    strcpy(buffGood.name , subBuff);
    subBuff= strtok(NULL, " ");
    strcpy(buffGood.measure , subBuff);
    buffGood.cnt = atoi(strtok(NULL, " "));
    buffGood.date.day = atoi(strtok(NULL, " "));
    buffGood.date.month = atoi(strtok(NULL, " "));
    buffGood.date.year = atoi(strtok(NULL, " "));
    buffGood.time.hours = atoi(strtok(NULL, " "));
    buffGood.time.minutes = atoi(strtok(NULL, " "));
    buffGood.expirationDate.day = atoi(strtok(NULL, " "));
    buffGood.expirationDate.month = atoi(strtok(NULL, " "));
    buffGood.expirationDate.year = atoi(strtok(NULL, " "));
    return buffGood;
}

void output (vector <tGoods> shop)
{
    cout << "|" << setw(6) << "ID|" << setw(11) << "Name|" << setw(11) << "Measure|" << setw(11) << "Count|" << setw(18) << "Product date|" << setw(14) << "Time|" << setw(19) << "Expiration date|\n";
    cout << "------------------------------------------------------------------------------------------\n";
    for(int i = 0; i < shop.size(); i++)
    {
        cout << "|" << setw(5);
        cout << shop[i].id;
        cout << "|" << setw(10);
        cout << shop[i].name;
        cout << "|" << setw(10);
        cout << shop[i].measure;
        cout << "|" << setw(10);
        cout << shop[i].cnt;
        cout << "|" << setw(10);
        cout << shop[i].date;
        cout << "|" << setw(10);
        cout << shop[i].time;
        cout << "|" << setw(10);
        cout << shop[i].expirationDate;
        cout << "|\n";

    }
}

bool isValidMeasure(char *str)
{
    return strcmp(str, "kg") == 0 || strcmp(str, "l") == 0 || strcmp(str, "pack") == 0 || strcmp(str, "ind") == 0;
}

int main()
{
    vector <tGoods> shop;
    vector <int> availableId;
    int maxID = 0;
    cout << "What do you want to do? [key word]\n- Add data: add\n- Save data to file: save\n- Restore data: restore\n- Output saved data: output\n- Search by specified criteria: search\nPlease, write the key word of your request\n";
    string request;
    while(cin >> request)
    {

        if(request == "add")
        {
            tGoods temp;
            cout << "Write element details:\n- name\n";
            cin >> temp.name;
            cout << "- measure[kg/l/ind/pack]\n";
            cin >> temp.measure;
            while(!isValidMeasure(temp.measure))
            {
                cout << "Issue! Measure isn't correct. Please input correct measure[kg/l/ind/pack]\n";
                cin >> temp.measure;
            }
            cout << "- count\n";
            cin >> temp.cnt;
            cout << "- production date[day month year]\n";
            cin >> temp.date;
            while(!temp.date.isValidDate())
            {
                cout << "Issue! Date isn't correct. Please input correct date\n";
                cin >> temp.date;
            }
            cout << "-production time[hours minutes]]\n";
            cin >> temp.time;
            while(!temp.time.isValidTime())
            {
                cout << "Issue! Time isn't correct. Please input correct time\n";
                cin >> temp.time;
            }
            cout << "- expiration date[day month year]\n";
            cin >> temp.expirationDate;
            while(!temp.expirationDate.isValidDate())
            {
                cout << "Issue! Date isn't correct. Please input correct date\n";
                cin >> temp.expirationDate;
            }
            if(!availableId.empty())
            {
                temp.id = *availableId.end();
                availableId.pop_back();
            }
            else
            {
                temp.id = maxID;
                maxID++;
            }

            shop.push_back(temp);
            cout << "---   Complete!!! ----\n";
        }
        else if(request == "save")
        {
            FILE *f = fopen("Data.txt", "w");
            int n = shop.size();
            fprintf(f, "%d\n", n);
            char *tmpData;
            for(int i = 0; i < shop.size(); i++)
            {
                fprintf(f, "%d %s %s %d %d %d %d ",shop[i].id, shop[i].name, shop[i].measure, shop[i].cnt,  shop[i].date.day, shop[i].date.month, shop[i].date.year);
                fprintf(f, "%d %d %d %d %d\n",shop[i].time.hours, shop[i].time.minutes, shop[i].expirationDate.day, shop[i].expirationDate.month, shop[i].date.year);
            }
            fprintf(f, "%d\n", availableId.size());
            for(int i = 0; i < availableId.size(); i++)
                fprintf(f, "%d ", availableId[i]);
            if(availableId.size() > 0) fprintf(f, "\n");
            fprintf(f, "%d\n", maxID);
            fclose(f);
            cout << "---   Complete!!! ---\n";
        }
        else if(request == "restore")
        {
            FILE *f = fopen("Data.txt", "r");
            if (f == NULL)
            {
                perror("Error opening file");
                return 1;
            }

            shop.clear();
            /*int n;
            tGoods temp;
            fscanf(f, "%d", n);
            for(int i = 0; i < n; i++)
            {
                fscanf(f, "%d %s %s %d", temp.id, temp.name, temp.measure,temp.cnt );
                fscanf(f, "%d %d %d %d %d",  temp.date.day, temp.date.month, temp.date.year, temp.time.hours, temp.time.minutes);
                fscanf(f, "%d %d %d",  temp.expirationDate.day, temp.expirationDate.month, temp.expirationDate.year);
                shop.push_back(temp);
            }*/

            char buffer[10000];
            fgets(buffer, sizeof(buffer),f);
            int n = atoi(buffer);
            for(int i = 0; i < n; i++)
            {
                fgets(buffer, sizeof(buffer),f);
                tGoods temp = convertInputData(buffer);
                shop.push_back(temp);
            }
            cout << "---   Complete!!! ---\n";
            fclose(f);
        }
        else if(request == "output")
        {
            output(shop);
        }
        else if(request == "search")
        {
            cout << "Choose type of requests:\n";
            cout << "Type 1: Products with a name that ends with a given text fragment\n";
            cout << "Type 2: Products with a given unit of measurement and a expiration date of at least the given one\n";
            cout << "Type 3: Products with a production date in the given range\n";
            cout << "Please, write the type of request(number 1, 2 or 3):\n";

            int typeRequest;
            cin >> typeRequest;
            if(typeRequest == 1)
            {
                cout << "Write a text fragment:\n";
            }
            else if(typeRequest == 2)
            {
                cout << "Write a text fragment:\n";
            }
            else if(typeRequest == 2)
            {
                cout << "Write a date range:\n";
            }
            else
            {
                cout << "Error!\nWrong request!";
                return 1;
            }

        }
        else
        {
            cout << "Error!\nWrong request!";
            return 1;
        }
        cout << "\n";
    }

    /*
    char* inputMessage;

    if (f == NULL) {
        perror("Error opening file");
        return 1;
    }

    while(fread(inputMessage, sizeof(char*),1,f))
    {
        cout << inputMessage;
    }*/



    return 0;
}
