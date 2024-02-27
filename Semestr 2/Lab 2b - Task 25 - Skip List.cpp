/* 25(***) Реалізувати структуру даних «список з пропусками» (Skip List, див. https://en.wikipedia.org/wiki/Skip_list ). 
Операції 1) додати елемент до списку; 2) знайти елемент за значенням.*/

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct tNode
{
    int value;
    tNode **forward;
    tNode(int newValue, int level) 
    {       
        this->value = newValue; 
        forward = new tNode*[level+1]; 
        for(int i = 0; i < level + 1; ++i) 
        {
            forward[i] = nullptr;
        }
    }; 
};


class tSkipList
{
    private:
        tNode *top;
        int MAXLVL; //маскимальна кількість рівнів у цьому листі
        int level; //даний рівень в листі
        float P;
    public:
        tSkipList(int inMAXLVL, float inP) 
        {      
            MAXLVL = inMAXLVL; 
            P = inP; 
            level = 0; 
            top = new tNode(-1, MAXLVL); 
        } 

        tNode* createNode(int newValue, int level) 
        { 
            tNode *n = new tNode(newValue, level); 
            return n; 
        }
        
        int randomLevel() 
        { 
            float r = (float)rand()/RAND_MAX; 
            int lvl = 0; 
            while(r < P && lvl < MAXLVL) 
            {    
                lvl++; 
                r = (float)rand()/RAND_MAX;
            } 
            return lvl;
        }

        //1) додати елемент до списку;
        void insertElement(int newValue) 
        { 
            tNode *current = top; 
            tNode *update[MAXLVL+1]; 
            for (int i = 0; i < MAXLVL + 1; ++i) 
            {
                update[i] = nullptr;
            }
            for(int i = level; i >= 0; i--) 
            { 
                while(current->forward[i] != nullptr && current->forward[i]->value < newValue) 
                    current = current->forward[i]; 
                update[i] = current; 
            } 
            current = current->forward[0]; 
            if (current == nullptr || current->value != newValue) 
            {      
                int rlevel = randomLevel();
                if(rlevel > level) 
                { 
                    for(int i=level+1;i<rlevel+1;i++) 
                        update[i] = top; 
                    level = rlevel; 
                } 
                tNode* n = createNode(newValue, rlevel); 
                for(int i=0;i<=rlevel;i++) 
                {       
                    n->forward[i] = update[i]->forward[i]; 
                    update[i]->forward[i] = n; 
                } 
            } 
        }
        // 2) знайти елемент за значенням.
        bool searchElement(int itemValue) 
        { 
            tNode *current = top; 
            for(int i = level; i >= 0; i--) 
            { 
                while(current->forward[i] && current->forward[i]->value < itemValue) 
                    current = current->forward[i]; 
            } 
            current = current->forward[0];
            return (current && current->value == itemValue) ;
        }
        bool deleteElement(int key)  
        { 
            tNode *current = top; 
            tNode *update[MAXLVL+1]; 
            for (int i = 0; i < MAXLVL + 1; ++i) 
                update[i] = nullptr;
            for(int i = level; i >= 0; i--) 
            { 
                while(current->forward[i] != nullptr &&current->forward[i]->value < key) 
                    current = current->forward[i]; 
                update[i] = current; 
            } 
            current = current->forward[0];
            if(current != nullptr and current->value == key) 
            { 
                for(int i=0;i<=level;i++) 
                {    
                    if(update[i]->forward[i] != current) 
                        break; 
                    update[i]->forward[i] = current->forward[i]; 
                } 
                while(level>0 && top->forward[level] == nullptr) 
                    level--; 
                delete current;
                return true;
            } 
            return false;
        }


