#include <iostream>
#include <string>
#include <chrono>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using namespace std::chrono;

const int ARR_MAX = 1e9;
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

    friend std::istream &operator>>(std::istream &is, tDate &p)
    {
        return is >> p.day >> p.month >> p.year;
    }

    friend std::ostream &operator<<(std::ostream &os, tDate p)
    {
        if (p.day < 10)
            os << "0";
        os << p.day << ".";
        if (p.month < 10)
            os << "0";
        return os << p.month << "." << p.year;
    }
};
class tStack
{
public:
    virtual void create_empty() = 0;
    virtual void push(tDate value) = 0;
    virtual void pop() = 0;
    virtual tDate peek() = 0;
    virtual bool isEmpty() const = 0;
    virtual void writeStack() = 0;
    virtual size_t sizeOfStruct() = 0;
    virtual ~tStack() {}
};

class tStackNode : public tStack {
private:
    struct tNode {
        tDate value;
        tNode *prev;
        tNode(tDate valueEL, tNode *prevEL)
        {
            value = valueEL;
            prev = prevEL;
        }
    };
    tNode *top;
public:
    // 1)create_empty – створення пустого стеку;
    void create_empty() override
    {
        top = nullptr;
    }
    // 2) push –  додавання елементу до стеку
    void push(tDate value) override
    {
        tNode *newNode = new tNode(value, top);
        /*newNode->value = value;
        newNode->prev = top;*/
        top = newNode;
    }
    // 3) pop –  вилучення елементу зі стеку;
    void pop() override
    {
        if (top != nullptr) {
            tNode *temp = top;
            top = top->prev;
            delete temp;
        }
    }
    // 4) peek – значення верхнього елементу стеку (без видалення)
    tDate peek() override
    {
        if (top != nullptr)
            return top->value;
        throw std::runtime_error("Stack is empty");
    }
    // 5) is_empty – перевірка на пустоту
    bool isEmpty() const override
    {
        return top == nullptr;
    }

    void writeStack() override
    {
        tNode *current = top;
        while (current != nullptr)
        {
            cout << current->value << endl;
            current = current->prev;
        }
        cout << endl;
    }
    size_t sizeOfStruct() override
    {
        size_t totalSize = 0;
        tNode *current = top;
        while (current != nullptr)
        {
            totalSize += sizeof(tNode); 
            totalSize += sizeof(tDate); 
            current = current->prev;
        }
        return totalSize;
    }
    ~tStackNode()
    {
        while (!isEmpty()) {
            pop();
        }
    }
};

class tStackArr : public tStack
{
private:
    int sizeOfArr;
    tDate arr[ARR_MAX];
public:
    // 1)create_empty – створення пустого стеку;
    void create_empty() override
    {
        sizeOfArr = 0;
    }
    // 2) push –  додавання елементу до стеку
    void push(tDate value) override
    {
        if (sizeOfArr < ARR_MAX)
            arr[sizeOfArr++] = value;
        else
            throw std::runtime_error("Stack overflow");
    }
    // 3) pop –  вилучення елементу зі стеку;
    void pop() override
    {
        if (sizeOfArr > 0)
            --sizeOfArr;
        else
            throw std::runtime_error("Stack is empty");
    }
    // 4) peek – значення верхнього елементу стеку (без видалення)
    tDate peek() override
    {
        if (sizeOfArr > 0)
            return arr[sizeOfArr - 1];
        else
            throw std::runtime_error("Stack is empty");
    }
    // 5) is_empty – перевірка на пустоту
    bool isEmpty() const override
    {
        return sizeOfArr == 0;
    }
    void writeStack() override
    {
        for (int i = sizeOfArr - 1; i >= 0; --i)
            cout << arr[i] << endl;
        cout << endl;
    }
    size_t sizeOfStruct() override
    {
        return sizeOfArr * sizeof(tDate);
    }
    /*~tStackArr()
    {
        delete[] arr;
    }*/
};

