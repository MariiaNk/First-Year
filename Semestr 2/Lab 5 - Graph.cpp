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
    virtual void print() = 0;
    virtual int size() = 0;
    virtual string className() = 0;
    virtual Graph* TransitiveClosure() = 0;
    virtual string bfsRandom(int) = 0;
    virtual string bfsPriority(int) = 0;
    virtual int* BellmanFordAlgo(int) = 0;
    virtual vector <int> KahnAlgo() = 0;
    virtual Graph* spanningTreeBFS (int) = 0;
    virtual int KruskalAlgo() = 0;
    void generateGraph(int CntVertex, int CntEdge, bool directedGraph);
    void changeSavingType();
};

class GraphMatrix: public Graph
{
private:
    int n;
    int adjacencyMatrix[NMAX][NMAX];
public:
    void cleanGraph();
    GraphMatrix();
    string className();
    int size();
    bool isConectedEdge(int st, int fn);
    void addEdge(int st, int fn, int weight = 1, bool directedEdge = false);
    void print();
    GraphMatrix* TransitiveClosure ();
    string bfsRandom(int startNode);
    string bfsPriority(int startNode);
    int* BellmanFordAlgo(int startNode); // minPath algorithm 
    vector<int> KahnAlgo(); //topological sort
    GraphMatrix* spanningTreeBFS (int startNode);
    int KruskalAlgo(); //min spanning tree

};

class GraphVector: public Graph
{
private:
    vector<vector<pair<int, int>>> adjacencyVector;
public:
    void cleanGraph();
    GraphVector();
    string className();
    int size();
    void addEdge(int st, int fn, int weight = 1, bool directedEdge = false);
    void print();
    void DFSUtil(int st, int fn, GraphMatrix* TransClosure);
    GraphMatrix* TransitiveClosure();
    string bfsRandom(int startNode);
    string bfsPriority(int startNode);
    int* BellmanFordAlgo(int startNode); // minPath algorithm 
    vector<int> KahnAlgo(); //topological sort
    GraphVector* spanningTreeBFS (int startNode);
    int KruskalAlgo(); //min spanning tree
};


