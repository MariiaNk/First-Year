#include <iostream>
#define NMAX 100
using namespace std;

struct MatrixAdj
{
    bool matrix[NMAX][NMAX];
    int n;
    MatrixAdj()
    {
        n = 0;
        for(int i = 0; i < NMAX; i++)
            for(int j = 0; j < NMAX; j++)
                matrix[i][j] = false;
    }
};
void dfs(MatrixAdj graph, int vertex, bool* visited)
{
    visited[vertex] = true;
    
    for(int i = 0; i < graph.n; i++)
    {
        if(graph.matrix[vertex][i] && !visited[i]) 
            dfs(graph, i, visited);
    }
}
/*Написати функцію, яка перевіряє зв’язність неорієнтованого графа, поданого матрицею суміжності.*/
bool checkConnectivity (MatrixAdj graph)
{
    bool* visited = new bool[NMAX];
    for(int i = 0; i < graph.n; i++)
        visited[i] = false;
    
    dfs(graph, 0, visited);
    for(int i = 0 ; i < graph.n; i++)
        if(!visited[i]) return false;
    return true;
}

bool  cyclicDFS (MatrixAdj graph, int vertex, bool* visited)
{
    visited[vertex] = true;
    
    for(int i = 0; i < graph.n; i++)
    {
        if(graph.matrix[vertex][i]) 
        {
            if( visited[i]) return true;
            dfs(graph, i, visited);
        }
            
    }
    return false;
}
/*Написати функцію, яка перевіряє ациклічність орієнтованого графа, поданого матрицею суміжності.*/
bool checkAntiCyclic(MatrixAdj graph)
{
    /*Повертає:
    true - якщо граф не має циклів
    false - граф має цикл*/
    bool* visited = new bool[NMAX];
    for(int i = 0; i < graph.n; i++)
        visited[i] = false;

    for(int i = 0; i < graph.n; i++)
    {
        if(!visited[i])
            if(cyclicDFS(graph, i, visited)) return false;
    }
    return true;
}

/*Написати функцію, яка визначає кількість ізольованих вершин неорієнтованого графа, поданого матрицею суміжності. */
int cntIsolated(MatrixAdj graph)
{
    int answer = 0;
    for(int i = 0; i < graph.n; i++)
    {
        int cntEdge = 0;
        for(int j = 0; j < graph.n; j++)
        {
            if(graph.matrix[i][j]) cntEdge++;
        }
        if(cntEdge == 0) answer++;
    }
    return answer;
}
int main()
{
    MatrixAdj graph;
    /*graph.n = 6;
    bool tempMatrix[NMAX][NMAX] = {
        {0, 1, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1},
        {0, 1, 1, 1, 0, 1},
        {0, 0, 1, 1, 1, 0}
    };*/
    // graph.n = 6;
    // bool tempMatrix[NMAX][NMAX] = {
    //     {0, 1, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 1, 0, 0},
    //     {0, 0, 1, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 1},
    //     {0, 0, 0, 0, 1, 0}
    // };

    
    /*graph.n = 5;
    bool tempMatrix[NMAX][NMAX] = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };*/

    graph.n = 6;
    bool tempMatrix[NMAX][NMAX] = {
        {0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0}
    };



    for(int i = 0; i < graph.n; i++)
        for(int j = 0; j < graph.n; j++)
            graph.matrix[i][j] = tempMatrix[i][j];
    cout << "Is graph connected? - ";
    if(checkConnectivity(graph)) cout << "YES\n";
    else cout << "NO\n";

    cout << "Is graph anticyclic? - ";
    if(checkAntiCyclic(graph)) cout << "YES\n";
    else cout << "NO\n";

    cout << "Count of isolated vertex: " << cntIsolated(graph) << endl;
}