#include "GraphBuilderMainMenu.h"



System::Void Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu::MainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	Graphics^ graf = MainCanvas->CreateGraphics();
	warningLabel->Text = "";
	Vertex temp(e->X, e->Y);
}


