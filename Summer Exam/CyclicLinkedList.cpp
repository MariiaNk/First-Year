#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node* next;
    Node* prev;
    Node(int value): value(value), next(nullptr), prev(nullptr) {}
};

Node* add(Node* head, int value) 
{
    Node* newNode = new Node(value);
    if (!head) 
    {
        // Робимо новий вузол циклічним
        newNode->next = newNode; 
        newNode->prev = newNode;
        return newNode;
    } 
    
    Node* current = head;
    while (current->next != head) 
        current = current->next;

        
    current->next = newNode;
    newNode->next = head;
    head->prev = newNode;
    newNode->prev = current;

    return head;
}

void print(Node* head) 
{
    if(head != nullptr)
    {
        Node* current = head;
        do
        {
            cout << current->prev->value << "-("<< current->value << ")-" << current->next->value << " ";
            current = current->next;
        }while (current != head);
        cout << endl;
    }
}

Node* copyAndReverse(Node* head)
{
    Node* current = head;
    do
    {
        swap(current->prev, current->next);
        current = current->prev;
    }while(current != head);
    return current->prev;
}

int main()
{
    Node* head = nullptr;
    head = add(head, 15);
    head = add(head, 24);
    head = add(head, 2);
    head = add(head, 28);
    print(head);

    Node* reverse = copyAndReverse(head);
    print(reverse);
}