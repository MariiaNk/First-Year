#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cassert>
#include <random>

#include "windows.h"
#include "psapi.h"

#include "benchmark.h"

#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
#define BOLD "\e[1m"
#define CLOSEBOLD  "\e[0m"

using namespace std;
using namespace std::chrono;

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


class B23Tree: public orderedStore
{
private:
    struct TreeNode 
    {
        complex data[2];
        int size; // number of data items
        TreeNode* children[3];
        TreeNode* parent; 

        TreeNode(complex data1, TreeNode* parent = nullptr) 
        {
            this->data[0] = data1;
            this->size = 1;
            children[0] = children[1] = children[2] = nullptr;
            this->parent = parent;
        }

        TreeNode(complex data1, complex data2, TreeNode* parent = nullptr) 
        {
            assert(data1<=data2);
            this->data[0] = data1;
            this->data[1] = data2;
            this->size = 2;
            children[0] = children[1] = children[2] = nullptr;
            this->parent = parent;
        }

        TreeNode(complex data1, complex data2, complex data3, TreeNode* parent = nullptr) 
        {
            assert(data1<=data2);
            assert(data2<=data3);

            this->data[0] = data2;
            this->size = 1;
            this->children[0] = new TreeNode(data1, this);
            this->children[1] = new TreeNode(data3, this);
            this->children[2] = nullptr;

            this->parent = parent;

        }

        void add_single_data(complex data) 
        {
            assert(size == 1);
            if (data > this->data[0]) {
                this->data[1] = data;
                size = 2;
            } else {
                this->data[1] = this->data[0];
                this->data[0] = data;
                size = 2;
            }
        }

	//return nullptr if added, else "4-node" (2-node with both children as 2-nodes)
        TreeNode* add_and_split(complex new_data) 
        {
            if (children[0] == nullptr) 
            {
                if (size == 1) 
                {
                    add_single_data(new_data);
                    return nullptr;
                } 
                else 
                {
                    if (new_data < data[0]) 
                        return new TreeNode(new_data, data[0], data[1]);
                    else if (new_data < data[1]) 
                        return new TreeNode(data[0], new_data, data[1]);
                    else 
                        return new TreeNode(data[0], data[1], new_data);
                }
            }
            TreeNode* extra = nullptr;
            if (size == 1) {
                if (new_data < data[0]) {
                    extra = children[0]->add_and_split(new_data);
                    if (!extra) { return nullptr;}
                    data[1] = data[0];
                    data[0] = extra->data[0];
                    children[2] = children[1];
                    children[0] = extra->children[0];
                    children[1] = extra->children[1];
                    size = 2;
                    return nullptr;
                } else {
                    extra = children[1]->add_and_split(new_data);
                    if (!extra) { return nullptr;}
                    data[1] = extra->data[0];
                    children[1] = extra->children[0];
                    children[2] = extra->children[1];
                    size = 2;
                    return nullptr;
                }
            } else {
                if (new_data < data[0]) {
                    extra = children[0]->add_and_split(new_data);
                    if (!extra) { return nullptr;}
                    TreeNode* result = new TreeNode(extra->data[0], data[0], data[1]);
                    result->children[0]->children[0] = extra->children[0];
                    result->children[0]->children[1] = extra->children[1];
                    result->children[1]->children[0] = children[1];
                    result->children[1]->children[1] = children[2];
                    return result;
                } else if (new_data < data[1]) {
                    extra = children[1]->add_and_split(new_data);
                    if (!extra) { return nullptr;}
                    TreeNode* result = new TreeNode(data[0], extra->data[0], data[1]);
                    result->children[0]->children[0] = children[0];
                    result->children[0]->children[1] = extra->children[0];
                    result->children[1]->children[0] = extra->children[1];
                    result->children[1]->children[1] = children[2];
                    return result;
                } else {
                    extra = children[2]->add_and_split(new_data);
                    if (!extra) { return nullptr;}
                    TreeNode* result = new TreeNode(data[0], data[1], extra->data[0]);
                    result->children[0]->children[0] = children[0];
                    result->children[0]->children[1] = children[1];
                    result->children[1]->children[0] = extra->children[0];
                    result->children[1]->children[1] = extra->children[1];
                    return result;
                }
            }
        }


