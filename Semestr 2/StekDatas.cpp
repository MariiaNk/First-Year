#include <iostream>
#include <ostream>

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

    friend std::ostream & operator<<(std::ostream &os, tDate& p)
    {
        if(p.day < 10)
            os << "0";
        os << p.day << ".";
        if(p.month < 10)
            os << "0";
        return os << p.month << "." << p.year ;
    }
};

struct tNode
{
    tDate value;
    tNode* prev;
    //1)create_empty – створення пустого стеку;
    void create_empty()
    {
        prev = nullptr;
        value = {0, 0, 0};
    }
    //2) push –  додавання елементу до стеку
    void push(tDate valueEL)
    {
        tNode* top = new tNode;
        top->value = valueEL;
        top->prev = this;
        *this = *top;
    }
    //3) pop –  вилучення елементу зі стеку;
    void pop()
    {
        if(this == NULL) std::cout << "Stack already empty!!!";
        else
        {
            tNode* temp = prev;
            delete this;
            *this = *temp;
        }
    }
    //4) peek – значення верхнього елементу стеку (без видалення)
    tDate peek() const
    {
        return value;
    }
    //5) is_empty – перевірка на пустоту
    bool is_empty() const
    {
        return (this == NULL);
    }
};

void writeStack(tNode* stack)
{
    tNode* current = stack;
    while (current != nullptr)
    {
        std::cout << (current->peek()) << std::endl;
        current = current->prev;
    }
}


int main()
{
    tNode* Calendar = new tNode;
    Calendar->create_empty();

    // Додавання елементу до стеку
    tDate date1 = {1, 2, 2024};
    Calendar->push(date1);

    // Перевірка верхнього елементу (без видалення)
    tDate topDate = Calendar->peek();
    std::cout << "Top date: " << topDate.day << "/" << topDate.month << "/" << topDate.year << std::endl;

    // Вилучення елементу зі стеку
    Calendar->pop();

    // Перевірка на пустоту
    if (Calendar->is_empty())
        std::cout << "Stack is empty" << std::endl;
    else
        std::cout << "Stack is not empty" << std::endl;

    delete Calendar;

    return 0;
}
