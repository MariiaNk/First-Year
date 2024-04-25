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
		/*radius = other.radius;
		boldness = other.boldness;
		colorVertex = other.colorVertex;
		colorEdge = other.colorEdge;*/
		return other;
	}
};

ref class Graph
{
private:
	bool directedGraph, weightedGraph;
	viewGraph style;
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

	void changeStyle(viewGraph% newGraphStyle);
	void Graph::drawEdge(Graphics^ graf, Vertex* a, Vertex* b, int type);
	void redrawGraph(Graphics^ graf);
	void drawVertex(Graphics^ graf, Vertex* a, int numVertex, int type);
};