class tStackVector : public tStack
{
private:
    std::vector<tDate> dynArr;
public:
    // 1)create_empty – створення пустого стеку;
    void create_empty() override
    {
        dynArr.clear();
    }
    // 2) push –  додавання елементу до стеку
    void push(tDate value) override
    {
        dynArr.push_back(value);
    }
    // 3) pop –  вилучення елементу зі стеку;
    void pop() override
    {
        if (!dynArr.empty())
            dynArr.pop_back();
        else
            throw std::runtime_error("Stack is empty");
    }
    // 4) peek – значення верхнього елементу стеку (без видалення)
    tDate peek() override
    {
        if (!dynArr.empty())
            return dynArr.back();
        else throw
            std::runtime_error("Stack is empty");
    }
    // 5) is_empty – перевірка на пустоту
    bool isEmpty() const override
    {
        return dynArr.empty();
    }
    void writeStack() override
    {
        for (int i = dynArr.size() - 1; i >= 0; --i)
            cout << dynArr[i] << endl;
        cout << endl;
    }
    size_t sizeOfStruct() override
    {
        size_t totalSize = dynArr.size() * sizeof(tDate);
        totalSize += sizeof(dynArr);
        return totalSize;
    }
    ~tStackVector()
    {
        dynArr.clear();
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
void InteractiveMode(int typeSave)
{
    int request;
    tStack *Calendar = nullptr;

    switch (typeSave) {
        case 3:
            cout << "Yeeehhh!\n";
            Calendar = new tStackNode();
            break;
        case 2:
            Calendar = new tStackVector();
            break;
        default:
            Calendar = new tStackArr();
            break;
    }

    do {
        outputMenu();
        cin >> request;
        switch (request) {
            case 1:
                Calendar -> create_empty();
                cout << " ==== Complete =====";
                break;
            case 2:
                Calendar->push(addElem());
                cout << " ==== Complete =====";
                break;
            case 3:
                Calendar->pop();
                cout << " ==== Complete =====";
                break;
            case 4:
                if (Calendar->isEmpty())
                    cout << "The stack is empty :(\n";
                else
                    cout << "The stack isn't empty!!!\n";
                break;
            case 5:
                cout << "The value of the top element of the stack: " << Calendar->peek() << endl;
                break;
            case 6:
                Calendar->writeStack();
                break;
            default:
                cout << "----- Error! Wrong request! Try again!!! -----";
        }
        cout << endl;
    } while (request != 7);

    delete Calendar;
}
tDate GenerateTypeDate()
{
    tDate generateDate;
    generateDate.day = rand() % 27 + 1;
    generateDate.month = rand() % 11 + 1;
    generateDate.year = rand()%70 + 1950;
    return generateDate;
}
void DemonstrationMode(int typeSave)
{
    srand(time(NULL));
    tStack *Calendar = nullptr;
    Calendar -> create_empty();
    switch (typeSave) {
        case 3:
            Calendar = new tStackNode();
            break;
        case 2:
            Calendar = new tStackVector();
            break;
        default:
            Calendar = new tStackArr();
            break;
    }

    for(int i = 0; i < 20; i++)
        Calendar->push(GenerateTypeDate());
    Calendar -> writeStack();
    cout << " Get the value of the top element of the stack (without removing): " << Calendar->peek() << "\n";
    cout << " Delete top item from stack\n";
    Calendar->pop();
    cout << " Get the value of the top element of the stack (without removing): " << Calendar->peek() << "\n";
    Calendar->writeStack();


}

void benchmarkMode(int typeSave, int sizeOfStore)
{
    srand(time(NULL));

    tStack *Calendar = nullptr;

    switch (typeSave) {
        case 3:
            Calendar = new tStackNode();
            break;
        case 2:
            Calendar = new tStackVector();
            break;
        default:
            Calendar = new tStackArr();
            break;
    }

    cout << "=== Output TIME results ===\n  Realization ";
    if(typeSave == 3) cout << "Struct\n";
    else if(typeSave == 2) cout << "Vector\n";
    else cout << "Array\n";
    auto totalStart = high_resolution_clock::now();

    auto start = high_resolution_clock::now();
    Calendar -> create_empty();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by CREATE EMPTY: " << duration.count() << " milliseconds" << endl;

    start = high_resolution_clock::now();
    for(int i = 0; i < sizeOfStore; i++)
        Calendar -> push(GenerateTypeDate());
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by PUSH*" << sizeOfStore << ": " << duration.count() << " milliseconds" << endl;

    //Calendar -> writeStack();
    start = high_resolution_clock::now();
    Calendar -> pop();
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by POP: " << duration.count() << " milliseconds" << endl;

    start = high_resolution_clock::now();
    tDate temp = Calendar -> peek();
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by PEEK: " << duration.count() << " milliseconds" << endl;

    start = high_resolution_clock::now();
    bool tempEmpty = Calendar -> isEmpty();
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by IS EMPTY: " << duration.count() << " milliseconds" << endl;

    auto totalStop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(totalStop - totalStart);
    cout << "Time taken by TOTAL: " << duration.count() << " milliseconds" << endl << endl;

    size_t objectSize = Calendar -> sizeOfStruct();
    cout << "==== SIZE OF";
    if(typeSave == 3) 
        cout << " STRUCT ==== \n";
    else if(typeSave == 2) 
        cout << " VECTOR ==== \n";
    else 
        cout << " ARRAY ==== \n";
    cout << "Size of Calendar: " << objectSize << " bytes" << endl << endl;

    delete Calendar;
}
int main()
{
    

    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\nEnter mode: ";
    char mode;
    cin >> mode;
    if (mode == 'i')
    {
        cout << "Type of saving:\n1 - array\n2 - vector\n3 - struct\nEnter type of saving: ";
        int save;
        cin >> save;
        if(save > 3 || save < 1)
        {
            cout << "Error. Program isn't started\n";
            return 1;
        }
        InteractiveMode(save);
    }
    else if(mode == 'd')
    {
        cout << "Type of saving:\n1 - array\n2 - vector\n3 - struct\nEnter type of saving: ";
        int save;
        cin >> save;
        if(save > 3 || save < 1)
        {
            cout << "Error. Program isn't started\n";
            return 1;
        }
        DemonstrationMode(save);
    }
    else if(mode == 'b')
    {
        int sizeOfStore = 0;
        cout << "Write count of element: \n";
        cin >> sizeOfStore;
        for(int i = 1; i <=3; ++i)
            benchmarkMode(i, sizeOfStore);
    }
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
    return 0;
}

