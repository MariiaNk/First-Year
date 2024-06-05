#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node* next;
    Node(int value): value(value), next(nullptr) {}
};

Node* add(Node* head, int value) 
{
    Node* newNode = new Node(value);
    if (!head) 
    {
        newNode->next = newNode; // Робимо новий вузол циклічним
        return newNode;
    } 
    
    Node* current = head;
    while (current->next != head) 
        current = current->next;

        
    current->next = newNode;
    newNode->next = head;

    return head;
}

void print(Node* head) 
{
    if(head != nullptr)
    {
        Node* current = head;
        do
        {
            cout << current->value << " ";
            current = current->next;
        }while (current != head);
        cout << endl;
    }
}

int main()
{
    Node* head = nullptr;
    head = add(head, 15);
    head = add(head, 24);
    head = add(head, 2);
    head = add(head, 28);
    print(head);
}