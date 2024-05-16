/* 2020 рік Білет 6 
№1 Написати функцію, яка у списку, що зберігається у зв'язному представленні, з кожної групи сусідніх однакових елементів залишає лише один*/
#include <iostream>

using namespace std;


struct LinkedList
{
private:
    struct Node
    {
        int value;
        Node* next;
        Node(int value): value(value), next(nullptr) {}
    };
public:
    Node* head;
    LinkedList(): head(nullptr) {}
    

    void deleteDuplicates()
    {
        Node* current = head;
        while(current->next)
        {
            if(current->value == current->next->value)
            {
                Node* duplicate = current->next;
                current->next = duplicate->next;
                delete duplicate;
            }
            else
                current = current->next;
        }
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
    LinkedList list;
    list.add(2);
    list.add(1);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(8);
    list.add(3);
    list.add(4);
    list.add(4);
    list.add(5);

    list.print();
    list.deleteDuplicates();
    list.print();
}