#pragma once
#include "Main.h"
#include "weighted_graph_edge.h"
#include "input_weighted_edge.h"
#include "settings_graph.h"
#include <msclr\marshal_cppstd.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <queue>

using namespace System::Threading;
using namespace System::Drawing::Drawing2D;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;
using namespace System::Media;
using namespace System::IO;

struct vertex
{
	int x = 0;
	int y = 0;
	bool selected = false;
} point[1000];

struct BridgeVertex {
	int exit = 0;
	int entrance = 0;
	int parent = -1;
	int color = 0;
	// 0 - white; 1 - grey; 2 - black;
} BridgePoint[1000];

struct TMinLen
{
	int len = INT_MAX;
	int parent = -1;
}Way[1000];

bool SelectedEdge[1000][1000] = { 0 }, FlagSelectedEdge = false;
int id_selected_point = -1;
bool scroll = false, isMouseDown = false;
bool weighted_graph = false, DfsAlgo = false, EulerWayAlgo = false, TopologicalAlgo = false, LookingForBridgeAlgo = false, DejkstraAlgo = false;
int min_adge = 1000000000;
bool visited[1000];
stack <int>  mystack;
int cnt_small_graph = 0, cnt_edge = 0;
int copy_matrix[1000][1000] = { 0 }, Color[1000] = { 0 };

vector <int> TempVector;
int CntClick = 0, BridgeTimer = 0;
int StepAlgo = 0;


[STAThread]
void Main() {
	Application::EnableVisualStyles();	Application::SetCompatibleTextRenderingDefault(false);
	GraphBuilder::Main form;
	Application::Run(% form);

}
void DeleteSelected(int N)
{
	FlagSelectedEdge = false;
	id_selected_point = -1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			SelectedEdge[i][j] = false;
		}
		point[i].selected = false;
	}
}

