/* 2020 рік Білет 6 
№1 В елеентах зв'язного списку розміщені цілі числа. Наисати функцію, що
роздруковує значення елементів розташованих між найменшим на найбільшим елементами списку.*/
#include <iostream>
#include <random>

using namespace std;

struct Node
{
    int value;
    Node* next;
    Node(int value): value(value), next(nullptr) {}
};

struct LinkedList
{
    Node* head;
    LinkedList(): head(nullptr) {}
    void printBetweenMinAndMax()
    {
        Node* current = head->next;
        Node* maxElem = head;
        Node* minElem = head;
        int whoIsLast = 2; //if whoIsLast = 2 then position of minElem is earlier than maxElem
        while(current)
        {
            if(current->value > maxElem->value)
            {
                maxElem = current;
                whoIsLast = 2;
            }
            if(current->value < minElem->value)
            {
                minElem = current;
                whoIsLast = 1;
            }
            current = current->next;
        }

        if(whoIsLast == 1) swap(minElem, maxElem);

        while(minElem != maxElem->next)
        {
            cout << minElem->value << " ";
            minElem = minElem->next;
        } 
        cout << endl;
    }

    void add(int value)
    {
        if(head == nullptr) 
            head = new Node(value);
        else
        {
            Node* current = head;
            while(current->next)
                current = current->next;
            current->next = new Node(value);
        }
    }

    void print() 
    {
        Node* current = head;
        while (current) 
        {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    srand(time(NULL));
    LinkedList list;
    for(int i = 0; i < 12; i++)
        list.add(rand()%100);

    list.print();
    list.printBetweenMinAndMax();
}


/*
 Node* minValue()
    {
        Node* current = head->next;
        Node* minElem = head;
        while(current)
        {
            if(current->value < minElem->value)
                minElem = current;
            current = current->next;
        }
        return minElem;
    }
    Node* maxValue()
    {
        Node* current = head->next;
        Node* maxElem = head;
        while(current)
        {
            if(current->value < maxElem->value)
                maxElem = current;
            current = current->next;
        }
        return maxElem;
    }
*/