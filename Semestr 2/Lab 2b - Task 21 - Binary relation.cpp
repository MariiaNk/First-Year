/* 21(**) Реалізувати роботу з бінарними відношеннями, 
представленими у вигляді списку.*/
#include <iostream>

using namespace std;

struct tRelation
{
    int x;
    int y;
    tRelation(int x=0, int y=0) : x(x), y(y) {}
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
    public:
        tNode *top;
        void create_empty() 
        {
            top = nullptr;
        }
        void push(tRelation data) 
        {
            tNode *newNode = new tNode(data, top);
            if(!isElementPresent(data))
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
            throw runtime_error("List is empty");
        }
        bool isEmpty() const 
        {
            return top == nullptr;
        }
        void writeList() 
        {
            tNode *current = top;
            while (current != nullptr)
            {
                cout << current->data;
                current = current->prev;
            }
            cout << "================" << endl;
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
        tRelation composition(tRelation relA, tRelation relB)
        {
            if(isElementPresent(relA) && isElementPresent(relB))
            {
                tRelation result(relA.x, relB.y);
                return tRelation(relA.x, relB.y);
            }
            throw "Relation 1 or Relation 2 isn't presented!!!";
        }
        BinaryRelationList()
        {
            create_empty();
        }
        void clearList()
        {
            while (!isEmpty()) 
                pop();
        }
    
};

BinaryRelationList intersection(BinaryRelationList& ListA, BinaryRelationList& ListB)
{
    BinaryRelationList result;
    tNode* current = ListA.top;

    while (current != nullptr) 
    {
        if (ListB.isElementPresent(current->data)) 
            result.push(current->data);
        current = current->prev;
    }
    return result;
}

BinaryRelationList unionList( const BinaryRelationList& ListA, const BinaryRelationList& ListB)
{
    BinaryRelationList result;
    tNode* currentA = ListA.top;
    while (currentA != nullptr) 
    {
        result.push(currentA->data);
        currentA = currentA->prev;
    }

    tNode* currentB = ListB.top;
    while (currentB != nullptr) 
    {
        if (!result.isElementPresent(currentB->data))
            result.push(currentB->data);
        currentB = currentB->prev;
    }
    return result;
}





void outputMenu()
{
    cout << "==== Binary Relation List MENU ====\n";
    cout << "1 - Add new item to list\n";
    cout << "2 - Remove top item from list\n";
    cout << "3 - The value of the top item\n";
    cout << "4 - Check if relation is in the list[Yes\\No]\n";
    cout << "5 - Check if list is empty\n";
    cout << "6 - Output all binary relation list\n";
    cout << "7 - Switch to another list\n";
    cout << "8 - Output name of list with which we work\n";
    cout << "9 - Union lists\n";
    cout << "10 - Intersection lists\n";
    cout << "11 - End program\n";
    cout << "===============================================\n";
}


void InteractiveMode()
{
    BinaryRelationList BRListA, BRListB, resultOperation;
    BinaryRelationList * BRList = &BRListA;
    int request;
    tRelation input;
    outputMenu();
    do {
        cout << "Please, write the number of your request:  ";
        cin >> request;
        switch (request) {
            case 1:
                cout << "Enter x-element and y-element: ";
                cin >> input;
                BRList->push(input);
                cout << " ==== Complete =====";
                break;
            case 2:
                BRList->pop();
                cout << " ==== Complete =====";
                break;
            case 3:
                cout << " The value of the top item: " << BRList->peek();
                break;
            case 4:
                cout << "Enter x-element and y-element: ";
                cin >> input;
                if (BRList->isElementPresent(input))
                    cout << "The (" << input.x << ',' << input.y << ") is presented\n";
                else
                    cout << "The (" << input.x << ',' << input.y << ") isn't presented :(\n";
                break;
            case 5:
                if (BRList->isEmpty())
                    cout << "The list is empty :(\n";
                else
                    cout << "The list isn't empty!!!\n";
                break;
            case 6:
                if(BRList == &BRListA) cout << "== LIST A ==\n";
                else cout << "== LIST B ==\n";
                BRList->writeList();
                break;
            case 7:
                if(BRList == &BRListA) BRList = &BRListB;
                else BRList = &BRListA;
                break;
            case 8:
                if(BRList == &BRListA) cout << "We work with list A\n";
                else cout << "We work with list B\n";
                break;
            case 9:
                cout << "== UNION ==\n";
                resultOperation.clearList();
                resultOperation = unionList(BRListA, BRListB);
                resultOperation.writeList();
                break;
            case 10:
                cout << "== INTERSECTION ==\n";
                resultOperation.clearList();
                resultOperation = intersection(BRListA, BRListB);
                resultOperation.writeList();
                break;
            default:
                cout << "----- Error! Wrong request! Try again!!! -----";
        }
        cout << endl;
    } while (request != 11);

} 

void DemonstrationMode()
{
    BinaryRelationList brA;
    brA.create_empty();
    brA.push({1, 2});
    brA.push({3, 4});
    brA.push({5, 6});
    brA.writeList();
    cout << "Is (1, 2) present? " << (brA.isElementPresent({1, 2}) ? "Yes" : "No") << endl;
    cout << "Is (2, 3) present? " << (brA.isElementPresent({2, 3}) ? "Yes" : "No") << endl;
    brA.pop();
    cout << "Top element in List: " << brA.peek();
    brA.push({10, 15});
    brA.removeElement({1, 2});
    brA.writeList();
    cout << brA.composition({10, 15}, {3, 4});

    BinaryRelationList brB;
    brB.create_empty();
    brB.push({1, 8});
    brB.push({1, 2});
    brB.push({3, 8});
    brB.push({1, 10});
    brB.push({11, 8});
    brB.push({13, 22});
    brB.push({3, 4});
    brB.writeList();

    cout << "Union:\n";
    BinaryRelationList resultUn = unionList(brA, brB);
    resultUn.writeList();
    cout << "intersection:\n";
    BinaryRelationList resultIn = intersection(brA, brB);
    resultIn.writeList();
    
    
}

void BenchmarkMode()
{
    BinaryRelationList BRList;
    BRList.create_empty();
    cout << "Enter count of relation: ";
    int cnt;
    cin >> cnt;

    tRelation item;
    for(int i = 0; i < cnt; i++)
    {
        item.x = rand()%100;
        item.y = rand()%100;
    }
}
int main()
{
    srand((unsigned)time(0)); 
    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\n";
    char mode;
    cin >> mode;
    if (mode == 'i')
        InteractiveMode();
    else if(mode == 'd')
        DemonstrationMode();
    else if(mode == 'b')
        BenchmarkMode();
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
}

/*
i
1 5 6
1 8 9
1 1 2
1 10 15
7
1 3 5
1 7 6
1 8 9
1 3 7
1 1 2
6
7
6
9
10
*/