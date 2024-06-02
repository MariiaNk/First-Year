#include "GraphBuilderMainMenu.h"
#include "Graph.h"
#include <algorithm>
#include <msclr\marshal_cppstd.h>

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::GraphBuilderMainMenu_Load(System::Object^ sender, System::EventArgs^ e)
{
	graf = MainCanvas->CreateGraphics();
	Width = 930;
	MainCanvas->Focus();
	GraphBuilderMainMenu::Focus();
}



System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::settingsTool_Click(System::Object^ sender, System::EventArgs^ e)
{
	Width = 1140;
	prewStyle = myGraph.style;
}


System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::buttonVertexColor_Click(System::Object^ sender, System::EventArgs^ e)
{
	pickColor->ShowDialog();
	Color newColor = pickColor->Color;
	myGraph.style.colorVertex = gcnew SolidBrush(newColor);
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::discardChanges_Click(System::Object^ sender, System::EventArgs^ e)
{
	Width = 930;
	myGraph.style = prewStyle;
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::saveChanges_Click(System::Object^ sender, System::EventArgs^ e)
{
	Width = 930;
	myGraph.redrawGraph(graf);
}


System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::trackRadius_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	myGraph.style.radius = trackRadius->Value;
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::trackBoldness_Scroll(System::Object^ sender, System::EventArgs^ e)
{
	myGraph.style.boldness = trackBoldness->Value;
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::buttonEdgeColor_Click(System::Object^ sender, System::EventArgs^ e)
{
	pickColor->ShowDialog();
	Color newColor = pickColor->Color;
	myGraph.style.colorEdge = gcnew SolidBrush(newColor);
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::MainCanvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	Vertex* temp = new Vertex(e->X, e->Y);

	if (myGraph.ifClickVertex(temp, -1) < 0 && myGraph.cntSelectedVertex > 0)
	{
		isMouseDown = true;
		startPosition = temp;
		currPosition = temp;
	}
}


System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::MainCanvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (isMouseDown)
	{
		int distanceX = (currPosition->x - e->X) * (currPosition->x - e->X);
		int distanceY = (currPosition->y - e->Y) * (currPosition->y - e->Y);
		if (sqrt(distanceX + distanceY) > myGraph.style.radius)
		{
			for (int i = 0; i < myGraph.cntSelectedVertex; i++)
			{
				myGraph.point[myGraph.idSelectedPoints[i]]->x -= currPosition->x - e->X;
				myGraph.point[myGraph.idSelectedPoints[i]]->y -= currPosition->y - e->Y;			
			}
			currPosition = new Vertex(e->X, e->Y);
			changePosition = true;
			myGraph.redrawGraph(graf);
		}
		
	}
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::MainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (changePosition)
	{
		int statusPoint = 0;
		for (int i = 0; i < myGraph.cntSelectedVertex; i++)
		{
			//current selected
			Vertex* temp = myGraph.point[myGraph.idSelectedPoints[i]];
			//порівнюємо виділену з усіма іншими 
			statusPoint = myGraph.ifClickVertex(temp, myGraph.idSelectedPoints[i]);
			if (statusPoint > -2 && statusPoint != myGraph.idSelectedPoints[i])
			{
				System::Media::SystemSounds::Beep->Play();
				warningLabel->Text = L" Не можна пересувати вершини надто близько";
				myGraph.point[myGraph.idSelectedPoints[i]]->x += startPosition->x - e->X;
				myGraph.point[myGraph.idSelectedPoints[i]]->y += startPosition->y - e->Y;
			}
			else
			{
				int max_x = MainCanvas->Width, max_y = MainCanvas->Height;
				if (!(temp->x > 1.5 * myGraph.style.radius && temp->y > 1.5 * myGraph.style.radius && (temp->x < max_x - 1.5 * myGraph.style.radius) && (temp->y < max_y - 1.5 * myGraph.style.radius)))
				{
					System::Media::SystemSounds::Beep->Play();
					warningLabel->Text = L"Не можна пересувати вершину надто близько до межі!";
					myGraph.point[myGraph.idSelectedPoints[i]]->x += startPosition->x - e->X;
					myGraph.point[myGraph.idSelectedPoints[i]]->y += startPosition->y - e->Y;
				}
			}
			
		}
		currPosition = new Vertex(0, 0, 0);
		startPosition = new Vertex(0, 0, 0);
		myGraph.unSelectVertex();
		myGraph.redrawGraph(graf);
	}
	else
	{
		Vertex* temp = new Vertex(e->X, e->Y);
		String^ error = myGraph.typeClick(temp);
		warningLabel->Text = error;
		if (weightedGraphMarker->Checked && myGraph.cntEdges != 0)
		{
			MainCanvas->Enabled = false;
			myGraph.selectedEdge = nullptr;
			myGraph.unSelectVertex();
			myGraph.redrawGraph(graf);
			inputWeightBox->Visible = true;
			warningLabel->Text = "Введіть вагу ребра " + (myGraph.allEdges[numTick]->start + 1) + " - " + (myGraph.allEdges[numTick]->end + 1) + " : ";
		}
		else myGraph.cntEdges = 0;
		myGraph.redrawGraph(graf);
	}
	changePosition = false;
	isMouseDown = false;
	
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::GraphBuilderMainMenu_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (e->KeyChar == (char)Keys::Back)
	{
		if (myGraph.cntSelectedVertex > 0)
		{
			myGraph.deleteSelectedVertex();
		}
		if (myGraph.selectedEdge != nullptr)
		{
			myGraph.deleteSelectedEdge();
		}

	}
	if (e->KeyChar == 'w' && directedGraphMarker->Checked)
	{
		if (myGraph.selectedEdge != nullptr)
		{
			if (myGraph.matrix[myGraph.selectedEdge->start][myGraph.selectedEdge->end] != 0)
			{
				myGraph.matrix[myGraph.selectedEdge->end][myGraph.selectedEdge->start] = 0;
			}
			else
			{
				myGraph.matrix[myGraph.selectedEdge->start][myGraph.selectedEdge->end] = myGraph.matrix[myGraph.selectedEdge->end][myGraph.selectedEdge->start];
				myGraph.matrix[myGraph.selectedEdge->end][myGraph.selectedEdge->start] = 0;
			}
			myGraph.selectedEdge = nullptr;
		}
	}
	if (e->KeyChar == 's' && directedGraphMarker->Checked)
	{
		if (myGraph.selectedEdge != nullptr)
		{
			if (myGraph.matrix[myGraph.selectedEdge->end][myGraph.selectedEdge->start] != 0)
			{
				myGraph.matrix[myGraph.selectedEdge->start][myGraph.selectedEdge->end] = 0;
			}
			else
			{
				myGraph.matrix[myGraph.selectedEdge->end][myGraph.selectedEdge->start] = myGraph.matrix[myGraph.selectedEdge->start][myGraph.selectedEdge->end];
				myGraph.matrix[myGraph.selectedEdge->start][myGraph.selectedEdge->end] = 0;
			}
			myGraph.selectedEdge = nullptr;
		}
	}
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::directedMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	directedGraphMarker->Checked = true;
	myGraph.selectedEdge = nullptr;
	myGraph.directedGraph = true;
	myGraph.unSelectVertex();
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::notDirectedMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	directedGraphMarker->Checked = false;
	myGraph.selectedEdge = nullptr;
	myGraph.directedGraph = true;
	myGraph.unWeightedEdge();
	myGraph.unSelectVertex();
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::weightedMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	weightedGraphMarker->Checked = true;
	MainCanvas->Enabled = false;
	myGraph.weightedGraph = true;
	myGraph.selectedEdge = nullptr;
	myGraph.unSelectVertex();
	myGraph.redrawGraph(graf);
	inputWeightBox->Visible = true;
	myGraph.findAllEdges();
	warningLabel->Text = "Введіть вагу ребра " + (myGraph.allEdges[numTick]->start + 1) + " - " + (myGraph.allEdges[numTick]->end + 1) + " : ";
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::notWeightedMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	weightedGraphMarker->Checked = false;
	myGraph.weightedGraph = false;
	myGraph.selectedEdge = nullptr;
	myGraph.unSelectVertex();
	myGraph.unWeightedEdge();
	myGraph.redrawGraph(graf);
}
System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::inputWeightBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (e->KeyChar == (char)Keys::Enter)
	{
		if (!inputFinishPathBox->Visible)
		{
			Edge* current = myGraph.allEdges[numTick];
			numTick++;
			String^ valueText = inputWeightBox->Text;
			inputWeightBox->Text = "";
			int value;
			bool converted = Int32::TryParse(valueText, value);
			if (converted)
			{
				myGraph.changeEdgeWeight(current->start, current->end, value);
				if (numTick < myGraph.cntEdges)
					warningLabel->Text = "Введіть вагу ребра " + (myGraph.allEdges[numTick]->start + 1) + " - " + (myGraph.allEdges[numTick]->end + 1) + " : ";
				else
				{
					warningLabel->Text = "";
					inputWeightBox->Visible = false;
					MainCanvas->Enabled = true;
					numTick = 0;
					myGraph.cntEdges = 0;
				}
				myGraph.redrawGraph(graf);
			}
		}
		
	}
}
System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::buttonStartPath_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ valueText = inputWeightBox->Text;
	int start, finish;
	bool convertedStart = Int32::TryParse(valueText, start);
	valueText = inputFinishPathBox->Text;
	bool convertedFinish = Int32::TryParse(valueText, finish);
	inputFinishPathBox->Text = "";
	inputWeightBox->Text = "";

	if ((convertedStart && convertedFinish) && (start > 0 && start <= myGraph.cntVertex) && (finish > 0 && finish <= myGraph.cntVertex))
	{
		startVertex = start - 1;
		finishVertex = finish - 1;
		myGraph.idSelectedPoints[myGraph.cntSelectedVertex] = startVertex;
		myGraph.cntSelectedVertex++;
		myGraph.idSelectedPoints[myGraph.cntSelectedVertex] = finishVertex;
		myGraph.cntSelectedVertex++;
		myGraph.redrawGraph(graf);
		int* distance = new int[1000];
		distance = myGraph.Dijkstras(startVertex);
		MessageBox::Show(L"Найменша відстань між " + (startVertex + 1) + " та " + (finishVertex + 1) + " = " + distance[finishVertex]);
		myGraph.unSelectVertex();
		inputWeightBox->Visible = false;
		inputFinishPathBox->Visible = false;
		buttonStartPath->Visible = false;
		warningLabel->Text = "";
		startVertex = -1;
		finishVertex = -1;
	}
	else MessageBox::Show(L"Не коректні вхідні дані");
}



