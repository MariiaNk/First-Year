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
}


