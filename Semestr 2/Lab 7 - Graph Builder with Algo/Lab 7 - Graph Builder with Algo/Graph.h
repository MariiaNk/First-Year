#pragma once

using namespace std;
using namespace System::Drawing;
using namespace System::Collections::Generic;

struct Vertex
{
	int x;
	int y;
	int marker;
	Vertex(int x = 0, int y = 0, int marker = 0) : x(x), y(y), marker(marker) {}
	Vertex* operator= (const Vertex* other)
	{
		x = other->x;
		y = other->y;
		marker = other->marker;
		return this;
	}
	
	
};
struct Edge
{
	int start;
	int end;
	Edge(int start = -1, int end = -1): start(start), end(end) {}
	bool nonEdge()
	{
		return start == -1 && end == -1;
	}
};
ref struct viewGraph
{
	Brush^ colorVertex;
	Brush^ colorEdge;
	int radius, boldness;
	viewGraph()
	{
		radius = 15;
		boldness = 8;
		colorVertex = Brushes::Gold;
		colorEdge = Brushes::Goldenrod;
	}
	viewGraph% operator= (viewGraph% other)
	{
		radius = other.radius;
		boldness = other.boldness;
		colorVertex = other.colorVertex;
		colorEdge = other.colorEdge;
		return *this;
	}
};

ref class Graph
{
private:
	bool directedGraph, weightedGraph;
	int cntVertex;
	//cntEdge;
	void dfsRec(int startNode, bool* visited);
public:
	viewGraph style;
	cli::array<Vertex*>^ point;
	Edge* selectedEdge;
	cli::array <int>^ idSelectedPoints;
	int cntSelectedVertex;
	cli::array<cli::array<int>^>^ matrix;
	int cntElemInOrder;
	List <int> orderAlgo;
	Graph();
	void addVertex(Vertex* coord);
	void unSelectVertex();
	void deleteSelectedVertex();
	void deleteSelectedEdge();
	bool conectedVertex(int numStart, int numFinish);
	bool checkSelectedVertex(int num);
	int ifClickVertex(Vertex* coord);
	Edge ifselectedEdge(Vertex* coord);
	System::String^ typeClick(Vertex* coord);

	void dfs(int startPoint);

	void Graph::drawEdge(Graphics^ graf,Vertex* a, Vertex* b, int type, bool directed);
	void redrawGraph(Graphics^ graf);
	void drawVertex(Graphics^ graf, Vertex* a, int numVertex, int type);
};
