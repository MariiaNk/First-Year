#include <iostream>
#include <vector>
#include <iomanip>
#define NMAX 1000
#define MAXVALUE 500


using namespace std;


class Graph
{
public:
    virtual void cleanGraph() = 0;
    virtual void addEdge(int st, int fn, int weight = 1) = 0;
    virtual void printMatrix() = 0;
    virtual string className() = 0;
    virtual void WarsallTransitiveClosure() = 0;
    void generateGraph(int CntVertex, int CntEdge);
    void changeSavingType();
};

/*class GraphVector: public Graph
{
private:
    int n;
    vector< vector<bool>> adjacencyMatrix;
    vector<vector<int>> weights;
    bool directedGraph = false;
public:
    GraphMatrix()
    {
        n = 0;
        for(int i = 0; i < NMAX; i++)
            for(int j = 0; j < NMAX; j++)
                adjacencyMatrix[i][j] = false;
    }
    void addEdge(int st, int fn, int weight = 1) 
    {
        adjacencyMatrix[st][fn] = true;
        weights[st][fn] = weight;
        if (!directedGraph) 
        {
            adjacencyMatrix[fn][st] = true;
            weights[fn][st] = weight;
        }
    }
};*/

class GraphMatrix: public Graph
{
private:
    int n;
    int adjacencyMatrix[NMAX][NMAX];
    bool directedGraph = false;
public:
    void cleanGraph()
    {
        n = 0;
        directedGraph = false;
        for(int i = 0; i < NMAX; i++)
            for(int j = 0; j < NMAX; j++)
                adjacencyMatrix[i][j] = false;
    }
    GraphMatrix()
    {
        cleanGraph();
    }
    string className()
    {
        return "Matrix";
    }
    void addEdge(int st, int fn, int weight = 1)
    {
        n = max(n, max(st, fn) + 1);
        adjacencyMatrix[st][fn] = weight;
        if(!directedGraph) adjacencyMatrix[fn][st] = weight;
    }
    void printMatrix()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cout << setw(5) << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void WarsallTransitiveClosure ()
    {
        GraphMatrix *transitiveClosureGraph = this;
        for(int i = 0; i <= n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                for(int k = 0; k < n; k++)
                {
                    transitiveClosureGraph->adjacencyMatrix[j][k] = transitiveClosureGraph->adjacencyMatrix[j][k] || (transitiveClosureGraph->adjacencyMatrix[j][i] && transitiveClosureGraph->adjacencyMatrix[i][k]);
                }
            }
        }
        *this = *transitiveClosureGraph;
    }
};

void Graph::generateGraph(int CntVertex, int CntEdge)
{
    cleanGraph();
    srand(0);
    int st, fn, value;
    for(int i = 0; i < CntEdge-1; i++)
    {
        st = rand() % CntVertex;
        fn = rand() % CntVertex;
        value = rand() % MAXVALUE;
        addEdge(st, fn, value);
    }
    st = rand() % CntVertex;
    value = rand() % MAXVALUE;
    addEdge(st, CntEdge - 1, value);
}
/*
void Graph::changeSavingType()
{
    if(className() == "Matrix")
    {
        GraphVector newGraph;
    }
}*/

void DemonstrationMode()
{
    Graph* myGraph;
    cout << "Save type:\nv - bit vector\nm - adjacency matrix\n";
    char type;
    cin >> type;
    switch (type)
    {
    case 'v':
        //myGraph = new GraphVector;
        break;
    case 'm':
        myGraph = new GraphMatrix;
        break;
    default:
        cout << "----- Error! Wrong request! Try again!!! -----";
        break;
    }
    myGraph->addEdge(0, 2);
    myGraph->addEdge(0, 3);
    myGraph->addEdge(1, 2);
    myGraph->addEdge(3, 2);
    myGraph->printMatrix();
    cout << "     === Closure ===    \n";
    myGraph->WarsallTransitiveClosure();
    myGraph->printMatrix();
}

int main()
{
    srand((unsigned)time(0)); 
    cout << "Input mode of work\ni - interactive\nd - demonstration\nb - benchmark\n";
    char mode;
    cin >> mode;
    // //if (mode == 'i')
    //     //InteractiveMode();
    // else 
    if(mode == 'd')
        DemonstrationMode();
    // else if(mode == 'b')
    //     BenchmarkMode();
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
}

