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

	int paddingX, paddingY = round(0.5 * radius);
	Font^ font = gcnew Font("Microsoft Sans Serif", 0.8 * radius, FontStyle::Bold);
	if (numVertex > 8) paddingX = round(0.8 * radius);
	else paddingX = round(0.5 * radius);
	graf->DrawString(num, font, brush, a->x - paddingX, a->y - paddingY);
}


void Graph::drawEdge(Graphics^ graf, Vertex* a, Vertex* b, int type)
{
	Pen^ pen;
	switch (type)
	{
		case 1:
			pen = gcnew Pen(colorEdge);
			break;
		case 2:
			pen = gcnew Pen(Brushes::Red);
			break;
	}
	pen->Width = boldness;
	graf->DrawLine(pen, a->x, a->y, b->x, b->y);
}

void Graph::redrawGraph(Graphics^ graf)
{
	for (int i = 0; i < cntVertex; i++)
	{
		for (int j = 0; j < cntVertex; j++)
		{
			if (matrix[i][j] == 1)
			{
				Vertex* st = point[i];
				Vertex* fn = point[j];
				drawEdge(graf, st, fn, 1);
			}

		}
	}
	int type = 1;
	for (int i = 0; i < cntVertex; i++)
	{
		type = (point[i]->selected) ? 2 : 1;
		drawVertex(graf, point[i], i, type);
	}
}