void DemonstrationMode()
{
    Graph* myGraph;
    cout << "Save type:\nv - adjacency vector\nm - adjacency matrix\n";
    char type;
    cin >> type;
    switch (type)
    {
    case 'v':
        myGraph = new GraphVector();
        break;
    case 'm':
        myGraph = new GraphMatrix();
        break;
    default:
        cout << "----- Error! Wrong request! Try again!!! -----";
        break;
    }
    /*myGraph->addEdge(1, 0, 4, true);
    myGraph->addEdge(1, 2, 3, true);
    myGraph->addEdge(3, 1, -1, true);
    myGraph->addEdge(0, 2, -2, true);
    myGraph->addEdge(2, 3, 2, true);*/
    myGraph->addEdge(0, 1, 1, true);
    myGraph->addEdge(0, 2, 1, true);
    myGraph->addEdge(1, 2, 1, true);
    myGraph->addEdge(2, 0, 1, true);
    myGraph->addEdge(2, 3, 1, true);
    myGraph->addEdge(3, 3, 1, true);
    myGraph->print();
    cout << "     === Closure ===    \n";
    Graph* closure = myGraph->TransitiveClosure();
    closure->print();

    cout << "   ==== GENERETE GRAPH ====\n";
    myGraph->generateGraph(5, 12, false);
    myGraph->print();
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
    myGraph->print();
    vector <int> topologicalOrder = myGraph->KahnAlgo();
    cout << "Order: ";
    for(auto node: topologicalOrder)
        cout << node << " ";
    cout << endl;

    cout << " ===== SPANNING TREE ALGORITHM ======\n";
    myGraph->generateGraph(5, 13, false);
    cout << "Graph:" << endl;
    myGraph->print();
    startNode = rand() % (myGraph->size());
    Graph* spanningTree = myGraph->spanningTreeBFS(startNode);
    cout << "Spanning Tree: start node = " << startNode << endl;
    spanningTree->print();

    cout << " ===== MIN SPANNING TREE ALGORITHM ======\n";
    myGraph->cleanGraph();
    myGraph->addEdge(0, 1, 2, false);
    myGraph->addEdge(0, 3, 6, false);
    myGraph->addEdge(1, 2, 3, false);
    myGraph->addEdge(1, 3, 8, false);
    myGraph->addEdge(1, 4, 5, false);
    myGraph->addEdge(2, 4, 7, false);
    myGraph->addEdge(3, 4, 9, false);
    cout << "Graph:" << endl;
    myGraph->print();
    int minWeight = myGraph->KruskalAlgo();
    cout << "Min weight of spanning tree: " << minWeight << endl;
}
/*
bool cmp(pair<int, int> a, pair<int, int> b); // comparator for sorting node neighbours [use i bfsPriority]
void outputQueue(queue <int> q); // temp function to output queue
*/
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

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.second < b.second;
}
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
void GraphVector::cleanGraph()
{
    adjacencyVector.clear();
}
GraphVector::GraphVector()
{
    cleanGraph();
}
string GraphVector::className()
{
    return "Vector";
}
int GraphVector::size()
{
    return adjacencyVector.size();
}
void GraphVector::addEdge(int st, int fn, int weight, bool directedEdge)
{
    if(adjacencyVector.size() <= st)
        adjacencyVector.resize(st + 1);
    if(adjacencyVector.size() <= fn)
            adjacencyVector.resize(fn + 1);

    adjacencyVector[st].push_back({fn, weight});
    if (!directedEdge)
        adjacencyVector[fn].push_back({st, weight});
}
void GraphVector::print()
{
    for(int i = 0; i < adjacencyVector.size(); i++)
    {
        cout << i << ": ";
        for(pair<int, int> neighbours: adjacencyVector[i])
            cout << neighbours.first << "[" << neighbours.second << "] ";
        cout << endl;
    }
}
void GraphVector::DFSUtil(int st, int fn, GraphMatrix* TransClosure)
{
    TransClosure->addEdge(st, fn, 1);

    for (pair <int, int> vertex : adjacencyVector[fn])
    {
        if (!TransClosure->isConectedEdge(st, vertex.first)) 
        {
            DFSUtil(st, vertex.first, TransClosure);
        }
    }
}
GraphMatrix* GraphVector::TransitiveClosure()
{
    GraphMatrix* TransClosure = new GraphMatrix();
    for (int i = 0; i < adjacencyVector.size(); i++)
        DFSUtil(i,i, TransClosure);
    return TransClosure;
}
string GraphVector::bfsRandom(int startNode)
{
    if(startNode >=  adjacencyVector.size()|| startNode < 0) return "error";
    bool visited[ adjacencyVector.size()];
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
        for(pair<int, int> neighbour: adjacencyVector[currentNode])
        {
            if(!visited[neighbour.first])
            {
                visited[neighbour.first] = true;
                q.push(neighbour.first);
            }

        }
    }
    return orderBFS;
}
string GraphVector::bfsPriority(int startNode)
{
    if(startNode >=  adjacencyVector.size() || startNode < 0) return "error";
    bool visited[ adjacencyVector.size()] = {0};
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
        for(pair<int, int> neighbour: adjacencyVector[currentNode])
        {
            if(!visited[neighbour.first])
            {
                visited[neighbour.first] = true;
                neighbours.push_back(neighbour);
            }
        }
        sort(neighbours.begin(), neighbours.end(), cmp);
        for(pair<int, int> neighbourNode: neighbours)
            q.push(neighbourNode.first);
        neighbours.clear();
    }
    return orderBFS;
}

int* GraphVector::BellmanFordAlgo(int startNode)
{
    int* distance = new int[NMAX];
    for(int i = 0; i < adjacencyVector.size(); i++)
        distance[i] = INF;
    distance[startNode] = 0;

    for(int i = 0; i < adjacencyVector.size(); i++)
    {
        for(pair <int, int> neighbour : adjacencyVector[i])
        {
            if(distance[i] + neighbour.second < distance[neighbour.first])
                    distance[neighbour.first] = distance[i] + neighbour.second;
        }
    }
    return distance;
}

vector<int> GraphVector::KahnAlgo()
{
    int n = adjacencyVector.size();

    int * indegree = new int[n];
    for(int i = 0; i < n; i++)
        indegree[i] = 0;

    for(int i = 0; i < n; i++)
    {
        for(pair<int, int> vertex: adjacencyVector[i])
            indegree[vertex.first]++;
    }
    queue <int> q;

    for(int i = 0; i < n; i++)
    {
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
        for (pair<int, int> vertex: adjacencyVector[currentNode])
        {
            indegree[vertex.first]--;
            if (indegree[vertex.first] == 0)
                q.push(vertex.first);
        }
    }
    return topologicalOrder;
}

GraphVector* GraphVector::spanningTreeBFS (int startNode)
{
    int n = adjacencyVector.size();
    GraphVector* spanningTree = new GraphVector();
    if(startNode >= n || startNode < 0) return spanningTree;

    bool visited[n] = {0};
    queue <int> q;

    visited[startNode] = true;
    q.push(startNode);

    while(!q.empty())
    {
        int currentNode = q.front();
        q.pop();
        for(pair<int, int> vertex: adjacencyVector[currentNode])
        {
            if(!visited[vertex.first])
            {
                visited[vertex.first] = true;
                q.push(vertex.first);
                //cout << "Add edge to spanning tree: " << currentNode << "-" << i << endl;
                spanningTree->addEdge(currentNode, vertex.first, vertex.second);
            }

        }
    }
    return spanningTree;
}

