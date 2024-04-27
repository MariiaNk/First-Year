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
	private: System::Windows::Forms::PictureBox^ MainCanvas;
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
			this->MainCanvas->Location = System::Drawing::Point(12, 47);
			this->MainCanvas->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->MainCanvas->Name = L"MainCanvas";
			this->MainCanvas->Size = System::Drawing::Size(1194, 562);
			this->MainCanvas->TabIndex = 0;
			this->MainCanvas->TabStop = false;
			this->MainCanvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphBuilderMainMenu::MainCanvas_MouseDown);
			this->MainCanvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphBuilderMainMenu::MainCanvas_MouseMove);
			this->MainCanvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphBuilderMainMenu::MainCanvas_MouseUp);
			// 
			// warningLabel
			// 
			this->warningLabel->AutoSize = true;
			this->warningLabel->BackColor = System::Drawing::Color::Transparent;
			this->warningLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->warningLabel->ForeColor = System::Drawing::Color::Red;
			this->warningLabel->Location = System::Drawing::Point(15, 624);
			this->warningLabel->Name = L"warningLabel";
			this->warningLabel->Size = System::Drawing::Size(0, 25);
			this->warningLabel->TabIndex = 8;
			// 
			// buttonVertexColor
			// 
			this->buttonVertexColor->BackColor = System::Drawing::Color::LightCyan;
			this->buttonVertexColor->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonVertexColor->Font = (gcnew System::Drawing::Font(L"Miriam Libre", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonVertexColor->ForeColor = System::Drawing::Color::Teal;
			this->buttonVertexColor->Location = System::Drawing::Point(1225, 103);
			this->buttonVertexColor->Name = L"buttonVertexColor";
			this->buttonVertexColor->Size = System::Drawing::Size(257, 52);
			this->buttonVertexColor->TabIndex = 9;
			this->buttonVertexColor->Text = L"Колір вершин";
			this->buttonVertexColor->UseVisualStyleBackColor = false;
			this->buttonVertexColor->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::buttonVertexColor_Click);
			// 
			// SettingsLabel
			// 
			this->SettingsLabel->AutoSize = true;
			this->SettingsLabel->Font = (gcnew System::Drawing::Font(L"Miriam Libre", 13.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SettingsLabel->ForeColor = System::Drawing::Color::Teal;
			this->SettingsLabel->Location = System::Drawing::Point(1235, 58);
			this->SettingsLabel->Name = L"SettingsLabel";
			this->SettingsLabel->Size = System::Drawing::Size(235, 30);
			this->SettingsLabel->TabIndex = 11;
			this->SettingsLabel->Text = L"Параметри графу";
			this->SettingsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// buttonEdgeColor
			// 
			this->buttonEdgeColor->BackColor = System::Drawing::Color::LightCyan;
			this->buttonEdgeColor->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonEdgeColor->Font = (gcnew System::Drawing::Font(L"Miriam Libre", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonEdgeColor->ForeColor = System::Drawing::Color::Teal;
			this->buttonEdgeColor->Location = System::Drawing::Point(1225, 265);
			this->buttonEdgeColor->Name = L"buttonEdgeColor";
			this->buttonEdgeColor->Size = System::Drawing::Size(257, 52);
			this->buttonEdgeColor->TabIndex = 12;
			this->buttonEdgeColor->Text = L"Колір ребра";
			this->buttonEdgeColor->UseVisualStyleBackColor = false;
			this->buttonEdgeColor->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::buttonEdgeColor_Click);
			// 
			// trackRadius
			// 
			this->trackRadius->Location = System::Drawing::Point(1225, 187);
			this->trackRadius->Maximum = 50;
			this->trackRadius->Minimum = 10;
			this->trackRadius->Name = L"trackRadius";
			this->trackRadius->Size = System::Drawing::Size(257, 56);
			this->trackRadius->TabIndex = 13;
			this->trackRadius->Value = 10;
			this->trackRadius->Scroll += gcnew System::EventHandler(this, &GraphBuilderMainMenu::trackRadius_Scroll);
			// 
			// RadiusLabel
			// 
			this->RadiusLabel->AutoSize = true;
			this->RadiusLabel->Font = (gcnew System::Drawing::Font(L"Miriam Libre", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RadiusLabel->ForeColor = System::Drawing::Color::Teal;
			this->RadiusLabel->Location = System::Drawing::Point(1291, 165);
			this->RadiusLabel->Name = L"RadiusLabel";
			this->RadiusLabel->Size = System::Drawing::Size(134, 24);
			this->RadiusLabel->TabIndex = 14;
			this->RadiusLabel->Text = L"Радіус вершин";
			this->RadiusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// BoldnessLabel
			// 
			this->BoldnessLabel->AutoSize = true;
			this->BoldnessLabel->Font = (gcnew System::Drawing::Font(L"Miriam Libre", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BoldnessLabel->ForeColor = System::Drawing::Color::Teal;
			this->BoldnessLabel->Location = System::Drawing::Point(1291, 331);
			this->BoldnessLabel->Name = L"BoldnessLabel";
			this->BoldnessLabel->Size = System::Drawing::Size(142, 24);
			this->BoldnessLabel->TabIndex = 16;
			this->BoldnessLabel->Text = L"Товщина ребра";
			this->BoldnessLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// trackBoldness
			// 
			this->trackBoldness->Location = System::Drawing::Point(1225, 353);
			this->trackBoldness->Maximum = 50;
			this->trackBoldness->Minimum = 10;
			this->trackBoldness->Name = L"trackBoldness";
			this->trackBoldness->Size = System::Drawing::Size(257, 56);
			this->trackBoldness->TabIndex = 15;
			this->trackBoldness->Value = 10;
			this->trackBoldness->Scroll += gcnew System::EventHandler(this, &GraphBuilderMainMenu::trackBoldness_Scroll);
			// 
			// discardChanges
			// 
			this->discardChanges->BackColor = System::Drawing::Color::MistyRose;
			this->discardChanges->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->discardChanges->Font = (gcnew System::Drawing::Font(L"Miriam Libre", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->discardChanges->ForeColor = System::Drawing::Color::Maroon;
			this->discardChanges->Location = System::Drawing::Point(1225, 499);
			this->discardChanges->Name = L"discardChanges";
			this->discardChanges->Size = System::Drawing::Size(257, 52);
			this->discardChanges->TabIndex = 17;
			this->discardChanges->Text = L"Відхилиити зміни";
			this->discardChanges->UseVisualStyleBackColor = false;
			this->discardChanges->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::discardChanges_Click);
			// 
			// saveChanges
			// 
			this->saveChanges->BackColor = System::Drawing::Color::LightCyan;
			this->saveChanges->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->saveChanges->Font = (gcnew System::Drawing::Font(L"Miriam Libre", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->saveChanges->ForeColor = System::Drawing::Color::Teal;
			this->saveChanges->Location = System::Drawing::Point(1225, 557);
			this->saveChanges->Name = L"saveChanges";
			this->saveChanges->Size = System::Drawing::Size(257, 52);
			this->saveChanges->TabIndex = 18;
			this->saveChanges->Text = L"Зберегти зміни";
			this->saveChanges->UseVisualStyleBackColor = false;
			this->saveChanges->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::saveChanges_Click);
			// 
			// GraphMenu
			// 
			this->GraphMenu->BackColor = System::Drawing::Color::PowderBlue;
			this->GraphMenu->ImageScalingSize = System::Drawing::Size(20, 20);
			this->GraphMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->settingsTool });
			this->GraphMenu->Location = System::Drawing::Point(0, 0);
			this->GraphMenu->Name = L"GraphMenu";
			this->GraphMenu->Size = System::Drawing::Size(1499, 28);
			this->GraphMenu->TabIndex = 19;
			this->GraphMenu->Text = L"GraphMenu";
			// 
			// settingsTool
			// 
			this->settingsTool->Name = L"settingsTool";
			this->settingsTool->Size = System::Drawing::Size(102, 24);
			this->settingsTool->Text = L"Параметри";
			this->settingsTool->Click += gcnew System::EventHandler(this, &GraphBuilderMainMenu::settingsTool_Click);
			// 
			// GraphBuilderMainMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Azure;
			this->ClientSize = System::Drawing::Size(1499, 660);
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
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MainMenuStrip = this->GraphMenu;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"GraphBuilderMainMenu";
			this->Text = L"Графобудівник";
			this->Load += gcnew System::EventHandler(this, &GraphBuilderMainMenu::GraphBuilderMainMenu_Load);
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
};
}
