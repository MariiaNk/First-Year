#pragma once
#include "Graph.h"

namespace Lab7GraphBuilderwithAlgo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GraphBuilderMainMenu
	/// </summary>
	public ref class GraphBuilderMainMenu : public System::Windows::Forms::Form
	{
	public:
		GraphBuilderMainMenu(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GraphBuilderMainMenu()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::Label^ warningLabel;
	private: System::Windows::Forms::ColorDialog^ pickColor;
	private: System::Windows::Forms::Button^ buttonVertexColor;
	private: System::Windows::Forms::Label^ SettingsLabel;
	private: System::Windows::Forms::Button^ buttonEdgeColor;
	private: System::Windows::Forms::TrackBar^ trackRadius;
	private: System::Windows::Forms::Label^ RadiusLabel;
	private: System::Windows::Forms::Label^ BoldnessLabel;
	private: System::Windows::Forms::TrackBar^ trackBoldness;
	private: System::Windows::Forms::Button^ discardChanges;
	private: System::Windows::Forms::Button^ saveChanges;
	private: System::Windows::Forms::MenuStrip^ GraphMenu;
	private: System::Windows::Forms::ToolStripMenuItem^ settingsTool;
	private: System::Windows::Forms::RadioButton^ directedGraphMarker;



	private: System::Windows::Forms::RadioButton^ weightedGraphMarker;
	private: System::Windows::Forms::RadioButton^ algoModeMarker;
	private: System::Windows::Forms::ToolStripMenuItem^ ÚËÔ√‡ÙÛToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ weightedMode;
	private: System::Windows::Forms::ToolStripMenuItem^ directedMode;




	private: System::Windows::Forms::ToolStripMenuItem^ algoMode;
	private: System::Windows::Forms::Button^ exitAlgoModeButton;
	private: System::Windows::Forms::PictureBox^ MainCanvas;
	private: System::Windows::Forms::ToolStripMenuItem^ dfsAlgoMode;
	private: System::Windows::Forms::Timer^ timer;
	private: System::Windows::Forms::TextBox^ inputWeightBox;
	private: System::Windows::Forms::ToolStripMenuItem^ Ù‡ÈÎToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ save;
	private: System::Windows::Forms::ToolStripMenuItem^ open;
	private: System::Windows::Forms::ToolStripMenuItem^ clearCanvas;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::ToolStripMenuItem^ bfsAlgoMode;

	private: System::Windows::Forms::ToolStripMenuItem^ topologicalSortAlgoMode;
	private: System::Windows::Forms::ToolStripMenuItem^ EulerWayMode;
	private: System::Windows::Forms::ToolStripMenuItem^ shortestPathAlgorithmMode;
	private: System::Windows::Forms::TextBox^ inputFinishPathBox;
	private: System::Windows::Forms::Button^ buttonStartPath;
	private: System::Windows::Forms::ToolStripMenuItem^ notWeightedMode;
	private: System::Windows::Forms::ToolStripMenuItem^ notDirectedMode;
	private: System::Windows::Forms::ToolStripMenuItem^ bridgesAlgo;














	private: System::ComponentModel::IContainer^ components;


	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GraphBuilderMainMenu::typeid));
			this->MainCanvas = (gcnew System::Windows::Forms::PictureBox());
			this->warningLabel = (gcnew System::Windows::Forms::Label());
			this->pickColor = (gcnew System::Windows::Forms::ColorDialog());
			this->buttonVertexColor = (gcnew System::Windows::Forms::Button());
			this->SettingsLabel = (gcnew System::Windows::Forms::Label());
			this->buttonEdgeColor = (gcnew System::Windows::Forms::Button());
			this->trackRadius = (gcnew System::Windows::Forms::TrackBar());
			this->RadiusLabel = (gcnew System::Windows::Forms::Label());
			this->BoldnessLabel = (gcnew System::Windows::Forms::Label());
			this->trackBoldness = (gcnew System::Windows::Forms::TrackBar());
			this->discardChanges = (gcnew System::Windows::Forms::Button());
			this->saveChanges = (gcnew System::Windows::Forms::Button());
			this->GraphMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->settingsTool = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ÚËÔ√‡ÙÛToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->weightedMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->directedMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->notWeightedMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->notDirectedMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->algoMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dfsAlgoMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bfsAlgoMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->topologicalSortAlgoMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EulerWayMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->shortestPathAlgorithmMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Ù‡ÈÎToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->save = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->open = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearCanvas = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->directedGraphMarker = (gcnew System::Windows::Forms::RadioButton());
			this->weightedGraphMarker = (gcnew System::Windows::Forms::RadioButton());
			this->algoModeMarker = (gcnew System::Windows::Forms::RadioButton());
			this->exitAlgoModeButton = (gcnew System::Windows::Forms::Button());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->inputWeightBox = (gcnew System::Windows::Forms::TextBox());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->inputFinishPathBox = (gcnew System::Windows::Forms::TextBox());
			this->buttonStartPath = (gcnew System::Windows::Forms::Button());
			this->bridgesAlgo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainCanvas))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackRadius))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBoldness))->BeginInit();
			this->GraphMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// MainCanvas
			// 
			this->MainCanvas->BackColor = System::Drawing::SystemColors::Window;
			this->MainCanvas->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			resources->ApplyResources(this->MainCanvas, L"MainCanvas");
			this->MainCanvas->Name = L"MainCanvas";
			this->MainCanvas->TabStop = false;
			this->MainCanvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphBuilderMainMenu::MainCanvas_MouseDown);
			this->MainCanvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphBuilderMainMenu::MainCanvas_MouseMove);
			this->MainCanvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphBuilderMainMenu::MainCanvas_MouseUp);
			// 
			// warningLabel
			// 
			resources->ApplyResources(this->warningLabel, L"warningLabel");
			this->warningLabel->BackColor = System::Drawing::Color::Transparent;
			this->warningLabel->ForeColor = System::Drawing::Color::Red;
			this->warningLabel->Name = L"warningLabel";
			// 
			// buttonVertexColor
			// 
			this->buttonVertexColor->BackColor = System::Drawing::Color::LightCyan;
			resources->ApplyResources(this->buttonVertexColor, L"buttonVertexColor");
			this->buttonVertexColor->ForeColor = System::Drawing::Color::Teal;
			this->buttonVertexColor->Name = L"buttonVertexColor";
			this->buttonVertexColor->UseVisualStyleBackColor = false;
			this->buttonVertexColor->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::buttonVertexColor_Click);
			// 
			// SettingsLabel
			// 
			resources->ApplyResources(this->SettingsLabel, L"SettingsLabel");
			this->SettingsLabel->ForeColor = System::Drawing::Color::Teal;
			this->SettingsLabel->Name = L"SettingsLabel";
			// 
			// buttonEdgeColor
			// 
			this->buttonEdgeColor->BackColor = System::Drawing::Color::LightCyan;
			resources->ApplyResources(this->buttonEdgeColor, L"buttonEdgeColor");
			this->buttonEdgeColor->ForeColor = System::Drawing::Color::Teal;
			this->buttonEdgeColor->Name = L"buttonEdgeColor";
			this->buttonEdgeColor->UseVisualStyleBackColor = false;
			this->buttonEdgeColor->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::buttonEdgeColor_Click);
			// 
			// trackRadius
			// 
			resources->ApplyResources(this->trackRadius, L"trackRadius");
			this->trackRadius->Maximum = 50;
			this->trackRadius->Minimum = 10;
			this->trackRadius->Name = L"trackRadius";
			this->trackRadius->Value = 10;
			this->trackRadius->Scroll += gcnew System::EventHandler(this, &GraphBuilderMainMenu::trackRadius_Scroll);
			// 
			// RadiusLabel
			// 
			resources->ApplyResources(this->RadiusLabel, L"RadiusLabel");
			this->RadiusLabel->ForeColor = System::Drawing::Color::Teal;
			this->RadiusLabel->Name = L"RadiusLabel";
			// 
			// BoldnessLabel
			// 
			resources->ApplyResources(this->BoldnessLabel, L"BoldnessLabel");
			this->BoldnessLabel->ForeColor = System::Drawing::Color::Teal;
			this->BoldnessLabel->Name = L"BoldnessLabel";
			// 
			// trackBoldness
			// 
			resources->ApplyResources(this->trackBoldness, L"trackBoldness");
			this->trackBoldness->Maximum = 50;
			this->trackBoldness->Minimum = 10;
			this->trackBoldness->Name = L"trackBoldness";
			this->trackBoldness->Value = 10;
			this->trackBoldness->Scroll += gcnew System::EventHandler(this, &GraphBuilderMainMenu::trackBoldness_Scroll);
			// 
			// discardChanges
			// 
			this->discardChanges->BackColor = System::Drawing::Color::MistyRose;
			resources->ApplyResources(this->discardChanges, L"discardChanges");
			this->discardChanges->ForeColor = System::Drawing::Color::Maroon;
			this->discardChanges->Name = L"discardChanges";
			this->discardChanges->UseVisualStyleBackColor = false;
			this->discardChanges->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::discardChanges_Click);
			// 
			// saveChanges
			// 
			this->saveChanges->BackColor = System::Drawing::Color::LightCyan;
			resources->ApplyResources(this->saveChanges, L"saveChanges");
			this->saveChanges->ForeColor = System::Drawing::Color::Teal;
			this->saveChanges->Name = L"saveChanges";
			this->saveChanges->UseVisualStyleBackColor = false;
			this->saveChanges->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::saveChanges_Click);
			// 
			// GraphMenu
			// 
			this->GraphMenu->BackColor = System::Drawing::Color::PowderBlue;
			this->GraphMenu->ImageScalingSize = System::Drawing::Size(20, 20);
			this->GraphMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->settingsTool, this->ÚËÔ√‡ÙÛToolStripMenuItem,
					this->algoMode, this->Ù‡ÈÎToolStripMenuItem
			});
			resources->ApplyResources(this->GraphMenu, L"GraphMenu");
			this->GraphMenu->Name = L"GraphMenu";
			// 
			// settingsTool
			// 
			this->settingsTool->Name = L"settingsTool";
			resources->ApplyResources(this->settingsTool, L"settingsTool");
			this->settingsTool->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::settingsTool_Click);
			// 
			// ÚËÔ√‡ÙÛToolStripMenuItem
			// 
			this->ÚËÔ√‡ÙÛToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->weightedMode,
					this->directedMode, this->notWeightedMode, this->notDirectedMode
			});
			this->ÚËÔ√‡ÙÛToolStripMenuItem->Name = L"ÚËÔ√‡ÙÛToolStripMenuItem";
			resources->ApplyResources(this->ÚËÔ√‡ÙÛToolStripMenuItem, L"ÚËÔ√‡ÙÛToolStripMenuItem");
			// 
			// weightedMode
			// 
			this->weightedMode->Name = L"weightedMode";
			resources->ApplyResources(this->weightedMode, L"weightedMode");
			this->weightedMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::weightedMode_Click);
			// 
			// directedMode
			// 
			this->directedMode->Name = L"directedMode";
			resources->ApplyResources(this->directedMode, L"directedMode");
			this->directedMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::directedMode_Click);
			// 
			// notWeightedMode
			// 
			this->notWeightedMode->Name = L"notWeightedMode";
			resources->ApplyResources(this->notWeightedMode, L"notWeightedMode");
			this->notWeightedMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::notWeightedMode_Click);
			// 
			// notDirectedMode
			// 
			this->notDirectedMode->Name = L"notDirectedMode";
			resources->ApplyResources(this->notDirectedMode, L"notDirectedMode");
			this->notDirectedMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::notDirectedMode_Click);
			// 
			// algoMode
			// 
			this->algoMode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->dfsAlgoMode,
					this->bfsAlgoMode, this->topologicalSortAlgoMode, this->EulerWayMode, this->shortestPathAlgorithmMode, this->bridgesAlgo
			});
			this->algoMode->Name = L"algoMode";
			resources->ApplyResources(this->algoMode, L"algoMode");
			this->algoMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::algoMode_Click);
			// 
			// dfsAlgoMode
			// 
			this->dfsAlgoMode->Name = L"dfsAlgoMode";
			resources->ApplyResources(this->dfsAlgoMode, L"dfsAlgoMode");
			this->dfsAlgoMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::dfsAlgoMode_Click);
			// 
			// bfsAlgoMode
			// 
			this->bfsAlgoMode->Name = L"bfsAlgoMode";
			resources->ApplyResources(this->bfsAlgoMode, L"bfsAlgoMode");
			this->bfsAlgoMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::bfsAlgoMode_Click);
			// 
			// topologicalSortAlgoMode
			// 
			this->topologicalSortAlgoMode->Name = L"topologicalSortAlgoMode";
			resources->ApplyResources(this->topologicalSortAlgoMode, L"topologicalSortAlgoMode");
			this->topologicalSortAlgoMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::topologicalSortAlgoMode_Click);
			// 
			// EulerWayMode
			// 
			this->EulerWayMode->Name = L"EulerWayMode";
			resources->ApplyResources(this->EulerWayMode, L"EulerWayMode");
			this->EulerWayMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::EulerWayMode_Click);
			// 
			// shortestPathAlgorithmMode
			// 
			this->shortestPathAlgorithmMode->Name = L"shortestPathAlgorithmMode";
			resources->ApplyResources(this->shortestPathAlgorithmMode, L"shortestPathAlgorithmMode");
			this->shortestPathAlgorithmMode->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::shortestPathAlgorithmMode_Click);
			// 
			// Ù‡ÈÎToolStripMenuItem
			// 
			this->Ù‡ÈÎToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->save,
					this->open, this->clearCanvas
			});
			this->Ù‡ÈÎToolStripMenuItem->Name = L"Ù‡ÈÎToolStripMenuItem";
			resources->ApplyResources(this->Ù‡ÈÎToolStripMenuItem, L"Ù‡ÈÎToolStripMenuItem");
			// 
			// save
			// 
			this->save->Name = L"save";
			resources->ApplyResources(this->save, L"save");
			this->save->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::save_Click);
			// 
			// open
			// 
			this->open->Name = L"open";
			resources->ApplyResources(this->open, L"open");
			this->open->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::open_Click);
			// 
			// clearCanvas
			// 
			this->clearCanvas->Name = L"clearCanvas";
			resources->ApplyResources(this->clearCanvas, L"clearCanvas");
			this->clearCanvas->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::clearCanvas_Click);
			// 
			// directedGraphMarker
			// 
			this->directedGraphMarker->AutoCheck = false;
			resources->ApplyResources(this->directedGraphMarker, L"directedGraphMarker");
			this->directedGraphMarker->BackColor = System::Drawing::Color::Transparent;
			this->directedGraphMarker->ForeColor = System::Drawing::Color::Teal;
			this->directedGraphMarker->Name = L"directedGraphMarker";
			this->directedGraphMarker->TabStop = true;
			this->directedGraphMarker->UseVisualStyleBackColor = false;
			// 
			// weightedGraphMarker
			// 
			this->weightedGraphMarker->AutoCheck = false;
			resources->ApplyResources(this->weightedGraphMarker, L"weightedGraphMarker");
			this->weightedGraphMarker->BackColor = System::Drawing::Color::Transparent;
			this->weightedGraphMarker->ForeColor = System::Drawing::Color::Teal;
			this->weightedGraphMarker->Name = L"weightedGraphMarker";
			this->weightedGraphMarker->TabStop = true;
			this->weightedGraphMarker->UseVisualStyleBackColor = false;
			// 
			// algoModeMarker
			// 
			this->algoModeMarker->AutoCheck = false;
			resources->ApplyResources(this->algoModeMarker, L"algoModeMarker");
			this->algoModeMarker->BackColor = System::Drawing::Color::Transparent;
			this->algoModeMarker->ForeColor = System::Drawing::Color::Crimson;
			this->algoModeMarker->Name = L"algoModeMarker";
			this->algoModeMarker->TabStop = true;
			this->algoModeMarker->UseVisualStyleBackColor = false;
			// 
			// exitAlgoModeButton
			// 
			this->exitAlgoModeButton->BackColor = System::Drawing::Color::MistyRose;
			resources->ApplyResources(this->exitAlgoModeButton, L"exitAlgoModeButton");
			this->exitAlgoModeButton->ForeColor = System::Drawing::Color::Maroon;
			this->exitAlgoModeButton->Name = L"exitAlgoModeButton";
			this->exitAlgoModeButton->UseVisualStyleBackColor = false;
			this->exitAlgoModeButton->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::exitAlgoModeButton_Click);
			// 
			// timer
			// 
			this->timer->Interval = 1000;
			this->timer->Tick += gcnew System::EventHandler(this, &GraphBuilderMainMenu::timer_Tick);
			// 
			// inputWeightBox
			// 
			resources->ApplyResources(this->inputWeightBox, L"inputWeightBox");
			this->inputWeightBox->Name = L"inputWeightBox";
			this->inputWeightBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GraphBuilderMainMenu::inputWeightBox_KeyPress);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog1";
			// 
			// inputFinishPathBox
			// 
			resources->ApplyResources(this->inputFinishPathBox, L"inputFinishPathBox");
			this->inputFinishPathBox->Name = L"inputFinishPathBox";
			// 
			// buttonStartPath
			// 
			this->buttonStartPath->BackColor = System::Drawing::Color::LightCyan;
			resources->ApplyResources(this->buttonStartPath, L"buttonStartPath");
			this->buttonStartPath->ForeColor = System::Drawing::Color::Teal;
			this->buttonStartPath->Name = L"buttonStartPath";
			this->buttonStartPath->UseVisualStyleBackColor = false;
			this->buttonStartPath->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::buttonStartPath_Click);
			// 
			// bridgesAlgo
			// 
			this->bridgesAlgo->Name = L"bridgesAlgo";
			resources->ApplyResources(this->bridgesAlgo, L"bridgesAlgo");
			this->bridgesAlgo->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::bridgesAlgo_Click);
			// 
			// GraphBuilderMainMenu
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Azure;
			this->Controls->Add(this->buttonStartPath);
			this->Controls->Add(this->inputFinishPathBox);
			this->Controls->Add(this->inputWeightBox);
			this->Controls->Add(this->exitAlgoModeButton);
			this->Controls->Add(this->algoModeMarker);
			this->Controls->Add(this->weightedGraphMarker);
			this->Controls->Add(this->directedGraphMarker);
			this->Controls->Add(this->saveChanges);
			this->Controls->Add(this->discardChanges);
			this->Controls->Add(this->BoldnessLabel);
			this->Controls->Add(this->trackBoldness);
			this->Controls->Add(this->RadiusLabel);
			this->Controls->Add(this->trackRadius);
			this->Controls->Add(this->buttonEdgeColor);
			this->Controls->Add(this->SettingsLabel);
			this->Controls->Add(this->buttonVertexColor);
			this->Controls->Add(this->warningLabel);
			this->Controls->Add(this->MainCanvas);
			this->Controls->Add(this->GraphMenu);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->KeyPreview = true;
			this->MainMenuStrip = this->GraphMenu;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"GraphBuilderMainMenu";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &GraphBuilderMainMenu::GraphBuilderMainMenu_FormClosing);
			this->Load += gcnew System::EventHandler(this, &GraphBuilderMainMenu::GraphBuilderMainMenu_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GraphBuilderMainMenu::GraphBuilderMainMenu_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainCanvas))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackRadius))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBoldness))->EndInit();
			this->GraphMenu->ResumeLayout(false);
			this->GraphMenu->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		Graph myGraph;
		viewGraph prewStyle;
		Graphics^ graf;
		bool isMouseDown = false, changePosition = false;
		int numTick = 0;
		int startVertex = -1, finishVertex = -1;
		Vertex* startPosition;
		Vertex* currPosition;
		System::Void MainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void GraphBuilderMainMenu_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonVertexColor_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void settingsTool_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void discardChanges_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void saveChanges_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void trackRadius_Scroll(System::Object^ sender, System::EventArgs^ e);
		System::Void trackBoldness_Scroll(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonEdgeColor_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void MainCanvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void MainCanvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void GraphBuilderMainMenu_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
		System::Void algoMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void exitAlgoModeButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void dfsAlgoMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void topologicalSortAlgoMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e);
		System::Void directedMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void weightedMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void inputWeightBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
		System::Void clearCanvas_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void save_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void open_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void GraphBuilderMainMenu_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
		System::Void bfsAlgoMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void EulerWayMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void shortestPathAlgorithmMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonStartPath_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void notWeightedMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void notDirectedMode_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void bridgesAlgo_Click(System::Object^ sender, System::EventArgs^ e);
};
}
