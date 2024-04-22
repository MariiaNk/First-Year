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
    virtual int size() = 0;
    virtual string className() = 0;
    virtual void WarsallTransitiveClosure() = 0;
    virtual string bfsRandom(int) = 0;
    virtual string bfsPriority(int) = 0;
    virtual int* BellmanFordAlgo(int) = 0;
    virtual vector <int> KahnAlgo() = 0;
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

// comparator for sorting node neighbours [use i bfsPriority]
bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.second < b.second;
}

// temp function to output queue
void outputQueue(queue <int> q)
{
    cout << "Output queue: ";
    while(!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
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
    int size()
    {
        return n;
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
    int* BellmanFordAlgo(int startNode)
    {
        int* distance = new int[NMAX];
        for(int i = 0; i < n; i++)
            distance[i] = INF;
        distance[startNode] = 0;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(adjacencyMatrix[i][j] != 0)
                {
                    if(distance[i] + adjacencyMatrix[i][j] < distance[j])
                        distance[j] = distance[i] + adjacencyMatrix[i][j];
                }
            }
        }
        return distance;
    } 
    vector<int> KahnAlgo()
    {
        int * indegree = new int[n];
        for(int i = 0; i < n; i++)
        {
            indegree[i] = 0;
        }

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(adjacencyMatrix[j][i] != 0 && adjacencyMatrix[j][i] != INF)
                {
                    indegree[i]++;
                    //cout << "Edge " << i << " to " << j << ";";
                }
            }
        }
        queue <int> q;
        for(int i = 0; i < n; i++)
        {
            //cout << i << " -> " << indegree[i] << "\n";
            if (indegree[i] == 0)
                q.push(i);
        }
        vector <int> topologicalOrder;
        while(!q.empty())
        {
            //outputQueue(q);
            int currentNode = q.front();
            q.pop();
            topologicalOrder.push_back(currentNode);
            for (int i = 0; i < n; i++) 
            {
                if (adjacencyMatrix[currentNode][i] != 0 && adjacencyMatrix[currentNode][i] != INF) 
                {
                    indegree[i]--;
                    if (indegree[i] == 0) 
                        q.push(i);
                }
            }
        }
        return topologicalOrder;
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
        if(st == fn)
        {
            i--;
            continue;
        }
        value = rand() % MAXVALUE;
        directed = rand()%2;
        addEdge(st, fn, value, directed);
    }
    do
    {
        st = rand() % CntVertex;
    } while (st == CntVertex-1);
    
    
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

    cout << " ==== SHORTEST PATH ====\n";
    int startNode = rand() % (myGraph->size());
    int * distance = myGraph->BellmanFordAlgo(startNode);
    for(int i = 0; i < myGraph->size(); i++)
    {
        cout << "From " << startNode << " to " << i << " = " << distance[i] << endl;
    }

    cout << " ==== TOPOLOGICAL ORDER ====\n";
    myGraph->cleanGraph();
    //Example 1
    /*myGraph->addEdge(0, 1, 1, true);
    myGraph->addEdge(1, 2, 3, true);
    myGraph->addEdge(3, 1, 51, true);
    myGraph->addEdge(3, 2, -2, true);*/
    //Example 2
    myGraph->addEdge(5, 0, 1, true);
    myGraph->addEdge(5, 2, 1, true);
    myGraph->addEdge(4, 0, 1, true);
    myGraph->addEdge(4, 1, 1, true);
    myGraph->addEdge(3, 1, 1, true);
    myGraph->addEdge(2, 0, 1, true);
    myGraph->addEdge(2, 3, 1, true);
    myGraph->addEdge(1, 0, 1, true);
    myGraph->printMatrix();
    vector <int> topologicalOrder = myGraph->KahnAlgo();
    cout << "Order: ";
    for(auto node: topologicalOrder)
        cout << node << " ";
    cout << endl;

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

