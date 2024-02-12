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
};

class tStack
{
    private:
        tNode *top;
    public:
        // 1)create_empty – створення пустого стеку;
        tStack()
        {
            top = nullptr;
        }
        // 2) push –  додавання елементу до стеку
        void push(tDate valueEL)
        {
            tNode *newNode = new tNode;
            newNode->value = valueEL;
            newNode->prev = top;
            top = newNode;
        }
        // 3) pop –  вилучення елементу зі стеку;
        void pop()
        {
            if(top == nullptr)
                cout << "Stack already empty!!!";
            else
            {
                tNode *temp = top;
                top = top->prev;
                delete temp;
            }
        }
        // 4) peek – значення верхнього елементу стеку (без видалення)
        tDate peek()
        {
            if(top != nullptr)
                return top->value;
            cout << "Stack already empty!!!";
            exit(EXIT_FAILURE);
        }
        // 5) is_empty – перевірка на пустоту
        bool is_empty() const
        {
            return top == nullptr;
        }
        void writeStack()
        {
            tNode *current = top;
            cout << "Stack:\n";
            while (current != nullptr)
            {
                cout << current->value << endl;
                current = current->prev;
            }
            cout << endl;
        }
        void deleteStack() 
        {
            while (!is_empty()) {
                pop();
            }
        }

};


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

void outputMenu()
{
    cout << "==== Stack MENU ====\n";
    cout << "1 - Create empty stack\n";
    cout << "2 - Add new item to stack\n";
    cout << "3 - Delete top item from stack\n";
    cout << "4 - Check for empty stack\n";
    cout << "5 - Get the value of the top element of the stack (without removing)\n";
    cout << "6 - Output all stack\n";
    cout << "7 - End program\n";
    cout << "Please, write the number of your request: ";

}
void InteractiveMode()
{
    tStack Calendar;
    int request;
    do
    {
        outputMenu();
        cin >> request;
        if (request == 1)
        {
            Calendar = tStack();
            cout << " ==== Complete =====";
        }
        else if (request == 2)
        {
            Calendar.push(addElem());
            cout << " ==== Complete =====";
        }
        else if (request == 3)
        {
            Calendar.pop();
            cout << " ==== Complete =====";
        }
        else if (request == 4)
        {
            if(Calendar.is_empty())
                cout << "The stack is empty :(\n";
            else
                cout << "The stack isn't empty!!!\n";
        }
        else if (request == 5)
        {
            cout << "The value of the top element of the stack: " << Calendar.peek() << endl;
        }

        else if (request == 6)
        {
            Calendar.writeStack();
        }
        else cout << "----- Error! Wrong request! Try again!!! -----";
        cout << endl;
    } while (request != 7);
    Calendar.deleteStack();
}

void DemonstrationMode()
{
    srand(time(NULL));
    tStack Calendar;
    Calendar = tStack();
    tDate generateDate;
    for(int i = 0; i < 20; i++)
    {
        generateDate.day = rand() % 27 + 1;
        generateDate.month = rand() % 11 + 1;
        generateDate.year = rand()%125 + 1900;

        Calendar.push(generateDate);
    }
    cout << " Get the value of the top element of the stack (without removing): " << Calendar.peek() << "\n";
    cout << " Delete top item from stack\n";
    Calendar.pop();
    cout << " Get the value of the top element of the stack (without removing): " << Calendar.peek() << "\n";
    Calendar.writeStack();
    Calendar.deleteStack();
}

int main()
{
    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\n";
    char mode;
    cin >> mode;
    if (mode == 'i')
        InteractiveMode();
    else if(mode == 'd')
        DemonstrationMode();
    /*else if(mode == 'b')
        //return benchmarkMode();*/
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
    return 0;


}
