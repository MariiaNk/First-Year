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
	/// Summary for weighted_graph_edge
	/// </summary>
	public ref class weighted_graph_edge : public System::Windows::Forms::Form
	{
	public:
		weighted_graph_edge(Main^ mainForm)
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
		~weighted_graph_edge()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ start_point;
	private: System::Windows::Forms::TextBox^ finish_point;


	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ weight_temp_edge;

	private: System::Windows::Forms::Button^ button_ok;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(weighted_graph_edge::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->start_point = (gcnew System::Windows::Forms::TextBox());
			this->finish_point = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->weight_temp_edge = (gcnew System::Windows::Forms::TextBox());
			this->button_ok = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::CadetBlue;
			this->label1->Location = System::Drawing::Point(13, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(196, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Початкова вершина";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::CadetBlue;
			this->label2->Location = System::Drawing::Point(13, 55);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(167, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Кінцева вершина";
			// 
			// start_point
			// 
			this->start_point->Location = System::Drawing::Point(247, 24);
			this->start_point->Multiline = true;
			this->start_point->Name = L"start_point";
			this->start_point->Size = System::Drawing::Size(82, 25);
			this->start_point->TabIndex = 2;
			// 
			// finish_point
			// 
			this->finish_point->Location = System::Drawing::Point(247, 55);
			this->finish_point->Multiline = true;
			this->finish_point->Name = L"finish_point";
			this->finish_point->Size = System::Drawing::Size(82, 25);
			this->finish_point->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::CadetBlue;
			this->label3->Location = System::Drawing::Point(13, 86);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(116, 25);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Вага ребра ";
			// 
			// weight_temp_edge
			// 
			this->weight_temp_edge->Location = System::Drawing::Point(247, 86);
			this->weight_temp_edge->Multiline = true;
			this->weight_temp_edge->Name = L"weight_temp_edge";
			this->weight_temp_edge->Size = System::Drawing::Size(82, 25);
			this->weight_temp_edge->TabIndex = 5;
			// 
			// button_ok
			// 
			this->button_ok->BackColor = System::Drawing::Color::CadetBlue;
			this->button_ok->Cursor = System::Windows::Forms::Cursors::Default;
			this->button_ok->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_ok->ForeColor = System::Drawing::Color::Transparent;
			this->button_ok->Location = System::Drawing::Point(197, 117);
			this->button_ok->Name = L"button_ok";
			this->button_ok->Size = System::Drawing::Size(132, 31);
			this->button_ok->TabIndex = 6;
			this->button_ok->Text = L"Внести зміни";
			this->button_ok->UseVisualStyleBackColor = false;
			this->button_ok->Click += gcnew System::EventHandler(this, &weighted_graph_edge::button_ok_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Azure;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::CadetBlue;
			this->label4->Location = System::Drawing::Point(13, 155);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(278, 25);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Потрібно додати вагу ребер:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::CadetBlue;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::Transparent;
			this->label5->Location = System::Drawing::Point(12, 190);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 25);
			this->label5->TabIndex = 8;
			// 
			// weighted_graph_edge
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Azure;
			this->ClientSize = System::Drawing::Size(341, 953);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button_ok);
			this->Controls->Add(this->weight_temp_edge);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->finish_point);
			this->Controls->Add(this->start_point);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"weighted_graph_edge";
			this->Text = L"Вага ребра";
			this->Load += gcnew System::EventHandler(this, &weighted_graph_edge::weighted_graph_edge_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		Main^ MainForm; 
		System::Void button_ok_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void weighted_graph_edge_Load(System::Object^ sender, System::EventArgs^ e);
};
}
