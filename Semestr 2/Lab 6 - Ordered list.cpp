#include <iostream>
#include <cmath>
#include <vector>
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
#define BOLD "\e[1m"
#define CLOSEBOLD  "\e[0m"
using namespace std;

struct complex
{
    //z = a + b*i, a - real, b - imaginary
    int real;
    int imaginary;
    complex(int real = 0, int imaginary = 0): real(real), imaginary(imaginary) {}
    complex operator-(const complex &other) const
    {
        return complex(real - other.real, imaginary - other.imaginary);
    }
    complex operator+(const int &other) const
    {
        return complex(real + other, imaginary);  
    }
    complex operator*(const complex &other) const
    {
        return complex(real*other.real - imaginary*other.imaginary, real*other.imaginary + imaginary*other.real);
    }
    complex operator*(const int &other) const
    {
        return complex(real * other, imaginary * other); 
    }
    int modul() const
    {
        return sqrt(real*real + imaginary*imaginary); 
    }
    int funcCompare() const
    {
        complex result = ((*this) * (*this) - (*this) * 20) + 22;
        return result.modul();
    }
    bool compare(const complex& other) const
    {
        if(real == other.real)
            return imaginary > other.imaginary;
        return real > other.real;
    }
    bool operator > (const complex& other) const
    {
        int thisMod = this->funcCompare();
        int otherMod = other.funcCompare();
        if (thisMod != otherMod)
            return compare(other);
        return thisMod > otherMod;
    }
    bool operator < (const complex& other) const
    {
        int thisMod = this->funcCompare();
        int otherMod = other.funcCompare();
        if (thisMod != otherMod)
            return !(compare(other));
        return thisMod < otherMod;
    }
    bool operator == (const complex& other) const
    {
        return (real == other.real) && (imaginary == other.imaginary);
    }
    bool operator <= (const complex& other) const
    {
        return *this < other || *this == other;
    }
    bool operator >= (const complex& other) const
    {
        return *this > other || *this == other;
    }
    friend ostream& operator<<(ostream& os, const complex& c) 
    {
        if (c.imaginary >= 0)
            os << c.real << "+" << c.imaginary << "i";
        else
            os << c.real << c.imaginary << "i";
        return os;
    }
};

class orderedStore
{    
public:
    virtual void add(complex item) = 0;
    virtual bool search(complex item) = 0;
    virtual void del(complex item) = 0;
    virtual vector<complex> searchByRange(complex minValue, complex maxValue) = 0;
    virtual void print() = 0;

};

