#include "GraphBuilderMainMenu.h"



System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::MainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	Graphics^ graf = MainCanvas->CreateGraphics();
	Vertex* temp = new Vertex(e->X, e->Y);
	String^ error = myGraph.typeClick(temp);	
	warningLabel->Text = error;
	myGraph.redrawGraph(graf);
}


