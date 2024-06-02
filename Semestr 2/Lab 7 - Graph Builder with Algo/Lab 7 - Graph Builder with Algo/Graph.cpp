#include "Graph.h"
#include <cmath>
#include <queue>
#include <stack>

void Graph::unSelectVertex()
{
	for (int i = 0; i < cntSelectedVertex; i++)
	{
		idSelectedPoints[i] = -1;
	}
	for (int i = 0; i < cntVertex; i++)
	{
		point[i]->marker = 0;
	}
	cntSelectedVertex = 0;
}

void Graph::unWeightedEdge()
{
	for (int i = 0; i < cntVertex; i++)
	{
		for (int j = 0; j < cntVertex; j++)
		{
			if (matrix[i][j] != 0 && matrix[j][i] == 0) matrix[j][i] = matrix[i][j];
		}
	}
}

void Graph::unDirectedGraph()
{
	for (int i = 0; i < cntVertex; i++)
	{
		for (int j = 0; j < cntVertex; j++)
		{
			if (matrix[i][j] != 0) matrix[j][i] = 1;
		}
	}
}
void Graph::cleanGraph()
{
	for (int i = 0; i < 1000; i++)
	{
		point[i] = nullptr;
		idSelectedPoints[i] = -1;
		allEdges[i] = nullptr;
		orderBridges[i] = new Edge;
		for (int j = 0; j < 1000; j++)
		{
			matrix[i][j] = 0;
		}
	}
	Edge* selectedEdge = nullptr;
	cntEdges = 0;
	cntVertex = 0;
	directedGraph = false;
	weightedGraph = false;
	needEdgeInAlgo = false;
	cntBridges = 0;
	colorAlgoVertex = Brushes::GreenYellow;
}
Graph::Graph()
{
	point = gcnew cli::array<Vertex*>(1000);
	idSelectedPoints = gcnew cli::array<int>(1000);
	matrix = gcnew cli::array<cli::array<int>^>(1000);
	for (int i = 0; i < 1000; i++)
		matrix[i] = gcnew cli::array<int>(1000);
	allEdges = gcnew cli::array<Edge*>(10000);
	orderBridges = gcnew cli::array<Edge*>(10000);
	cleanGraph();
}
void Graph::deleteSelectedVertex()
{
	System::Array::Sort(idSelectedPoints, 0, cntSelectedVertex);
	cli::array<cli::array<int>^>^ newMatrix = gcnew cli::array<cli::array<int>^>(1000);
	for (int i = 0; i < 1000; i++)
		newMatrix[i] = gcnew cli::array<int>(1000);
	int jRow = 0, jCol = 0;
	for (int i = 0; i < cntVertex; i++)
	{
		if (i != idSelectedPoints[jRow] || jRow == cntSelectedVertex)
		{
			jCol = 0;
			for (int k = 0; k < cntVertex; k++)
			{
				if (k != idSelectedPoints[jCol] || jCol == cntSelectedVertex)
					newMatrix[i - jRow][k - jCol] = matrix[i][k];
				else jCol++;
			}
		}
		else jRow++;
	}
	matrix = newMatrix;
	for (int i = cntSelectedVertex - 1; i >= 0; i--)
	{
		for (int j = idSelectedPoints[i]; j < cntVertex - 1; j++)
			point[j] = point[j + 1];
		if( i == cntSelectedVertex - 1) point[cntVertex - 1] = new Vertex;
		idSelectedPoints[i] = -1;
	}
	cntVertex -= cntSelectedVertex;
	cntSelectedVertex = 0;
}
int distance(Vertex* a, Vertex* b)
{
	int distanceX = (a->x - b->x)* (a->x - b->x);
	int distanceY = (a->y - b->y) * (a->y - b->y);
	return sqrt(distanceX + distanceY);
}
void Graph::deleteSelectedEdge()
{
	matrix[selectedEdge->start][selectedEdge->end] = 0;
	matrix[selectedEdge->end][selectedEdge->start] = 0;
	selectedEdge = nullptr;
}
void Graph::addVertex(Vertex* coord)
{
	point[cntVertex] = coord;

	if (cntSelectedVertex > 0)
	{
		for (int i = 0; i < cntSelectedVertex; i++)
		{
			matrix[cntVertex][idSelectedPoints[i]] = 1;
			matrix[idSelectedPoints[i]][cntVertex] = 1;
			allEdges[cntEdges] = new Edge(cntVertex, idSelectedPoints[i]);
			cntEdges++;
		}
	}

	cntVertex++;
	unSelectVertex();
}

