#include "Graph.h"
#include <cmath>
#include <vector>

void Graph::drawVertex(Graphics^ graf, Vertex* a, int numVertex, int type)
{
	/* Types:
	-1 - previous algo
	0 - ordinary
	1 - selected
	num - weight of edge
	*/
	switch (type)
	{
	case -1:
		graf->FillEllipse(Brushes::YellowGreen, a->x - style.radius, a->y - style.radius, 2 * style.radius, 2 * style.radius);
		graf->DrawEllipse(Pens::Black, a->x - style.radius, a->y - style.radius, 2 * style.radius, 2 * style.radius);
		break;
	case 0:
		graf->FillEllipse(style.colorVertex, a->x - style.radius, a->y - style.radius, 2 * style.radius, 2 * style.radius);
		graf->DrawEllipse(Pens::Black, a->x - style.radius, a->y - style.radius, 2 * style.radius, 2 * style.radius);
		break;
	case 1:
		graf->FillEllipse(Brushes::Red, a->x - style.radius, a->y - style.radius, 2 * style.radius, 2 * style.radius);
		graf->DrawEllipse(Pens::Black, a->x - style.radius, a->y - style.radius, 2 * style.radius, 2 * style.radius);
		break;
	case 3:
		graf->FillEllipse(Brushes::White, a->x - style.radius, a->y - style.radius, 2 * style.radius, 2 * style.radius);
		break;
	}

	System::String^ num = (numVertex + 1).ToString();
	Brush^ brush = gcnew SolidBrush(Color::Blue);
	graf->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;

	int paddingX, paddingY = round(0.5 * style.radius);
	Font^ font = gcnew Font("Microsoft Sans Serif", 0.8 * style.radius, FontStyle::Bold);
	if (numVertex > 8) paddingX = round(0.8 * style.radius);
	else paddingX = round(0.5 * style.radius);
	graf->DrawString(num, font, brush, a->x - paddingX, a->y - paddingY);
}
//посунемо кінець щоб стрілочка була не під вершиною
void moveEndForCap(Vertex &start, Vertex &end, int radius)
{
	int lenX = abs(start.x - end.x);
	int lenY = abs(start.y - end.y);
	int len_edge = sqrt(lenX * lenX + lenY * lenY);

	int cof_x = lenX * radius / len_edge;
	if (start.x > end.x)
	{
		start.x -= cof_x;
		end.x += cof_x;
	}
	else
	{
		start.x += cof_x;
		end.x -= cof_x;
	}

	int cof_y = lenY * radius / len_edge;
	if (start.y > end.y)
	{
		start.y -= cof_y;
		end.y += cof_y;
	}
	else
	{
		start.y += cof_y;
		end.y -= cof_y;
	}
}

void Graph::drawEdge(Graphics^ graf,Vertex* a, Vertex* b, int type, bool directed)
{
	Pen^ pen;
	switch (type)
	{
		case 1:
			pen = gcnew Pen(style.colorEdge);
			break;
		case 2:
			pen = gcnew Pen(Brushes::Red);
			break;
	}
	pen->Width = style.boldness;
	Vertex st = *a;
	Vertex fn = *b;
	if (directed)
	{
		pen->EndCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;
		moveEndForCap(st, fn, style.radius);
	}
	
	graf->DrawLine(pen, st.x, st.y, fn.x, fn.y);
}

void Graph::redrawGraph(Graphics^ graf)
{
	graf->Clear(Color::White);
	for (int i = 0; i < cntVertex; i++)
	{
		for (int j = i + 1; j < cntVertex; j++)
		{
			if (matrix[i][j] == 1 || matrix[j][i] == 1)
			{
				Vertex* st = point[i];
				Vertex* fn = point[j];
				bool directed = true;
				if (matrix[i][j] == 1 && matrix[j][i] == 1) directed = false;
				if (directed && matrix[i][j] == 0) swap(st, fn);
				drawEdge(graf, st, fn, 1, directed);
			}

		}
	}
	if (selectedEdge != nullptr)
	{
		int i = selectedEdge->start;
		int j = selectedEdge->end;
		Vertex* st = point[i];
		Vertex* fn = point[j];
		
		bool directed = true;
		if (matrix[i][j] == 1 && matrix[j][i] == 1) directed = false;
		if (directed && matrix[i][j] == 0) swap(st, fn);

		drawEdge(graf, st, fn, 2, directed);
	}
	int type = 1;
	for (int i = 0; i < cntVertex; i++)
	{
		drawVertex(graf, point[i], i, point[i]->marker);
	}
}



