#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Tree
{
    private:
        struct TreeNode
        {
            int data;
            TreeNode* parent;
            vector < TreeNode*> children;
            TreeNode(int value = 0) : data(value), children() {}
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
        void deleteSubTree(TreeNode* root)
        {
            if (root == nullptr)
                return;
            for (TreeNode* child : root->children)
                deleteSubTree(child);
            delete root;
        }
        void outputSpaceMethod(TreeNode* parent, int depth ) 
        {
            if (parent == nullptr) 
                return;
            for (int i = 0; i < depth; ++i)
                cout << "   "; 
            cout << setw(3) << parent->data << endl;
            for (auto child : parent->children)
                outputSpaceMethod(child, depth + 1);
        }
    public:
        TreeNode* root;
        Tree(): root(nullptr) {}
        Tree(int value) 
        {
            root = new TreeNode();
            root->data = value;
        }
        void addNode (int valueNode, int minCountChildren, int maxCountChildren)
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
        void printSpaceMethod() 
        {
            outputSpaceMethod(root, 0);
        }
        void deleteNode(int valueNode)
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
    
};
class BinaryTree
{
    private:
        struct BinaryTreeNode
        {
            int data;
            BinaryTreeNode* leftSon;
            BinaryTreeNode* rightSon;
            BinaryTreeNode(int data = 0): data(data), leftSon(nullptr), rightSon(nullptr) {};
        };
        BinaryTreeNode* insertBinaryNode(int valueNode , BinaryTreeNode* &parent)
        {
            if (parent == nullptr) 
            {
                return new BinaryTreeNode(valueNode);
                //parent = new BinaryTreeNode(valueNode);
                //cout << "First node added: " << parent->data << endl;
            }
            else
            {
                if (valueNode < parent->data) 
                    parent->leftSon = insertBinaryNode( valueNode, parent->leftSon);
                else 
                    parent->rightSon = insertBinaryNode(valueNode, parent->rightSon);
            }   
            return parent; 
        }
        void outputDirectOrder(BinaryTreeNode* parent)
        {
            if (parent) 
            {
                cout << parent->data << ", ";
                outputDirectOrder(parent->leftSon);
                outputDirectOrder(parent->rightSon);
            }
        }
        void outputSpaceMethod(BinaryTreeNode* parent, int depth) 
        {
            if (parent == nullptr) 
                return;

            for (int i = 0; i < depth; ++i)
                cout << "   "; 
            cout << setw(3) << parent->data << endl;

            if(parent->leftSon != nullptr)
                outputSpaceMethod(parent->leftSon , depth + 1);
            
            if(parent->rightSon != nullptr)
                outputSpaceMethod(parent->rightSon , depth + 1);
        }
    public:
        BinaryTreeNode* root;
        BinaryTree(): root(nullptr){};
        void addNode(int valueNode)
        {
            root = insertBinaryNode(valueNode, root);
        }
        void printDirectOrder()
        {
            outputDirectOrder(root);
        }
        void printSpaceMethod()
        {
            outputSpaceMethod(root, 0);
        }
};
class BooleanTree
{
    private:
        struct BinaryBooleanTreeNode
        {
            char data;
            BinaryBooleanTreeNode* leftSon;
            BinaryBooleanTreeNode* rightSon;
            BinaryBooleanTreeNode(char data = ' '): data(data), leftSon(nullptr), rightSon(nullptr) {};
        };
        bool isOperator(char c) 
        {
            return (c == '&' || c == '|' || c == '!' || c == '^' || c == '-' || c == '=');
        }
        string convertToPolish (string str)
        {
            map <char, int> priority;
            priority['!'] = 5;
            priority['&'] = 4;
            priority['|'] = 3;
            priority['-'] = 2;
            priority['='] = 1;

            string input;
            stack <char> signs;
            input.clear();
            char ch;

            for(int i = 0; i < str.size(); i++)
            {
                ch = str[i];
                if((ch == '0' || ch == '1') || isalpha(ch))
                {
                    input += ch;
                }
                else if(ch == '(')
                {
                    signs.push(ch);
                }
                else if(ch == ')')
                {
                    while(signs.top() != '(' )
                    {
                        input += signs.top();
                        signs.pop();
                        if(signs.empty()) return "error";
                    }
                    signs.pop();

                }
                else if(isOperator(ch))
                {
                    while(!signs.empty()&& signs.top() != '(' && priority[ch] >= priority[signs.top()])
                    {
                        input += signs.top();
                        signs.pop();
                    }
                    signs.push(ch);
                }
                else if(ch != ' ') return "error";
            }

            while(!signs.empty())
            {
                input += signs.top();
                signs.pop();
            }
            return input;
        }
        BinaryBooleanTreeNode* buildExpressionTreeHelper(string expression) 
        {
            stack <BinaryBooleanTreeNode*> nodes;
            expression = convertToPolish(expression);
            for(int i = 0; i < expression.size(); i++)
            {
                BinaryBooleanTreeNode* newNode = new BinaryBooleanTreeNode(expression[i]);
                if(isOperator(expression[i]))   
                {
                    if(!nodes.empty())
                    {
                        newNode->rightSon = nodes.top();
                        nodes.pop();
                    }

                    if(!nodes.empty())
                    {
                        newNode->leftSon = nodes.top();
                        nodes.pop();
                    }
                    nodes.push(newNode);
                }                 
                else
                    nodes.push(newNode);
                
            }
            return nodes.top();
        }
        void outputDirectOrder(BinaryBooleanTreeNode* parent)
        {
            if (parent) 
            {
                cout << parent->data << "";
                outputDirectOrder(parent->leftSon);
                outputDirectOrder(parent->rightSon);
            }
        }
        void outputSpaceMethod(BinaryBooleanTreeNode* parent, int depth) 
        {
            if (parent == nullptr) 
                return;

            for (int i = 0; i < depth; ++i)
                cout << "   "; 
            cout << setw(3) << parent->data << endl;

            if(parent->leftSon != nullptr)
                outputSpaceMethod(parent->leftSon , depth + 1);
            
            if(parent->rightSon != nullptr)
                outputSpaceMethod(parent->rightSon , depth + 1);
        }

        bool calculateBoolean(BinaryBooleanTreeNode* node, bool leftValue, bool rightValue)
        {
            switch (node->data) 
            {
                case '!':
                    return !rightValue;
                case '&':
                    return leftValue && rightValue;
                case '|':
                    return leftValue || rightValue;
                case '^':
                    return leftValue != rightValue;
                case '-':
                    return !leftValue || rightValue;
                case '=':
                    return leftValue == rightValue;
            }
            return false;
        }
        bool calculatePostorder(BinaryBooleanTreeNode* node, map <char, int> &input)
        {
            if(node == nullptr)
                return false;
            if(!isOperator(node->data))
            {
                if(node->data == '0' || node->data == '1')
                    return node->data - '0';
                else
                {
                    if(input.find(node->data) == input.end())
                    {
                        bool newValue;
                        cout << "Enter \"" << node->data << "\" value: ";
                        cin >> newValue;
                        input[node->data] = newValue;
                    }
                    return input[node->data];
                }
            }

            char left = calculatePostorder(node->leftSon, input);
            bool leftValue = left - '0';
            char right = calculatePostorder(node->rightSon, input);
            bool rightValue = right - '0';
            
            return calculateBoolean(node, leftValue, rightValue);
        }
        void simplifyBooleanTree(BinaryBooleanTreeNode* &node)
        {
            if(node == nullptr)
                return;

            if(isOperator(node->data) )
            {
                if(node->data == '!' && (node->leftSon->data == '1' || node->leftSon->data == '0' || node->leftSon == nullptr) && (node->rightSon->data == '1' || node->rightSon->data == '0' || node->rightSon == nullptr)) 
                {
                    bool binaryData;
                    if(node->leftSon != nullptr)
                        binaryData = node->leftSon - '0';
                    else
                        binaryData = node->rightSon - '0';
                    binaryData += 1;
                    
                    delete node->rightSon;
                    delete node->leftSon;
                    delete node;
                    node = new BinaryBooleanTreeNode(binaryData + '0');
                }
                else if((node->leftSon != nullptr && node->rightSon != nullptr) && !isOperator(node->leftSon->data) && !isOperator(node->rightSon->data))
                {
                    if(node->leftSon->data == node->rightSon->data)
                    {
                        switch (node->data)
                        {
                            case '&': case '|':
                            {
                                BinaryBooleanTreeNode* newData = new BinaryBooleanTreeNode(node->rightSon->data);
                                delete node->rightSon;
                                delete node->leftSon;
                                node = newData;
                                break;
                            }
                            case '^':
                            {
                                delete node->rightSon;
                                delete node->leftSon;
                                delete node;
                                node = new BinaryBooleanTreeNode('0'); 
                                break;
                            }
                            case '-': case '=':
                            {
                                delete node->rightSon;
                                delete node->leftSon;
                                delete node;
                                node = new BinaryBooleanTreeNode('1'); 
                                break;
                            }                   
                        }
                    }
                    else if ((node->leftSon->data == '1' || node->leftSon->data == '0') && (node->rightSon->data == '1' || node->rightSon->data == '0'))
                    {
                        bool leftValue = node->leftSon - '0';
                        bool rightValue = node->rightSon - '0';
                        bool binaryData = calculateBoolean(node, leftValue, rightValue);
                        
                        delete node->rightSon;
                        delete node->leftSon;
                        delete node;
                        node = new BinaryBooleanTreeNode(binaryData + '0');
                    }                    
                }
            }
            simplifyBooleanTree(node->leftSon);
            simplifyBooleanTree(node->rightSon);
        }
        void findAllVariables (BinaryBooleanTreeNode* node, string &variables)
        {
            if(node == nullptr)
                return;
            if(!isOperator(node->data))
            {
                if(!(node->data == '0' || node->data == '1'))
                {
                    if(variables.find(node->data) ==  string::npos)
                        variables += node->data;
                }
            }

            findAllVariables(node->leftSon, variables);
            findAllVariables(node->rightSon, variables);
        }
    public:
        BinaryBooleanTreeNode* root;
        BooleanTree(string& expression)
        {
            root = buildExpressionTreeHelper(expression);
        }
        BooleanTree()
        {
            root = nullptr;
        }
        void BuildTree(string& expression)
        {
            root = buildExpressionTreeHelper(expression);
        }
        void printDirectOrder(string& expression)
        {
            outputDirectOrder(root);
        }
        void printSpaceMethod()
        {
            outputSpaceMethod(root, 0);
        } 
        void calculate()
        {
            map <char, int> input;
            bool answer = calculatePostorder(root, input) ;
            cout << "Result:" << answer << endl;
        }
        void simplify()
        {
            simplifyBooleanTree(root);
        }
        int checkStateResult()
        {
            map <char, int> input;
            string variables;
            variables.clear();
            int answer[2] = {0,0};
            findAllVariables(root, variables);
            int pow2 = 1;
            for(int i = 0; i <variables.size(); i++)
            {
                cout << "SET # " << i << endl;
                for(auto symb: variables)
                {
                    input[symb] = ((i - i % pow2)/pow2)%2;
                    cout << symb << " = " << input[symb] << endl;
                }
                int res = calculatePostorder(root, input);
                cout << "f = " << res << endl;
                answer[res]++;
                pow2 *= 2;
            }

            if (answer[0] == variables.size()) return 0;
            if (answer[1] == variables.size()) return 1;
            return -1;
        }
};

void DemonstrationMode()
{
    cout << "******************** TREE ********************" << endl;
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
    myTree.printSpaceMethod();

    myTree.deleteNode(513);

    cout << " ==== SPACE METHOD === " << endl;
    myTree.printSpaceMethod();

    cout << "**************** BINARY TREE *****************" << endl;
    BinaryTree myBinTree;
    myBinTree.addNode(6);
    myBinTree.addNode(15);
    myBinTree.addNode(3);
    myBinTree.addNode(513);
    myBinTree.addNode(21);
    myBinTree.addNode(658);
    myBinTree.addNode(41);

    cout << " ==== Sequential presentation Binary Tree === " << endl;
    myBinTree.printDirectOrder();
    cout << "\n ==== SPACE METHOD  Binary Tree === " << endl;
    myBinTree.printSpaceMethod();


    cout << "**************** BOOLEAN TREE *****************" << endl;
    string expression;
    num = 2; //rand() % 5;
    switch (num)
    {
        case 1:
        {
            expression = "( ! (1 | 0)) - (1 - a)"; // output 1
            break;
        }
        case 2:
        {
            expression = "(A & !A) | (B & !B)"; //always state
            break;
        }  
        case 3:
        {
            expression = "(a | b) & (a & a)"; // simplify: (a | b) & a
            break;
        }
        case 4:
        {
            expression = "(a - a) & (b = b)"; // simplify: 1 & 1
            break;
        }
    
    }

    BooleanTree boolTree(expression);
    boolTree.printDirectOrder(expression);
    cout << "\n ==== SPACE METHOD === " << endl;
    boolTree.printSpaceMethod();
    cout << "\nCalculate 0/1 Tree: \n";
    boolTree.calculate();
    cout << "\nSimplify: \n";
    boolTree.simplify();
    boolTree.printSpaceMethod();    
    cout << "\nCheck:\n";
    int res = boolTree.checkStateResult();
    if(res == 0) cout << "Contradiction"<< endl;
    else if(res == 1) cout << "Tautology" << endl;
    else cout << "No rule" << endl;
}
void outputMenu()
{
    cout << "==== Tree Menu ====\n";
    cout << "1 - Add node to tree\n";
    cout << "2 - Delete node from tree\n";
    cout << "3 - Output tree\n";
    cout << "==== Binary Tree Menu ====\n";
    cout << "4 - Add node to binary tree\n";
    cout << "5 - Output binary tree\n";
    cout << "6 - Output directed order for binary tree\n";
    cout << "==== Tree For Boolaen Expression Menu ====\n";
    cout << "7 - Convert expression to tree\n";
    cout << "8 - Calculate expression tree\n";
    cout << "9 - Simplify expression tree\n";
    cout << "10 - Check if expression is state\n";
    cout << "11 - Output tree for boolaen expression\n";
    cout << "0 - End program\n";
    cout << "===============================================\n";
}


void InteractiveMode()
{
    Tree myTree;
    BinaryTree myBinTree;
    BooleanTree myBoolTree;
    int request;
    int input;
    outputMenu();
    do {
        cout << "Please, write the number of your request:  ";
        cin >> request;
        switch (request) 
        {
            case 1:
                cout << "Enter node value: ";
                cin >> input;
                int minPow, maxPow;
                cout << "Enter minimum exponent: ";
                cin >> minPow;
                cout << "Enter maximum exponent: ";
                cin >> maxPow;
                myTree.addNode(input, minPow, maxPow);
                cout << " ==== Complete =====";
                break;
            case 2:
                cout << "Enter deleting node value: ";
                cin >> input;
                myTree.deleteNode(input);
                cout << " ==== Complete =====";
                break;
            case 3:
                myTree.printSpaceMethod();
                break;
            case 4:
                cout << "Enter node value: ";
                cin >> input;
                myBinTree.addNode(input);
                cout << " ==== Complete =====";
                break;
            case 5:
                myBinTree.printSpaceMethod();
                break;
            case 6:
                myBinTree.printDirectOrder();
                break;
            case 7:
            {
                cout << "Enter boolean expression: ";
                string expression;
                //(a|b)&(a&a)
                cin >> expression;
                myBoolTree.BuildTree(expression);
                cout << " ==== Complete =====";
                break;
            }
            case 8:
                myBoolTree.calculate();
                break;
            case 9:
                myBoolTree.simplify();
                cout << " ==== Complete =====";
                break;
            case 10:
            {
                int res = myBoolTree.checkStateResult();
                if(res == 0) cout << "Contradiction"<< endl;
                else if(res == 1) cout << "Tautology" << endl;
                else cout << "No rule" << endl;
                break;
            }
            case 11:
                myBoolTree.printSpaceMethod();
                break;
            default:
                cout << "----- Error! Wrong request! Try again!!! -----";
                break;
        }
        cout << endl;
    } while (request !=0);

} 

int main() 
{
    srand(0);
    cout << "Input mode of work\nd - demonstration\ni - interactive\n";
    cout << "Enter request:";
    char mode;
    cin >> mode;
    if(mode == 'd')
        DemonstrationMode();
    else if(mode == 'i')
        InteractiveMode();
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
    return 0;
}