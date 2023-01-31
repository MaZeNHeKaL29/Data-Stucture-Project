#pragma once
#include "MyForm.h"

#using <system.drawing.dll>

namespace XMLProject {

	
	using namespace System::Drawing;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;	

	/// <summary>
	/// Summary for XML_Form
	/// </summary>
	public ref class XML_Form : public System::Windows::Forms::Form
	{
	public:
		XML_Form(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ textBox1;

	private: System::Windows::Forms::Label^ label1;
	private: String^ str_xml;
	private: System::Windows::Forms::Button^ button2;
	private: String^ str_filename;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog2;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: Stream^ myStream;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ button11;
	private: StreamWriter^ sw;
	public: void xml2json(String^ str_filename, String^& str_json);
	public: void xmlprettify(String^ str_filename, String^& str_xml);
	public: void xmlminify(String^ str_filename, String^& str_xml_mini);
	public: void compress(String^ str_filename);
	public: void decompress(String^ str_filename);
	public: void check_xml(String^ str_filename, String^& str_xml_error);
	public: void correct_xml(String^ str_filename, String^& xml_error);
	public: void graph(String^ str_filename, String^& information);
	public: void search_graph(String^ str_filename,String^ search, String^ type, String^& post);
	protected:

	protected:
		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~XML_Form()
		{
			if (components)
			{
				delete components;
			}
		}

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(XML_Form::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 15, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button1->Location = System::Drawing::Point(933, 505);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(141, 41);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Browse";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &XML_Form::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox1->Size = System::Drawing::Size(1064, 380);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(8, 520);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(99, 19);
			this->label1->TabIndex = 3;
			this->label1->Text = L"No XML File";
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button2->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button2->Location = System::Drawing::Point(197, 423);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(172, 41);
			this->button2->TabIndex = 4;
			this->button2->Text = L"XML2JSON";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &XML_Form::button2_Click);
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button3->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button3->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button3->Location = System::Drawing::Point(374, 423);
			this->button3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(165, 41);
			this->button3->TabIndex = 5;
			this->button3->Text = L"XMLPretty";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &XML_Form::button3_Click);
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button4->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button4->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button4->Location = System::Drawing::Point(902, 423);
			this->button4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(172, 41);
			this->button4->TabIndex = 6;
			this->button4->Text = L"CheckXML";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &XML_Form::button4_Click);
			// 
			// button5
			// 
			this->button5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button5->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button5->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button5->Location = System::Drawing::Point(725, 423);
			this->button5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(172, 41);
			this->button5->TabIndex = 7;
			this->button5->Text = L"CorrectXML";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &XML_Form::button5_Click);
			// 
			// button6
			// 
			this->button6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button6->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button6->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button6->Location = System::Drawing::Point(20, 408);
			this->button6->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(172, 41);
			this->button6->TabIndex = 8;
			this->button6->Text = L"Compress";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &XML_Form::button6_Click);
			// 
			// button7
			// 
			this->button7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button7->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button7->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button7->Location = System::Drawing::Point(5, 467);
			this->button7->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(187, 41);
			this->button7->TabIndex = 9;
			this->button7->Text = L"Decompress";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &XML_Form::button7_Click);
			// 
			// button8
			// 
			this->button8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button8->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button8->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button8->Location = System::Drawing::Point(209, 496);
			this->button8->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(172, 41);
			this->button8->TabIndex = 10;
			this->button8->Text = L"Graph";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &XML_Form::button8_Click);
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->FileName = L"openFileDialog2";
			// 
			// button9
			// 
			this->button9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button9->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button9->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button9->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button9->Location = System::Drawing::Point(553, 423);
			this->button9->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(165, 41);
			this->button9->TabIndex = 11;
			this->button9->Text = L"XMLMinify";
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &XML_Form::button9_Click);
			// 
			// button10
			// 
			this->button10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button10->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button10->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 15, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button10->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button10->Location = System::Drawing::Point(786, 505);
			this->button10->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(141, 41);
			this->button10->TabIndex = 12;
			this->button10->Text = L"Save";
			this->button10->UseVisualStyleBackColor = false;
			this->button10->Click += gcnew System::EventHandler(this, &XML_Form::button10_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(422, 478);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(160, 22);
			this->textBox2->TabIndex = 13;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Topic", L"Word" });
			this->comboBox1->Location = System::Drawing::Point(588, 476);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 24);
			this->comboBox1->TabIndex = 14;
			// 
			// button11
			// 
			this->button11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button11->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button11->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button11->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button11->Location = System::Drawing::Point(588, 506);
			this->button11->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(121, 33);
			this->button11->TabIndex = 15;
			this->button11->Text = L"Search";
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &XML_Form::button11_Click);
			// 
			// XML_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1078, 548);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"XML_Form";
			this->Text = L"XML_Form";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog1->InitialDirectory = "C";
		openFileDialog1->Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			myStream = openFileDialog1->OpenFile();
			if ((myStream != nullptr))
			{
				String^ json;
				str_filename = openFileDialog1->FileName;
				str_xml = File::ReadAllText(str_filename);
				label1->Text = "An XML File is Read";
				textBox1->Text = str_xml;
				myStream->Close();
			}
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
    {
		if ((myStream) != nullptr || sw != nullptr)
		{
			String^ json;
			xml2json(str_filename, json);
			textBox1->Text = json;
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if ((myStream) != nullptr || sw != nullptr)
		{
			String^ xml_pretty;
			xmlprettify(str_filename, xml_pretty);
			textBox1->Text = xml_pretty;
		}
	}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	if ((myStream) != nullptr || sw != nullptr)
	{
		compress(str_filename);
		textBox1->Text = "Compressed successfully.";
	}
}
private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	Stream^ myStream2;
	openFileDialog2->InitialDirectory = "C";
	openFileDialog2->Filter = "mcf files (*.mcf)|*.mcf|All files (*.*)|*.*";
	if (openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if ((myStream2 = openFileDialog2->OpenFile()) != nullptr)
		{
			String^ str_filename2 = openFileDialog2->FileName;
			decompress(str_filename2);
			textBox1->Text = "Decompressed successfully.";
			myStream2->Close();
		}
	}
}
private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
	if ((myStream) != nullptr || sw != nullptr)
	{
		String^ xml_pretty;
		xmlminify(str_filename, xml_pretty);
		textBox1->Text = xml_pretty;
	}
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	if ((myStream) != nullptr || sw != nullptr)
	{
		String^ xml_error;
		check_xml(str_filename, xml_error);
		textBox1->Text = xml_error;
	}
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	if ((myStream) != nullptr || sw != nullptr)
	{
		String^ xml_corrected;
		correct_xml(str_filename, xml_corrected);
		textBox1->Text = xml_corrected;
	}
}
private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
	sw = gcnew StreamWriter("xml_created.xml");
	sw->Write(textBox1->Text);
	str_filename = "xml_created.xml";
	label1->Text = "An XML File is Read";
	sw->Close();
}
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
	if ((myStream) != nullptr || sw != nullptr)
	{
		String^ information;
		graph(str_filename, information);
		textBox1->Text = information;
		MyForm^ frm1 = gcnew MyForm;
		frm1->pictureBox1->Image = Image::FromFile("graphVisualization.dot.png");
		frm1->Show();
	}
}
private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e) {
	if ((myStream) != nullptr || sw != nullptr)
	{
		String^ post;
		graph(str_filename, post);
		search_graph(str_filename,textBox2->Text, comboBox1->Text, post);
		textBox1->Text = post;
	}
}
};
}
