#include "Graph.h"
#include <cmath>

void Graph::drawVertex(Graphics^ graf, Vertex* a, int numVertex, int type)
{
	/* Types:
	1 - ordinary
	2 - selected
	3 - weight of edge
	*/
	switch (type)
	{
	case 1:
		graf->FillEllipse(colorVertex, a->x - radius, a->y - radius, 2 * radius, 2 * radius);
		graf->DrawEllipse(Pens::Black, a->x - radius, a->y - radius, 2 * radius, 2 * radius);
		break;
	case 2:
		graf->FillEllipse(Brushes::Red, a->x - radius, a->y - radius, 2 * radius, 2 * radius);
		graf->DrawEllipse(Pens::Black, a->x - radius, a->y - radius, 2 * radius, 2 * radius);
		break;
	case 3:
		graf->FillEllipse(Brushes::White, a->x - radius, a->y - radius, 2 * radius, 2 * radius);
		break;
	}

	System::String^ num = (numVertex + 1).ToString();
	Brush^ brush = gcnew SolidBrush(Color::Blue);
	graf->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;

	int padding;
	Font^ font = gcnew Font("Microsoft Sans Serif", 0.8 * radius, FontStyle::Bold);
	if (numVertex > 8) padding = round(0. * radius);
	else padding = round(0.5 * radius);
	graf->DrawString(num, font, brush, a->x - padding, a->y - padding);
}

void Graph::drawEdge(Graphics^ graf, Vertex* a, Vertex* b, int type)
{
	Pen^ pen;
	pen->Width = boldness;
	switch (type)
	{
	case 1:
		pen = gcnew Pen(colorEdge);
		break;
	case 2:
		pen = gcnew Pen(Brushes::Red);
		break;
	}
	graf->DrawLine(pen, a->x, a->y, b->x, b->y);
}
void Graph::redrawGraph(Graphics^ graf)
{
	for (int i = 0; i < cntVertex; i++)
	{
		for (int j = 0; j < cntVertex; j++)
		{
			if (matrix[i][j] == -1)
			{
				Vertex* st = point[i];
				Vertex* fn = point[j];
				drawEdge(graf, st, fn, 1);
			}

		}
	}
	for (int i = 0; i < cntVertex; i++)
	{
		drawVertex(graf, point[i], i + 1, 1);
	}
}

int distance(Vertex* a, Vertex* b)
{
	return sqrt(a->x * a->x - b->x * b->x) + sqrt(a->y * a->y - b->y * b->y);
}
System::String^ Graph::addVertex(Vertex* coord)
{
	for (int i = 0; i < cntVertex; i++)
	{
		if (distance(point[i], coord) < 3 * radius)
		{
			return L"Не можна малювати вершини надто близько!";
		}
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
}



