#include "GraphBuilderMainMenu.h"
#include "Graph.h"
#include <algorithm>

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

	if (myGraph.ifClickVertex(temp) < 0 && myGraph.cntSelectedVertex > 0)
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
			statusPoint = myGraph.ifClickVertex(temp);
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
	}
	else
	{
		Vertex* temp = new Vertex(e->X, e->Y);
		String^ error = myGraph.typeClick(temp);
		warningLabel->Text = error;
	}
	changePosition = false;
	isMouseDown = false;
	myGraph.redrawGraph(graf);
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
	if (e->KeyChar == 'w')
	{
		if (myGraph.selectedEdge != nullptr)
		{
			myGraph.matrix[myGraph.selectedEdge->start][myGraph.selectedEdge->end] = 1;
			myGraph.matrix[myGraph.selectedEdge->end][myGraph.selectedEdge->start] = 0;
			myGraph.selectedEdge = nullptr;
		}
	}
	if (e->KeyChar == 's')
	{
		if (myGraph.selectedEdge != nullptr)
		{
			myGraph.matrix[myGraph.selectedEdge->start][myGraph.selectedEdge->end] = 0;
			myGraph.matrix[myGraph.selectedEdge->end][myGraph.selectedEdge->start] = 1;
			myGraph.selectedEdge = nullptr;
		}
	}
	myGraph.redrawGraph(graf);
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
	myGraph.unSelectVertex();
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::timer_Tick(System::Object^ sender, System::EventArgs^ e)
{
	if (numTickAlgo == myGraph.orderAlgo.Count)
	{
		if (numTickAlgo != 0) myGraph.point[myGraph.orderAlgo[numTickAlgo - 1]]->marker = 0;
		if (numTickAlgo > 1)  myGraph.point[myGraph.orderAlgo[numTickAlgo - 2]]->marker = 0;
		myGraph.redrawGraph(graf);
		timer->Stop();
	}
	else
	{
		if(numTickAlgo > 1)  myGraph.point[myGraph.orderAlgo[numTickAlgo - 2]]->marker = 0;
		if (numTickAlgo != 0) myGraph.point[myGraph.orderAlgo[numTickAlgo - 1]]->marker = -1;
		myGraph.point[myGraph.orderAlgo[numTickAlgo]]->marker = 1;
		myGraph.redrawGraph(graf);
		numTickAlgo++;
	}
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::dfsAlgoMode_Click(System::Object^ sender, System::EventArgs^ e)
{
	numTickAlgo = 0;
	myGraph.dfs(0);
	myGraph.unSelectVertex();
	timer->Start();
}
