#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct TreeNode
{
    int data;
    TreeNode* parent;
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
    void printSpaceMethod(TreeNode* , int);
    void deleteNode(int);
    
};

struct BinaryTreeNode
{
    int data;
    BinaryTreeNode* leftSon;
    BinaryTreeNode* rightSon;
    BinaryTreeNode(int data = 0): data(data), leftSon(nullptr), rightSon(nullptr) {};
};

struct BinaryTree
{
    BinaryTreeNode* root;
    BinaryTree(): root(nullptr){};
    BinaryTreeNode* addNode(int, BinaryTreeNode*);
    void print(BinaryTreeNode*);
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

    int sizeSubTree = 1;
    for (TreeNode* child : node->children) 
        sizeSubTree += subTreeSize(child);
    return sizeSubTree;
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
        if(currentChildren->children.size() <= maxCountChildren)
            return findTargetNode(currentChildren, minCountChildren, maxCountChildren);
        else
        {
            if(current->children.size() <= maxCountChildren) 
                return current;
            else
                return findTargetNode(findMinChildrenSubTree(current), minCountChildren, maxCountChildren);
        }
    }

}

void Tree::addNode (int valueNode, int minCountChildren, int maxCountChildren)
{
    if(root == nullptr) root = new TreeNode(valueNode);
    else
    {
        TreeNode* targetNode = findTargetNode(root, minCountChildren, maxCountChildren);
        TreeNode* newNode = new TreeNode(valueNode);
        newNode->parent = targetNode;
        targetNode->children.push_back(newNode);
    }   
}
void deleteSubTree(TreeNode* root)
{
    if (root == nullptr)
        return;
    for (TreeNode* child : root->children)
        deleteSubTree(child);
    delete root;
}
void Tree::deleteNode(int valueNode)
{
    queue <TreeNode*> nodes;
    nodes.push(root);
    while(!nodes.empty())
    {
        if(nodes.front()->data == valueNode)
        {
            TreeNode* currentNodeParent = nodes.front()->parent;
            for(int i = 0;i < currentNodeParent->children.size(); i++)
            {
                if(currentNodeParent->children[i] == nodes.front())
                {
                    currentNodeParent->children.erase(currentNodeParent->children.begin()+i);
                    break;
                }
            }
            deleteSubTree(nodes.front());
            
        }
        else
        {
            for(TreeNode* child: nodes.front()->children)
            {
                nodes.push(child);
            }
        }
        nodes.pop();
    }
}
void Tree::printSpaceMethod(TreeNode* parent, int depth = 0) 
{
    
    if (parent == nullptr) 
        return;

    for (int i = 0; i < depth; ++i)
        cout << "   "; 
    cout << setw(3) << parent->data << endl;

    for (auto child : parent->children)
        printSpaceMethod(child, depth + 1);

}
void BinaryTree::print(BinaryTreeNode* parent)
{
    if (parent) 
    {
        cout << parent->data << ", ";
        print(parent->leftSon);
        print(parent->rightSon);
    }
}

BinaryTreeNode* BinaryTree::addNode(int valueNode , BinaryTreeNode* parent)
{
    if (parent == nullptr) 
        return new BinaryTreeNode(valueNode);


    if (valueNode < parent->data) 
        parent->leftSon = addNode( valueNode, parent->leftSon);
    else 
        parent->rightSon = addNode(valueNode, parent->rightSon);
    
    return parent;
}



void DemonstrationMode()
{
    int num = rand() % 3;

    Tree myTree;
    switch (num)
    {
    case 1:
    {
        myTree.addNode(10, 5, 10);
        myTree.addNode(16, 5, 10);
        myTree.addNode(24, 5, 10);
        myTree.addNode(13, 5, 10);
        myTree.addNode(513, 5, 10);
        myTree.addNode(26, 5, 10);
        myTree.addNode(4, 5, 10);
        myTree.addNode(3, 5, 10);
        break;
    }
    case 2:
    {
        myTree.addNode(10, 2, 4);
        myTree.addNode(16, 2, 4);
        myTree.addNode(24, 2, 4);
        myTree.addNode(13, 2, 4);
        myTree.addNode(513, 2, 4);
        myTree.addNode(26, 2, 4);
        myTree.addNode(4, 2, 4);
        myTree.addNode(3, 2, 4);
        myTree.addNode(513, 1, 3);
        break;
    }   
    
    }

    cout << " ==== SPACE METHOD === " << endl;
    myTree.printSpaceMethod(myTree.root);

    myTree.deleteNode(513);

    cout << " ==== SPACE METHOD === " << endl;
    myTree.printSpaceMethod(myTree.root);

    BinaryTree myBinTree;
    myBinTree.addNode(6, myBinTree.root);
    myBinTree.addNode(15, myBinTree.root);
    myBinTree.addNode(3, myBinTree.root);
    myBinTree.addNode(513,  myBinTree.root);
    myBinTree.addNode(21,  myBinTree.root);
    myBinTree.addNode(658,  myBinTree.root);
    myBinTree.addNode(41,  myBinTree.root);

    cout << " ==== Sequential presentation === " << endl;
    myBinTree.print(myBinTree.root);



    
}

void BenchmarkMode()
{
    int n;
    cout << "Enter count of element (<100): ";
    cin >> n;
    int minCnt, maxCnt, data;
    Tree myTree;
    duration<double> durationProcess;
    for(int i = 0; i < n; i++)
    {
        minCnt = 1 + rand()%5;
        maxCnt = minCnt+rand()%5;
        data = rand()%1000;
        auto start = high_resolution_clock::now();
        myTree.addNode(data, minCnt, maxCnt);
        auto stop = high_resolution_clock::now();
        durationProcess += duration_cast<microseconds>(stop - start);
    }

    cout << "Time taken by ADD NODE:  " << durationProcess.count() << " microseconds" << endl;
    
    auto start = high_resolution_clock::now();
    myTree.deleteNode(rand()%1000);
    auto stop = high_resolution_clock::now();
    auto durationDelete = duration_cast<microseconds>(stop - start);
    cout << "Time taken by DELETE NODE: " << durationDelete.count() << " microseconds" << endl;
    

}


int main() 
{
    srand(0);
    cout << "Input mode of work\nd - demonstration\nb - benchmark\n";
    cout << "Enter request:";
    char mode;
    cin >> mode;
    if(mode == 'd')
        DemonstrationMode();
    else if(mode == 'b')
        BenchmarkMode();
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
    return 0;
}