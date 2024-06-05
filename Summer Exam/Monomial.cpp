#include <iostream>

using namespace std;

struct Node
{
    int coeff;
    int degree; // оскільки ми не зберігаємо одночленів з нульовими коефіцієнтами.
    Node *next;

    Node(int coeff_item, int degree_item, Node *next_item = nullptr)
    {
        coeff = coeff_item;
        degree = degree_item;
        next = next_item;
    }
};

Node *addMonomial(Node *polynom, int coeff_item, int degree_item)
{
    if (coeff_item == 0)
        return polynom;

    Node *newNode = new Node(coeff_item, degree_item);
    // пустий список
    if (polynom == nullptr)
        return newNode;

    // додамо елемент з найменшою степінню
    if (polynom->degree > degree_item)
    {
        newNode->next = polynom;
        return newNode;
    }

    // оновлюємо найменший елемент
    if (polynom->degree == degree_item)
    {
        polynom->coeff += coeff_item;
        // видаляємо найменший елемент, якщо коефіцієнт 0
        if (polynom->coeff == 0)
        {
            Node *temp = polynom->next;
            delete polynom;
            return temp;
        }
        return polynom;
    }

    Node *current = polynom;
    while (current->next && current->next->degree < degree_item)
        current = current->next;

    if (current->next && current->next->degree == degree_item)
    {
        current->next->coeff += coeff_item;
        if (current->next->coeff == 0)
        {
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }
    else
    {
        newNode->next = current->next;
        current->next = newNode;
    }

    return polynom;
}

void print(Node *polynom)
{
    cout << "Polynom: ";
    Node *current = polynom;
    while (current)
    {
        if (current->coeff >= 0)
            cout << "+";
        cout << current->coeff << "x^" << current->degree;
        current = current->next;
    }
    cout << endl;
}
/*Многочлен від однієї змінної з цілими коефіцієнтам можна подати у вигляді зв'язного списку,
впорядкованим за зростанням степені змінної, без зберігання одночленів з нульовими коефіцієнтами.
Написати функцію, яка знаходить степінь многочлена*/
int degreePolynom(Node *polynom)
{
    Node *current = polynom;
    while (current->next)
        current = current->next;
    return current->degree;
}

/*Поліном від однієї змінної з цілими коефіцієнтами можна подати зв’язним списком,
впорядкованим за зростанням степені змінної, без зберігання одночленів з нульовими коефіцієнтами.
Написати функцію, яка знаходить суму двох поліномів */
Node *additionPolynoms_ver1(Node *firstPolynom, Node *secondPolynom)
{
    Node *result = nullptr;

    Node *current = firstPolynom;
    while (current)
    {
        result = addMonomial(result, current->coeff, current->degree);
        current = current->next;
    }

    current = secondPolynom;
    while (current)
    {
        result = addMonomial(result, current->coeff, current->degree);
        current = current->next;
    }

    return result;
}
int main()
{
    Node *polynom = nullptr;
    polynom = addMonomial(polynom, 1, 4);
    polynom = addMonomial(polynom, -5, 3);
    polynom = addMonomial(polynom, 8, 1);
    polynom = addMonomial(polynom, 1, 2);
    print(polynom);
    polynom = addMonomial(polynom, 3, 2);
    polynom = addMonomial(polynom, 0, 5);
    print(polynom);
    cout << "Polynom degree: " << degreePolynom(polynom) << endl;

    Node *secondPolynom = nullptr;
    secondPolynom = addMonomial(secondPolynom, 3, 2);
    secondPolynom = addMonomial(secondPolynom, 8, 4);
    secondPolynom = addMonomial(secondPolynom, -7, 1);
    secondPolynom = addMonomial(secondPolynom, -9, 3);
    secondPolynom = addMonomial(secondPolynom, 8, 5);
    print(secondPolynom);

    Node *res = additionPolynoms(polynom, secondPolynom);
    print(res);
}