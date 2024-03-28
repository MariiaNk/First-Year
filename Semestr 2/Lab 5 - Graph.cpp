#include <iostream>
#include <vector>
#define NMAX 1000
using namespace std;



class Graph
{
    private:
        struct GraphVector
        {
            int n;
            vector< vector<bool>> adjacencyMatrix;
        };

        struct GraphMatrix
        {
            int n;
            bool adjacencyMatrix[NMAX][NMAX];
        }   
    public:
        GraphVector myGraph;
        GraphVector WarsallTransitiveClosure ()
        {
            GraphVector transitiveClosureGraph = myGraph;
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
}