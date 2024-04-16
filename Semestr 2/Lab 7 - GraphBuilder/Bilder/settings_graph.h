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
	/// Summary for settings_graph
	/// </summary>
	public ref class settings_graph : public System::Windows::Forms::Form
	{
	public:
		settings_graph(Main^ mainForm)
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
		~settings_graph()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ColorDialog^ colorDialog1;
	protected:
	private: System::Windows::Forms::Button^ color_vertex;
	private: System::Windows::Forms::Button^ color_edge;
	private: System::Windows::Forms::Label^ boldness_edge;
	private: System::Windows::Forms::Label^ radius_vertex;


	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TrackBar^ choose_radius;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::TrackBar^ choose_boldness;
	private: System::Windows::Forms::Button^ button1;
	private: System::ComponentModel::IContainer^ components;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(settings_graph::typeid));
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->color_vertex = (gcnew System::Windows::Forms::Button());
			this->color_edge = (gcnew System::Windows::Forms::Button());
			this->boldness_edge = (gcnew System::Windows::Forms::Label());
			this->radius_vertex = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->choose_radius = (gcnew System::Windows::Forms::TrackBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->choose_boldness = (gcnew System::Windows::Forms::TrackBar());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->choose_radius))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->choose_boldness))->BeginInit();
			this->SuspendLayout();
			// 
			// color_vertex
			// 
			this->color_vertex->BackColor = System::Drawing::Color::White;
			this->color_vertex->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->color_vertex->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->color_vertex->ForeColor = System::Drawing::Color::Teal;
			this->color_vertex->Location = System::Drawing::Point(12, 110);
			this->color_vertex->Name = L"color_vertex";
			this->color_vertex->Size = System::Drawing::Size(133, 46);
			this->color_vertex->TabIndex = 0;
			this->color_vertex->Text = L"Колір вершини";
			this->color_vertex->UseVisualStyleBackColor = false;
			this->color_vertex->Click += gcnew System::EventHandler(this, &settings_graph::color_vertex_Click);
			// 
			// color_edge
			// 
			this->color_edge->BackColor = System::Drawing::Color::White;
			this->color_edge->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->color_edge->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->color_edge->ForeColor = System::Drawing::Color::Teal;
			this->color_edge->Location = System::Drawing::Point(9, 300);
			this->color_edge->Name = L"color_edge";
			this->color_edge->Size = System::Drawing::Size(133, 46);
			this->color_edge->TabIndex = 1;
			this->color_edge->Text = L"Колір ребра";
			this->color_edge->UseVisualStyleBackColor = false;
			this->color_edge->Click += gcnew System::EventHandler(this, &settings_graph::color_edge_Click);
			// 
			// boldness_edge
			// 
			this->boldness_edge->BackColor = System::Drawing::Color::Azure;
			this->boldness_edge->ForeColor = System::Drawing::Color::Teal;
			this->boldness_edge->Location = System::Drawing::Point(3, 197);
			this->boldness_edge->Name = L"boldness_edge";
			this->boldness_edge->Size = System::Drawing::Size(133, 25);
			this->boldness_edge->TabIndex = 2;
			this->boldness_edge->Text = L"Товщина ребра";
			this->boldness_edge->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// radius_vertex
			// 
			this->radius_vertex->BackColor = System::Drawing::Color::Azure;
			this->radius_vertex->ForeColor = System::Drawing::Color::Teal;
			this->radius_vertex->Location = System::Drawing::Point(12, 20);
			this->radius_vertex->Name = L"radius_vertex";
			this->radius_vertex->Size = System::Drawing::Size(133, 25);
			this->radius_vertex->TabIndex = 3;
			this->radius_vertex->Text = L"Радіус вершини";
			this->radius_vertex->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Azure;
			this->pictureBox1->Location = System::Drawing::Point(152, 18);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(400, 400);
			this->pictureBox1->TabIndex = 6;
			this->pictureBox1->TabStop = false;
			// 
			// choose_radius
			// 
			this->choose_radius->Location = System::Drawing::Point(12, 48);
			this->choose_radius->Name = L"choose_radius";
			this->choose_radius->Size = System::Drawing::Size(130, 56);
			this->choose_radius->TabIndex = 7;
			this->choose_radius->Scroll += gcnew System::EventHandler(this, &settings_graph::choose_radius_Scroll);
			// 
			// timer1
			// 
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &settings_graph::timer1_Tick);
			// 
			// choose_boldness
			// 
			this->choose_boldness->Location = System::Drawing::Point(9, 225);
			this->choose_boldness->Name = L"choose_boldness";
			this->choose_boldness->Size = System::Drawing::Size(130, 56);
			this->choose_boldness->TabIndex = 8;
			this->choose_boldness->Scroll += gcnew System::EventHandler(this, &settings_graph::choose_boldness_Scroll);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::LightBlue;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::Teal;
			this->button1->Location = System::Drawing::Point(9, 362);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(133, 56);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Застосувати зміни";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &settings_graph::button1_Click);
			// 
			// settings_graph
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Azure;
			this->ClientSize = System::Drawing::Size(564, 430);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->choose_boldness);
			this->Controls->Add(this->choose_radius);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->radius_vertex);
			this->Controls->Add(this->boldness_edge);
			this->Controls->Add(this->color_edge);
			this->Controls->Add(this->color_vertex);
			//this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"settings_graph";
			this->Text = L"Параметри";
			this->Load += gcnew System::EventHandler(this, &settings_graph::settings_graph_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->choose_radius))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->choose_boldness))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		Main^ MainForm; 
		System::Void GraphBuilder::settings_graph::redraw_graph();
		System::Void settings_graph_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void choose_radius_Scroll(System::Object^ sender, System::EventArgs^ e);
		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
		System::Void color_edge_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void choose_boldness_Scroll(System::Object^ sender, System::EventArgs^ e);
		System::Void color_vertex_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
};
}
