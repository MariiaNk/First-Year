#include <iostream>
#include <string>

using namespace std;

struct tDate
{
    int day;
    int month;
    int year;

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

    friend istream &operator>>(istream &is, tDate &p)
    {
        return is >> p.day >> p.month >> p.year;
    }

    friend ostream &operator<<(ostream &os, tDate p)
    {
        if (p.day < 10)
            os << "0";
        os << p.day << ".";
        if (p.month < 10)
            os << "0";
        return os << p.month << "." << p.year;
    }
};

struct tNode
{
    tDate value;
    tNode *prev;
    // 1)create_empty – створення пустого стеку;
    void create_empty()
    {
        prev = nullptr;
        value = {0, 0, 0};
    }
    // 2) push –  додавання елементу до стеку
    void push(tDate valueEL)
    {
        tNode *top = new tNode;
        top->value = valueEL;
        top->prev = this;
        *this = *top;
    }
    // 3) pop –  вилучення елементу зі стеку;
    void pop()
    {
        if(this->is_empty()) 
            cout << "Stack already empty!!!";
        else
        {
            tNode *temp = prev;
            delete this;
            *this = *temp;
        }
    }
    // 4) peek – значення верхнього елементу стеку (без видалення)
    tDate peek() const
    {
        return value;
    }
    // 5) is_empty – перевірка на пустоту
    bool is_empty() const
    {
        return (prev == nullptr && (value.day == 0 && value.month == 0 && value.year == 0));
    }
};
void writeStack(tNode *stack)
{
    tNode *current = stack;
    while (current != nullptr)
    {
        cout << (current->peek()) << endl;
        current = current->prev;
    }
}
tDate addElem()
{
    tDate temp;
    cout << "Enter date[day month year]\n";
    cin >> temp;
    while (!temp.isValidDate())
    {
        cout << "Issue! Date isn't correct. Please input correct date\n";
        cin >> temp;
    }
    return temp;
}
int InteractiveMode()
{
    tNode *Calendar = new tNode;
    Calendar->create_empty();
    cout << "What do you want to do? [key word]\n- Create empty stack: create empty\n- Add new item from stack: add\n- Delete item to stack: pop\n- : peek\n- Output all stack: output\n- Delete an element by ID: delete\n- End program: end\nPlease, write the key word of your request\n";
    string request;
    do
    {
        cin.ignore();
        getline(std::cin, request);
        if (request == "add")
        {
            Calendar->push(addElem());
        }
        else if (request == "pop")
        {
            Calendar->pop();
        }
        else if (request == "peek")
        {
        }
        else if (request == "top")
        {
        }
        else if (request == "is empty")
        {
        }
        else if (request == "create empty")
        {
        }
        else if(request == "output")
        {
            
        }
        else cout << "Error!\nWrong request!\nTry again!!!\n";
    } while (request != "end");

    delete Calendar;
    return 0;
}

int main()
{
    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\n";
    char mode;
    cin >> mode;
    if (mode == 'i')
        return InteractiveMode();
    /*else if(mode == 'd')
        //return DemonstrationMode();
    else if(mode == 'b')
        //return benchmarkMode();
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }*/
    return 0;

    /*tDate date1 = {1, 2, 2024};
    Calendar->push(date1);

    // Перевірка верхнього елементу (без видалення)
    tDate topDate = Calendar->peek();
    cout << "Top date: " << topDate.day << "/" << topDate.month << "/" << topDate.year << endl;

    // Вилучення елементу зі стеку
    Calendar->pop();

    // Перевірка на пустоту
    if (Calendar->is_empty())
        cout << "Stack is empty" << endl;
    else
        cout << "Stack is not empty" << endl;

    */

    return 0;
}
