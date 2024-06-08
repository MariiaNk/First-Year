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

/*Написати функцію, яка визначає кількість внутрішніх вершин бінарного дерева, 
що представлене у стандартній формі*/
int countInternalVertex(BinaryTreeNode *node)
{
    if (node == nullptr)
        return 0;

    int cnt = 0;
    if (node->right != nullptr || node->left != nullptr)
        cnt = 1;

    cnt += countInternalVertex(node->left);
    cnt += countInternalVertex(node->right);

    return cnt;
}

/*Написати функцію, яка обчислює кількість елементів більших за v у множині,
що представлена невпорядкованим бінарним деревом у "стандартній формі"*/
int countElementBigherThen(BinaryTreeNode *node, int item)
{
    if (node == nullptr)
        return 0;

    int cnt = 0;
    if (node->value > item)
        cnt = 1;

    cnt += countElementBigherThen(node->left, item);
    cnt += countElementBigherThen(node->right, item);

    return cnt;
}
/*Написати функцію для визначення кількості листів з відмітками, що належать інтервалу [u, v],
у невпорядкованого бінарного дерева, що зберігається у стандартній формі.*/
int countElementINRange(BinaryTreeNode *node, int start, int finish)
{
    if (node == nullptr)
        return 0;

    int cnt = 0;
    if (node->value >= start && node->value <= finish)
        cnt = 1;

    cnt += countElementINRange(node->left, start, finish);
    cnt += countElementINRange(node->right, start, finish);

    return cnt;
}

/*Написати функцію для знаходження у невпорядкованому бінарному дереві, 
що зберігається у ‘стандартній формі’ вершини зі значенням v та рівня, де розташована ця вершина*/
struct AnswerNode{
    BinaryTreeNode* node;
    int level;
    AnswerNode()
    {
        node = nullptr;
        level = -1;
    }
    AnswerNode(BinaryTreeNode* node, int level): node(node), level(level) {}
    bool empty()
    {
        return node == nullptr && level == -1;
    }
};

AnswerNode findElementInTree(BinaryTreeNode *node, int value, int level)
{
    if(node == nullptr) return AnswerNode(); 
    if(node->value == value) return AnswerNode(node, level);

    AnswerNode leftAnswer = findElementInTree(node->left, value, level + 1);
    AnswerNode rightAnswer = findElementInTree(node->right, value, level + 1);
    
    if(leftAnswer.empty()) return rightAnswer;
    return leftAnswer;

}

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

// виведення дерева в симетричному порядку
void symOrder(BinaryTreeNode *root)
{
    if (root)
    {
        symOrder(root->left);
        cout << root->value << ", ";
        symOrder(root->right);
    }
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
    srand(84);
    BinaryTreeNode *root = buildUnique(20);
    symOrder(root);
    cout << "ROOT: " << root->value << "\n";
    print2DUtil(root, 0);
    cout << "Bigger than 57: " << countElementBigherThen(root, 57) << endl;
    cout << "In range 15 and 57: " << countElementINRange(root, 15, 57) << endl;
    cout << "Count Internal vertex: " << countInternalVertex(root) << endl;

    AnswerNode ans = findElementInTree(root, 94, 1);
    cout << "Result: " << ans.node->value << " " << ans.level << endl;

    cout << "Levels: ";
    printLevelOrder(root);
    cout << endl;
}