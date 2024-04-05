#pragma once
#include "Main.h"

namespace GraphBuilder {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for input_weighted_edge
	/// </summary>
	public ref class input_weighted_edge : public System::Windows::Forms::Form
	{
	public:
		input_weighted_edge(Main^ mainForm)
		{
			MainForm = mainForm;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~input_weighted_edge()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ input_weighted;
	protected:

	private: System::Windows::Forms::Button^ button_ok;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(input_weighted_edge::typeid));
			this->input_weighted = (gcnew System::Windows::Forms::TextBox());
			this->button_ok = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// input_weighted
			// 
			this->input_weighted->Font = (gcnew System::Drawing::Font(L"Tahoma", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input_weighted->Location = System::Drawing::Point(12, 12);
			this->input_weighted->Multiline = true;
			this->input_weighted->Name = L"input_weighted";
			this->input_weighted->Size = System::Drawing::Size(295, 70);
			this->input_weighted->TabIndex = 3;
			this->input_weighted->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button_ok
			// 
			this->button_ok->BackColor = System::Drawing::Color::CadetBlue;
			this->button_ok->Cursor = System::Windows::Forms::Cursors::Default;
			this->button_ok->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_ok->ForeColor = System::Drawing::Color::Transparent;
			this->button_ok->Location = System::Drawing::Point(175, 88);
			this->button_ok->Name = L"button_ok";
			this->button_ok->Size = System::Drawing::Size(132, 31);
			this->button_ok->TabIndex = 2;
			this->button_ok->Text = L"Внести зміни";
			this->button_ok->UseVisualStyleBackColor = false;
			this->button_ok->Click += gcnew System::EventHandler(this, &input_weighted_edge::button_ok_Click);
			// 
			// input_weighted_edge
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(317, 130);
			this->Controls->Add(this->input_weighted);
			this->Controls->Add(this->button_ok);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"input_weighted_edge";
			this->Text = L"Вага ребра";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		Main^ MainForm;
		System::Void button_ok_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
