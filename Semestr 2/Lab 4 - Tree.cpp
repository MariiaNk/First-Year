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
    void printBranchMethod();
    void printSpaceMethod(TreeNode* , int);
    void deleteNode(int);
    
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
int countLeaves(TreeNode* node)
{
    if (node == nullptr)
        return 0;
    if (node->children.empty())
        return 1;
    int leaves = 0;
    for (auto child : node->children)
        leaves += countLeaves(child);
    return leaves;
}

string printLine(int n, string elem, string out = "")
{
    if (n <= 0) return out;
    for(int i = 0; i < n; i++)
        out+= elem;
    return out;
}
void printLayer (vector <TreeNode*> levelNodes, int cntLeaves, int &minSpace)
{
    int spaceByNode = int(((cntLeaves*2 - 1)*5) / levelNodes.size());
    if(spaceByNode > minSpace)  spaceByNode = minSpace;
    else minSpace = spaceByNode;
    spaceByNode -= (levelNodes.size() - 1)*5;
    string spaceStr = "     ", nodeStr = "  |  ",  brunches;
    for(int i = 0; i < levelNodes.size(); i++)
    {
        TreeNode* node = levelNodes[i];
        int cntChildren = node->children.size();
        if(cntChildren <= 1) 
        {
            cout << "(" << setw(3) << node->data << ")";
            if(cntChildren == 1) brunches +=  nodeStr;
            else brunches += spaceStr;
        }
        else
        {
            int side1, side2;
            if(cntChildren%2 == 1) side1 = side2 =  round(cntChildren/2);
            else 
            {
                side2 = cntChildren/2;
                side1 = side2 - 1;
            }
            if(i < levelNodes.size()/2) swap(side1, side2);
            int space = (spaceByNode - 10*(side1 + side2) - 5 )/2;
            if (space < 0) space = 0; 

            //cout << spaceByNode << " " << space << endl;
            //cout << cntChildren << " = 1 + " <<  side1 << " + " << side2 << " [" << space << "]"<< endl;
            cout << printLine(space, " ");
            cout << printLine(side1, " _________");
            cout << "(" << setw(3) << node->data << ")";
            cout << printLine(side2, "_________ ");
            cout << printLine(space, " ");

            brunches = printLine(space, " ", brunches);
            brunches = printLine(side1, nodeStr + spaceStr, brunches);
            brunches += nodeStr;
            brunches = printLine(side2, spaceStr + nodeStr, brunches);
            brunches = printLine(space, " ", brunches);
        }
        cout << spaceStr;
        brunches += spaceStr;
    }
    cout << endl << brunches << endl;
}
void Tree::printBranchMethod() 
{
    
    if (root == nullptr) 
        return;

    int cntLeaves = countLeaves(root);
    queue <TreeNode*> nodes;
    vector <TreeNode*> levelNodes;
    TreeNode* newLevelElem = root;
    nodes.push(root);
    levelNodes.push_back(root);
    int minSpace = (cntLeaves*2 - 1) * 5;
    while(!nodes.empty())
    {
        TreeNode* top = nodes.front();
        nodes.pop();
        if(top == newLevelElem)
        {
            if(levelNodes.size() != 0)
                printLayer(levelNodes, cntLeaves, minSpace);
            //cout << "End Level" << levelNodes.size() << "\n";
            levelNodes.clear();
            if(top->children.size() != 0)
                newLevelElem = top->children[0];
            else 
                newLevelElem = nullptr;
        }

        for(int i = 0; i < top->children.size(); i++)
        {
            nodes.push(top->children[i]);
            levelNodes.push_back(top->children[i]);
        }
    }
    

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

    cout << " ==== BRANCH METHOD === " << endl;
    myTree.printBranchMethod();

    myTree.deleteNode(513);

    cout << " ==== SPACE METHOD === " << endl;
    myTree.printSpaceMethod(myTree.root);

    cout << " ==== BRANCH METHOD === " << endl;
    myTree.printBranchMethod();
    
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
    cout << " ==== SPACE METHOD === " << endl;
    myTree.printSpaceMethod(myTree.root);
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