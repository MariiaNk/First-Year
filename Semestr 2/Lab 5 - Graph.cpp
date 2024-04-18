#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#define NMAX 1000
#define MAXVALUE 500
#define INF 99999

using namespace std;


class Graph
{
public:
    virtual void cleanGraph() = 0;
    virtual void addEdge(int, int, int, bool) = 0;
    virtual void printMatrix() = 0;
    virtual string className() = 0;
    virtual void WarsallTransitiveClosure() = 0;
    virtual string bfsRandom(int) = 0;
    virtual string bfsPriority(int) = 0;
    void generateGraph(int, int);
    void changeSavingType();
};

/*class GraphVector: public Graph
{
private:
    int n;
    vector< vector<bool>> adjacencyMatrix;
    vector<vector<int>> weights;
public:
    void cleanGraph()
    {
        n = 0;
        for(int i = 0; i < NMAX; i++)
            for(int j = 0; j < NMAX; j++)
                adjacencyMatrix[i][j] = false;
    }
    GraphVector()
    {
        cleanGraph();
    }
    string className()
    {
        return "Vector";
    }
    void addEdge(int st, int fn, int weight = 1, bool directedEdge = false) 
    {
        adjacencyMatrix[st][fn] = true;
        weights[st][fn] = weight;
        if (!directedEdge) 
        {
            adjacencyMatrix[fn][st] = true;
            weights[fn][st] = weight;
        }
    }
};*/

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.second < b.second;
}

class GraphMatrix: public Graph
{
private:
    int n;
    int adjacencyMatrix[NMAX][NMAX];
public:
    void cleanGraph()
    {
        n = 0;
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
    void addEdge(int st, int fn, int weight = 1, bool directedEdge = false)
    {
        n = max(n, max(st, fn) + 1);
        adjacencyMatrix[st][fn] = weight;
        if(!directedEdge) adjacencyMatrix[fn][st] = weight;
        else  adjacencyMatrix[fn][st] = INF;
    }
    void printMatrix()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cout << setw(5) << ((adjacencyMatrix[i][j] != INF) ? adjacencyMatrix[i][j] : 0) << " ";
            } 
            cout << endl;
        }
    }
    void WarsallTransitiveClosure ()
    {
        for(int i = 0; i <= n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                for(int k = 0; k < n; k++)
                {
                    if (adjacencyMatrix[i][j] > adjacencyMatrix[i][k] + adjacencyMatrix[k][j])
                        adjacencyMatrix[i][j] = adjacencyMatrix[i][k] + adjacencyMatrix[k][j];
                }
            }
        }
    }
    string bfsRandom(int startNode)
    {
        if(startNode >= n || startNode < 0) return "error";
        bool visited[n];
        queue <int> q;
        string orderBFS;
        orderBFS.clear();

        visited[startNode] = true;
        q.push(startNode);

        while(!q.empty())
        {
            int currentNode = q.front();
            q.pop();
            orderBFS += to_string(currentNode) + " ";
            for(int i = 0; i < n; i++)
            {
                if(adjacencyMatrix[currentNode][i] != 0 && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
                    
            }
        }
        return orderBFS;
    }
    string bfsPriority(int startNode)
    {
        if(startNode >= n || startNode < 0) return "error";
        bool visited[n] = {0};
        vector <pair<int, int>> neighbours;
        queue <int> q;
        string orderBFS;
        orderBFS.clear();

        visited[startNode] = true;
        q.push(startNode);

        while(!q.empty())
        {
            int currentNode = q.front();
            q.pop();
            orderBFS += to_string(currentNode) + " ";
            for(int i = 0; i < n; i++)
            {
                if(adjacencyMatrix[currentNode][i] != 0 && !visited[i])
                {
                    visited[i] = true;
                    neighbours.push_back({i, adjacencyMatrix[startNode][i]});
                }
            }
            /*cout << "Neighbour " << currentNode << ": " ;
            for(pair<int, int> neighbourNode: neighbours)
                cout << neighbourNode.first << " ";  
            cout << endl;*/
            sort(neighbours.begin(), neighbours.end(), cmp);
            for(pair<int, int> neighbourNode: neighbours)
                q.push(neighbourNode.first);   
            neighbours.clear();
        }
        return orderBFS;
    }
    void BellmanFordAlgo
    {
        
    } 
};


void Graph::generateGraph(int CntVertex, int CntEdge)
{
    cleanGraph();
    int st, fn, value;
    bool directed;
    for(int i = 0; i < CntEdge-1; i++)
    {
        st = rand() % CntVertex;
        fn = rand() % CntVertex;
        value = rand() % MAXVALUE;
        directed = rand()%2;
        addEdge(st, fn, value, directed);
    }
    st = rand() % CntVertex;
    value = rand() % MAXVALUE;
    directed = rand()%2;
    addEdge(st, CntVertex - 1, value, directed);
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
    myGraph->addEdge(1, 0, 4, true);
    myGraph->addEdge(1, 2, 3, true);
    myGraph->addEdge(3, 1, -1, true);
    myGraph->addEdge(0, 2, -2, true);
    myGraph->addEdge(2, 3, 2, true);
    myGraph->printMatrix();
    cout << "     === Closure ===    \n";
    myGraph->WarsallTransitiveClosure();
    myGraph->printMatrix();

    cout << "   ==== GENERETE GRAPH ====\n";
    myGraph->generateGraph(5, 12);
    myGraph->printMatrix();
    cout << "Order BFS: " << myGraph->bfsRandom(3) << endl;
    cout << "Order priority BFS: " << myGraph->bfsPriority(3) << endl;
    
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

