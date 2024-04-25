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

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainCanvas))->BeginInit();
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
			// 
			// GraphBuilderMainMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Azure;
			this->ClientSize = System::Drawing::Size(1499, 660);
			this->Controls->Add(this->buttonEdgeColor);
			this->Controls->Add(this->SettingsLabel);
			this->Controls->Add(this->buttonVertexColor);
			this->Controls->Add(this->warningLabel);
			this->Controls->Add(this->MainCanvas);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"GraphBuilderMainMenu";
			this->Text = L"Графобудівник";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainCanvas))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		Graph myGraph;
		System::Void MainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void progressBar1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
