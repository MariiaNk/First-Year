#include "settings_graph.h"
#include <iostream>
#include <string>

using namespace System;
using namespace System::Drawing;
using namespace std;

bool change = false;

System::Void GraphBuilder::settings_graph::redraw_graph()
{
	
	int st_x = 50, st_y = 250, fn_x = 250, fn_y = 50;
	int temp = 1;

	Brush^ pen_cl = MainForm->edge_color;
	Pen^ pen = gcnew Pen(pen_cl);
	pen->Width =  MainForm->boldness;
	Brush^ cl = MainForm->vertex_color;
	Graphics^ graf = pictureBox1->CreateGraphics();
	Brush^ brush = gcnew SolidBrush(Color::Blue);

	graf->Clear(Color::Azure);
	System::Drawing::Font^ font = gcnew System::Drawing::Font("Microsoft Sans Serif", 0.8 * MainForm->R, FontStyle::Bold);

	graf->DrawLine(pen, st_x, st_y, fn_x, fn_y);

	graf->FillEllipse(cl, st_x - MainForm->R, st_y - MainForm->R, 2 * MainForm->R, 2 * MainForm->R);
	graf->DrawEllipse(Pens::Black, st_x - MainForm->R, st_y - MainForm->R, 2 * MainForm->R, 2 * MainForm->R);
	graf->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;
	graf->DrawString(temp.ToString(), font, brush, st_x - round(0.5 * MainForm->R), st_y - (round(0.5 * MainForm->R)));

	graf->FillEllipse(cl, fn_x - MainForm->R, fn_y - MainForm->R, 2 * MainForm->R, 2 * MainForm->R);
	graf->DrawEllipse(Pens::Black, fn_x - MainForm->R, fn_y - MainForm->R, 2 * MainForm->R, 2 * MainForm->R);
	graf->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;
	graf->DrawString((temp+1).ToString(), font, brush, fn_x - round(0.5 * MainForm->R), fn_y - (round(0.5 * MainForm->R)));
}

System::Void GraphBuilder::settings_graph::settings_graph_Load(System::Object^ sender, System::EventArgs^ e)
{
	timer1->Start();
	change = true;
	choose_radius->Minimum = (int)(MainForm->boldness * 4 / 3);
	choose_radius->Maximum = MainForm->max_radius;
	choose_boldness->Minimum = 1;
	choose_boldness->Maximum = (int)(MainForm->max_radius * 3 / 4);

}

System::Void GraphBuilder::settings_graph::choose_radius_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	MainForm->R = choose_radius->Value;
	choose_boldness->Maximum = (int)(MainForm->max_radius * 3 / 4);
	change = true;
}

System::Void GraphBuilder::settings_graph::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
	if (change)
	{
		change = false;
		redraw_graph();
	}
}

System::Void GraphBuilder::settings_graph::color_edge_Click(System::Object^ sender, System::EventArgs^ e)
{
	colorDialog1->ShowDialog();
	Color dia_color = colorDialog1->Color;
	SolidBrush^ temp = gcnew SolidBrush(dia_color);
	MainForm->edge_color = temp;
	change = true;
}

System::Void GraphBuilder::settings_graph::choose_boldness_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	MainForm->boldness = choose_boldness->Value;
	choose_radius->Minimum = (int)(MainForm->boldness * 4 / 3);
	change = true;
}

System::Void GraphBuilder::settings_graph::color_vertex_Click(System::Object^ sender, System::EventArgs^ e)
{
	colorDialog1->ShowDialog();
	Color dia_color = colorDialog1->Color;
	SolidBrush^ temp = gcnew SolidBrush(dia_color);
	MainForm->vertex_color = temp;
	change = true;
}

System::Void GraphBuilder::settings_graph::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	MainForm->change = true;
	settings_graph::Close();
}
