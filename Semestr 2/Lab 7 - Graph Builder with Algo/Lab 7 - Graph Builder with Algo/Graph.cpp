#include "Graph.h"
#include <cmath>
#include <queue>

void Graph::unSelectVertex()
{
	for (int i = 0; i < cntSelectedVertex; i++)
	{
		point[idSelectedPoints[i]]->marker = 0;
		idSelectedPoints[i] = -1;
	}
	cntSelectedVertex = 0;
}
void Graph::cleanGraph()
{
	for (int i = 0; i < 1000; i++)
	{
		point[i] = nullptr;
		idSelectedPoints[i] = -1;
		allEdges[i] = nullptr;
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

bool Graph::IsDirectedAntiCycle()
{
	bool visited[1000] = { false };
	bool inStack[1000] = { false }; 

	for (int i = 0; i < cntVertex; i++)
	{
		if (!visited[i] && HasCycle(i, visited, inStack))
		{
			return false;
		}
	}

	return true;
}

bool Graph::HasCycle(int vertex, bool* visited, bool* inStack)
{
	if (inStack[vertex])
		return true; // Cycle detected

	visited[vertex] = true;
	inStack[vertex] = true;

	for (int i = 0; i < cntVertex; i++)
	{
		if (matrix[vertex][i] != 0) // Check only outgoing edges for directedness
		{
			if (!visited[i] && HasCycle(i, visited, inStack))
				return true; // Cycle detected in child
		}
	}

	inStack[vertex] = false; // Backtrack
	return false;
}


void Graph::topologicalSort()
{
	int* indegree = new int[cntVertex];
	for (int i = 0; i < cntVertex; i++)
	{
		indegree[i] = 0;
	}

	for (int i = 0; i < cntVertex; i++)
	{
		for (int j = 0; j < cntVertex; j++)
		{
			if (matrix[j][i] != 0 || matrix[j][i] != 0)
			{
				indegree[i]++;
			}
		}
	}
	queue <int> q;
	for (int i = 0; i < cntVertex; i++)
	{
		if (indegree[i] == 0)
			q.push(i);
	}

	while (!q.empty())
	{
		int currentNode = q.front();
		q.pop();
		orderAlgo.Add(currentNode);
		cntElemInOrder++;
		for (int i = 0; i < cntVertex; i++)
		{
			if (matrix[currentNode][i] != 0 || matrix[i][currentNode] != 0)
			{
				indegree[i]--;
				if (indegree[i] == 0)
					q.push(i);
			}
		}
	}
}