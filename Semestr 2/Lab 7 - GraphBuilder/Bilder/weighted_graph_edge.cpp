#include "weighted_graph_edge.h"
#include <string>
using namespace std;

string edges;

System::Void GraphBuilder::weighted_graph_edge::button_ok_Click(System::Object^ sender, System::EventArgs^ e)
{
    int temp;
    if (int::TryParse(start_point->Text, temp))
    {
        int st = temp - 1;
        if (st > MainForm->cnt_edge)
        {
            MessageBox::Show(L"Вершин " + (st + 1).ToString() + L" не існує!\nІснують вершини з індексом до " + (MainForm->cnt_edge + 1).ToString());
            start_point->Clear();
            finish_point->Clear();
        }
        else
        {
            if (int::TryParse(finish_point->Text, temp))
            {

                int fn = temp - 1;
                if (fn > MainForm->cnt_edge)
                {
                    MessageBox::Show(L"Вершин " + (fn + 1).ToString() + L" не існує!");
                    finish_point->Clear();
                }
                else
                {
                    if (MainForm->matrix[st][fn] != 0 && (MainForm->matrix[fn][st] != 0 || MainForm->directed_graph))
                    {
                        if (int::TryParse(weight_temp_edge->Text, temp))
                        {
                            int w = temp;
                            MainForm->matrix[st][fn] = w;
                            if (!MainForm->directed_graph) MainForm->matrix[fn][st] = w;
                            MainForm->cnt_weighted_edge++;

                            if (MainForm->cnt_weighted_edge == MainForm->cnt_edge)
                            {
                                MessageBox::Show(L"Ви вказали вагу всіх ребер.");
                                MainForm->change = true;
                                weighted_graph_edge::Close();
                            }
                            start_point->Clear();
                            finish_point->Clear();
                            weight_temp_edge->Clear();
                        }
                        else
                        {
                            weight_temp_edge->Clear();
                            MessageBox::Show(L"Вхідні дані не коректні!");
                        }

                    }
                    else
                    {
                        String^ m = L"Між вершинами " + (st + 1).ToString() + L" та " + (fn + 1).ToString() + L" немає ребра!\nПотрібно додати вагу ребер:\n";
                        m += gcnew String(edges.c_str());
                        MessageBox::Show(m);
                        start_point->Clear();
                        finish_point->Clear();
                        weight_temp_edge->Clear();
                    }
                }
            }
            else
            {
                finish_point->Clear();
                weight_temp_edge->Clear();
                MessageBox::Show(L"Вхідні дані не коректні!");
            }
        }
    }
    else 
    {
        start_point->Clear();
        finish_point->Clear();
        weight_temp_edge->Clear();
        MessageBox::Show(L"Вхідні дані не коректні!");
    }
    edges.clear();
    int cnt_row = 0;
    for (int i = 0; i < MainForm->cnt_point; i++)
    {
        for (int j = i + 1; j < MainForm->cnt_point; j++)
        {
            if (MainForm->matrix[i][j] == -1)
            {
                edges += to_string(i + 1) + " -> " + to_string(j + 1) + "\n";
                cnt_row++;
            }
            else if (MainForm->matrix[i][j] == 0 && MainForm->matrix[j][i] == -1)
            {
                edges += to_string(j + 1) + " -> " + to_string(i + 1) + "\n";
                cnt_row++;
            }
        }
    }
    label5->Text = gcnew String(edges.c_str());
    weighted_graph_edge::Height = 201 + 16 * (cnt_row + 2);
}

System::Void GraphBuilder::weighted_graph_edge::weighted_graph_edge_Load(System::Object^ sender, System::EventArgs^ e)
{
    int cnt_row = 0;
    for (int i = 0; i < MainForm->cnt_point; i++)
    {
        for (int j = i + 1; j < MainForm->cnt_point; j++)
        {
            if (MainForm->matrix[i][j] == -1) 
            {
                edges += to_string(i + 1) + " -> " + to_string(j + 1) + "\n";
                cnt_row++;
            }
            else if (MainForm->matrix[i][j] == 0 && MainForm->matrix[j][i] == -1) 
            {
                edges += to_string(j + 1) + " -> " + to_string(i + 1) + "\n";
                cnt_row++;
            }
        }
    }
    weighted_graph_edge::Height = 201 + 16 * (cnt_row + 2);
    label5->Text = gcnew String(edges.c_str());
    
}