        TreeNode* find_max_subtree() {
            if (children[2]) {
                assert(size == 2);
                return children[2]->find_max_subtree();
            }
            if (children[1]) {
                assert(size == 1);
                return children[1]->find_max_subtree();
            }
            assert(children[0] == nullptr);
            return this; // no children
        }

        complex get_max_data() 
        {
            if (size == 2) {
                return data[1];
            } else {
                return data[0];
            }
        }
	    enum RemoveResult {Removed, NotFound, NeedParentRemove};

        //void rebalance(TreeNode* current_child, TreeNode* left_child, TreeNode* right_child) {
        // returns true if rebalance complete - no need to rebalance parent
        bool rebalance(int index_current_child) {
            assert(index_current_child < size + 1);
            TreeNode* current_child = children[index_current_child];
            assert(current_child);
            assert(current_child->size == 0);
            TreeNode* left_child = nullptr;
            if (index_current_child > 0) { left_child = children[index_current_child-1]; }
            TreeNode *right_child = (index_current_child < size) ?
                                        children[index_current_child + 1] :
                                        nullptr;
            assert(left_child != nullptr || right_child != nullptr);

            if (left_child && left_child->size == 2) {
            assert(index_current_child - 1 >= 0); // can access data in next lines
                current_child->data[0] = this->data[index_current_child - 1];
                this->data[index_current_child - 1] = left_child->data[1];

                current_child->children[1] = current_child->children[0];
                current_child->children[0] = left_child->children[2];
                left_child->children[2] = nullptr;

                current_child->size = 1;
                left_child->size = 1;
                return true;
            }

            if (right_child && right_child->size == 2) {
            assert(index_current_child < this->size);
                current_child->data[0] = this->data[index_current_child]; // not index + 1
                this->data[index_current_child] = right_child->data[0];
                right_child->data[0] = right_child->data[1];

                current_child->children[1] = right_child->children[0];
                right_child->children[0] = right_child->children[1];
                right_child->children[1] = right_child->children[2];
                right_child->children[2] = nullptr;

                current_child->size = 1;
                right_child->size = 1;
                return true;
            }

            if (left_child) {
                assert(left_child->size == 1);
                assert(index_current_child - 1 >=0);

                left_child->data[1] = this->data[index_current_child - 1];

                left_child->children[2] = current_child->children[0];

                left_child->size = 2;
                this->size--;

                if (this->size == 0) {
                assert(this->children[0] == left_child);
                assert(this->children[1] == current_child);
                assert(this->children[2] == nullptr);
                delete current_child;
                this->children[1] = nullptr; // maybe not needed - this will be fixed in parent rebalance?
                return false;
                }
                assert(this->size == 1);
                if (index_current_child == 1) {
                    this->data[0] = this->data[1];
                    assert(this->children[0] == left_child);
                    assert(this->children[1] == current_child);
                    delete current_child;
                    this->children[1] = this->children[2];
                    this->children[2] = nullptr;
                    return true;
                }
                assert(index_current_child == 2); { // to make this case similar to previous (same indent level)
            assert(this->children[1] == left_child);
            assert(this->children[2] == current_child);
            delete current_child;
            this->children[2] = nullptr;
            return true;
                }


            }
            assert(right_child!=nullptr);
            assert(right_child->size == 1);

            right_child->data[1] = right_child->data[0];
            right_child->data[0] = this->data[index_current_child]; // not index + 1!!
            assert(right_child->data[0] < right_child->data[1]);

            if (current_child->children[0] != nullptr) {
            assert(right_child->children[0] != nullptr);
            assert(right_child->children[1] != nullptr);
            // previous tree was balanced, if current_child had children - then right_child must have children too
            right_child->children[2] = right_child->children[1];
            right_child->children[1] = right_child->children[0];
            right_child->children[0] = current_child->children[0];

            } else {
            assert(current_child->children[0] == nullptr);
        assert(right_child->children[0] == nullptr);
        assert(right_child->children[1] == nullptr);
        // in this case, no need to copy nullptrs - previous code would work, but it is extra work
            }
            right_child->size = 2;
            this->size--;

            if (this->size == 0) {
        assert(this->children[0] == current_child);
        assert(this->children[1] == right_child);
        assert(this->children[2] == nullptr);
        delete current_child;
        this->children[0] = this->children[1];
        this->children[1] = nullptr; // maybe not needed - this will be fixed in parent rebalance?
        return false;
        }
            assert(this->size == 1);
            if (index_current_child == 0) {
        assert(this->children[0] == current_child);
        assert(this->children[1] == right_child);
                this->data[0] = this->data[1];
                delete current_child;
                this->children[0] = this->children[1];
                this->children[1] = this->children[2];
                this->children[2] = nullptr;
                return true;
            }
            assert(index_current_child == 1); {
        assert(this->children[1] == current_child);
        assert(this->children[2] == right_child);
        delete current_child;
        this->children[1] = this->children[2];
        this->children[2] = nullptr;
        return true;
            }

        }