class orderedLinkedList: public orderedStore
{
private:
    struct Node
    {
        complex value;
        Node* next;
        Node(complex valueItem = 0)
        {
            value = valueItem;
            next = nullptr;
        }
    };
public:
    Node* head;
    orderedLinkedList()
    {
        head = nullptr;
    }
    void add(complex item) 
    {
        if (head == nullptr) 
        {
            Node *newNode = new Node(item);
            head = newNode;
        } 
        else 
        {
            Node* curr = head;
            Node* prev = nullptr;
            bool stop = false;
            while (curr != nullptr && !stop) 
            {
                if (curr->value > item)
                    stop = true;
                else 
                {
                    prev = curr;
                    curr = curr->next;
                }
            }
            Node *temp = new Node(item);
            if (prev == nullptr) 
            {
                temp->next = head;
                head = temp;
            } else 
            {
                temp->next = curr;
                prev->next = temp;
            } 
        }                      
    }
    bool search(complex item) 
    {
        Node *current = head;
        bool found = false;
        bool stop = false;
        while (current != nullptr && !found && !stop) 
        {
            if (current->value == item)
                found = true;
            else 
            {
                if (current->value > item)
                    stop = true;
                else
                    current = current->next;
            }
        }
        return found;
    }
    void del(complex item) 
    {
        Node *curr = head, *prev = nullptr;
        while (curr != nullptr && !(curr->value == item)) 
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return;

        if (prev == nullptr) 
            head = curr->next; 
        else
            prev->next = curr->next;
        delete curr;
    }
    vector<complex> searchByRange(complex minValue, complex maxValue) 
    {
        vector<complex> results;
        Node* curr = head;
        while (curr != nullptr && curr->value < minValue) 
            curr = curr->next; 
        while (curr != nullptr && curr->value <= maxValue) 
        {
            results.push_back(curr->value);
            curr = curr->next;
        }
        return results;
    }
    void print()
    {
        cout << UNDERLINE << "Linked list:" << CLOSEUNDERLINE << endl;
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->value << endl;
            current = current->next;
        }
    }
};
class orderedArray: public orderedStore
{
public:
    vector<complex> data;
    void add(complex item) 
    {
        int low = 0, high = data.size() - 1, mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (data[mid] < item)
                low = mid + 1;
            else
                high = mid - 1;
        }
        data.insert(data.begin() + low, item);
    }
    bool search(complex item) 
    {
        int low = 0, high = data.size() - 1, mid;
        while (low <= high) 
        {
            mid = (low + high) / 2;
            if (data[mid] == item)
                return true;
            else 
            {
                if (data[mid] < item) 
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return false;
    }
    void del(complex item) 
    {
        int low = 0, high = data.size() - 1, mid;
        while (low <= high) 
        {
            mid = (low + high) / 2;
            if (data[mid] == item)
            {
                data.erase(data.begin() + mid);
                return;
            }
            else 
            {
                if (data[mid] < item)
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            
        }
    }
    vector<complex> searchByRange(complex minValue, complex maxValue) 
    {
        vector<complex> results;
        for (const auto& item : data) 
        {
            if (item > maxValue) 
                break;
            if (item >= minValue) 
                results.push_back(item);
        }
        return results;
    }
    void print() 
    {
        cout << UNDERLINE << "Array list:" << CLOSEUNDERLINE << endl;
        
        for (auto& item : data)
            cout << item << endl;
    }
};
class binarySearchTree: public orderedStore
{
private:
    struct treeNode
    {
        complex value;
        treeNode* left;
        treeNode* right;
        treeNode(complex valueItem = 0)
        {
            value = valueItem;
            left = nullptr;
            right = nullptr;
        }
    };
    treeNode* insert(treeNode* node, complex key)
    {
        if (node == nullptr)
            return new treeNode(key);
        if (key < node->value)
            node->left = insert(node->left, key);
        else if (key > node->value)
            node->right = insert(node->right, key);
        return node;
    }
    treeNode* searchRecur(treeNode* node, complex key)
    {
        if (node == nullptr || node->value == key)
            return node;
        if (node->value < key)
            return searchRecur(node->right, key);
        return searchRecur(node->left, key);
    }
    void inorder(treeNode* node)
    {
        if (node != nullptr) 
        {
            inorder(node->left);
            cout << node->value << "; ";
            inorder(node->right);
        }
    }
    treeNode* deleteNode(treeNode* root, complex key)
    {
        if (root == nullptr)
            return root;
        if (key < root->value) 
        {
            root->left = deleteNode(root->left, key);
            return root;
        }
        else if (key > root->value) 
        {
            root->right = deleteNode(root->right, key);
            return root;
        }


        if (root->left == nullptr)
        {
            treeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) 
        {
            treeNode* temp = root->left;
            delete root;
            return temp;
        }

        treeNode* succParent = root;
        treeNode* succ = root->right;
        while (succ->left != nullptr) 
        {
            succParent = succ;
            succ = succ->left;
        }
        root->value = succ->value;

        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
        
        delete succ;
        return root;
    }
    void searchRangeRecur(treeNode* node, complex low, complex high, vector<complex>& results) 
    {
        if (!node) return;

        if (low < node->value)
            searchRangeRecur(node->left, low, high, results);

        if (low <= node->value && node->value <= high)
            results.push_back(node->value);

        if (node->value < high)
            searchRangeRecur(node->right, low, high, results);
    }
public:
    treeNode* root;
    binarySearchTree()
    {
        root = nullptr;
    }
    void add(complex item)
    {
        treeNode* newNode = insert(root, item);
        if(root == nullptr) root = newNode;
        
    }
    bool search(complex item) 
    {
        treeNode* searchResult = searchRecur(root, item);
        return searchResult != nullptr;
    }
    void print() //inorder
    {
        cout << UNDERLINE << "Binary seacrh tree - [inorder]" << CLOSEUNDERLINE << endl;
        inorder(root);
        cout << endl;
    }
    void del(complex item)
    {
        root = deleteNode(root, item);
    }
    vector<complex> searchByRange(complex minValue, complex maxValue) 
    {
        vector <complex> result;
        result.clear();
        searchRangeRecur(root, minValue, maxValue, result);
        return result;
    }

};
class AVLtree: public orderedStore
{
private:
    struct avlNode
    {
        complex value;
        avlNode* left;
        avlNode* right;
        int height;
        avlNode(complex valueItem = 0)
        {
            value = valueItem;
            left = nullptr;
            right = nullptr;
            height = 0;
        }
    };
    int height(avlNode *N)  
    {  
        if (N == NULL)  
            return 0;  
        return N->height;  
    }  
    avlNode *rightRotate(avlNode *y)  
    {  
        avlNode *x = y->left;  
        avlNode *T2 = x->right;  

        x->right = y;  
        y->left = T2;  
    
        y->height = max(height(y->left), height(y->right)) + 1;  
        x->height = max(height(x->left), height(x->right)) + 1;  
    
        return x;  
    }  
    avlNode *leftRotate(avlNode *x)  
    {  
        avlNode *y = x->right;  
        avlNode *T2 = y->left;  

        y->left = x;  
        x->right = T2;  
    
        x->height = max(height(x->left), height(x->right)) + 1;  
        y->height = max(height(y->left), height(y->right)) + 1;  

        return y;  
    }  
    int getBalance(avlNode *N)  
    {  
        if (N == NULL)  
            return 0;  
        return height(N->left) - height(N->right);  
    }  
    avlNode* insert(avlNode* node, complex key)  
    {  
        if (node == NULL)  
            return new avlNode(key);
    
        if (key < node->value)  
            node->left = insert(node->left, key);  
        else if (key > node->value)  
            node->right = insert(node->right, key);  
        else 
            return node;  
    
        node->height = 1 + max(height(node->left),  
                            height(node->right));  
    
        int balance = getBalance(node);  

        if (balance > 1 && key < node->left->value)  
            return rightRotate(node);  
    
        if (balance < -1 && key > node->right->value)  
            return leftRotate(node);  

        if (balance > 1 && key > node->left->value)  
        {  
            node->left = leftRotate(node->left);  
            return rightRotate(node);  
        }  
    
        if (balance < -1 && key < node->right->value)  
        {  
            node->right = rightRotate(node->right);  
            return leftRotate(node);  
        }  
    
        return node;  
    } 
    void inOrder(avlNode *root)  
    {  
        if(root != NULL)  
        {  
            inOrder(root->left);  
            cout << root->value << endl;     
            inOrder(root->right);  
        }  
    }  
    avlNode * minValueNode(avlNode* node) 
    { 
        avlNode* current = node; 
        while (current->left != NULL) 
            current = current->left; 
        return current; 
    } 
    avlNode* deleteNode(avlNode* node, complex key) 
    { 
        if (node == NULL) 
            return node; 

        if ( key < node->value ) 
            node->left = deleteNode(node->left, key); 
        else if( key > node->value ) 
            node->right = deleteNode(node->right, key); 
        else
        { 
            if( (node->left == NULL) || (node->right == NULL) ) 
            { 
                avlNode *temp = node->left ? node->left : node->right; 
                if (temp == NULL) 
                { 
                    temp = node; 
                    node = NULL; 
                } 
                else
                    *node = *temp; 
                free(temp); 
            } 
            else
            { 
                avlNode* temp = minValueNode(node->right); 
                node->value = temp->value; 
                node->right = deleteNode(node->right, temp->value); 
            } 
        } 
    
        if (node == NULL) 
            return node; 
        node->height = 1 + max(height(node->left), height(node->right)); 
    
        int balance = getBalance(node); 
    
     
        if (balance > 1 && getBalance(node->left) >= 0) 
            return rightRotate(node); 
    
        if (balance > 1 && getBalance(node->left) < 0) 
        { 
            node->left = leftRotate(node->left); 
            return rightRotate(node); 
        } 
    
        if (balance < -1 && getBalance(node->right) <= 0) 
            return leftRotate(node); 
    
        if (balance < -1 && getBalance(node->right) > 0) 
        { 
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        } 
    
        return node; 
    } 
    bool AVLsearch( avlNode* root, complex key)
    {
        if (root == NULL)
            return false;
        else if (root->value == key)
            return true;
        else if (root->value > key) 
        {
            bool val = AVLsearch(root->left, key);
            return val;
        }
        else 
        {
            bool val = AVLsearch(root->right, key);
            return val;
        }
    }
    void searchRangeRecur(avlNode* node, complex low, complex high, vector<complex>& results) 
    {
        if (!node) return;

        if (low < node->value)
            searchRangeRecur(node->left, low, high, results);

        if (low <= node->value && node->value <= high)
            results.push_back(node->value);

        if (node->value < high)
            searchRangeRecur(node->right, low, high, results);
    }
public:
    avlNode* root;
    void add(complex item) 
    {
        root = insert(root, item);
    } 
    void print() //inOrder
    {
        cout << UNDERLINE << "AVL tree - [inorder]" << CLOSEUNDERLINE << endl;
        inOrder(root);
    }
    void del(complex item)
    {
        root = deleteNode(root, item);
    }
    bool search(complex item)
    {
        return AVLsearch(root, item);
    }
    vector<complex> searchByRange(complex minValue, complex maxValue) 
    {
        vector<complex> result;
        searchRangeRecur(root, minValue, maxValue, result);
        return result;
    }
};
int main()
{
    orderedStore* array = nullptr;
    cout << "Save type:\n1 - Linked List\n2 - Ordered Array\n3 - Binary search tree\n4 - AVL tree\n";
    int type;
    cin >> type;
    switch (type)
    {
    case 1:
        array = new orderedLinkedList();
        break;
    case 2:
        array = new orderedArray();
        break;
    case 3:
        array = new binarySearchTree();
        break;
    case 4:
        array = new AVLtree();
        break;
    default:
        cout << "----- Error! Wrong request! ----";
        break;
    }
    array->add({15, 4});
    array->add({45, 1});
    array->add({34, 0});
    array->add(56);
    array->add(1);
    array->print();
    complex searchItem(15, 4);
    cout << "Is " << BOLD << searchItem << CLOSEBOLD << " in ordered list? - ";
    if(array->search(searchItem))
        cout << "Yes\n";
    else cout << "No\n";
    searchItem = {19, -8};
    cout << "Is " << BOLD << searchItem << CLOSEBOLD << " in ordered list? - ";
    if(array->search(searchItem))
        cout << "Yes\n";
    else cout << "No\n";
    array->del({34, 0});
    cout << "Delete 34+0i in store " << endl;
    array->print();
    complex minValue(13, 4), maxValue(56, 8);
    vector <complex> searchResult = array->searchByRange(minValue, maxValue);
    cout << "Result of searching in range: " << minValue << " to " << maxValue << endl; 
    for(int i = 0; i < searchResult.size(); i++)
    {
        cout << searchResult[i] << "; ";
    }
}