System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::timer_Tick(System::Object^ sender, System::EventArgs^ e)
{
	if (myGraph.cntBridges == 0)
	{
		if (numTick == myGraph.orderAlgo.Count)
		{
			if (numTick != 0) myGraph.point[myGraph.orderAlgo[numTick - 1]]->marker = 0;
			if (numTick > 1)  myGraph.point[myGraph.orderAlgo[numTick - 2]]->marker = 0;
			myGraph.selectedEdge = nullptr;
			myGraph.redrawGraph(graf);
			timer->Stop();
			myGraph.orderAlgo.Clear();
		}
		else
		{
			if (myGraph.needEdgeInAlgo && numTick != 0)
			{
				myGraph.selectedEdge = new Edge;
				myGraph.selectedEdge->start = myGraph.orderAlgo[numTick - 1];
				myGraph.selectedEdge->end = myGraph.orderAlgo[numTick];
			}

			if (numTick > 1)  myGraph.point[myGraph.orderAlgo[numTick - 2]]->marker = 0;
			if (numTick != 0) myGraph.point[myGraph.orderAlgo[numTick - 1]]->marker = -1;
			myGraph.point[myGraph.orderAlgo[numTick]]->marker = 1;
			myGraph.redrawGraph(graf);
			numTick++;
		}
	}
	else
	{
		if (numTick == myGraph.cntBridges)
		{
			myGraph.point[myGraph.selectedEdge->start]->marker = 0;
			myGraph.point[myGraph.selectedEdge->end]->marker = 0;
			myGraph.selectedEdge = nullptr;
			myGraph.redrawGraph(graf);
			timer->Stop();
			myGraph.cntBridges = 0;
		}
		else
		{
			if (myGraph.selectedEdge)
			{
				myGraph.point[myGraph.selectedEdge->start]->marker = 0;
				myGraph.point[myGraph.selectedEdge->end]->marker = 0;
			}			

			myGraph.selectedEdge = myGraph.orderBridges[numTick];
			myGraph.point[myGraph.selectedEdge->start]->marker = 1;
			myGraph.point[myGraph.selectedEdge->end]->marker = 1;

			myGraph.redrawGraph(graf);
			numTick++;
		}
	}
}