        // can set size to 0, this means parent needs to fix it
        RemoveResult remove(complex data_to_remove)
        {
            RemoveResult result;
            if (children[0] == nullptr) {
                if (size == 1) {
                    if (data[0] == data_to_remove) {
                        size = 0;
                        return NeedParentRemove;
                    } else {
                        return NotFound;
                    }
                } else { // size == 2
                    if (data[0] == data_to_remove) {
                        data[0] = data[1];
                        size = 1;
                        return Removed;
                    } else if (data[1] == data_to_remove) {
                        size = 1;
                        return Removed;
                    } else {
                        return NotFound;
                    }
                }
            }
            if (size == 1) {
                if (data_to_remove < data[0]) {
                    RemoveResult result = children[0]->remove(data_to_remove);
                    if (result == NeedParentRemove) {
                        rebalance(0);
                        if (this->size == 0) {return NeedParentRemove;}
                        else { return Removed;}
                    } else {
                        return result;
                    }
                } else if (data_to_remove > data[0]) {
                    RemoveResult result = children[1]->remove(data_to_remove);
                    if (result == NeedParentRemove) {
                        rebalance(1);
                        if (this->size == 0) {return NeedParentRemove;}
                        else { return Removed;}
                    } else {
                        return result;
                    }
                } else { // removing our only data
                    TreeNode* prev = children[0]->find_max_subtree();
                    assert(prev->children[0] == nullptr);
                    complex prev_data = prev->get_max_data();
                    data[0] = prev_data;
                    //prev->remove(prev_data, parent???)
                    result = this->children[0]->remove(prev_data); // because we know prev, but don't know full sequence of parents
                    assert(result != NotFound);
                    if (result == Removed) { return Removed;}
                    rebalance(0);
                    if (this->size == 0) {return NeedParentRemove;}
                    else { return Removed;}
                }
            }
            if (size == 2) {
                if (data_to_remove < data[0]) {
                    RemoveResult result = children[0]->remove(data_to_remove);
                    if (result == NeedParentRemove) {
                        rebalance(0);
                        assert(this->size > 0);
                        return Removed;
                    } else {
                        return result;
                    }
                } else if (data_to_remove == data[0]) {
                    TreeNode* prev = children[0]->find_max_subtree();
                    assert(prev->children[0] == nullptr);
                    complex prev_data = prev->get_max_data();
                    data[0] = prev_data;
                    result = this->children[0]->remove(prev_data); // because we know prev, but don't know full sequence of parents
                    assert(result != NotFound);
                    if (result == Removed) { return Removed;}
                    rebalance(0);
                    assert(this->size > 0);
                    return Removed;
                }
                else if (data_to_remove < data[1]) {
                    RemoveResult result = children[1]->remove(data_to_remove);
                    if (result == NeedParentRemove) {
                        rebalance(1);
                        assert(this->size > 0);
                        return Removed;
                    } else {
                        return result;
                    }
                } else if (data_to_remove == data[1]) {
                    TreeNode* prev = children[1]->find_max_subtree();
                    assert(prev->children[0] == nullptr);
                    complex prev_data = prev->get_max_data();
                    data[1] = prev_data;
                    result = this->children[1]->remove(prev_data); // because we know prev, but don't know full sequence of parents
                    assert(result != NotFound);
                    if (result == Removed) { return Removed;}
                    rebalance(1);
                    assert(this->size > 0);
                    return Removed;
                } else { // data_to_remove > data[1]
                    RemoveResult result = children[2]->remove(data_to_remove);
                    if (result == NeedParentRemove) {
                        rebalance(2);
                        assert(this->size > 0);
                        return Removed;
                    } else {
                        return result;
                    }
                }
            }
            return result;
        }

