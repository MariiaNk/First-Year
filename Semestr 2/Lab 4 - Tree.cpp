#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    int data;
    vector < TreeNode*> children;
    TreeNode(int value = 0) : data(value), children() {}
};

struct Tree
{
    TreeNode* root;
    Tree() 
    {
        root = nullptr;
    }
    Tree(int value) 
    {
        root = new TreeNode();
        root->data = value;
    }
    void addNode (int, int, int);
    
};

TreeNode* findMinChildren (TreeNode *parent)
{
    int etalon = parent -> children[0] -> children.size();
    TreeNode* targetNode = parent->children[0];
    for(int i = 1; i < parent->children.size(); i++)
    {
        if (parent->children[i]->children.size() < etalon)
        {
            etalon = parent->children[i]->children.size();
            targetNode = parent->children[i];
        }
    }
    return targetNode;
}

int subTreeSize(TreeNode* node) 
{
    if (node == nullptr)
        return 0;

    int size = 1;
    for (TreeNode* child : node->children) 
        size += subtreeSize(child);
    return size;
}

TreeNode* findMinChildrenSubTree(TreeNode* parent)
{
    int etalon = subTreeSize(parent -> children[0]);
    TreeNode* targetNode = parent->children[0];
    for(int i = 1; i < parent->children.size(); i++)
    {
        int currentSize = subTreeSize(parent -> children[i]);
        if (currentSize < etalon)
        {
            etalon = currentSize;
            targetNode = parent->children[i];
        }
    }
    return targetNode;
}
TreeNode* findTargetNode (TreeNode *current, int minCountChildren, int maxCountChildren)
{
    if(current->children.size() < minCountChildren)
        return current;
    else
    {
        TreeNode* currentChildren = findMinChildren(current);
        if(currentChildren->children.size() < maxCountChildren)
            return findTargetNode(currentChildren, minCountChildren, maxCountChildren);
        else
        {
            if(current->children.size() < maxCountChildren) 
                return current;
            else
                return findTargetNode(findMinChildrenSubTree(current), minCountChildren, maxCountChildren);
        }
    }

}

void Tree::addNode (int valueNode, int minCountChildren, int maxCountChildren)
{
    TreeNode* targetNode = findTargetNode(root, minCountChildren, maxCountChildren);
    TreeNode* newNode = new TreeNode(valueNode);
    targetNode->children.push_back(newNode);
}
void printTree(TreeNode* parent, int depth) 
{
    if (parent == nullptr) 
        return;

    for (int i = 0; i < depth; ++i)
        cout << "  "; 
    cout << parent->data << endl;

    for (auto child : parent->children)
        printTree(child, depth + 1);

}

int main()
{
    Tree myTree;
    myTree.addNode(10, 5, 10);
    myTree.addNode(16, 5, 10);
    myTree.addNode(24, 5, 10);
    myTree.addNode(13, 5, 10);
    myTree.addNode(513, 5, 10);
    myTree.addNode(26, 5, 10);
    myTree.addNode(4, 5, 10);
    myTree.addNode(3, 5, 10);
    printTree(myTree.root, 0);
}