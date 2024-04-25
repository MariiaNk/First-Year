#include "Graph.h"
#include <cmath>

Graph::Graph()
{
	point = gcnew array<Vertex*>(1000);
	idSelectedPoints = gcnew array<int>(1000);
	matrix = gcnew array<array<int>^>(1000);
	for (int i = 0; i < 1000; i++)
		matrix[i] = gcnew array<int>(1000);

	cntVertex = 0;
	cntEdge = 0;
	cntSelectedVertex = 0;
	directedGraph = false;
	weightedGraph = false;

	radius = 15;
	colorVertex = Brushes::LightGoldenrodYellow;
	colorEdge = Brushes::Crimson;
}

int distance(Vertex* a, Vertex* b)
{
	int distanceX = (a->x - b->x)* (a->x - b->x);
	int distanceY = (a->y - b->y) * (a->y - b->y);
	return sqrt(distanceX) + sqrt(distanceY);
}

System::String^ Graph::addVertex(Vertex* coord)
{
	int tempDistance = 0;
	for (int i = 0; i < cntVertex; i++)
	{
		tempDistance = distance(point[i], coord);
		if (tempDistance < 2 * radius)
		{
			idSelectedPoints[cntSelectedVertex] = i;
			cntSelectedVertex++;
			return " ";
		}
		else if (tempDistance < 3 * radius)
			return L"Не можна малювати вершини надто близько!";
	}

	point[cntVertex] = coord;
	cntVertex++;
	if (cntSelectedVertex > 0)
	{
		for (int i = 0; i < cntSelectedVertex; i++)
		{
			matrix[cntVertex][idSelectedPoints[i]] = -1;
			matrix[idSelectedPoints[i]][cntVertex] = -1;
		}
		cntSelectedVertex = 0;
	}
	return "";
}