bool Graph::conectedVertex(int numStart, int numFinish)
{
	return !(matrix[numStart][numFinish] == 0 && matrix[numFinish][numStart] == 0);
}
bool Graph::checkSelectedVertex(int num)
{
	bool selected = true;
	for (int i = 0; i < cntSelectedVertex; i++)
	{
		if (!conectedVertex(idSelectedPoints[i], num))
		{
			selected = false;
			matrix[idSelectedPoints[i]][num] = 1;
			matrix[num][idSelectedPoints[i]] = 1;
			allEdges[cntEdges] = new Edge(num, idSelectedPoints[i]);
			cntEdges++;
		}
	}
	return selected;
}
//numCompare - вершина з якою ми порівнюємо 
int Graph::ifClickVertex(Vertex* coord, int numCompare )
{
	/*
	num - select vertex
	-1 - can't draw vertex
	-2 - free space
	*/
	int tempDistance = 0;
	for (int i = 0; i < cntVertex; i++)
	{
		if (numCompare == i) continue;
		tempDistance = distance(point[i], coord);
		if (tempDistance < 2 * style.radius)
			return i;
		else if (tempDistance < 3 * style.radius)
			return -1;
	}

	return -2;
}
bool ifClickEdge(Vertex* start, Vertex* end, int radiusEdge, Vertex* curr)
{
	int kofA = (end->y - start->y);
	int kofB = (start->x - end->x);
	int kofC = (end->x * start->y - start->x * end->y);
	int distance = abs(kofA * curr->x + kofB * curr->y + kofC) / sqrt(kofA*kofA + kofB*kofB);

	if (distance < radiusEdge)
	{
		if (System::Math::Min(start->x, end->x) - radiusEdge <= curr->x && System::Math::Max(start->x, end->x) + radiusEdge >= curr->x)
		{
			if (System::Math::Min(start->y, end->y) - radiusEdge <= curr->y && System::Math::Max(start->y, end->y) + radiusEdge >= curr->y)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;

}
Edge Graph::ifselectedEdge(Vertex* coord)
{
	int radiusEdge = style.boldness / 2 + style.radius;
	for (int i = 0; i < cntVertex; i++)
	{
		Vertex* start = point[i];
		for (int j = i + 1; j < cntVertex; j++)
		{
			if (matrix[i][j] != 0 || matrix[j][i] != 0)
			{
				Vertex* end = point[j];
				if (ifClickEdge(start, end, radiusEdge, coord))
				{
					if (matrix[i][j] != 0) return { i,j };
					else return { j, i };
				}
			}
		}
	}
	return{ -1, -1 };
}
System::String^ Graph::typeClick(Vertex* coord)
{
	int numVertex = ifClickVertex(coord, -1);
	selectedEdge = nullptr;
	if(numVertex == -1) return L"Не можна малювати вершини надто близько!";
	if (numVertex == -2)
	{
		Edge currSelectedEdge = ifselectedEdge(coord);
		if (currSelectedEdge.end == -1 && currSelectedEdge.start == -1)
		{
			addVertex(coord);
		}
		else
		{
			selectedEdge = new Edge();
			selectedEdge->end = currSelectedEdge.end;
			selectedEdge->start = currSelectedEdge.start;
		}
		return " ";		
	}

	if (checkSelectedVertex(numVertex))
	{
		idSelectedPoints[cntSelectedVertex] = numVertex;
		point[numVertex]->marker = 1;
		cntSelectedVertex++;
	}
	else
	{
		unSelectVertex();
	}
	return " ";	
}
void Graph::findAllEdges()
{
	cntEdges = 0;
	for (int i = 0; i < cntVertex; i++)
	{
		for (int j = i + 1; j < cntVertex; j++)
		{
			if (matrix[i][j] != 0 || matrix[j][i] != 0)
			{
				int start = i;
				int finish = j;
				if (matrix[i][j] == 0) swap(start, finish);
				allEdges[cntEdges] = new Edge(start, finish);
				cntEdges++;
			}
		}
	}
}
void Graph::changeEdgeWeight(int st, int fn, int value)
{
	matrix[st][fn] = value;
	if(matrix[fn][st] != 0) matrix[fn][st] = value;
}
void Graph::dfsRec(int startNode, bool* visited)
{
	visited[startNode] = true;
	orderAlgo.Add(startNode);
	for (int i = 0; i < cntVertex; i++)
	{
		if (matrix[startNode][i] != 0 && !visited[i])
			dfsRec(i, visited);
	}
}
void Graph::dfs(int startNode)
{
	orderAlgo.Clear();
	bool *visited = new bool[cntVertex];
	for (int i = 0; i < cntVertex; i++)
		visited[i] = false;
	dfsRec(startNode, visited);
}

void Graph::bfs(int startPoint)
{
	bool visited[1000] = { false };
	queue<int> q;
	visited[startPoint] = true;
	q.push(startPoint);
	orderAlgo.Add(startPoint);

	while (!q.empty()) 
	{
		int startPoint = q.front();
		q.pop();
		for (int i = 0; i < cntVertex; i++)  
		{
			if (matrix[startPoint][i] != 0)
			{
				if (!visited[i]) 
				{
					visited[i] = true;
					q.push(i);
					orderAlgo.Add(i);
				}
			}
		}
	}
	
}

bool Graph::isFullDirected()
{
	for (int i = 0; i < cntVertex; i++)
	{
		for (int j = 0; j < cntVertex; j++)
		{
			if (matrix[i][j] == matrix[j][i] && matrix[i][j] != 0)
				return false;
		}
	}

	return true;
}

bool Graph::isCyclicUtil(int v, bool visited[], bool* recStack)
{
	if (visited[v] == false) 
	{
		visited[v] = true;
		recStack[v] = true;

		for (int i = 0; i < cntVertex; ++i) 
		{
			if (matrix[v][i] != 0)
			{
				int adjVertex = i;
				if (!visited[adjVertex] && isCyclicUtil(adjVertex, visited, recStack))
					return true;
				else if (recStack[adjVertex])
					return true;
			}
			
		}
	}

	recStack[v] = false;
	return false;
}



bool Graph::HasCycle()
{
	bool* visited = new bool[1000];
	bool* recStack = new bool[1000];
	for (int i = 0; i < cntVertex; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	for (int i = 0; i < cntVertex; i++)
		if (!visited[i] && isCyclicUtil(i, visited, recStack))
			return true;

	return false;
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
	visited[v] = true;

	
	for (int i = 0; i < cntVertex; ++i) 
	{
		if (matrix[v][i] != 0)
		{
			int adjVertex = i;
			if (!visited[adjVertex])
				topologicalSortUtil(adjVertex, visited, Stack);
		}
		
	}

	Stack.push(v);
}
void Graph::topologicalSort()
{
	stack<int> Stack;

	bool* visited = new bool[1000];
	for (int i = 0; i < cntVertex; i++)
		visited[i] = false;

	for (int i = 0; i < cntVertex; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	while (Stack.empty() == false) 
	{
		orderAlgo.Add(Stack.top());
		Stack.pop();
	}
}
int Graph::StartVertexEulerCheck()
{
	int even = 0, start = 0;
	for (int i = 0; i < cntVertex; i++)
	{
		int pov_vertex = 0;
		for (int j = 0; j < cntVertex; j++)
		{
			if (matrix[i][j] != 0) pov_vertex++;
		}
		if (pov_vertex % 2 != 0)
		{
			even++;
			start = i;
		}
	}
	if (even == 2) return start;
	else return -1;
}

void Graph::EulerWayDFS(int startNode)
{
	int copy_matrix[100][100];

	for (int i = 0; i < cntVertex; i++)
		for (int j = 0; j < cntVertex; j++)
			copy_matrix[i][j] = matrix[i][j];

	int id_temp = 0, i = 0;
	
	stack <int> mystack;
	mystack.push(startNode);
	while (!mystack.empty())
	{
		id_temp = mystack.top();
		i = 0;
		while (i < cntVertex && copy_matrix[id_temp][i] == 0) 
			i++;
		if (i == cntVertex)
		{
			orderAlgo.Add(mystack.top());
			mystack.pop();
		}
		else
		{
			mystack.push(i);
			copy_matrix[i][id_temp] = 0;
			copy_matrix[id_temp][i] = 0;
		}

	}
}


int* Graph::Dijkstras(int start)
{
	int distance[1000];
	int parent[1000];
	priority_queue <pair<int, int>> que;
	for (int i = 0; i < cntVertex; i++)
	{
		distance[i] = INT_MAX;
		parent[i] = -1;
	}
	distance[start] = 0;
	que.push(make_pair(0, start));

	while (!que.empty())
	{
		int top = que.top().second;
		int dist = que.top().first;
		que.pop();
		for (int i = 0; i < cntVertex; i++)
		{
			if (matrix[top][i] != 0 && dist + matrix[top][i] < distance[i])
			{
				distance[i] = dist + matrix[top][i];
				parent[i] = top;
				que.push(make_pair(distance[i], i));
			}
		}
	}
	return distance;
}


void Graph::bridgeUtil(int u, vector<bool>& visited, vector<int>& disc, vector<int>& low, int parent)
{
	static int time = 0;
	visited[u] = true;
	disc[u] = low[u] = ++time;

	for(int i = 0; i < cntVertex; i++)
	{
		if (matrix[u][i] != 0)
		{
			int v = i;   
			if (v == parent)
				continue;
			if (visited[v]) 
			{
				low[u] = min(low[u], disc[v]);
			}
			else 
			{
				parent = u;
				bridgeUtil(v, visited, disc, low, parent);
				low[u] = min(low[u], low[v]);
				if (low[v] > disc[u])
				{
					orderBridges[cntBridges] = new Edge(v, u);
					cntBridges++;
				}

			}
		}
		
	}
}

void Graph::bridge()
{
	vector<bool> visited(cntVertex, false);
	vector<int> disc(cntVertex, -1);
	vector<int> low(cntVertex, -1);

	int parent = -1;

	for (int i = 0; i < cntVertex; i++)
		if (visited[i] == false)
			bridgeUtil(i, visited, disc, low, parent);
}