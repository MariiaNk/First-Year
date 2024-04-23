#include "GraphBuilderMainMenu.h"

[System::STAThread]
void Main() {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	Lab7GraphBuilderwithAlgo::GraphBuilderMainMenu form;
	System::Windows::Forms::Application::Run(% form);

}