pair <int, int> IdSelected(int N)
{
	if (!FlagSelectedEdge) return { -1, -1 };
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (SelectedEdge[i][j]) return { i, j };
		}
	}
}
long long pov(int a)
{
	return a * a;
}
int check_vertex(vertex a, int rad, vertex skip, int cnt_point)
{
	int i = 0;
	if (skip.x == point[i].x && skip.y == point[i].y) i++;
	while (i < cnt_point && pov(a.x - point[i].x) + pov(a.y - point[i].y) > pov(rad))
	{
		i++;
		if (skip.x == point[i].x && skip.y == point[i].y) i++;
	}
	if (i >= cnt_point) return -1;
	return i;
}
int dist(vertex point, int a, int b, int c)
{
	return abs(a * point.x + b * point.y + c) / sqrt(pov(a) + pov(b));
} 
pair<int, int> check_edge(vertex a, int bold_edge, int ** matrix, int cnt_point, int R)
{
	int r_edge = (bold_edge/2 + R);
	for (int i = 0; i < cnt_point; i++)
	{
		vertex b = point[i];
		for (int j = i + 1; j < cnt_point; j++)
		{
			if (matrix[i][j] != 0 || matrix[j][i] != 0)
			{
				vertex c = point[j];

				int k_a = (c.y - b.y);
				int k_b = (b.x - c.x);
				int k_c = (c.x * b.y - b.x * c.y);

				int rule_edge = dist(a, k_a, k_b, k_c);
				
				/*MessageBox::Show(rule_edge.ToString() + "<=" + (r_edge).ToString() + "\n" + min(b.x, c.x).ToString() + "<" + a.x.ToString() + "\n" + (b.x, c.x).ToString() + ">" + a.x.ToString() + "\n" + min(b.y, c.y).ToString() + "<" + a.y.ToString() + "\n" + max(b.y, c.y).ToString() + ">" + a.y.ToString());*/
				if (rule_edge <= r_edge && (min(b.x, c.x) - r_edge  <= a.x && max(b.x, c.x)  + r_edge >= a.x) && (min(b.y, c.y) - r_edge <= a.y && max(b.y, c.y) + r_edge >= a.y))
				{
					if(matrix[i][j] != 0) return { i,j };
					else return { j, i };
				}
			}
		}
	}
	return { -1, -1 };


}
void draw_vertex(Graphics ^graf,vertex a, int id_a, Brush ^ cl, int R)
{
	Font ^ font = gcnew Font("Microsoft Sans Serif", 0.8*R, FontStyle::Bold);
	graf->FillEllipse(cl, a.x - R, a.y - R, 2 * R, 2 * R);
	if(cl != Brushes::White) graf->DrawEllipse(Pens::Black, a.x - R, a.y - R, 2 * R, 2 * R);
	String^ num = (id_a+1).ToString();
	Brush^ brush = gcnew SolidBrush(Color::Blue);
	graf->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;
	if (id_a > 8) graf->DrawString(num, font, brush, a.x - round(0.8 * R), a.y - round(0.5 * R));
	else graf->DrawString(num, font, brush, a.x - round(0.5*R), a.y - (round(0.5 * R)));
	
}
void swap(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}
void draw_edge(Graphics^ graf, int** matrix, int st, int fn, Brush^ cl, int bold, int R, bool directed_graph)
{
	Pen^ pen = gcnew Pen(cl);
	pen->Width = bold;
	
	
	if(directed_graph && matrix[st][fn] != matrix[fn][st])
	{
		int len_x = abs(point[st].x - point[fn].x);
		int len_y = abs(point[st].y - point[fn].y);
		int len_edge = sqrt(len_x * len_x + len_y * len_y);

		min_adge = min(min_adge, len_edge);
		pen->EndCap = LineCap::ArrowAnchor;
		if (matrix[st][fn] == 0)
			swap(st, fn);
		vertex start, finish;
		int cof_x = len_x * R / len_edge;
		if (point[st].x > point[fn].x)
		{
			start.x = point[st].x - cof_x;
			finish.x = point[fn].x + cof_x;
		}
		else
		{
			start.x = point[st].x + cof_x;
			finish.x = point[fn].x - cof_x;
		}

		int cof_y = len_y * R / len_edge;
		if (point[st].y > point[fn].y)
		{
			start.y = point[st].y - cof_y;
			finish.y = point[fn].y + cof_y;
		}
		else
		{
			start.y = point[st].y + cof_y;
			finish.y = point[fn].y - cof_y;
		}
		graf->DrawLine(pen, start.x, start.y, finish.x, finish.y);
	}
	else graf->DrawLine(pen, point[st].x, point[st].y, point[fn].x, point[fn].y);
	
	if (weighted_graph && matrix[st][fn] != -1)
	{
		vertex temp;
		temp.x = (point[st].x + point[fn].x) / 2;
		temp.y = (point[st].y + point[fn].y) / 2;
		int weight = matrix[st][fn] - 1;
		draw_vertex(graf, temp, weight, Brushes::White, R);
	}
}
System::Void GraphBuilder::Main::Main_Load(System::Object^ sender, System::EventArgs^ e) {
	Main::Height = 566;
	timer1->Start();
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			matrix[i][j] = 0;
		}
	}
	about_graph->Rows->Add(L"К-сть вершин", "0");
	about_graph->Rows->Add(L"К-сть ребер", "0");
	about_graph->Rows->Add(L"Зважений", "False");
	about_graph->Rows->Add(L"Орієнтований", "False");
}
System::Void GraphBuilder::Main::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	int pen_r = GraphBuilder::Main::boldness;
	Brush^ pen_cl = GraphBuilder::Main::edge_color;
	Graphics^ graf = pictureBox1->CreateGraphics();

	if (LookingForBridgeAlgo) change = true;
	isMouseDown = false;
	
	if (scroll)
	{
		scroll = false;
		point[id_selected_point].selected = false;
		id_selected_point = -1;
		change = true;
	}
	else
	{
		warning_label->Text = "";
		vertex temp = { e->X, e->Y };
		/*temp.x = e->X;
		temp.y = e->Y;*/
		int rule_vertex = -1;
		pair<int, int> rule_edge = { -1, -1 };

		if (cnt_point != 0)
			rule_vertex = check_vertex(temp, 3 * R, { -1, -1 }, cnt_point);
		if (cnt_edge != 0)
			rule_edge = check_edge(temp, pen_r, matrix, cnt_point, R);
		if (rule_vertex == -1 && rule_edge.first == -1)
		{
			//Not selected---------------------------------------------------------------------------------
			int max_x = pictureBox1->Width, max_y = pictureBox1->Height;
			if (temp.x > 1.5 * R && temp.y > 1.5 * R && (temp.x < max_x - 1.5 * R) && (temp.y < max_y - 1.5 * R))
			{
				point[cnt_point] = temp;
				if (id_selected_point != -1)
				{
					matrix[id_selected_point][cnt_point] = -1;
					matrix[cnt_point][id_selected_point] = -1;

					if (weighted_graph)
					{
						input_weighted_edge^ f2 = gcnew input_weighted_edge(this);
						f2->Show();
						Main::Hide();
					}

					draw_edge(graf, matrix, id_selected_point, cnt_point, pen_cl, pen_r, R, directed_graph);
					cnt_edge++;
					about_graph[1, 1]->Value = cnt_edge.ToString();
					point[id_selected_point].selected = false;
					draw_vertex(graf, point[id_selected_point], id_selected_point, GraphBuilder::Main::vertex_color, R);
					id_selected_point = -1;
				}
				draw_vertex(graf, point[cnt_point], cnt_point, GraphBuilder::Main::vertex_color, R);
				cnt_point++;
				about_graph[1, 0]->Value = cnt_point.ToString();
			}
			else
			{
				SystemSounds::Beep->Play();
				warning_label->Text = L"Не можна намалювати вершину надто близько до межі!";
				change = true;

			}

		}
		else if (rule_edge.first != -1 || rule_vertex != -1)
		{
			rule_vertex = check_vertex(temp, R, { -1, -1 }, cnt_point);
			if (rule_vertex > -1)
			{
				//Selected vertex---------------------------------------------------------------------------------
				if (id_selected_point != -1)
				{
					//Selected two vertex---------------------------------------------------------------------------------
					if (matrix[rule_vertex][id_selected_point] == 0 && matrix[id_selected_point][rule_vertex] == 0)
					{
						if (FlagSelectedEdge)
						{
							DeleteSelected(cnt_point);
							redraw_graph(graf);
						}
						matrix[id_selected_point][rule_vertex] = -1;
						matrix[rule_vertex][id_selected_point] = -1;

						if (weighted_graph)
						{
							input_weighted_edge^ f2 = gcnew input_weighted_edge(this);
							f2->Show();
							Main::Hide();
						}

						draw_edge(graf, matrix, id_selected_point, rule_vertex, pen_cl, pen_r, R, directed_graph);
						cnt_edge++;
						about_graph[1, 1]->Value = cnt_edge.ToString();
						draw_vertex(graf, point[id_selected_point], id_selected_point, GraphBuilder::Main::vertex_color, R);
						point[id_selected_point].selected = false;
						draw_vertex(graf, point[rule_vertex], rule_vertex, GraphBuilder::Main::vertex_color, R);
						id_selected_point = -1;
					}
				}
				else
				{
					if (FlagSelectedEdge)
					{
						DeleteSelected(cnt_point);
						redraw_graph(graf);
					}

					id_selected_point = rule_vertex;
					point[id_selected_point].selected = true;
					draw_vertex(graf, point[id_selected_point], id_selected_point, Brushes::Red, R);
				}
			}
			else if (rule_edge.first != -1)
			{
				/*MessageBox::Show("Ok");*/
				if (FlagSelectedEdge)
				{
					DeleteSelected(cnt_point);
					redraw_graph(graf);
				}

				SelectedEdge[rule_edge.first][rule_edge.second] = true;
				if(!directed_graph)SelectedEdge[rule_edge.second][rule_edge.first] = true;
				FlagSelectedEdge = true;
				redraw_graph(graf);


			}

		}
		
	}

	//pictureBox1->BackColor = Color::Red;
}
System::Void GraphBuilder::Main::redraw_graph(Graphics^ graf)
{
	cnt_edge = 0;
	int pen_r = GraphBuilder::Main::boldness;
	Brush^ pen_cl = GraphBuilder::Main::edge_color;
	graf->Clear(Color::White);
	int st, fn;/*
	MessageBox::Show(L"Малюю");*/
	for (int i = 0; i < cnt_point; i++)
	{
		for (int j = i + 1; j < cnt_point; j++)
		{ 
			if (matrix[i][j] != 0)
			{
				if (matrix[i][j] == -1 && weighted_graph && weight_edge != 0)
				{
					if(matrix[i][j] == matrix[j][i])matrix[j][i] = weight_edge;
					matrix[i][j] = weight_edge;
					weight_edge = 0;
					
					if(SelectedEdge[i][j]) draw_edge(graf, matrix, i, j, Brushes::Red, pen_r, R, directed_graph);
					else draw_edge(graf, matrix, i, j, pen_cl, pen_r, R, directed_graph);
					cnt_edge++;
				}
				else 
				{
					if (SelectedEdge[i][j]) draw_edge(graf, matrix, i, j, Brushes::Red, pen_r, R, directed_graph);
					else draw_edge(graf, matrix, i, j, pen_cl, pen_r, R, directed_graph);
					cnt_edge++;
				}
			}
			else if (matrix[j][i] != 0)
			{
				if (matrix[j][i] == -1 && weighted_graph && weight_edge != 0)
				{
					matrix[j][i] = weight_edge;
					weight_edge = 0;
					if (SelectedEdge[j][i]) draw_edge(graf, matrix, j, i, Brushes::Red, pen_r, R, directed_graph);
					else draw_edge(graf, matrix, j, i, pen_cl, pen_r, R, directed_graph);
					cnt_edge++;
				}
				else 
				{
					if (SelectedEdge[j][i]) draw_edge(graf, matrix, j, i, Brushes::Red, pen_r, R, directed_graph);
					else draw_edge(graf, matrix, j, i, pen_cl, pen_r, R, directed_graph);
					cnt_edge++;
				}
			}

		}
	}
	for (int i = 0; i < cnt_point; i++)
	{
		if(point[i].selected) draw_vertex(graf,point[i], i, Brushes::Red, R);
		else draw_vertex(graf,point[i], i, vertex_color, R);
	}

	about_graph[1, 1]->Value = cnt_edge.ToString();
	about_graph[1, 0]->Value = cnt_point.ToString();
	if (weighted_graph) about_graph[1, 2]->Value = "True";
	else about_graph[1, 2]->Value = "False";
	if (directed_graph) about_graph[1, 3]->Value = "True";
	else about_graph[1, 3]->Value = "False";
}
System::Void GraphBuilder::Main::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
	
	if (change)
	{
		if (!Main::Visible) Main::Show();
		else
		{
			change = false;
			if (DejkstraAlgo && !TempVector.empty())
			{
				//MessageBox::Show((TempVector[StepAlgo]).ToString() + " " + (TempVector[StepAlgo - 1]).ToString());
				SelectedEdge[TempVector[StepAlgo]][TempVector[StepAlgo-1]] = true;
				if(!directed_graph) SelectedEdge[TempVector[StepAlgo - 1]][TempVector[StepAlgo]] = true;
				StepAlgo--;
				if(StepAlgo == 0) point[TempVector[0]].selected = true;
				else if (StepAlgo == -1)
				{
					//MessageBox::Show(L"Кінець");
					timer1->Interval = 50;
					DejkstraAlgo = false;
					DeleteSelected(cnt_point);
					ClearAlgo();
				}

			}
			else 
			{
				
				LookingForBridgeAlgo = false;
			}

			if (StepAlgo != -1)
			{
				Graphics^ graf = pictureBox1->CreateGraphics();
				redraw_graph(graf);
			}
			if (DejkstraAlgo && !TempVector.empty() && StepAlgo != 0) change = true;
			

			
		}
	}
}
System::Void GraphBuilder::Main::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	vertex temp;
	temp.x = e->X;
	temp.y = e->Y;
	int rule = check_vertex(temp, R, {-1, -1}, cnt_point);
	if(rule == id_selected_point && id_selected_point != -1)isMouseDown = true;
	 
}
System::Void GraphBuilder::Main::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (isMouseDown)
	{
		vertex temp;
		temp.x = e->X;
		temp.y = e->Y;
		temp.selected = true;
		int max_x = pictureBox1->Width, max_y = pictureBox1->Height;
		if (temp.x > 1.5 * R && temp.y > 1.5 * R && (temp.x < max_x - 1.5 * R) && (temp.y < max_y - 1.5 * R))
		{
			int rule = check_vertex(temp, 3 * R, point[id_selected_point], cnt_point);
			/*MessageBox::Show(L"Помилка");*/
			int len_x = abs(point[id_selected_point].x - temp.x);
			int len_y = abs(point[id_selected_point].y - temp.y);
			int check_len = sqrt(len_x * len_x + len_y * len_y);
			if(check_len > R)
			{
				if (rule == -1 || rule == id_selected_point)
				{
					scroll = true;
					point[id_selected_point] = temp;
					change = true;

				}
				else
				{
					SystemSounds::Beep->Play();
					warning_label->Text = L"Не можна пересувати вершини надто близько!";
					isMouseDown = false;
					point[id_selected_point].selected = false;
					id_selected_point = -1;
					change = true;
				}
			}
		}
		else
		{
			SystemSounds::Beep->Play();
			warning_label->Text = L"Не можна пересувати вершину надто близько до межі!";
		}
		
	}
	
}
System::Void GraphBuilder::Main::Main_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Back )
	{
		if (id_selected_point > -1)
		{
			for (int i = id_selected_point + 1; i < cnt_point; i++)
			{
				for (int j = 0; j < cnt_point; j++)
				{
					matrix[i - 1][j] = matrix[i][j];
				}
			}
			for (int i = 0; i < cnt_point; i++)
			{
				matrix[cnt_point - 1][i] = 0;
			}
			for (int i = id_selected_point + 1; i < cnt_point; i++)
			{
				for (int j = 0; j < cnt_point - 1; j++)
				{
					matrix[j][i - 1] = matrix[j][i];
				}
			}
			for (int i = 0; i < cnt_point; i++)
			{
				matrix[i][cnt_point - 1] = 0;
			}
			for (int i = id_selected_point + 1; i < cnt_point; i++)
			{
				point[i - 1] = point[i];
			}
			point[cnt_point - 1] = { 0,0 };

			cnt_point--;
			about_graph[1, 0]->Value = cnt_point.ToString();

			id_selected_point = -1;
			//MessageBox::Show(cnt_point.ToString());
			change = true;
		}
		else if (FlagSelectedEdge)
		{
			pair <int, int> Selected = IdSelected(cnt_point);
			matrix[Selected.first][Selected.second] = 0;
			matrix[Selected.second][Selected.first] = 0;
			cnt_edge--;
			about_graph[1, 1]->Value = cnt_edge.ToString();
			DeleteSelected(cnt_point);
			change = true;
		}
	}
	if (directed_graph && FlagSelectedEdge)
	{
		//change directed graph
		pair <int, int> Selected = IdSelected(cnt_point);
		int st = Selected.first;
		int fn = Selected.second;
		if (e->KeyCode == Keys::Up)
		{
			DeleteSelected(cnt_point);
			if (st > fn) swap(st, fn);
			if (matrix[st][fn] == 0) matrix[st][fn] = matrix[fn][st];
			matrix[fn][st] = 0;
			change = true;
		}
		if (e->KeyCode == Keys::Down)
		{
			DeleteSelected(cnt_point);
			if (st < fn) swap(st, fn);
			if (matrix[st][fn] == 0) matrix[st][fn] = matrix[fn][st];
			matrix[fn][st] = 0;
			change = true;
		}
		if (e->KeyCode == Keys::N)
		{
			DeleteSelected(cnt_point);
			if (matrix[st][fn] == 0) matrix[st][fn] = matrix[fn][st];
			else matrix[fn][st] = matrix[st][fn];
			change = true;
		}


	}
	if (weighted_graph && FlagSelectedEdge)
	{
		//change weight edge in  graph
		pair <int, int> Selected = IdSelected(cnt_point);
		int st = Selected.first;
		int fn = Selected.second;
		if (e->KeyCode == Keys::Space)
		{
			if (matrix[st][fn] == 0 && matrix[fn][st] != 0) matrix[fn][st] = -1;
			else if (matrix[fn][st] == 0 && matrix[st][fn] != 0) matrix[st][fn] = -1;
			else
			{
				matrix[fn][st] = -1;
				matrix[st][fn] = -1;
			}
			input_weighted_edge^ f2 = gcnew input_weighted_edge(this);
			f2->Show();
			Main::Hide();
		}


	}
}
System::Void GraphBuilder::Main::open_graph_Click(System::Object^ sender, System::EventArgs^ e)
{
	directed_graph = false;
	weighted_graph = false;
	ifstream read_graph;
	
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		string ss = msclr::interop::marshal_as<std::string>(openFileDialog1->FileName);
		read_graph.open(ss);
		string num;
		read_graph >> num;
		cnt_point = stoi(num);
		for (int i = 0; i < cnt_point; i++)
		{
			read_graph >> point[i].x >> point[i].y;
		}
		for (int i = 0; i < cnt_point; i++)
		{
			for (int j = 0; j < cnt_point; j++)
			{
				read_graph >> matrix[i][j];
				if (matrix[i][j] != -1 && matrix[i][j] != 0)
				{
					weighted_graph = true;
				}
			}
		}
		for (int i = 0; i < cnt_point && !directed_graph; i++)
		{
			for (int j = i + 1; j < cnt_point && !directed_graph; j++)
			{
				if (matrix[i][j] != matrix[j][i]) directed_graph = true;
			}
		}
		change = true;

	}
	

	
}
System::Void GraphBuilder::Main::save_graph_Click(System::Object^ sender, System::EventArgs^ e)
{
	ofstream write_graph;

	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		string ss = msclr::interop::marshal_as<std::string>(saveFileDialog1->FileName);
		write_graph.open(ss);
		write_graph << cnt_point << "\n";
		for (int i = 0; i < cnt_point; i++)
		{
			write_graph << point[i].x << " " << point[i].y << "\n";
		}
		for (int i = 0; i < cnt_point; i++)
		{
			for (int j = 0; j < cnt_point; j++)
			{
				write_graph << matrix[i][j] << " ";
			}
			write_graph << "\n";
		}
		MessageBox::Show(L"Граф збережено!");
	}
	
}
System::Void GraphBuilder::Main::settings_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (min_adge != 1000000000) max_radius = min_adge / 4;
	settings_graph^ f2 = gcnew settings_graph(this);
	f2->Show();
	Main::Hide();
}
System::Void GraphBuilder::Main::choose_weighted_graph_Click(System::Object^ sender, System::EventArgs^ e)
{
	about_graph[1, 2]->Value = "True";
	weighted_graph = true;
	weighted_graph_edge^ f2 = gcnew weighted_graph_edge(this);
	f2->Show();
	Main::Hide();

}
System::Void GraphBuilder::Main::choose_directed_graph_Click(System::Object^ sender, System::EventArgs^ e)
{
	about_graph[1, 3]->Value = "True";
	directed_graph = true;
	change = true;
}
System::Void GraphBuilder::Main::ClearAlgo()
{
	EulerWayAlgo = false;
	EulerWayAlgo = false;
	TopologicalAlgo = false;

	pictureBox1->Enabled = true;
	warning_label->Text = "";

	Main::Height = 566;
	button_next_step->Visible = false;
	point[0].selected = false;
	change = true;
	CntClick = 0;
}
System::Void GraphBuilder::Main::StartAlgo()
{
	while (!mystack.empty())
		mystack.pop();
	for (int i = 0; i < 1000; i++)
		visited[i] = false;
	TempVector.clear();

	pictureBox1->Enabled = false;
	Main::Height = 615;
	button_next_step->Visible = true;
}
void StageDfs(int root, int N, int** matrix)
{
	int i = 0, TempVertex = 0;
	mystack.push(root);
	visited[root] = true;
	TempVector.push_back(root);
	while(!mystack.empty())
	{
		TempVertex = mystack.top();
		i = 0;
		while (i < N && (matrix[TempVertex][i] == 0 || visited[i])) i++;
		if (i == N)
		{
			if (TempVector.back() != mystack.top()) 
				TempVector.push_back(mystack.top());
			mystack.pop();
		}
		else
		{
			if (TempVector.back() != mystack.top())
				TempVector.push_back(mystack.top());
			TempVector.push_back(i);
			mystack.push(i);
			visited[i] = true;
		}
	}

}
void DFS(int N, int** matrix)
{
	for (int i = 0; i < N; i++)
		if (!visited[i]) 
		{
			cnt_small_graph++;
			StageDfs(i, N, matrix);
		}
}
System::Void GraphBuilder::Main::DepthFirstSearch_Click(System::Object^ sender, System::EventArgs^ e)
{
	cnt_small_graph = 0;
	if (cnt_point != 0)
	{
		DfsAlgo = true;
		StartAlgo();

		DFS(cnt_point, matrix);
		
		warning_label->Text = L"Стек: ";
		change = true;
	}
	else warning_label->Text = L"Полотно пусте!";
}
void StageTopologicalDFS(int root, int N, int** matrix)
{
	visited[root] = true;
	mystack.push(root);
	int i = 0;
	while (!mystack.empty())
	{
		int TempVertex = mystack.top();
		i = 0;
		while (i < N && (matrix[TempVertex][i] == 0 && matrix[i][TempVertex] == 0 || visited[i])) i++;
		if(i == N) 
		{
			TempVector.push_back(mystack.top());
			mystack.pop();
		}
		else
		{
			mystack.push(i);
			visited[i] = true;
		}
	}
}
void TopologicalDFS(int N, int** matrix)
{
	for (int i = 0; i < N; i++)
		if(!visited[i])
			StageTopologicalDFS(i, N, matrix);
}
System::Void GraphBuilder::Main::TopologicalSort_Click(System::Object^ sender, System::EventArgs^ e)
{
	bool rule = true;
	for (int i = 0; i < cnt_point && rule; i++)
		for (int j = i + 1; j < cnt_point && rule; j++)
			if (matrix[i][j] == matrix[j][i] && matrix[i][j] != 0) rule = false;

	if(rule)
	{
		Graphics^ graf = pictureBox1->CreateGraphics();
		StartAlgo();
		TopologicalAlgo = true;
		TopologicalDFS(cnt_point, matrix);
		warning_label->Text = L"Топологічний порядок: ";
		change = true;
		CntClick = TempVector.size() - 1;
	}
	else warning_label->Text = L"Неможливо виконати алгоритм";
}
int StartVertexEulerCheck(int** matrix, int N)
{
	int even = 0, start = 0;
	for (int i = 0; i < N; i++)
	{
		int pov_vertex = 0;
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] != 0) pov_vertex++;
		}
		if (pov_vertex % 2 != 0)
		{
			even++;
			start = i;
		}
	}
	if (even == 2) return start;
	else return -1;
}
vector <int> EulerWay_dfs(int copy_matrix[][1000], int N, int start)
{
	vector <int> Eulway;
	int id_temp = 0, i = 0;
	mystack.push(start);
	while (!mystack.empty())
	{
		id_temp = mystack.top();
		i = 0;
		while (i < N && copy_matrix[id_temp][i] == 0) i++;
		if (i == N)
		{
			Eulway.push_back(mystack.top());
			mystack.pop();
		}
		else
		{
			mystack.push(i);
			copy_matrix[i][id_temp] = 0;
			copy_matrix[id_temp][i] = 0;
		}

	}
	return Eulway;
}
System::Void GraphBuilder::Main::EulerWay_Click(System::Object^ sender, System::EventArgs^ e)
{
	int rule = StartVertexEulerCheck(matrix, cnt_point);
	if (rule != -1 && !directed_graph)
	{
		Graphics^ graf = pictureBox1->CreateGraphics();
		StartAlgo();
		EulerWayAlgo = true;
		mystack.push(0);

		for (int i = 0; i < cnt_point; i++)
			for (int j = 0; j < cnt_point; j++)
				copy_matrix[i][j] = matrix[i][j];

		TempVector = EulerWay_dfs(copy_matrix, cnt_point, rule);
		warning_label->Text = L"Ейлерів шлях: ";
		change = true;
	}
	else warning_label->Text = L"Неможливо виконати алгоритм";
}
void DejkstraFunc(int** matrix, int N, int root)
{
	priority_queue <pair<int, int>> Queue;
	for (int i = 0; i < N; i++)
	{
		Way[i].len = INT_MAX;
		Way[i].parent = -1;
	}
	Way[root].len = 0;
	Queue.push(make_pair(0, root));
	while (!Queue.empty())
	{
		int Nod = Queue.top().second;
		int Dist = Queue.top().first;
		Queue.pop();

		for (int i = 0; i < N; i++)
		{
			if (matrix[Nod][i] != 0 && Dist + matrix[Nod][i] < Way[i].len)
			{
					Way[i].len = Dist + matrix[Nod][i];
					Way[i].parent = Nod;
					Queue.push({ Way[i].len, i });
			}
		}


	}
}
System::Void GraphBuilder::Main::Dejkstra_Click(System::Object^ sender, System::EventArgs^ e)
{
	StInput->Visible = true;
	FnInput->Visible = true;
	StartAlgo();
	change = true;
	DejkstraAlgo = true;
	
	
}
System::Void GraphBuilder::Main::button_next_step_Click(System::Object^ sender, System::EventArgs^ e)
{
	Graphics^ graf = pictureBox1->CreateGraphics();
	string TempPos;
	if (DfsAlgo)
	{
		if(CntClick < TempVector.size())
		{
			TempPos = to_string(TempVector[CntClick] + 1) + " ";
			warning_label->Text += gcnew String(TempPos.c_str());
			if (CntClick != 0) draw_vertex(graf, point[TempVector[CntClick - 1]], TempVector[CntClick - 1], Brushes::Violet, R);
			draw_vertex(graf, point[TempVector[CntClick]], TempVector[CntClick], Brushes::Red, R);
			CntClick++;
		}
		else
		{
			MessageBox::Show(L"Кількість компонентів зв'язноті: " + cnt_small_graph.ToString());
			ClearAlgo();
		}

	}
	else if (EulerWayAlgo)
	{
		if(CntClick + 1 < TempVector.size())
		{
			TempPos = to_string(TempVector[CntClick] + 1) + " ";
			warning_label->Text += gcnew String(TempPos.c_str());
			draw_edge(graf, matrix, TempVector[CntClick], TempVector[CntClick + 1], Brushes::Red, boldness, R, directed_graph);
			draw_vertex(graf, point[TempVector[CntClick]], TempVector[CntClick], GraphBuilder::Main::vertex_color, R);
			draw_vertex(graf, point[TempVector[CntClick + 1]], TempVector[CntClick + 1], GraphBuilder::Main::vertex_color, R);
			if (CntClick != 0)
			{
				draw_edge(graf, matrix, TempVector[CntClick], TempVector[CntClick - 1], Brushes::Orange, boldness, R, directed_graph);
				draw_vertex(graf, point[TempVector[CntClick]], TempVector[CntClick], GraphBuilder::Main::vertex_color, R);
				draw_vertex(graf, point[TempVector[CntClick - 1]], TempVector[CntClick - 1], GraphBuilder::Main::vertex_color, R);
			}
			CntClick++;
		}
		else
			ClearAlgo();

	}
	else if (TopologicalAlgo)
	{
		int temp_st, temp_fn;
		if (CntClick > 0)
		{
			TempPos = to_string(TempVector[CntClick] + 1) + " ";
			warning_label->Text += gcnew String(TempPos.c_str());
			temp_st = TempVector[CntClick];
			temp_fn = TempVector[CntClick - 1];
			if (matrix[temp_st][temp_fn] != matrix[temp_fn][temp_st])
			{
				draw_edge(graf, matrix, temp_st, temp_fn, Brushes::Red, boldness, R, directed_graph);
				draw_vertex(graf, point[temp_fn], temp_fn, GraphBuilder::Main::vertex_color, R);
			}
			draw_vertex(graf, point[temp_st], temp_st, Brushes::Red, R);
			
			if (CntClick != TempVector.size() - 1)
			{
				temp_fn = TempVector[CntClick + 1];
				if(matrix[temp_st][temp_fn] != matrix[temp_fn][temp_st] )
				{
					draw_edge(graf, matrix, temp_st, temp_fn, Brushes::Orange, boldness, R, directed_graph);
				}
				draw_vertex(graf, point[temp_fn], temp_fn, Brushes::LightPink, R);
				draw_vertex(graf, point[temp_st], temp_st, Brushes::Red, R);
			}
			CntClick--;
		}
		else if (CntClick == 0)
		{
			TempPos = to_string(TempVector[CntClick] + 1) + " ";
			warning_label->Text += gcnew String(TempPos.c_str());
			temp_st = TempVector[CntClick];
			temp_fn = TempVector[CntClick + 1];
			if (matrix[temp_st][temp_fn] != matrix[temp_fn][temp_st])
			{
				draw_edge(graf, matrix, temp_st, temp_fn, Brushes::Orange, boldness, R, directed_graph);
				draw_vertex(graf, point[temp_fn], temp_fn, Brushes::LightPink, R);
			}
			draw_vertex(graf, point[temp_st], temp_st, Brushes::Red, R);
			
			CntClick--;
		}
		else
				ClearAlgo();
		

	}
	else if(DejkstraAlgo)
	{
		int StPoint = int::Parse(StInput->Text);
		int FnPoint = int::Parse(FnInput->Text);
		if (StPoint == FnPoint || StPoint > cnt_point || StPoint < 1 || FnPoint > cnt_point || FnPoint < 1) MessageBox::Show(L"Некоректні вхідні дані");
		else
		{
			StPoint--;
			FnPoint--;
			point[StPoint].selected = true;
			DejkstraFunc(matrix, cnt_point, StPoint);
			MessageBox::Show(Way[FnPoint].len.ToString());
			TempVector.clear();
			TempVector.push_back(FnPoint);
			int prev = Way[FnPoint].parent;
			while (prev != -1)
			{
				TempVector.push_back(prev);
				prev = Way[prev].parent;
			}
			StepAlgo = TempVector.size() - 1;
			FlagSelectedEdge = true;
			timer1->Interval = 1000;
			change = true;
		}
	}
}
void StageBridgeDfs(int root, int N, int** matrix)
{
	int i = 0, TempVertex = 0;
	mystack.push(root);
	BridgePoint[root].exit = BridgeTimer;
	BridgeTimer++;
	BridgePoint[root].color = 1;
	BridgePoint[root].parent = -1;
	visited[root] = true;

	while (!mystack.empty())
	{
		TempVertex = mystack.top();
		i = 0;
		while (i < N && (matrix[TempVertex][i] == 0 || visited[i])) i++;
		if (i == N)
		{
			BridgePoint[TempVertex].color = 2;
			int MinPoint = BridgePoint[TempVertex].exit;
			for (int i = 0; i < N; i++)
			{
				if (matrix[TempVertex][i] != 0 && i != BridgePoint[TempVertex].parent)
				{
					if (BridgePoint[i].color == 1)
						MinPoint = min(MinPoint, BridgePoint[i].exit);
					else if (BridgePoint[i].color == 2)
						MinPoint = min(MinPoint, BridgePoint[i].entrance);
				}
			}
			BridgePoint[TempVertex].entrance = MinPoint;
			mystack.pop();

		}
		else
		{
			BridgePoint[i].exit = BridgeTimer;
			BridgeTimer++;
			BridgePoint[i].parent = TempVertex;
			BridgePoint[i].color = 1;
			mystack.push(i);
			visited[i] = true;
		}
	}

}
System::Void GraphBuilder::Main::LookingForBridge_Click(System::Object^ sender, System::EventArgs^ e)
{
	Graphics^ graf = pictureBox1->CreateGraphics();
	while (!mystack.empty())
		mystack.pop();
	for (int i = 0; i < 1000; i++)
		visited[i] = false;
	TempVector.clear();
	for (int i = 0; i < 1000; i++)
		BridgePoint[i] = { 0,0,-1,0 };

	LookingForBridgeAlgo = true;
	for (int i = 0; i < cnt_point; i++)
		if (!visited[i])
		{
			StageBridgeDfs(i, cnt_point, matrix);
		}
	for (int i = 0; i < cnt_point; i++)
	{
		if ((BridgePoint[i].exit == BridgePoint[i].entrance) && BridgePoint[i].parent != - 1)
		{
			draw_edge(graf, matrix, BridgePoint[i].parent,i, Brushes::Orange, boldness, R, directed_graph);
			draw_vertex(graf, point[BridgePoint[i].parent], BridgePoint[i].parent, GraphBuilder::Main::vertex_color, R);
			draw_vertex(graf, point[i], i, GraphBuilder::Main::vertex_color, R);
		}
		
	}
}
System::Void GraphBuilder::Main::ClaerAll_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (int i = 0; i < 1000; i++)
		for (int j = 0; j < 1000; j++)
		{
			matrix[i][j] = 0;
			matrix[j][i] = 0;
		}
	
	DeleteSelected(cnt_point);
	cnt_point = 0;
	weighted_graph = false;
	directed_graph = false;
	min_adge = 1000000000;
	change = true;
}
