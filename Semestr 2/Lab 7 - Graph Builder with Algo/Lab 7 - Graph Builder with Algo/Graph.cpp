#include "Graph.h"
#include <cmath>


void Graph::unSelectVertex()
{
	for (int i = 0; i < cntSelectedVertex; i++)
	{
		point[idSelectedPoints[i]]->selected = false;
		idSelectedPoints[i] = -1;
	}
	cntSelectedVertex = 0;
}


Graph::Graph()
{
	point = gcnew array<Vertex*>(1000);
	idSelectedPoints = gcnew array<int>(1000);
	matrix = gcnew array<array<int>^>(1000);
	for (int i = 0; i < 1000; i++)
		matrix[i] = gcnew array<int>(1000);
	for (int i = 0; i < 1000; i++)
	{
		idSelectedPoints[i] = -1;
		for (int j = 0; j < 1000; j++)
			matrix[i][j] = 0;
	}
		
	cntVertex = 0;
	cntEdge = 0;
	directedGraph = false;
	weightedGraph = false;

}

int distance(Vertex* a, Vertex* b)
{
	int distanceX = (a->x - b->x)* (a->x - b->x);
	int distanceY = (a->y - b->y) * (a->y - b->y);
	return sqrt(distanceX) + sqrt(distanceY);
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
		}
	}
	return selected;
}

int Graph::checkClickCoord(Vertex* coord)
{
	/*
	num - select vertex
	-1 - can't draw vertex
	-2 - free space
	*/
	int tempDistance = 0;
	for (int i = 0; i < cntVertex; i++)
	{
		tempDistance = distance(point[i], coord);
		if (tempDistance < 2 * style.radius)
			return i;
		else if (tempDistance < 3 * style.radius)
			return -1;
	}
	return -2;
}
System::String^ Graph::typeClick(Vertex* coord)
{
	int numVertex = checkClickCoord(coord);
	if(numVertex == -1) return L"Не можна малювати вершини надто близько!";
	if (numVertex == -2)
	{
		addVertex(coord);
		return " ";
	}

	if (checkSelectedVertex(numVertex))
	{
		idSelectedPoints[cntSelectedVertex] = numVertex;
		point[numVertex]->selected = true;
		cntSelectedVertex++;
	}
	else unSelectVertex();
	return " ";

	
}