int findPath(int* parent, int id)
{
    while(parent[id] != id)
        id = parent[id];
    return id;
}

int GraphVector::KruskalAlgo()
{
    int n = adjacencyVector.size();

    int minWeight = 0;
    int edgeCount = 0;
    int parent[n];
    for(int i = 0; i < n; i++)
        parent[i] = i;

    while(edgeCount < n - 1)
    {
        int minEdge = INT_MAX, st, fn;
        st = fn = -1;
        for(int i = 0; i < n; i++)
            for(auto vertex: adjacencyVector[i])
            {
                int iPath = findPath(parent, i), jPath = findPath(parent,vertex.first);
                if(iPath != jPath && vertex.second< minEdge)
                {
                    minEdge = vertex.second;
                    st = iPath;
                    fn = jPath;
                }
            }
        parent[st] = fn;
        edgeCount++;
        minWeight += minEdge;
    }
    return minWeight;
}

void GraphMatrix::cleanGraph()
{
    n = 0;
    for(int i = 0; i < NMAX; i++)
        for(int j = 0; j < NMAX; j++)
            adjacencyMatrix[i][j] = false;
}
GraphMatrix::GraphMatrix()
{
    cleanGraph();
}
string GraphMatrix::className()
{
    return "Matrix";
}
int GraphMatrix::size()
{
    return n;
}
bool GraphMatrix::isConectedEdge(int st, int fn)
{
    return (adjacencyMatrix[st][fn] != 0);
}
void GraphMatrix::addEdge(int st, int fn, int weight, bool directedEdge)
{
    n = max(n, max(st, fn) + 1);
    adjacencyMatrix[st][fn] = weight;
    if(!directedEdge) adjacencyMatrix[fn][st] = weight;
    else if(adjacencyMatrix[fn][st] == 0)  adjacencyMatrix[fn][st] = INF;
}

void GraphMatrix::print()
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

GraphMatrix* GraphMatrix::TransitiveClosure()
{
    GraphMatrix* TransClosure = this;
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (TransClosure->adjacencyMatrix[i][k] == 1 && TransClosure->adjacencyMatrix[k][j] == 1) 
                    TransClosure->adjacencyMatrix[i][j] = 1;
            }
        }
    }
    return TransClosure;
}
string GraphMatrix::bfsRandom(int startNode)
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
string GraphMatrix::bfsPriority(int startNode)
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
int* GraphMatrix::BellmanFordAlgo(int startNode)
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
vector<int> GraphMatrix::KahnAlgo()
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
GraphMatrix* GraphMatrix::spanningTreeBFS (int startNode)
{
    GraphMatrix* spanningTree = new GraphMatrix;
    if(startNode >= n || startNode < 0) return spanningTree;

    bool visited[n] = {0};
    queue <int> q;

    visited[startNode] = true;
    q.push(startNode);

    while(!q.empty())
    {
        int currentNode = q.front();
        q.pop();
        for(int i = 0; i < n; i++)
        {
            if(adjacencyMatrix[currentNode][i] != 0 && !visited[i])
            {
                visited[i] = true;
                q.push(i);
                //cout << "Add edge to spanning tree: " << currentNode << "-" << i << endl;
                spanningTree->addEdge(currentNode, i, adjacencyMatrix[currentNode][i]);
            }

        }
    }
    return spanningTree;
}


int GraphMatrix::KruskalAlgo()
{
    int minWeight = 0;
    int edgeCount = 0;
    int parent[n];
    for(int i = 0; i < n; i++)
        parent[i] = i;

    while(edgeCount < n - 1)
    {
        int minEdge = INT_MAX, st, fn;
        st = fn = -1;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                int iPath = findPath(parent, i), jPath = findPath(parent,j);
                if(iPath != jPath && adjacencyMatrix[i][j] < minEdge && adjacencyMatrix[i][j] != 0)
                {
                    minEdge = adjacencyMatrix[i][j];
                    st = iPath;
                    fn = jPath;
                }
            }
        parent[st] = fn;
        edgeCount++;
        minWeight += minEdge;
    }
    return minWeight;

}

/*
void Graph::changeSavingType()
{
    if(className() == "Matrix")
    {
        GraphVector newGraph;
    }
}*/

void Graph::generateGraph(int CntVertex, int CntEdge, bool directedGraph)
{
    cleanGraph();
    int st, fn, value;
    bool directed = false;
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
        if(directedGraph) directed = rand()%2;
        addEdge(st, fn, value, directed);
    }

    do
    {
        st = rand() % CntVertex;
    } while (st == CntVertex-1);
    value = rand() % MAXVALUE;
    if(directedGraph) directed = rand()%2;
    addEdge(st, CntVertex - 1, value, directed);
}

