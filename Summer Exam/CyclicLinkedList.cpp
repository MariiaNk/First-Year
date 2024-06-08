#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node* next;
    Node* prev;
    Node(int value = 0): value(value), next(nullptr), prev(nullptr) {}
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
/*В елементах циклічного списку розміщені цілі числа. Написати функцію копіювання списку, помінявши порядок на обернений*/
Node* copyAndReverse(Node* head) 
{
    if (!head) return nullptr;

    Node* current = head;
    Node* newHead = nullptr;

    do 
    {
        Node* newNode = new Node(current->value);

        if (!newHead) 
        {
            newNode->next = newNode;
            newNode->prev = newNode;
            newHead = newNode;
        } 
        else 
        {
            newNode->next = newHead;
            newNode->prev = newHead->prev;
            newHead->prev->next = newNode;
            newHead->prev = newNode;
            newHead = newNode;
        }

        current = current->next;
    } 
    while (current != head);

    return newHead;
}


void remove(Node* &head, Node* item)
{
    if(item == head && item->next == head) 
        head = nullptr;
    else 
    {
        item->prev->next = item->next;
        item->next->prev = item->prev;

        if(item == head) head = head->next;
    }
    delete item;
}

Node* addNewHead(Node* head, int value) 
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

    return newNode;
}

/*В елементах зв’язного циклічного списку розміщенні цілі числа. 
Написати функцію, що впорядковує список, збираючи спочатку всі непарні числа, а потім - парні*/
void  reorder(Node*& head)
{
    if (!head || head->next == head) return;

    Node* current = head;
    Node* next; //щоб зберігти куди переходити, після переміщення елементу
    bool end = false;
    do
    {
        next = current->next;
        if(current->value % 2 == 1 && current != head)
        {
            int value = current->value;
            if(next == head)  end = true;
            remove(head, current);
            head = addNewHead(head, value);
        } 
        current = next;

    } while(current != head && !end);
}
int main()
{
    Node* head = nullptr;
    head = add(head, 17);
    head = add(head, 57);
    head = add(head, 42);
    head = add(head, 23);
    head = add(head, 83);
    print(head);

    Node* reverse = copyAndReverse(head);
    print(reverse);

    reorder(head);
    print(head);
}