        void print_in_order() 
        {
            if (children[0]) 
            {
                children[0]->print_in_order();
            }
            cout<<data[0]<<endl;
            if (children[1]) 
            {
                children[1]->print_in_order();
            }
            if (size == 2) {
                cout<<data[1]<<endl;
                if (children[2]) {
                    children[2]->print_in_order();
                }
            }
        }
        bool search(complex target)  const
        {
            if (target == data[0] || (size == 2 && target == data[1])) {
                return true;
            }
            if (children[0] == nullptr) {
                return false;  // Leaf node, and target not found
            }
            if (target < data[0]) {
                return children[0]->search(target);
            } else if (size == 1 || target < data[1]) {
                return children[1]->search(target);
            } else {
                return children[2]->search(target);
            }
        }
    };
    void searchRangeRecursive(TreeNode* node, const complex& minValue, const complex& maxValue, vector<complex>& result) const 
    {
        if (!node) {
        return;
    }

    // Traverse left child
    if (node->children[0] && node->data[0] >= minValue) {
        searchRangeRecursive(node->children[0], minValue, maxValue, result);
    }

    // Add node data within range
    for (int i = 0; i < node->size; ++i) {
        if (minValue <= node->data[i] && node->data[i] <= maxValue) {
            result.push_back(node->data[i]);
        }
    }

    // Traverse middle child
    if (node->children[1] && node->size == 2 && node->data[1] >= minValue) {
        searchRangeRecursive(node->children[1], minValue, maxValue, result);
    }

    // Traverse right child
    if (node->children[2] && node->size == 2 && node->data[1] <= maxValue) {
        searchRangeRecursive(node->children[2], minValue, maxValue, result);
    }
    }
public:
	TreeNode* root;
	B23Tree() 
    {
		root = nullptr;
	}
	void add(complex data) 
    {
		if (!root)
			root = new TreeNode(data);
		else 
        {
			TreeNode* extra = root->add_and_split(data);
			if (extra) {
				root = extra;
			}
		}

	}
	void del(complex data) 
    {
		TreeNode::RemoveResult result = root->remove(data);
		if (result == TreeNode::NotFound) {return;}
		if (result == TreeNode::Removed) {return;}
		if (result == TreeNode::NeedParentRemove) {
			root = root->children[0];
		}
	}
	void print() 
    {
         cout << UNDERLINE << "2,3 Tree - [inorder]" << CLOSEUNDERLINE << endl;
		if(root) 
            root->print_in_order();
		else 
            cout<<"empty tree";
	}
    bool search(complex item)  
    {
        if (!root) 
            return false; 
        
        return root->search(item);
    }
    vector<complex> searchByRange(complex minValue, complex maxValue)
    {
        vector<complex> result;
        if (!root) 
            return result; 
        searchRangeRecursive(root, minValue, maxValue, result);
        return result;
    }
};

