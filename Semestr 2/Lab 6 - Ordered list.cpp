#include <iostream>
#include <cmath>
#include <vector>

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
    friend ostream& operator<<(ostream& os, const complex& c) 
    {
        if (c.imaginary >= 0)
            os << c.real << "+" << c.imaginary << "i";
        else
            os << c.real << c.imaginary << "i";
        return os;
    }
};



class orderedLinkedList
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
        while (curr != nullptr && (curr->value < maxValue || curr->value == maxValue)) 
        {
            results.push_back(curr->value);
            curr = curr->next;
        }
        return results;
    }
    void print()
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->value << endl;
            current = current->next;
        }
    }
};
class orderedArray
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
            if (item > minValue || item == minValue) 
                results.push_back(item);
        }
        return results;
    }
    void print() 
    {
        for (auto& item : data)
            cout << item << " ";
        cout << endl;
    }
};
class binarySearchTree
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
        inorder(root);
    }
    void del(complex item)
    {
        root = deleteNode(root, item);
    }
    

};
int main()
{
    binarySearchTree myList;
    myList.add({15, 4});
    myList.add({45, 1});
    myList.add({34, 0});
    myList.add(56);
    myList.add(1);
    myList.print();
    if(myList.search({15, 4}))
        cout << "Yes\n";
    else cout << "No\n";
    if(myList.search(19))
        cout << "Yes\n";
    else cout << "No\n";
    myList.del({56, 0});
    // vector <complex> searchResult = myList.searchByRange({13, 4}, {56, 8});
    // for(int i = 0; i < searchResult.size(); i++)
    // {
    //     cout << searchResult[i] << "; ";
    // }
}