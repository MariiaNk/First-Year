#include <iostream>
#include <queue>
#define NMAX 10000

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
int main()
{
    structAdj graph;
    add(graph, 2, 5);
    add(graph, 1, 3);
    add(graph, 0, 4);
    add(graph, 1, 4);
    add(graph, 5, 4);
    print(graph);
    /*if(checkAdjacency(graph, 1, 2)) cout << "YES\n";
    else cout<<"NO\n";*/

    find_vertex_fixed_distance(graph, 3, 3);
}