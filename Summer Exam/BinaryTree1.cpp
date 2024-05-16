/* 2020 рік Білет 6 
№3 Написати функцію, яка обчислює кількість елементів більших за v у множині, що представлена 
невпорядкованим бінарним деревом у "стандартній формі"*/
#include <iostream>

using namespace std;

struct BinaryTreeNode
{
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode(int value): value(value), left(nullptr), right(nullptr) {};
};

int countElementBigherThen(BinaryTreeNode* node, int item)
{
    if(node == nullptr) return 0;

    int cnt = 0;
    if(node->value > 0) cnt = 1;

    cnt += countElementBigherThen(node->left, item);
    cnt += countElementBigherThen(node->right, item);

    return  cnt ;
}

int main()
{
    BinaryTreeNode* root = nullptr;

}