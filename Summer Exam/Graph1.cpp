#include <iostream>
#include <queue>
#define NMAX 100

using namespace std;

struct Node
{
    int value;
    Node* next;
    Node(int value): value(value), next(nullptr) {}
};

struct structAdj
{
    int n;
    Node* neighbours[NMAX];

    structAdj()
    {
        n = 0;
        for(int i = 0; i < NMAX; i++)
            neighbours[i] = nullptr;
    }
};

/*Написати функцію, яка перевіряє суміжність двох заданих вершин 
у неорієнтованому графі, що поданий структурою суміжності */
bool checkAdjacency(structAdj graph, int st, int fn)
{
    if(st < 0 || st >= graph.n || fn < 0 || fn > graph.n)
        return false;
    
    Node* currentNeighbour = graph.neighbours[st];
    while(currentNeighbour)
    {
        if(currentNeighbour->value == fn) 
            return true;
        currentNeighbour = currentNeighbour->next;
    }
    return false;
}

//Алгоритм (Дейкстри) - Обчислення відстаней від заданої вершини
int* distance_from_vertex(structAdj graph, int start)
{
    int* distance = new int[NMAX];
    for(int i = 0; i < NMAX; i++)
        distance[i] = INT_MAX;
    
    distance[start] = 0;
    queue <int> que;
    que.push(start);
    while(!que.empty())
    {
        int vertex = que.front();
        que.pop();
        Node* current = graph.neighbours[vertex];
        while(current)
        {
            if(distance[current->value] == INT_MAX)
            {
                distance[current->value] = distance[vertex] + 1;
                que.push(current->value);
            }
            current = current->next;
        }
    }
    return distance;
}

void find_vertex_fixed_distance(structAdj graph, int vertex, int distance)
{
    int* dist = distance_from_vertex(graph, vertex);
    for(int i = 0 ; i < graph.n; i++)
    {
        if(dist[i] == distance)
            cout << i << " ";
    }
}

void dfs(structAdj graph, int vertex, bool* visited)
{
    visited[vertex] = true;
    Node* current = graph.neighbours[vertex];
    while(current)
    {
        if(!visited[current->value]) 
            dfs(graph, current->value, visited);
        current = current->next;
    }
}
bool isEulerian(structAdj graph) 
{
    bool* visited = new bool[NMAX];
    dfs(graph, 0, visited);

    for(int i = 0; i < graph.n; i++)
    {
        if(!visited[i]) return false;

        Node* current = graph.neighbours[i];
        int indegree = 0;
        while(current)
        {
            indegree++;
            current = current->next;
        }
        if(indegree % 2 != 0) return false;
    }

    return true;
}
/*Знайти всі вершини графа, що поданий структурою суміжності, які досягні від заданої вершини*/
void findAllAvailable(structAdj graph, int vertex)
{
    bool* visited = new bool[NMAX];
    for(int i = 0; i < graph.n; i++)
        visited[i] = false;
    dfs(graph, vertex, visited);
    cout << "All available from " << vertex << " : ";
    for(int i = 0; i < graph.n; i++)
    {
        if(visited[i]) cout << i << " ";
    }
}

void add(structAdj &graph, int st, int fn)
{
    graph.n = max(graph.n, max(st + 1, fn + 1));
    if(!graph.neighbours[st])
        graph.neighbours[st] = new Node(fn);
    else
    {
        Node* current = graph.neighbours[st];
        while(current->next)
            current = current->next;
        current->next = new Node(fn);
    }

    if(!graph.neighbours[fn])
        graph.neighbours[fn] = new Node(st);
    else
    {
        Node* current = graph.neighbours[fn];
        while(current->next)
            current = current->next;
        current->next = new Node(st);
    }
}

void print(structAdj graph) 
{
    for (int i = 0; i < graph.n; i++) 
    {
        cout << "Vertex " << i << ":";
        Node* currentNeighbour = graph.neighbours[i];
        while (currentNeighbour) 
        {
            cout << " " << currentNeighbour->value;
            currentNeighbour = currentNeighbour->next;
        }
        cout << endl;
    }
}
/*Написати функцію, яка за матрицею суміжності графа будує його структуру суміжності*/
structAdj buildStructAdj(bool matrix[NMAX][NMAX], int count)
{
    structAdj graph;
    graph.n = count;
    for(int i = 0; i < count; i++)
    {
        for(int j = i + 1; j < count; j++)
        {
            if(matrix[i][j])
            {
                add(graph, i, j);
            }
        }
    }
    return graph;
}


void dfsForSpanningTree(structAdj graph, int vertex, bool* visited, structAdj& spanningTree)
{
    visited[vertex] = true;
    Node* current = graph.neighbours[vertex];
    while(current)
    {
        if(!visited[current->value]) 
        {
            add(spanningTree, current->value, vertex);
            dfsForSpanningTree(graph, current->value, visited, spanningTree);
        }
        current = current->next;
    }
}

structAdj buildSpanningTree (structAdj graph)
{
    structAdj spanningTree;
    bool* visited = new bool[NMAX];
    for(int i = 0; i < graph.n; i++)
        visited[i] = false;

    for(int i = 0; i < graph.n; i++)
    {
        if(!visited[i])
        {
            dfsForSpanningTree(graph, i, visited, spanningTree);
        }
    }
    return spanningTree;
}
int main()
{
    structAdj graph;
    add(graph, 0, 1);
    add(graph, 0, 2);
    add(graph, 1, 2);
    add(graph, 2, 3);
    add(graph, 2, 4);
    add(graph, 3, 4);
    print(graph);
    /*if(checkAdjacency(graph, 1, 2)) cout << "YES\n";
    else cout<<"NO\n";*/

    find_vertex_fixed_distance(graph, 3, 3);
    findAllAvailable(graph, 4);

    if(isEulerian(graph)) cout << "YES\n";
    else cout << "NO\n";

    bool matrix[NMAX][NMAX] = {
        {0, 1, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1},
        {0, 1, 1, 1, 0, 1},
        {0, 0, 1, 1, 1, 0}
    };
    graph = buildStructAdj(matrix, 6);
    print(graph);

    structAdj spanningTree = buildSpanningTree(graph);
    cout << "Spanning Tree:\n";
    print(spanningTree);
    
}