#pragma once


namespace GraphBuilder {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{
			InitializeComponent();

			for (int i = 0; i < 1000; i++)
			{
				matrix[i] = new int[1000];
			}
		}
	

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: 
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::Timer^ timer1;
	    System::Windows::Forms::MenuStrip^ menuStrip1;
	    System::Windows::Forms::ColorDialog^ colorDialog1;
	    System::Windows::Forms::ToolStripMenuItem^ file;
	    System::Windows::Forms::ToolStripMenuItem^ settings;
	    System::Windows::Forms::ToolStripMenuItem^ save_graph;
	    System::Windows::Forms::ToolStripMenuItem^ open_graph;
	    System::Windows::Forms::Label^ warning_label;
	    System::Windows::Forms::ToolStripMenuItem^ type_graph;
	    System::Windows::Forms::ToolStripMenuItem^ choose_weighted_graph;
	    System::Windows::Forms::ToolStripMenuItem^ choose_directed_graph;
	    System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	    System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	    System::Windows::Forms::ToolStripMenuItem^ алгоритмиToolStripMenuItem;
	    System::Windows::Forms::ToolStripMenuItem^ DepthFirstSearch;
	    System::Windows::Forms::Button^ button_next_step;
	    System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	    System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	    System::Windows::Forms::DataGridView^ about_graph;
	    System::Windows::Forms::ToolStripMenuItem^ EulerWay;
	    System::Windows::Forms::ToolStripMenuItem^ TopologicalSort;
	    System::Windows::Forms::ToolStripMenuItem^ LookingForBridge;
	    System::Windows::Forms::ToolStripMenuItem^ ClaerAll;
	    System::Windows::Forms::TextBox^ StInput;
	    System::Windows::Forms::TextBox^ FnInput;
	    System::Windows::Forms::ToolStripMenuItem^ Dejkstra;
	    System::ComponentModel::IContainer^ components;
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
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->file = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->save_graph = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->open_graph = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ClaerAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->settings = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->type_graph = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->choose_weighted_graph = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->choose_directed_graph = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->алгоритмиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DepthFirstSearch = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EulerWay = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TopologicalSort = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LookingForBridge = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Dejkstra = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->warning_label = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button_next_step = (gcnew System::Windows::Forms::Button());
			this->about_graph = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StInput = (gcnew System::Windows::Forms::TextBox());
			this->FnInput = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->about_graph))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(16, 42);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(877, 416);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::pictureBox1_MouseUp);
			// 
			// timer1
			// 
			this->timer1->Interval = 50;
			this->timer1->Tick += gcnew System::EventHandler(this, &Main::timer1_Tick);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->file, this->settings,
					this->type_graph, this->алгоритмиToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(5, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1153, 26);
			this->menuStrip1->TabIndex = 6;
			// 
			// file
			// 
			this->file->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->save_graph, this->open_graph,
					this->ClaerAll
			});
			this->file->Name = L"file";
			this->file->Size = System::Drawing::Size(60, 22);
			this->file->Text = L"Файл";
			// 
			// save_graph
			// 
			this->save_graph->Name = L"save_graph";
			this->save_graph->Size = System::Drawing::Size(219, 26);
			this->save_graph->Text = L"Зберегти граф";
			this->save_graph->Click += gcnew System::EventHandler(this, &Main::save_graph_Click);
			// 
			// open_graph
			// 
			this->open_graph->Name = L"open_graph";
			this->open_graph->Size = System::Drawing::Size(219, 26);
			this->open_graph->Text = L"Відкрити граф";
			this->open_graph->Click += gcnew System::EventHandler(this, &Main::open_graph_Click);
			// 
			// ClaerAll
			// 
			this->ClaerAll->Name = L"ClaerAll";
			this->ClaerAll->Size = System::Drawing::Size(219, 26);
			this->ClaerAll->Text = L"Очистити полотно";
			this->ClaerAll->Click += gcnew System::EventHandler(this, &Main::ClaerAll_Click);
			// 
			// settings
			// 
			this->settings->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settings->Name = L"settings";
			this->settings->Size = System::Drawing::Size(99, 22);
			this->settings->Text = L"Параметри";
			this->settings->Click += gcnew System::EventHandler(this, &Main::settings_Click);
			// 
			// type_graph
			// 
			this->type_graph->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->choose_weighted_graph,
					this->choose_directed_graph
			});
			this->type_graph->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->type_graph->Name = L"type_graph";
			this->type_graph->Size = System::Drawing::Size(93, 22);
			this->type_graph->Text = L"Тип графу";
			// 
			// choose_weighted_graph
			// 
			this->choose_weighted_graph->Name = L"choose_weighted_graph";
			this->choose_weighted_graph->Size = System::Drawing::Size(185, 26);
			this->choose_weighted_graph->Text = L"Зважений";
			this->choose_weighted_graph->Click += gcnew System::EventHandler(this, &Main::choose_weighted_graph_Click);
			// 
			// choose_directed_graph
			// 
			this->choose_directed_graph->Name = L"choose_directed_graph";
			this->choose_directed_graph->Size = System::Drawing::Size(185, 26);
			this->choose_directed_graph->Text = L"Орієнтований";
			this->choose_directed_graph->Click += gcnew System::EventHandler(this, &Main::choose_directed_graph_Click);
			// 
			// алгоритмиToolStripMenuItem
			// 
			this->алгоритмиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->DepthFirstSearch,
					this->EulerWay, this->TopologicalSort, this->LookingForBridge, this->Dejkstra
			});
			this->алгоритмиToolStripMenuItem->Name = L"алгоритмиToolStripMenuItem";
			this->алгоритмиToolStripMenuItem->Size = System::Drawing::Size(97, 22);
			this->алгоритмиToolStripMenuItem->Text = L"Алгоритми";
			// 
			// DepthFirstSearch
			// 
			this->DepthFirstSearch->Name = L"DepthFirstSearch";
			this->DepthFirstSearch->Size = System::Drawing::Size(259, 26);
			this->DepthFirstSearch->Text = L"Пошук в глибину";
			this->DepthFirstSearch->Click += gcnew System::EventHandler(this, &Main::DepthFirstSearch_Click);
			// 
			// EulerWay
			// 
			this->EulerWay->Name = L"EulerWay";
			this->EulerWay->Size = System::Drawing::Size(259, 26);
			this->EulerWay->Text = L"Ейлерів шлях";
			this->EulerWay->Click += gcnew System::EventHandler(this, &Main::EulerWay_Click);
			// 
			// TopologicalSort
			// 
			this->TopologicalSort->Name = L"TopologicalSort";
			this->TopologicalSort->Size = System::Drawing::Size(259, 26);
			this->TopologicalSort->Text = L"Топологічне сортування";
			this->TopologicalSort->Click += gcnew System::EventHandler(this, &Main::TopologicalSort_Click);
			// 
			// LookingForBridge
			// 
			this->LookingForBridge->Name = L"LookingForBridge";
			this->LookingForBridge->Size = System::Drawing::Size(259, 26);
			this->LookingForBridge->Text = L"Пошук мостів";
			this->LookingForBridge->Click += gcnew System::EventHandler(this, &Main::LookingForBridge_Click);
			// 
			// Dejkstra
			// 
			this->Dejkstra->Name = L"Dejkstra";
			this->Dejkstra->Size = System::Drawing::Size(259, 26);
			this->Dejkstra->Text = L"Мінімальний шлях";
			this->Dejkstra->Click += gcnew System::EventHandler(this, &Main::Dejkstra_Click);
			// 
			// warning_label
			// 
			this->warning_label->AutoSize = true;
			this->warning_label->BackColor = System::Drawing::Color::Transparent;
			this->warning_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->warning_label->ForeColor = System::Drawing::Color::Red;
			this->warning_label->Location = System::Drawing::Point(22, 475);
			this->warning_label->Name = L"warning_label";
			this->warning_label->Size = System::Drawing::Size(0, 25);
			this->warning_label->TabIndex = 7;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button_next_step
			// 
			this->button_next_step->BackColor = System::Drawing::Color::MintCream;
			this->button_next_step->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_next_step->Location = System::Drawing::Point(16, 518);
			this->button_next_step->Name = L"button_next_step";
			this->button_next_step->Size = System::Drawing::Size(152, 38);
			this->button_next_step->TabIndex = 8;
			this->button_next_step->Text = L"Наступний крок";
			this->button_next_step->UseVisualStyleBackColor = false;
			this->button_next_step->Visible = false;
			this->button_next_step->Click += gcnew System::EventHandler(this, &Main::button_next_step_Click);
			// 
			// about_graph
			// 
			this->about_graph->AllowUserToAddRows = false;
			this->about_graph->AllowUserToDeleteRows = false;
			this->about_graph->BackgroundColor = System::Drawing::Color::White;
			this->about_graph->ClipboardCopyMode = System::Windows::Forms::DataGridViewClipboardCopyMode::Disable;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::Color::DarkCyan;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::Color::DarkCyan;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->about_graph->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->about_graph->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->about_graph->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->Column1,
					this->Column2
			});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::Color::DarkCyan;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::Color::DarkCyan;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->about_graph->DefaultCellStyle = dataGridViewCellStyle2;
			this->about_graph->Enabled = false;
			this->about_graph->Location = System::Drawing::Point(900, 42);
			this->about_graph->Name = L"about_graph";
			this->about_graph->ReadOnly = true;
			this->about_graph->RowHeadersVisible = false;
			this->about_graph->RowHeadersWidth = 51;
			this->about_graph->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->about_graph->RowTemplate->Height = 24;
			this->about_graph->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->about_graph->Size = System::Drawing::Size(240, 416);
			this->about_graph->TabIndex = 9;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Властивість";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 120;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Статус";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Width = 120;
			// 
			// StInput
			// 
			this->StInput->Location = System::Drawing::Point(16, 475);
			this->StInput->Multiline = true;
			this->StInput->Name = L"StInput";
			this->StInput->Size = System::Drawing::Size(67, 37);
			this->StInput->TabIndex = 10;
			this->StInput->Text = L"Старт";
			this->StInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->StInput->Visible = false;
			// 
			// FnInput
			// 
			this->FnInput->Location = System::Drawing::Point(101, 475);
			this->FnInput->Multiline = true;
			this->FnInput->Name = L"FnInput";
			this->FnInput->Size = System::Drawing::Size(67, 37);
			this->FnInput->TabIndex = 11;
			this->FnInput->Text = L"Фініш";
			this->FnInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->FnInput->Visible = false;
			// 
			// Main
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::LightCyan;
			this->ClientSize = System::Drawing::Size(1153, 568);
			this->Controls->Add(this->FnInput);
			this->Controls->Add(this->StInput);
			this->Controls->Add(this->about_graph);
			this->Controls->Add(this->button_next_step);
			this->Controls->Add(this->warning_label);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->ForeColor = System::Drawing::Color::DarkCyan;
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"Main";
			this->Text = L"Графобудівник";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::Main_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->about_graph))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		String ^ windir = System::Environment::GetEnvironmentVariable("Windir");
		System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void Main_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
		System::Void GraphBuilder::Main::redraw_graph(Graphics^ graf);
		System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void open_graph_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void Main_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		System::Void choose_weighted_graph_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void choose_directed_graph_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void save_graph_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void DepthFirstSearch_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button_next_step_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void settings_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void EulerWay_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void TopologicalSort_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void GraphBuilder::Main::ClearAlgo();
		System::Void GraphBuilder::Main::StartAlgo();
		System::Void LookingForBridge_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ClaerAll_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void Dejkstra_Click(System::Object^ sender, System::EventArgs^ e);
	public:
		Brush^ vertex_color = Brushes::GreenYellow;
		Brush^ edge_color = Brushes::CadetBlue;
		int R = 15;
		int boldness = 8;
		int change = false;
		int weight_edge = 0;
		int cnt_weighted_edge = 0;
		int** matrix = new int*[1000];
		int cnt_point = 0;
		int cnt_edge = 0;
		bool directed_graph = false;
		int max_radius = 15;



};

}
