#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#define STRMAX 100000

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
        if(p.day < 10)
            os << setw(6) << "0";
        else
            os << setw(7);
        os << p.day << ".";
        if(p.month < 10)
            os << "0";
        return os << p.month << "." << p.year ;
    }

    bool isValidDate() const
    {
        if (month < 1 || month > 12)
            return false;
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
            daysInMonth[2] = 29;
        if (day < 1 || day > daysInMonth[month])
            return false;
        if (year < 1900 || year > 2100)
            return false;
        return true;
    }

    bool operator >= (const tDate& other) const
    {
        if (year != other.year)
            return year > other.year;
        if (month != other.month)
            return month > other.month;
        return day >= other.day;
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
        if( p.hours < 10)
            os << setw(4) << "0";
        else
            os << setw(5);
        os << p.hours << ":";
        if(p.minutes < 10)
            os << "0";
        return os << p.minutes ;
    }
    bool isValidTime() const
    {
        if(minutes > 60 || minutes < 0)
            return false;
        if(hours > 23 || hours < 0)
            return false;
        return true;
    }

};
struct tGoods
{
    int id;
    char name[STRMAX];
    char measure[STRMAX];
    int cnt; //кількість товару
    tDate date; // дата виробництва
    tTime time; // час виробництва в хвилинах
    tDate expirationDate; //термін придатності
};
void outputGood (tGoods temp)
{
    cout << "|" << setw(5) << temp.id << "|" << setw(10) << temp.name;
    cout << "|" << setw(10) << temp.measure<<"|" << setw(10) << temp.cnt;
    cout << "|" << temp.date << "|" << temp.time << "|" << temp.expirationDate << "|\n";
}
void outputheader ()
{
    cout << "|" << setw(6) << "ID|" << setw(11) << "Name|" << setw(11) << "Measure|" << setw(11) << "Count|" << setw(16) << "Product date|" << setw(9) << "Time|" << setw(16) << "Expiration date|\n";
    cout << "---------------------------------------------------------------------------------\n";
}
void outputData(vector <tGoods> const &shop)
{
    outputheader();
    for(int i = 0; i < shop.size(); i++)
        outputGood(shop[i]);
}
bool isValidMeasure(char *str)
{
    return strcmp(str, "kg") == 0 || strcmp(str, "l") == 0 || strcmp(str, "pack") == 0 || strcmp(str, "ind") == 0;
}
void outputFindData(vector <int> const &res, vector <tGoods> const &shop)
{
    if(res.size() == 0) cout << "Ohhhh! No matching!\n";
    else
    {
        outputheader();
        for(auto ids: res)
            outputGood(shop[ids]);
    }
}
vector <int> findEndFragment(vector <tGoods> const &shop, const char * endFrag)
{
    vector <int> findId;
    int sizeFrag = strlen(endFrag);
    for(int i = 0; i < shop.size(); i++)
    {
        int j = 1, sizeName = strlen(shop[i].name);
        if(sizeFrag <= sizeName)
        {
            while(j <= sizeFrag && shop[i].name[sizeName - j] == endFrag[sizeFrag - j])
                j++;
            if(j == sizeFrag + 1) findId.push_back(i);
        }

    }
    return findId;
}
vector <int> findMeasureDate (vector <tGoods> const &shop, const char * measureReq, tDate const &dateReq)
{
    vector <int> findId;
    for(int i = 0; i < shop.size(); i++)
    {
        if(strcmp(shop[i].measure, measureReq) == 0)
        {
            //cout << i << ":" << shop[i].expirationDate << " <= [" << dateReq << "]\n"
            if(shop[i].expirationDate >= dateReq)
                findId.push_back(i);
        }
    }
    return findId;
}
vector <int> findDateInRange (vector <tGoods> const &shop,  tDate const &first, tDate const &finish)
{
    vector <int> findId;
    for(int i = 0; i < shop.size(); i++)
    {
        if(shop[i].date >= first && finish >= shop[i].date)
            findId.push_back(i);
    }
    return findId;
}
int findWithId(vector <tGoods> const shop,  const int&idReq)
{
    vector <int> findId;
    for(int i = 0; i < shop.size(); i++)
    {
        if(shop[i].id == idReq)
            return i;
    }
    return -1;
}
tGoods addElement(vector <int> &availableId, int &maxID)
{
    tGoods temp;
    cout << "Write element details:\n- name\n";
    cin.ignore();
    cin.getline(temp.name, sizeof(temp.name));
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
        temp.id = availableId.back();
        availableId.pop_back();
    }
    else
    {
        temp.id = maxID;
        maxID++;
    }
    return temp;
}
void saveDataToFile(vector <tGoods> const &shop, vector <int> const &availableId, int maxID, char * format)
{
    FILE *f;
    if(strcmp(format, "bin") == 0)
        f = fopen("BinData.bin", "wb");
    else
        f = fopen("Data.txt", "w");

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
int restoreDataFromFile(vector <tGoods> &shop, vector <int> &availableId, int &maxID, char* format)
{
    FILE *f;
    if(strcmp(format, "bin") == 0)
        f = fopen("BinData.bin", "rb");
    else if (strcmp(format, "txt") == 0)
        f = fopen("Data.txt", "r");
    if (f == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    shop.clear();
    int n;
    tGoods temp;
    fscanf(f, "%d", &n);
    for(int i = 0; i < n; i++)
    {
        fscanf(f, "%d %s %s %d", &temp.id, &temp.name, &temp.measure, &temp.cnt );
        fscanf(f, "%d %d %d %d %d",  &temp.date.day, &temp.date.month, &temp.date.year, &temp.time.hours, &temp.time.minutes);
        fscanf(f, "%d %d %d",  &temp.expirationDate.day, &temp.expirationDate.month, &temp.expirationDate.year);
        shop.push_back(temp);
    }
    fscanf(f, "%d", &n);
    availableId.clear();
    int notUsedId = 0;
    for(int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &notUsedId);
        availableId.push_back(notUsedId);
    }
    fscanf(f, "%d", &maxID);
    fclose(f);
    cout << "---   Complete!!! ---\n";
}
void searchDataReq (vector <tGoods>const &shop)
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
        char endReq[STRMAX];
        cin >> endReq;
        cout << endReq << "\n";
        vector <int> res = findEndFragment(shop, endReq);
        outputFindData(res, shop);
    }
    else if(typeRequest == 2)
    {
        cout << "Write a unit of measurement:\n";
        char measureReq[STRMAX];
        tDate dateReq;
        cin >> measureReq;
        while(!isValidMeasure(measureReq))
        {
            cout << "Issue! Measure isn't correct. Please input correct measure[kg/l/ind/pack]\n";
            cin >> measureReq;
        }
        cout << "Write a expiration date of at least the given one:\n";
        cin >> dateReq;
        while(!dateReq.isValidDate())
        {
            cout << "Issue! Date isn't correct. Please input correct date\n";
            cin >> dateReq;
        }
        vector <int> res = findMeasureDate(shop, measureReq, dateReq);
        outputFindData(res, shop);


    }
    else if(typeRequest == 3)
    {
        cout << "Write a first date in range:\n";
        tDate firstDate;
        cin >> firstDate;
        while(!firstDate.isValidDate())
        {
            cout << "Issue! Date isn't correct. Please input correct date\n";
            cin >> firstDate;
        }
        cout << "Write a latest date in range:\n";
        tDate finishDate;
        cin >> finishDate;
        while(!finishDate.isValidDate())
        {
            cout << "Issue! Date isn't correct. Please input correct date\n";
            cin >> finishDate;
        }
        vector <int> res = findDateInRange(shop, firstDate, finishDate);
        outputFindData(res, shop);
    }
    else  cout << "Error!\nWrong request!\nTry again!!!\n";
    cout << "---   Complete!!! ---\n";
}
void deleteElemByID(vector <tGoods> &shop, vector<int> &availableId, int idReq)
{
    int res = findWithId(shop, idReq);
    if(res == -1) cout << "Ohhhh! No matching!";
    else
    {
        shop.erase(shop.begin() + res);
        availableId.push_back(idReq);
        cout << "---   Complete!!! ---\n";
    }
}
void modifyElementByID(vector <tGoods> &shop, int idReq)
{
    int numId = findWithId(shop, idReq);
    if(numId == -1)
        cout << "Ohhhh! No matching!";
    else
    {
        char strReq[STRMAX];
        do
        {
            cout << "Write a variable you want change[name, measure, count, product date, product time, expiration data]:\nIf you want save changes write: end\n";
            cin >> strReq;
            if(strcmp(strReq, "name") == 0)
            {
                char nameReq[STRMAX];
                cout << "Write a new name: ";
                cin.ignore();
                cin.getline(nameReq, sizeof(nameReq));
                strcpy(shop[numId].name, nameReq);
            }
            else if (strcmp(strReq, "measure") == 0)
            {
                char measureReq[STRMAX];
                cout << "Write a new measure: ";
                cin >> measureReq;
                while(!isValidMeasure(measureReq))
                {
                    cout << "Issue! Measure isn't correct. Please input correct measure[kg/l/ind/pack]\n";
                    cin >> measureReq;
                }
                strcpy(shop[numId].measure, measureReq);
            }
            else if (strcmp(strReq, "count") == 0)
            {
                int digReq;
                cout << "Write a new count: ";
                cin >> digReq;
                shop[numId].cnt = digReq;
            }
            else if (strcmp(strReq, "product date") == 0)
            {
                tDate dateReq;
                cout << "Write a new product date: ";
                cin >> dateReq;
                while(!dateReq.isValidDate())
                {
                    cout << "Issue! Date isn't correct. Please input correct date\n";
                    cin >> dateReq;
                }
                shop[numId].date = dateReq;
            }
            else if (strcmp(strReq, "product time") == 0)
            {
                tTime timeReq;
                cin >> timeReq;
                while(!timeReq.isValidTime())
                {
                    cout << "Issue! Time isn't correct. Please input correct time\n";
                    cin >> timeReq;
                }
                shop[numId].time = timeReq;
            }
            else if (strcmp(strReq, "expiration data") == 0)
            {
                tDate dateReq;
                cout << "Write a new expiration date: ";
                cin >> dateReq;
                while(!dateReq.isValidDate())
                {
                    cout << "Issue! Date isn't correct. Please input correct date\n";
                    cin >> dateReq;
                }
                shop[numId].expirationDate = dateReq;
            }
            else if(strcmp(strReq, "end") != 0) cout << "Error!\nWrong variable!\nTry again!!!\n";


        }
        while(strcmp(strReq, "end") != 0);
    }
}
int InteractiveMode()
{
    vector <tGoods> shop;
    vector <int> availableId;
    int maxID = 0;
    cout << "What do you want to do? [key word]\n- Add data: add\n- Save data to file: save\n- Restore data: restore\n- Output saved data: output\n- Search by specified criteria: search\n- Delete an element by ID: delete\n- Modify element by id: modify\nPlease, write the key word of your request\n";
    string request;
    while(cin >> request)
    {
        if(request == "add")
            shop.push_back(addElement(availableId, maxID));
        else if(request == "save")
        {
            cout << "What file do you choose: bin / txt: ";
            char format[STRMAX];
            cin >> format;
            while(strcmp(format, "bin") != 0 && strcmp(format, "txt") != 0)
            {
                cout << "Issue! Format of file isn't correct. Please input correct format[bin / txt]\n";
                cin >> format;
            }
            saveDataToFile(shop, availableId, maxID, format);
        }
        else if(request == "restore")
        {
            cout << "What file do you choose: bin / txt: ";
            char format[STRMAX];
            cin >> format;
            while(strcmp(format, "bin") != 0 && strcmp(format, "txt") != 0)
            {
                cout << "Issue! Format of file isn't correct. Please input correct format[bin / txt]\n";
                cin >> format;
            }
            if (restoreDataFromFile(shop, availableId, maxID, format) == 1)  return 1;
        }
        else if(request == "output")
            outputData(shop);
        else if(request == "search")
            searchDataReq(shop);
        else if(request == "delete")
        {
            cout << "Write an ID of element:\n";
            int idReq;
            cin >> idReq;
            deleteElemByID(shop, availableId, idReq);
        }
        else if(request == "modify")
        {
            int idReq;
            cout << "Write an ID of element:\n";
            cin >> idReq;
            modifyElementByID(shop, idReq);
        }
        else cout << "Error!\nWrong request!\nTry again!!!\n";
        cout << "\n";
    }
    return 0;
}
int DemonstrationMode()
{
    vector <tGoods> shop;
    vector <int> availableId;
    int maxID = 0;
    //restore
    cout << "Req1 [restore]\n";
    if(restoreDataFromFile(shop, availableId,maxID, "txt") == 1) return 1;
    //output
    cout << "Req2 [output]\n";
    outputData(shop);
    //delete middle elem
    int idReq = shop.size()/2;
    cout << "Req3 [delElwithId " << idReq << "]\n";
    deleteElemByID(shop, availableId, idReq);
    //output
    cout << "Req4 [output]\n";
    outputData(shop);
    //search
    cout << "Req5: search type 5 with fragment \"oko\"\n";
    vector <int> res = findEndFragment(shop, "oko");
    outputFindData(res, shop);
    //add
    cout << "Req5 [add elem]\n";
    tGoods temp = {-1, "Son", "ind", 100, {12, 01, 2024}, {18, 19}, {12, 01, 2026}};
    if(!availableId.empty())
    {
        temp.id = availableId.back();
        availableId.pop_back();
    }
    else
    {
        temp.id = maxID;
        maxID++;
    }
    shop.push_back(temp);
    outputheader();
    outputGood(temp);
    //output
    cout << "Req6 [output]\n";
    outputData(shop);
    return 0;
}
char* GenerateString()
{
    char *availableSymb = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int sizeSymb = strlen(availableSymb);
    char* str = new char[STRMAX];
    int n = rand()%7 + 2;
    int symbId;
    for(int i = 0; i < n; i++)
    {
        symbId = rand() % (sizeSymb-1);
        str[i] = availableSymb[symbId];
    }
    str[n] = '\0';
    return str;
}
tDate GenerateTypeDate(tDate start)
{
    tDate temp;
    temp.day = rand() % (27 - start.day) + 1 + start.day;
    temp.month = rand() % (12 - start.month) + 1 + start.month;
    temp.year = rand() % 100 +  start.year;
    return temp;
}
vector <tGoods> GenerateData(int shopSize)
{
    int randDig;
    vector <tGoods> shop;
    vector<char*> availableMeasure = {"kg", "l", "ind", "kg"};
    tGoods temp;
    for(int i = 0; i <shopSize; i++)
    {
        temp.id = i;
        strcpy(temp.name , GenerateString());
        randDig = rand() % 4;
        strcpy(temp.measure , availableMeasure[randDig]);
        temp.date = GenerateTypeDate({1,1,1900});
        temp.cnt = rand() % 1000;
        temp.time = {rand()%24, rand()%60};
        temp.expirationDate = GenerateTypeDate(temp.date);
        outputGood(temp);
        shop.push_back(temp);
    }
    return shop;
}
int benchmarkMode()
{
    srand(time(NULL));
    int shopSize = 0;
    vector <int> availableId;
    int maxID = 0;
    cout << "Write count of element: \n";
    cin >> shopSize;
    //auto start = high_resolution_clock::now();
    vector <tGoods> shop = GenerateData(shopSize);
    outputData(shop);
    saveDataToFile(shop, availableId, maxID, "bin");
    /*restoreDataFromFile(shop, availableId, maxID, "bin");
    vector <int> res1 = findEndFragment(shop, GenerateString());
    outputFindData(res1, shop);
    /*int randDig = rand() % 4;
    vector<char*> availableMeasure = {"kg", "l", "ind", "kg"};
    char *meaTemp = availableMeasure[randDig];
    tDate datTemp = GenerateTypeDate({1,1,1900});
    vector <int> res2 = findMeasureDate(shop, meaTemp, datTemp) ;
    outputFindData(res2, shop);
    tDate first = GenerateTypeDate({1,1,1900});
    vector <int> res3 = findDateInRange(shop, first, GenerateTypeDate(first));
    outputFindData(res3, shop);*/
    outputData(shop);
    return 0;

}
int main()
{
    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\n";
    char mode;
    cin >> mode;
    if(mode == 'i')
        return InteractiveMode();
    else if(mode == 'd')
        return DemonstrationMode();
    else if(mode == 'b')
        return benchmarkMode();
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
    return 0;
}
/*
restore
output
search
1
oko
*/

/*
restore
output
search
2
kg
20 01 2022
*/

/*
restore
output
modify
3
count
456
end
output
*/
