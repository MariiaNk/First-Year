/*Написати функцію, яка перевіряє суміжність двох заданих вершин 
у неорієнтованому графі, що поданий структурою суміжності */

#include <iostream>
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

void add(structAdj &graph, int st, int fn)
{
    graph.n = max(graph.n, max(st, fn));
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
    cout << "+";
    print(graph);
    if(checkAdjacency(graph, 1, 2)) cout << "YES\n";
    else cout<<"NO\n";
}