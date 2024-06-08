#include <iostream>
#include <cstring>

using namespace std;



struct Node
{
    int value;
    Node *next;
    Node(int value) : value(value), next(nullptr) {}
};
void push(Node *&head, int value)
{
    if (head == nullptr)
    {
        head = new Node(value);
    }
    else
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
}

void pop(Node *&head)
{
    if (head == nullptr)
        return;
    else
    {
        Node *current = head;
        head = head->next;
        delete current;
    }
}


//відсутня перевірка на правильність вхідної інформації
//відсутня перевірка на порожність стека  в кінці

/* Написати функцію для обчислення значення виразу з цілих чисел та операцій “+”, ”*” 
записано у форму ПОЛІЗ. Потрібний стек реалізувати власноруч*/
bool countPoliz(int* expr, int n, int &result)
{
    /*Повертає: false - якщо помилка*/
    //Припустимо, що числа у полізі тільки не від'ємні, тоді зарезервуємо
    // -1 як '*' та -2 як '+' 
    result = 0;
    Node* stack = nullptr;

    int digit = 0;
    for(int i = 0; i < n; i++)
    {
        if(expr[i] == -1 || expr[i] == -2)
        {
            if(!stack || !stack->next)
                return false;
            digit = stack->value;
            pop(stack);
            if(expr[i] == -2) stack->value += digit;
            else stack->value *= digit;
        }
        else if(expr[i] >= 0)
            push(stack, (expr[i]));
        else return false;
    }

    if(!stack) return false;
    
    if(stack->next == nullptr) 
    {
        result = stack->value;
        return true;
    }
    return false;
    
}
int main()
{
    // -1 = '*'  
    // -2 = '+'
    int expr[] = {2, 3, 4 , -2, -1};
    int n = sizeof(expr) / sizeof(expr[0]);
    int result = 0;
    if(!countPoliz(expr, n, result)) cout << "Error\n";
    else cout << result << endl;
}