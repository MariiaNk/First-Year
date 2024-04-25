#include "GraphBuilderMainMenu.h"

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::GraphBuilderMainMenu_Load(System::Object^ sender, System::EventArgs^ e)
{
	graf = MainCanvas->CreateGraphics();
	Width = 930;
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::MainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	Vertex* temp = new Vertex(e->X, e->Y);
	String^ error = myGraph.typeClick(temp);	
	warningLabel->Text = error;
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::settingsTool_Click(System::Object^ sender, System::EventArgs^ e)
{
	Width = 1140;
}


System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::buttonVertexColor_Click(System::Object^ sender, System::EventArgs^ e)
{
	pickColor->ShowDialog();
	Color newColor = pickColor->Color;
	newStyle.colorVertex = gcnew SolidBrush(newColor);
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::discardChanges_Click(System::Object^ sender, System::EventArgs^ e)
{
	Width = 930;
	myGraph.redrawGraph(graf);
}

System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::saveChanges_Click(System::Object^ sender, System::EventArgs^ e)
{
	myGraph.changeStyle(newStyle);
	Width = 930;
	myGraph.redrawGraph(graf);
}