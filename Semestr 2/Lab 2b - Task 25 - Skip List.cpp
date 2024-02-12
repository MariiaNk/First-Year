/* 25*** Реалізувати структуру даних «список з пропусками» (Skip List, див. https://en.wikipedia.org/wiki/Skip_list ). 
Операції 1) додати елемент до списку; 2) знайти елемент за значенням.*/

#include <iostream>

using namespace std;

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
                while(current->forward[i] != NULL && current->forward[i]->value < newValue) 
                    current = current->forward[i]; 
                update[i] = current; 
            } 
            current = current->forward[0]; 
            if (current == NULL || current->value != newValue) 
            {      // Generate a random level for node 
                    int rlevel = randomLevel();
                    if(rlevel > level) 
                    { 
                        for(int i=level+1;i<rlevel+1;i++) 
                            update[i] = top; 
                        // Update the list current level 
                        level = rlevel; 
                    } 
                // create new node with random level generated 
                tNode* n = createNode(newValue, rlevel); 
                // insert node by rearranging pointers 
                for(int i=0;i<=rlevel;i++) 
                {       
                    n->forward[i] = update[i]->forward[i]; 
                    update[i]->forward[i] = n; 
                } 
                cout<<"Successfully Inserted item "<<newValue<<endl; 
            } 
        }
        // 2) знайти елемент за значенням.
        void searchElement(int itemValue) 
        { 
            tNode *current = top; 
            for(int i = level; i >= 0; i--) 
            { 
                while(current->forward[i] && current->forward[i]->value < itemValue) 
                    current = current->forward[i]; 
            } 
            current = current->forward[0];
            if(current && current->value == itemValue) 
                cout<<"Found item: "<< itemValue <<endl; 
            else cout << "Item " << itemValue <<  " isn't found" << endl;
        }

        void displayList() 
        {         
            cout<<"\n=====Skip List=====\n"; 
            for(int i=0;i<=level;i++) 
            {
                tNode *node = top->forward[i]; 
                cout<<"Level "<<i<<": "; 
                while(node != NULL) 
                {
                    cout<<node->value<<" "; 
                    node = node->forward[i]; 
                } 
                cout<<endl; 
            } 
        } 
};
void outputMenu()
{
    cout << "==== Skip List MENU ====\n";
    cout << "1 - Add new item to skip list\n";
    cout << "2 - Search item by value\n";
    cout << "3 - Output all skip list\n";
    cout << "4 - End program\n";
    cout << "Please, write the number of your request: ";

}
void InteractiveMode()
{
    outputMenu();
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
    //Search for node 19 
    lst.searchElement(19); 
    lst.displayList(); 

    /*tSkipList l(3, 0.5);
    l.insertElement(10);
    l.insertElement(40);
    l.insertElement(20);
    l.insertElement(19);
    l.insertElement(21);
    l.insertElement(78);
    l.insertElement(47);
    l.insertElement(26);
    l.insertElement(89);
    l.insertElement(26);
    l.displayList();*/
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
    /*else if(mode == 'b')
        //return benchmarkMode();*/
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
}

