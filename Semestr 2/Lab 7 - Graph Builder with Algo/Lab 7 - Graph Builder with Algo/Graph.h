#pragma once

using namespace std;
using namespace System::Drawing;

struct Vertex
{
	int x;
	int y;
	bool selected;
	Vertex(int x = 0, int y = 0, bool selected = false) : x(x), y(y), selected(selected) {}
	
};
ref class Graph
{
private:
	bool directedGraph, weightedGraph;
	Brush^ colorVertex;
	Brush^ colorEdge;
	int radius, boldness;
	int cntVertex, cntEdge;
public:
	cli::array<Vertex*>^ point;
	cli::array <int>^ idSelectedPoints;
	int cntSelectedVertex;
	cli::array<cli::array<int>^>^ matrix;
	Graph();
	void addVertex(Vertex* coord);
	void unSelectVertex();
	bool conectedVertex(int numStart, int numFinish);
	bool checkSelectedVertex(int num);
	System::String^ typeClick(Vertex* coord);

	void Graph::drawEdge(Graphics^ graf, Vertex* a, Vertex* b, int type);
	void redrawGraph(Graphics^ graf);
	void drawVertex(Graphics^ graf, Vertex* a, int numVertex, int type);
};
