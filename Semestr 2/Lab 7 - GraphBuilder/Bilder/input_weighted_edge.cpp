#include "input_weighted_edge.h"

System::Void GraphBuilder::input_weighted_edge::button_ok_Click(System::Object^ sender, System::EventArgs^ e)
{
	MainForm->weight_edge = int::Parse(input_weighted->Text);
	MainForm->change = true;
	input_weighted_edge::Close();

}
