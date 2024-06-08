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

BinaryTreeNode *build(int countVertex, std::unordered_set<int> &usedValues)
{
    BinaryTreeNode *p;
    int nodeValue, nleft, nright;
    if (!countVertex)
        return nullptr; // empty tree

    nleft = countVertex / 2;          // number of nodes in the left subtree
    nright = countVertex - nleft - 1; // number of nodes in the right subtree

    // Generate a unique node value
    do
    {
        nodeValue = rand() % 100; // generate a random value
    } while (usedValues.find(nodeValue) != usedValues.end()); // check if it's already used

    usedValues.insert(nodeValue); // mark the value as used

    p = new BinaryTreeNode(nodeValue);    // create the root
    p->left = build(nleft, usedValues);   // build the left subtree
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

struct Node
{
    BinaryTreeNode *value;
    Node *next;
    Node(BinaryTreeNode *value) : value(value), next(nullptr) {}
};
void push(Node *&head, BinaryTreeNode *value)
{
    if (head == nullptr)
    {
        head = new Node(value);
    }
    else
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
}

void pop(Node *&head)
{
    if (head == nullptr)
        return;
    else
    {
        Node *current = head;
        head = head->next;
        delete current;
    }
}

/*Написати не рекурсивну функцію (з використанням стека) для друкування відміток
вузлів бінарного дерева, поданого в стандартній формі, при його проходженні в оберненому порядку.*/
void printReverseOrder(BinaryTreeNode *root)
{
    if (!root)
        return;

    Node *stack = nullptr;
    BinaryTreeNode* lastNodeVisited = nullptr;
    BinaryTreeNode* current = root;

    while (stack != nullptr || current != nullptr) {
        if (current != nullptr) {
            push(stack, current);
            current = current->left;
        } 
        else
        {
            BinaryTreeNode* peekNode = stack->value;
            if (peekNode->right != nullptr && lastNodeVisited != peekNode->right)
                current = peekNode->right;
            else 
            {
                cout << peekNode->value << ", ";
                lastNodeVisited = peekNode;
                pop(stack);
            }
        }
    }
}
int main()
{
    srand(17);
    BinaryTreeNode *root = buildUnique(8);
    cout << "ROOT: " << root->value << "\n";
    print2DUtil(root, 0);

    cout << "Reverse order: ";
    printReverseOrder(root);
    cout << endl;
}