void DemonstrationMode()
{
    orderedStore* array = nullptr;
    cout << "Save type:\n1 - Linked List\n2 - Ordered Array\n3 - Binary search tree\n4 - AVL tree\n5 - 2,3 Tree\n";
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
    case 5:
        array = new B23Tree();
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

void outputMenu()
{
    cout << "==== Ordered Store Menu ====\n";
    cout << "1 - Add value to store\n";
    cout << "2 - Delete value from store\n";
    cout << "3 - Search value in store\n";
    cout << "4 - Search value in range in store\n";
    cout << "5 - Print store\n";
    cout << "0 - End program\n";
    cout << "===============================================\n";
}

void InteractiveMode()
{
    orderedStore* array = nullptr;
    cout << "Save type:\n1 - Linked List\n2 - Ordered Array\n3 - Binary search tree\n4 - AVL tree\n5 - 2,3 Tree\n";
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
    case 5:
        array = new B23Tree();
        break;
    default:
        cout << "----- Error! Wrong request! ----";
        break;
    }
    outputMenu();
    complex value;
    int request;
    do {
        cout << "Please, write the number of your request:  ";
        cin >> request;
        switch (request)
        {
            case 1:
            {
                cout << "Enter value [real imaginary]: ";
                cin >> value.real >> value.imaginary;
                array->add(value);
                cout << " ==== Complete =====";
                break;
            }
            case 2:
            {
                cout << "Enter value [real imaginary]: ";
                cin >> value.real >> value.imaginary;
                array->del(value);
                cout << " ==== Complete =====";
                break;
            }
            case 3:
            {
                cout << "Enter value [real imaginary]: ";
                cin >> value.real >> value.imaginary;
                if(array->search(value))
                    cout << "Yes\n";
                else cout << "No\n";
                break;
            }
            case 4:
            {
                complex minValue, maxValue;
                cout << "Enter min value [real imaginary]: ";
                cin >> minValue.real >> minValue.imaginary;
                cout << "Enter max value [real imaginary]: ";
                cin >> maxValue.real >> maxValue.imaginary;
                vector <complex> searchResult = array->searchByRange(minValue, maxValue);
                cout << "Result of searching in range: " << minValue << " to " << maxValue << endl; 
                for(int i = 0; i < searchResult.size(); i++)
                {
                    cout << searchResult[i] << "; ";
                }
                break;
            }
            case 5:
                array->print();
                break;
            default:
                cout << "----- Error! Wrong request! Try again!!! -----";
                break;
        }
        cout << endl;
    } while (request !=0);
}
size_t get_current_virtual_memory() 
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    return virtualMemUsedByMe;
}

size_t get_current_physical_memory() 
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
    return physMemUsedByMe;
}

void BenchmarkMode()
{
    int cntElem;
    
    cout << "Enter count of elements: ";
    cin >> cntElem;
    auto start = high_resolution_clock::now();
    BenchmarkMax* bmArray = new BenchmarkMax("Create Array");
    orderedStore* array = nullptr;
    delete bmArray;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by create array:  " << duration.count() << " microseconds" << endl;

    cout << "Save type:\n1 - Linked List\n2 - Ordered Array\n3 - Binary search tree\n4 - AVL tree\n5 - 2,3 Tree\n";
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
    case 5:
        array = new B23Tree();
        break;
    default:
        cout << "----- Error! Wrong request! ----";
        break;
    }

    complex Item;
    start = high_resolution_clock::now();
    bmArray = new BenchmarkMax("Add element");
    for(int i = 0; i < cntElem; i++)
    {
        Item = {rand()%100, rand()%100};
        array->add(Item);
    }
    delete bmArray;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by add item * " << cntElem << ": " << duration.count() << " microseconds" << endl;

    Item = {rand()%100, rand()%100};
    start = high_resolution_clock::now();
    bmArray = new BenchmarkMax("Delete element");
    array->print();
    delete bmArray;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by print:  " << duration.count() << " microseconds" << endl;

    Item = {rand()%100, rand()%100};
    start = high_resolution_clock::now();
    bmArray = new BenchmarkMax("Delete element");
    array->del(Item);
    delete bmArray;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by delete item:  " << duration.count() << " microseconds" << endl;

    Item = {rand()%100, rand()%100};
    start = high_resolution_clock::now();
    bmArray = new BenchmarkMax("Add element");
    array->search(Item);
    delete bmArray;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by search item:  " << duration.count() << " microseconds" << endl;

    Item = {rand()%100, rand()%100};
    complex endItem =  {rand()%100, rand()%100};
    start = high_resolution_clock::now();
    bmArray = new BenchmarkMax("Add element");
    array->searchByRange(Item, endItem);
    delete bmArray;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by search in range item:  " << duration.count() << " microseconds" << endl;

}
int main()
{
    srand((unsigned)time(0));
    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\n";
    char mode;
    cin >> mode;
    if (mode == 'i')
        InteractiveMode();
    else
    if(mode == 'd')
        DemonstrationMode();
    else if(mode == 'b')
        BenchmarkMode();
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
}