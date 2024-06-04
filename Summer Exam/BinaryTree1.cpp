/* 2020 рік Білет 6
№3 Написати функцію, яка обчислює кількість елементів більших за v у множині, що представлена
невпорядкованим бінарним деревом у "стандартній формі"*/
#include <iostream>

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

    cout << node->value << " : " << cnt << "\n";
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



BinaryTreeNode *build(int countVertex)
{
    BinaryTreeNode *p;
    int nodeValue, nleft, nright;
    if (!countVertex)
        return nullptr; // порожнє дерево

    nleft = countVertex / 2;          // кількість вузлів у лівому піддереві
    nright = countVertex - nleft - 1; // кількість вузлів у правому піддереві

    nodeValue = rand() % 100;

    p = new BinaryTreeNode(nodeValue); // створюємо корінь
    p->left = build(nleft);            // будуємо ліве
    p->right = build(nright);          // будуємо праве
    return p;
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
int main()
{
    srand(84);
    BinaryTreeNode *root = build(20);
    symOrder(root);
    cout << "ROOT: " << root->value << "\n";
    print2DUtil(root, 0);
    cout << "Bigger than 57: " << countElementBigherThen(root, 57) << endl;
    cout << "Count Internal vertex: " << countInternalVertex(root);
}