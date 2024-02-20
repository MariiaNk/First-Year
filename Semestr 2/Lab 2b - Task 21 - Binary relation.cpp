/* 21(**) Реалізувати роботу з бінарними відношеннями, 
представленими у вигляді списку.*/
#include <iostream>

using namespace std;

struct tRelation
{
    int x;
    int y;
    friend bool operator!=(const tRelation& lp, const tRelation& rp) 
    {
        return lp.x != rp.x || lp.y != rp.y;
    }

    friend std::istream &operator>>(std::istream &is, tRelation &p)
    {
        return is >> p.x >> p.y;
    }

    friend std::ostream &operator<<(std::ostream &os, tRelation p)
    {
        return os << p.x << "->" << p.y << endl;
    }
};

struct tNode 
{
    tRelation data;
    tNode* prev;
    tNode (tRelation data, tNode * prev = nullptr) : data(data), prev(prev) {}
};


class BinaryRelationList
{
    private:
        tNode *top;
    public:
        void create_empty() 
        {
            top = nullptr;
        }
        void push(tRelation data) 
        {
            tNode *newNode = new tNode(data, top);
            top = newNode;
        }
        void pop() 
        {
            if (top != nullptr)
            {
                tNode *temp = top;
                top = top->prev;
                delete temp;
            }
        }
        tRelation peek() 
        {
            if (top != nullptr)
                return top->data;
            throw std::runtime_error("Stack is empty");
        }
        bool isEmpty() const 
        {
            return top == nullptr;
        }

        void writeList() 
        {
            cout << "Binary Relation:\n";
            tNode *current = top;
            while (current != nullptr)
            {
                cout << current->data;
                current = current->prev;
            }
            cout << endl;
        }

        bool isElementPresent(tRelation findElem)
        {
            tNode *current = top;
            while (current != nullptr && current->data != findElem)
                current = current->prev;
            return current != nullptr;
        }

        void removeElement(tRelation findElem)
    {
        tNode *current = top;
        while (current->prev != nullptr && current->prev->data != findElem) 
            current = current->prev;
        
        if (current->prev != nullptr) 
        {
            tNode *temp = current -> prev;
            current -> prev = current -> prev -> prev;
            delete temp;
        }
    }


        size_t sizeOfStruct() 
        {
            size_t totalSize = 0;
            tNode *current = top;
            while (current != nullptr)
            {
                totalSize += sizeof(tNode); 
                totalSize += sizeof(tRelation); 
                current = current->prev;
            }
            return totalSize;
        }
        ~BinaryRelationList()
        {
            while (!isEmpty()) {
                pop();
            }
        }
};

void outputMenu()
{
    cout << "==== Binary Relation List MENU ====\n";
    cout << "1 - Add new item to list\n";
    cout << "2 - Remove top item from list\n";
    cout << "3 - The value of the top item\n";
    cout << "4 - Check if relation is in the list[Yes\\No]\n";
    cout << "5 - Check if list is empty\n";
    cout << "6 - Output all binary relation list\n";
    cout << "7 - End program\n";
    cout << "Please, write the number of your request: ";

}
void InteractiveMode()
{
    BinaryRelationList BRList;
    BRList -> create_empty();
    int request;
    do {
        outputMenu();
        cin >> request;
        switch (request) {
            case 1:
                tRelation input;
                cout << "Enter x-element and y-element:";
                BRList->push(addElem());
                cout << " ==== Complete =====";
                break;
            case 2:
                BRList->pop();
                cout << " ==== Complete =====";
                break;
            case 3:
                cout << " The value of the top item: " << BRList.peek();
                break;
            case 4:
                
            case 5:
                if (BRList->isEmpty())
                    cout << "The stack is empty :(\n";
                else
                    cout << "The stack isn't empty!!!\n";
                break;
            case 6:
                BRList->writeStack();
                break;
            default:
                cout << "----- Error! Wrong request! Try again!!! -----";
        }
        cout << endl;
    } while (request != 7);

    delete BRList;
} 
void DemonstrationMode()
{
    BinaryRelationList br;
    br.create_empty();
    br.push({1, 2});
    br.push({3, 4});
    br.push({5, 6});

    
    br.writeList();

    cout << "Is (1, 2) present? " << (br.isElementPresent({1, 2}) ? "Yes" : "No") << endl;
    cout << "Is (2, 3) present? " << (br.isElementPresent({2, 3}) ? "Yes" : "No") << endl;
    br.pop();
    cout << "Top element in List: " << br.peek();

    br.push({10, 15});
    br.removeElement({1, 2});

    br.writeList();


}

int main()
{
    srand((unsigned)time(0)); 
    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\n";
    char mode;
    cin >> mode;
    /*if (mode == 'i')
        InteractiveMode();
    else*/ if(mode == 'd')
        DemonstrationMode();
    /*else if(mode == 'b')
        //return benchmarkMode();*/
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
}
