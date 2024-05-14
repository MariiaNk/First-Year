#pragma once
#include <fstream>
#include <iostream>

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
	int cntVertex;
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
	int cntEdges;
	cli::array <Edge*>^ allEdges;
	bool directedGraph, weightedGraph;
	Brush^ colorAlgoVertex;

	void cleanGraph();
	Graph();
	void addVertex(Vertex* coord);
	void unSelectVertex();
	void deleteSelectedVertex();
	void deleteSelectedEdge();
	bool conectedVertex(int numStart, int numFinish);
	bool checkSelectedVertex(int num);
	int ifClickVertex(Vertex* coord, int numCompare);
	Edge ifselectedEdge(Vertex* coord);
	System::String^ typeClick(Vertex* coord);
	void changeEdgeWeight(int st, int fn, int value);
	void findAllEdges();

	void dfs(int startPoint);
	void bfs(int startPoint);
	bool IsDirectedAntiCycle();
	bool HasCycle(int vertex, bool* visited, bool* inStack);
	void topologicalSort();

	void Graph::drawEdge(Graphics^ graf,Vertex* a, Vertex* b, int type, bool directed, int value);
	void redrawGraph(Graphics^ graf);
	void drawVertex(Graphics^ graf, Vertex* a, int numVertex, int type);

	void outputGraph(string path);
	void readGraph(string path);
};
