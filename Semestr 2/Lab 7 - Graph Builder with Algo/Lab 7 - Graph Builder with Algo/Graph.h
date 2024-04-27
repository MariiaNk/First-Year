#pragma once

using namespace std;
using namespace System::Drawing;

struct Vertex
{
	int x;
	int y;
	bool selected;
	Vertex(int x = 0, int y = 0, bool selected = false) : x(x), y(y), selected(selected) {}
	Vertex* operator= (const Vertex* other)
	{
		x = other->x;
		y = other->y;
		selected = other->selected;
		return this;
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
	int cntVertex, cntEdge;
public:
	viewGraph style;
	cli::array<Vertex*>^ point;
	cli::array <int>^ idSelectedPoints;
	int cntSelectedVertex;
	cli::array<cli::array<int>^>^ matrix;
	Graph();
	void addVertex(Vertex* coord);
	void unSelectVertex();
	bool conectedVertex(int numStart, int numFinish);
	bool checkSelectedVertex(int num);
	int checkClickCoord(Vertex* coord);
	System::String^ typeClick(Vertex* coord);

	void Graph::drawEdge(Graphics^ graf, Vertex* a, Vertex* b, int type);
	void redrawGraph(Graphics^ graf);
	void drawVertex(Graphics^ graf, Vertex* a, int numVertex, int type);
};
