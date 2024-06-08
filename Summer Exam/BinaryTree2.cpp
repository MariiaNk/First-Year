#include <iostream>
#include <unordered_set>

using namespace std;

struct BinaryTreeNode
{
    int value;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode(int value) : value(value), left(nullptr), right(nullptr){};
};


BinaryTreeNode *build(int countVertex, std::unordered_set<int>& usedValues)
{
    BinaryTreeNode *p;
    int nodeValue, nleft, nright;
    if (!countVertex)
        return nullptr; // empty tree

    nleft = countVertex / 2;          // number of nodes in the left subtree
    nright = countVertex - nleft - 1; // number of nodes in the right subtree

    // Generate a unique node value
    do {
        nodeValue = rand() % 100; // generate a random value
    } while (usedValues.find(nodeValue) != usedValues.end()); // check if it's already used

    usedValues.insert(nodeValue); // mark the value as used

    p = new BinaryTreeNode(nodeValue); // create the root
    p->left = build(nleft, usedValues); // build the left subtree
    p->right = build(nright, usedValues); // build the right subtree

    return p;
}

BinaryTreeNode *buildUnique(int countVertex)
{
    std::unordered_set<int> usedValues;
    return build(countVertex, usedValues);
}

void print2DUtil(BinaryTreeNode *root, int space)
{
    if (root == NULL)
        return;
    space += 4;
    print2DUtil(root->right, space);
    for (int i = 4; i < space; i++)
        cout << " ";
    cout << root->value << "\n";
    print2DUtil(root->left, space);
}

/*Використовуючи відповідний механізм черг або стеків, написати функцію, 
яка виводить елементи бінарного дерева, поданого в стандартній формі, 
по рівнях (починаючи з кореня дерева, далі з синів кореня й далі)*/
struct Node{
    BinaryTreeNode* value;
    Node* next;
    Node (BinaryTreeNode* value) : value(value), next(nullptr) {}
};
void push(Node* &head, Node* &tail, BinaryTreeNode* value)
{
    if(head == nullptr)
    {
        head = tail = new Node(value);
    }
    else
    {
        Node* newNode = new Node(value);
        tail->next = newNode;
        tail = newNode;
    }
}

void pop(Node* &head, Node* &tail)
{
    if(head == nullptr) return;
    else if(head == tail) head = tail = nullptr;
    else
    {
        Node* current = head;
        head = head->next;
        delete current;
    }
}

void printLevelOrder(BinaryTreeNode* root)
{
    if(!root) return;

    Node* queHead = nullptr;
    Node* queTail = nullptr;
    push(queHead, queTail, root);

    while(queHead != nullptr && queTail != nullptr)
    {
        BinaryTreeNode* current = queHead->value;
        pop(queHead, queTail);
        cout << current->value << " ";

        if(current->left != nullptr) 
            push(queHead, queTail, current->left);

        if(current->right != nullptr) 
            push(queHead, queTail, current->right);
    }

    
}


int main()
{
    srand(time(0));
    BinaryTreeNode *root = buildUnique(8);
    cout << "ROOT: " << root->value << "\n";
    print2DUtil(root, 0);

    cout << "Levels: ";
    printLevelOrder(root);
    cout << endl;
}