System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::clearCanvas_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ message = L"Ви впевнені, що хочете очистити полотно?\nПоточний граф не буде збережено";
	String^ caption = "Попередження";
	System::Windows::Forms::DialogResult result = MessageBox::Show(message, caption, MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (result == System::Windows::Forms::DialogResult::Yes)
	{
		myGraph.cleanGraph();
		myGraph.redrawGraph(graf);
	}
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::save_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		string ss = msclr::interop::marshal_as<std::string>(saveFileDialog->FileName);
		myGraph.outputGraph(ss);
		MessageBox::Show(L"Граф збережено!");
	}
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::open_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ message = L"Ви впевнені, що хочете відкрити новий граф?\nПоточний граф не буде збережено";
	String^ caption = "Попередження";
	System::Windows::Forms::DialogResult result = MessageBox::Show(message, caption, MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (result == System::Windows::Forms::DialogResult::Yes)
	{
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			string ss = msclr::interop::marshal_as<std::string>(openFileDialog->FileName);
			myGraph.readGraph(ss);
			if (myGraph.directedGraph) directedGraphMarker->Checked = true;
			if (myGraph.weightedGraph) weightedGraphMarker->Checked = true;
			myGraph.redrawGraph(graf);
		}
	}

}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::GraphBuilderMainMenu_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
	String^ message = L"Чи бажаєте зберегти граф перед закриттям?";
	String^ caption = "Попередження";
	System::Windows::Forms::DialogResult result = MessageBox::Show(message, caption, MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (result == System::Windows::Forms::DialogResult::Yes)
	{
		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			string ss = msclr::interop::marshal_as<std::string>(saveFileDialog->FileName);
			myGraph.outputGraph(ss);
			MessageBox::Show(L"Граф збережено!");
		}
	}
}
System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::algoMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	algoModeMarker->Checked = true;
	exitAlgoModeButton->Visible = true;
	MainCanvas->Enabled = false;
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::exitAlgoModeButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	algoModeMarker->Checked = false;
	exitAlgoModeButton->Visible = false;
	MainCanvas->Enabled = true;

	myGraph.orderAlgo.Clear();
	numTick = 0;
	myGraph.cntBridges = 0;
	timer->Stop();

	myGraph.unSelectVertex();
	myGraph.redrawGraph(graf);
}
System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::dfsAlgoMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	numTick = 0;
	int start = 0;
	if (myGraph.cntSelectedVertex != 0) start = myGraph.idSelectedPoints[0];
	myGraph.dfs(start);
	myGraph.unSelectVertex();
	timer->Start();
}
System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::bfsAlgoMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	numTick = 0;
	int start = 0;
	if (myGraph.cntSelectedVertex != 0) start = myGraph.idSelectedPoints[0];
	myGraph.bfs(start);
	myGraph.unSelectVertex();
	timer->Start();
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::topologicalSortAlgoMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	numTick = 0;
	bool checkDAG = !myGraph.HasCycle() && myGraph.isFullDirected();
	if (!directedGraphMarker->Checked || !checkDAG)
		MessageBox::Show(L"На жаль, у цьому графі не можна виконати топологічне сортування :(");
	else
	{
		myGraph.topologicalSort();
		if(myGraph.orderAlgo.Count == 0)
			MessageBox::Show(L"На жаль, у цьому графі не можна виконати топологічне сортування :(");
		else
		{
			myGraph.unSelectVertex();
			timer->Start();
		}
		
	}
	
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::EulerWayMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	numTick = 0;
	int checkEulerWay = myGraph.StartVertexEulerCheck();
	if (checkEulerWay != -1 && !(directedGraphMarker->Checked))
	{
		myGraph.needEdgeInAlgo = true;
		myGraph.EulerWayDFS(checkEulerWay);
		myGraph.unSelectVertex();
		timer->Start();
	}
	else
		MessageBox::Show(L"На жаль, у цьому графі не має Ейлерового шляху :(");
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::shortestPathAlgorithmMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	numTick = 0;
	myGraph.unSelectVertex();
	inputWeightBox->Visible = true;
	inputFinishPathBox->Visible = true;
	buttonStartPath->Visible = true;
	warningLabel->Text = L"Початковa і фанальна вершини:";
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::bridgesAlgo_Click(System::Object^ sender, System::EventArgs^ e)
{
	numTick = 0;
	myGraph.unSelectVertex();
	myGraph.bridge();
	timer->Start();
}