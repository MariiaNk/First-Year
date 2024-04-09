#include <iostream>
#include <vector>
#define NMAX 1000
using namespace std;



class Graph
{
    private:
    public:
        GraphVector myGraph;
        

class GraphVector: public Graph
{
private:
    int n;
    vector< vector<bool>> adjacencyMatrix;
public:
    GraphMatrix()
    {
        n = 0;
        for(int i = 0; i < NMAX; i++)
            for(int j = 0; j < NMAX; j++)
                adjacencyMatrix[i][j] = false;
    }
};

class GraphVector: public Graph
{
private:
    int n;
    bool adjacencyMatrix[NMAX][NMAX];
public:
    GraphMatrix()
    {
        n = 0;
        for(int i = 0; i < NMAX; i++)
            for(int j = 0; j < NMAX; j++)
                adjacencyMatrix[i][j] = false;
    }
    GraphVector WarsallTransitiveClosure ()
    {
        GraphVector transitiveClosureGraph = this;
        for(int i = 0; i <= myGraph.n; i++)
        {
            for(int j = 0; j < myGraph.n; j++)
            {
                for(int k = 0; k < myGraph.n; k++)
                {
                    transitiveClosureGraph.adjacencyMatrix[j]][k] = transitiveClosureGraph.adjacencyMatrix[j][k] || (transitiveClosureGraph.adjacencyMatrix[j][i] && transitiveClosureGraph.adjacencyMatrix[i][k]);
                }
            }
        }
        return transitiveClosureGraph;
    }
};



void DemonstrationMode()
{
    Graph myGraph;
}

int main()
{

}
