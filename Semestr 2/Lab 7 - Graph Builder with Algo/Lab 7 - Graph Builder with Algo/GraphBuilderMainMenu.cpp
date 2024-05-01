#include "GraphBuilderMainMenu.h"
#include "Graph.h"
#include <algorithm>

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::GraphBuilderMainMenu_Load(System::Object^ sender, System::EventArgs^ e)
{
	graf = MainCanvas->CreateGraphics();
	Width = 930;
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

	if (myGraph.checkClickCoord(temp) < 0 && myGraph.cntSelectedVertex > 0)
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

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::MainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (changePosition)
	{
		changePosition = false;
		isMouseDown = false;
		int statusPoint = 0;
		for (int i = 0; i < myGraph.cntSelectedVertex; i++)
		{
			Vertex* temp = myGraph.point[myGraph.idSelectedPoints[i]];
			statusPoint = myGraph.checkClickCoord(temp);
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
		
		myGraph.unSelectVertex();
	}
	else
	{
		Vertex* temp = new Vertex(e->X, e->Y);
		String^ error = myGraph.typeClick(temp);
		warningLabel->Text = error;
	}
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::GraphBuilderMainMenu_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (e->KeyChar == (char)Keys::Back)
	{
		if (myGraph.cntSelectedVertex > 0)
		{
			myGraph.deleteSelectedVertex();
			myGraph.redrawGraph(graf);
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
	myGraph.redrawGraph(graf);
}