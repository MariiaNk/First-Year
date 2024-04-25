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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MainCanvas))->BeginInit();
			this->SuspendLayout();
			// 
			// MainCanvas
			// 
			this->MainCanvas->BackColor = System::Drawing::SystemColors::Window;
			this->MainCanvas->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->MainCanvas->Location = System::Drawing::Point(9, 38);
			this->MainCanvas->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->MainCanvas->Name = L"MainCanvas";
			this->MainCanvas->Size = System::Drawing::Size(925, 457);
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
			this->warningLabel->Location = System::Drawing::Point(11, 507);
			this->warningLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->warningLabel->Name = L"warningLabel";
			this->warningLabel->Size = System::Drawing::Size(0, 20);
			this->warningLabel->TabIndex = 8;
			// 
			// GraphBuilderMainMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Azure;
			this->ClientSize = System::Drawing::Size(945, 536);
			this->Controls->Add(this->warningLabel);
			this->Controls->Add(this->MainCanvas);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
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
	};
}
