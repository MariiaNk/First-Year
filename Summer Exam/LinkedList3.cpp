/* 2020 рік Білет 6 
№1 В елементах двохзв’язного списку розміщені цілі числа. Написати функцію, що вилучає всі мінімальні елементи.*/
#include <iostream>
#include <random>

using namespace std;

struct Node
{
    int value;
    Node* next;
    Node* prev;
    Node(int value = 0): value(value), next(nullptr), prev (nullptr) {}
};

struct LinkedList
{
    Node* head;
    Node* tail;
    LinkedList(): head(nullptr), tail(nullptr) {}
    int minValue()
    {
        Node* current = head->next;
        int minElem = head->value;
        while(current)
        {
            if(current->value < minElem)
                minElem = current->value;
            current = current->next;
        }
        return minElem;
    }
    void remove(Node* item)
    {
        if(item != nullptr)
        {
            if(item == tail)
                tail = item->prev;
            else
                item->next->prev = item->prev;

            if(item == head)
                head = item->next;
            else
                item->prev->next = item->next;
            delete item;
        }
    }
    void deleteAllMinElement()
    {
        int minimumValue = minValue();
        Node* current = head;
        Node* nextElem;
        while(current)
        {
            nextElem = current->next;
            if(current->value == minimumValue)
                remove(current);
            current = nextElem;
        }
    }
    void add(int value)
    {
        Node* newNode = new Node(value);
        if(tail == nullptr)
        
            head = tail = newNode;
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
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

    list.add(25);
    list.add(34);
    list.add(16);
    list.add(7);
    list.add(87);
    list.add(7);
    
    list.print();
    list.deleteAllMinElement();
    list.print();
}