        void displayList() 
        {         
            cout<<"\n===== Skip List =====\n"; 
            for(int i=0;i<=level;i++) 
            {
                tNode *node = top->forward[i]; 
                cout<<"Level "<<i<<": "; 
                while(node != nullptr) 
                {
                    cout<<node->value<<" "; 
                    node = node->forward[i]; 
                } 
                cout<<endl; 
            } 
        } 
        size_t sizeOfList() 
        {
            size_t totalSize = sizeof(*this); 
            totalSize += sizeof(top);
            totalSize += sizeof(MAXLVL);
            totalSize += sizeof(level);
            totalSize += sizeof(P);
            tNode *current = top->forward[0];
            while (current != nullptr) 
            {
                totalSize += sizeof(*current);
                totalSize += sizeof(tNode*) * (MAXLVL + 1);
                current = current->forward[0];
            }
            return totalSize;
        }
};
void outputMenu()
{
    cout << "==== Skip List MENU ====\n";
    cout << "1 - Add new item to skip list\n";
    cout << "2 - Search item by value\n";
    cout << "3 - Search item by value\n";
    cout << "4 - Output all skip list\n";
    cout << "5 - End program\n";

}
void InteractiveMode()
{
    tSkipList lst(10, 0.5); 
    int request;
    outputMenu();
    do
    {
        cout << "Please, write the number of your request: ";
        cin >> request;
        int itemValue;
        switch (request)
        {
            case 1:
                cout << "Enter value of new element: ";
                cin >> itemValue;
                lst.insertElement(itemValue);
                cout<<"Successfully Inserted item "<< itemValue <<endl; 
                break;
            case 2:
                cout << "Enter value of searching element: ";
                cin >> itemValue;
                if(lst.searchElement(itemValue))
                    cout<<"Found item: "<< itemValue <<endl; 
                else cout << "Item " << itemValue <<  " isn't found" << endl;
                break;
            case 3:
                cout << "Enter value of element you want delete: ";
                cin >> itemValue; 
                if(lst.deleteElement(itemValue))
                    cout<<"Successfully deleted item "<<itemValue<<endl; 
                else cout << "Item " << itemValue << " isn't deleted :(" << endl;
                break;
            case 4:
                lst.displayList();
                break;
            default:
                cout << "----- Error! Wrong request! Try again!!! -----" << endl;
                break;
        }
    } while (request != 5);
    
} 
void DemonstrationMode()
{
    tSkipList lst(3, 0.5); 
    lst.insertElement(3); 
    lst.insertElement(6); 
    lst.insertElement(7); 
    lst.insertElement(9); 
    lst.insertElement(12); 
    lst.insertElement(19); 
    lst.insertElement(17); 
    lst.insertElement(26); 
    lst.insertElement(21); 
    lst.insertElement(25); 
    lst.displayList(); 

    lst.insertElement(28); 
    lst.displayList(); 
    //Search for node 19 
    lst.searchElement(19); 
    lst.deleteElement(19);
    lst.displayList(); 
}
void BenchmarkMode()
{
    tSkipList SkList(10, 0.5); 
    cout << "Enter count of elements: ";
    int cnt;
    cin >> cnt;
    
    auto totalStart = high_resolution_clock::now();

    auto start = high_resolution_clock::now();
    for(int i = 0; i < cnt; i++)
    {
        SkList.insertElement(rand()%100);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by GENERATE AND PUSH*" << cnt <<":  " << duration.count() << " milliseconds" << endl;
    
    start = high_resolution_clock::now();
    bool ans = SkList.searchElement(rand()%100);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by SEARCH" <<":  " << duration.count() << " milliseconds" << endl;
    
    start = high_resolution_clock::now();
    ans = SkList.deleteElement(rand()%100);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by DELETE" << cnt <<":  " << duration.count() << " milliseconds" << endl;

    auto totalStop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(totalStop - totalStart);
    cout << "Time taken by TOTAL: " << duration.count() << " milliseconds" << endl << endl;

    cout << "MEMORY USED BY LIST: " << SkList.sizeOfList() << " bytes" << endl << endl;
}


int main()
{
    srand((unsigned)time(0)); 
    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\n";
    cout << "Please, write the character of your request: ";
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

