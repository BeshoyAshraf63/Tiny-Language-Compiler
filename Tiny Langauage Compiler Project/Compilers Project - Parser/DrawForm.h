#pragma once
#include <iostream>
#include "Tree.h"
#include <fstream>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "Parser.h"
#include "Scanner.h"

#define NEW_FILE_INIT_NAME	"newFile.txt"

namespace CompilersProjectParser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DrawForm
	/// </summary>
	public ref class DrawForm : public System::Windows::Forms::Form
	{
	public:
		DrawForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			syntaxTree = nullptr;
			shouldDraw = false;
			shouldShowScannerOutput = false;
			openFile = gcnew String("");
			fileModified = true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DrawForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btn_generate_tree;
	protected:


	private: System::Windows::Forms::Panel^ pnl_editor_top;

	private: System::Windows::Forms::Panel^ pnl_draw;
	private: System::Windows::Forms::Panel^ pnl_draw_container;
	private: System::Windows::Forms::Button^ btn_export_png;
	private: System::Windows::Forms::TabControl^ tab_container;

	private: System::Windows::Forms::TabPage^ tab_editor;
	private: System::Windows::Forms::TabPage^ tab_tree;



	private: System::Windows::Forms::Panel^ pnl_syntax_top;
	private: System::Windows::Forms::Button^ btn_load_file;
	private: System::Windows::Forms::Button^ btn_check_sntx;
	private: System::Windows::Forms::Button^ btn_save_file;
	private: System::Windows::Forms::TextBox^ txt_editor;
	private: System::Windows::Forms::Panel^ pnl_txt_editor_container;
	private: System::Windows::Forms::Panel^ pnl_editor_bottom;
	private: System::Windows::Forms::Label^ lbl_file_name;
	private: System::Windows::Forms::Label^ lbl_file_name_static;
	private: System::Windows::Forms::Button^ btn_new_file;
	private: System::Windows::Forms::TabPage^ tab_scanner;
	private: System::Windows::Forms::TextBox^ txt_scanner_str;





	protected:

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
			this->btn_generate_tree = (gcnew System::Windows::Forms::Button());
			this->pnl_editor_top = (gcnew System::Windows::Forms::Panel());
			this->btn_new_file = (gcnew System::Windows::Forms::Button());
			this->btn_save_file = (gcnew System::Windows::Forms::Button());
			this->btn_load_file = (gcnew System::Windows::Forms::Button());
			this->btn_check_sntx = (gcnew System::Windows::Forms::Button());
			this->btn_export_png = (gcnew System::Windows::Forms::Button());
			this->pnl_draw = (gcnew System::Windows::Forms::Panel());
			this->pnl_draw_container = (gcnew System::Windows::Forms::Panel());
			this->tab_container = (gcnew System::Windows::Forms::TabControl());
			this->tab_editor = (gcnew System::Windows::Forms::TabPage());
			this->pnl_txt_editor_container = (gcnew System::Windows::Forms::Panel());
			this->txt_editor = (gcnew System::Windows::Forms::TextBox());
			this->pnl_editor_bottom = (gcnew System::Windows::Forms::Panel());
			this->lbl_file_name = (gcnew System::Windows::Forms::Label());
			this->lbl_file_name_static = (gcnew System::Windows::Forms::Label());
			this->tab_scanner = (gcnew System::Windows::Forms::TabPage());
			this->tab_tree = (gcnew System::Windows::Forms::TabPage());
			this->pnl_syntax_top = (gcnew System::Windows::Forms::Panel());
			this->txt_scanner_str = (gcnew System::Windows::Forms::TextBox());
			this->pnl_editor_top->SuspendLayout();
			this->pnl_draw_container->SuspendLayout();
			this->tab_container->SuspendLayout();
			this->tab_editor->SuspendLayout();
			this->pnl_txt_editor_container->SuspendLayout();
			this->pnl_editor_bottom->SuspendLayout();
			this->tab_scanner->SuspendLayout();
			this->tab_tree->SuspendLayout();
			this->pnl_syntax_top->SuspendLayout();
			this->SuspendLayout();
			// 
			// btn_generate_tree
			// 
			this->btn_generate_tree->Dock = System::Windows::Forms::DockStyle::Right;
			this->btn_generate_tree->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_generate_tree->Location = System::Drawing::Point(766, 0);
			this->btn_generate_tree->Margin = System::Windows::Forms::Padding(0);
			this->btn_generate_tree->Name = L"btn_generate_tree";
			this->btn_generate_tree->Size = System::Drawing::Size(200, 45);
			this->btn_generate_tree->TabIndex = 1;
			this->btn_generate_tree->Text = L"Generate Syntax Tree";
			this->btn_generate_tree->UseVisualStyleBackColor = true;
			this->btn_generate_tree->Click += gcnew System::EventHandler(this, &DrawForm::btn_generate_tree_Click);
			// 
			// pnl_editor_top
			// 
			this->pnl_editor_top->BackColor = System::Drawing::Color::WhiteSmoke;
			this->pnl_editor_top->Controls->Add(this->btn_new_file);
			this->pnl_editor_top->Controls->Add(this->btn_save_file);
			this->pnl_editor_top->Controls->Add(this->btn_load_file);
			this->pnl_editor_top->Controls->Add(this->btn_check_sntx);
			this->pnl_editor_top->Controls->Add(this->btn_generate_tree);
			this->pnl_editor_top->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnl_editor_top->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pnl_editor_top->Location = System::Drawing::Point(0, 0);
			this->pnl_editor_top->Name = L"pnl_editor_top";
			this->pnl_editor_top->Size = System::Drawing::Size(966, 45);
			this->pnl_editor_top->TabIndex = 2;
			// 
			// btn_new_file
			// 
			this->btn_new_file->Dock = System::Windows::Forms::DockStyle::Left;
			this->btn_new_file->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_new_file->Location = System::Drawing::Point(266, 0);
			this->btn_new_file->Margin = System::Windows::Forms::Padding(0);
			this->btn_new_file->Name = L"btn_new_file";
			this->btn_new_file->Size = System::Drawing::Size(133, 45);
			this->btn_new_file->TabIndex = 5;
			this->btn_new_file->Text = L"New File";
			this->btn_new_file->UseVisualStyleBackColor = true;
			this->btn_new_file->Click += gcnew System::EventHandler(this, &DrawForm::btn_new_file_Click);
			// 
			// btn_save_file
			// 
			this->btn_save_file->Dock = System::Windows::Forms::DockStyle::Left;
			this->btn_save_file->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_save_file->Location = System::Drawing::Point(133, 0);
			this->btn_save_file->Margin = System::Windows::Forms::Padding(0);
			this->btn_save_file->Name = L"btn_save_file";
			this->btn_save_file->Size = System::Drawing::Size(133, 45);
			this->btn_save_file->TabIndex = 4;
			this->btn_save_file->Text = L"Save File";
			this->btn_save_file->UseVisualStyleBackColor = true;
			this->btn_save_file->Click += gcnew System::EventHandler(this, &DrawForm::btn_save_file_Click);
			// 
			// btn_load_file
			// 
			this->btn_load_file->Dock = System::Windows::Forms::DockStyle::Left;
			this->btn_load_file->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_load_file->Location = System::Drawing::Point(0, 0);
			this->btn_load_file->Margin = System::Windows::Forms::Padding(0);
			this->btn_load_file->Name = L"btn_load_file";
			this->btn_load_file->Size = System::Drawing::Size(133, 45);
			this->btn_load_file->TabIndex = 3;
			this->btn_load_file->Text = L"Load File";
			this->btn_load_file->UseVisualStyleBackColor = true;
			this->btn_load_file->Click += gcnew System::EventHandler(this, &DrawForm::btn_load_file_Click);
			// 
			// btn_check_sntx
			// 
			this->btn_check_sntx->Dock = System::Windows::Forms::DockStyle::Right;
			this->btn_check_sntx->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_check_sntx->Location = System::Drawing::Point(566, 0);
			this->btn_check_sntx->Margin = System::Windows::Forms::Padding(0);
			this->btn_check_sntx->Name = L"btn_check_sntx";
			this->btn_check_sntx->Size = System::Drawing::Size(200, 45);
			this->btn_check_sntx->TabIndex = 2;
			this->btn_check_sntx->Text = L"Check Syntax";
			this->btn_check_sntx->UseVisualStyleBackColor = true;
			this->btn_check_sntx->Click += gcnew System::EventHandler(this, &DrawForm::btn_check_sntx_Click);
			// 
			// btn_export_png
			// 
			this->btn_export_png->Dock = System::Windows::Forms::DockStyle::Right;
			this->btn_export_png->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_export_png->Location = System::Drawing::Point(766, 0);
			this->btn_export_png->Name = L"btn_export_png";
			this->btn_export_png->Size = System::Drawing::Size(200, 45);
			this->btn_export_png->TabIndex = 2;
			this->btn_export_png->Text = L"Export As PNG";
			this->btn_export_png->UseVisualStyleBackColor = true;
			this->btn_export_png->Click += gcnew System::EventHandler(this, &DrawForm::btn_export_png_Click);
			// 
			// pnl_draw
			// 
			this->pnl_draw->BackColor = System::Drawing::Color::White;
			this->pnl_draw->Location = System::Drawing::Point(305, 81);
			this->pnl_draw->Name = L"pnl_draw";
			this->pnl_draw->Size = System::Drawing::Size(553, 380);
			this->pnl_draw->TabIndex = 3;
			this->pnl_draw->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &DrawForm::pnl_draw_Paint);
			// 
			// pnl_draw_container
			// 
			this->pnl_draw_container->AutoScroll = true;
			this->pnl_draw_container->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->pnl_draw_container->BackColor = System::Drawing::Color::White;
			this->pnl_draw_container->Controls->Add(this->pnl_draw);
			this->pnl_draw_container->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnl_draw_container->Location = System::Drawing::Point(0, 45);
			this->pnl_draw_container->Name = L"pnl_draw_container";
			this->pnl_draw_container->Size = System::Drawing::Size(966, 565);
			this->pnl_draw_container->TabIndex = 4;
			this->pnl_draw_container->ClientSizeChanged += gcnew System::EventHandler(this, &DrawForm::pnl_draw_container_ClientSizeChanged);
			// 
			// tab_container
			// 
			this->tab_container->Controls->Add(this->tab_editor);
			this->tab_container->Controls->Add(this->tab_scanner);
			this->tab_container->Controls->Add(this->tab_tree);
			this->tab_container->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tab_container->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tab_container->ItemSize = System::Drawing::Size(400, 30);
			this->tab_container->Location = System::Drawing::Point(0, 0);
			this->tab_container->Name = L"tab_container";
			this->tab_container->Padding = System::Drawing::Point(6, 2);
			this->tab_container->SelectedIndex = 0;
			this->tab_container->Size = System::Drawing::Size(974, 648);
			this->tab_container->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tab_container->TabIndex = 0;
			this->tab_container->SelectedIndexChanged += gcnew System::EventHandler(this, &DrawForm::tab_container_SelectedIndexChanged);
			// 
			// tab_editor
			// 
			this->tab_editor->Controls->Add(this->pnl_txt_editor_container);
			this->tab_editor->Controls->Add(this->pnl_editor_top);
			this->tab_editor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tab_editor->Location = System::Drawing::Point(4, 34);
			this->tab_editor->Name = L"tab_editor";
			this->tab_editor->Size = System::Drawing::Size(966, 610);
			this->tab_editor->TabIndex = 0;
			this->tab_editor->Text = L"Editor";
			this->tab_editor->UseVisualStyleBackColor = true;
			// 
			// pnl_txt_editor_container
			// 
			this->pnl_txt_editor_container->Controls->Add(this->txt_editor);
			this->pnl_txt_editor_container->Controls->Add(this->pnl_editor_bottom);
			this->pnl_txt_editor_container->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnl_txt_editor_container->Location = System::Drawing::Point(0, 45);
			this->pnl_txt_editor_container->Name = L"pnl_txt_editor_container";
			this->pnl_txt_editor_container->Padding = System::Windows::Forms::Padding(0, 10, 0, 0);
			this->pnl_txt_editor_container->Size = System::Drawing::Size(966, 565);
			this->pnl_txt_editor_container->TabIndex = 4;
			// 
			// txt_editor
			// 
			this->txt_editor->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txt_editor->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txt_editor->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txt_editor->Location = System::Drawing::Point(0, 10);
			this->txt_editor->Multiline = true;
			this->txt_editor->Name = L"txt_editor";
			this->txt_editor->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txt_editor->Size = System::Drawing::Size(966, 510);
			this->txt_editor->TabIndex = 3;
			this->txt_editor->TextChanged += gcnew System::EventHandler(this, &DrawForm::txt_editor_TextChanged);
			// 
			// pnl_editor_bottom
			// 
			this->pnl_editor_bottom->BackColor = System::Drawing::Color::WhiteSmoke;
			this->pnl_editor_bottom->Controls->Add(this->lbl_file_name);
			this->pnl_editor_bottom->Controls->Add(this->lbl_file_name_static);
			this->pnl_editor_bottom->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->pnl_editor_bottom->Location = System::Drawing::Point(0, 520);
			this->pnl_editor_bottom->Name = L"pnl_editor_bottom";
			this->pnl_editor_bottom->Size = System::Drawing::Size(966, 45);
			this->pnl_editor_bottom->TabIndex = 4;
			// 
			// lbl_file_name
			// 
			this->lbl_file_name->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl_file_name->Location = System::Drawing::Point(89, 0);
			this->lbl_file_name->Name = L"lbl_file_name";
			this->lbl_file_name->Size = System::Drawing::Size(877, 45);
			this->lbl_file_name->TabIndex = 1;
			this->lbl_file_name->Text = L"newFile.txt";
			this->lbl_file_name->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lbl_file_name_static
			// 
			this->lbl_file_name_static->Dock = System::Windows::Forms::DockStyle::Left;
			this->lbl_file_name_static->Location = System::Drawing::Point(0, 0);
			this->lbl_file_name_static->Name = L"lbl_file_name_static";
			this->lbl_file_name_static->Size = System::Drawing::Size(89, 45);
			this->lbl_file_name_static->TabIndex = 0;
			this->lbl_file_name_static->Text = L"File Name:";
			this->lbl_file_name_static->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tab_scanner
			// 
			this->tab_scanner->Controls->Add(this->txt_scanner_str);
			this->tab_scanner->Location = System::Drawing::Point(4, 34);
			this->tab_scanner->Name = L"tab_scanner";
			this->tab_scanner->Padding = System::Windows::Forms::Padding(3);
			this->tab_scanner->Size = System::Drawing::Size(966, 610);
			this->tab_scanner->TabIndex = 2;
			this->tab_scanner->Text = L"Scanner Output";
			this->tab_scanner->UseVisualStyleBackColor = true;
			// 
			// tab_tree
			// 
			this->tab_tree->Controls->Add(this->pnl_draw_container);
			this->tab_tree->Controls->Add(this->pnl_syntax_top);
			this->tab_tree->Location = System::Drawing::Point(4, 34);
			this->tab_tree->Name = L"tab_tree";
			this->tab_tree->Size = System::Drawing::Size(966, 610);
			this->tab_tree->TabIndex = 1;
			this->tab_tree->Text = L"Syntax Tree";
			this->tab_tree->UseVisualStyleBackColor = true;
			// 
			// pnl_syntax_top
			// 
			this->pnl_syntax_top->BackColor = System::Drawing::Color::WhiteSmoke;
			this->pnl_syntax_top->Controls->Add(this->btn_export_png);
			this->pnl_syntax_top->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnl_syntax_top->Location = System::Drawing::Point(0, 0);
			this->pnl_syntax_top->Name = L"pnl_syntax_top";
			this->pnl_syntax_top->Size = System::Drawing::Size(966, 45);
			this->pnl_syntax_top->TabIndex = 5;
			// 
			// txt_scanner_str
			// 
			this->txt_scanner_str->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txt_scanner_str->Location = System::Drawing::Point(3, 3);
			this->txt_scanner_str->Multiline = true;
			this->txt_scanner_str->Name = L"txt_scanner_str";
			this->txt_scanner_str->ReadOnly = true;
			this->txt_scanner_str->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txt_scanner_str->Size = System::Drawing::Size(960, 604);
			this->txt_scanner_str->TabIndex = 5;
			// 
			// DrawForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(974, 648);
			this->Controls->Add(this->tab_container);
			this->MinimumSize = System::Drawing::Size(825, 500);
			this->Name = L"DrawForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"TINY Language Parser";
			this->Load += gcnew System::EventHandler(this, &DrawForm::DrawForm_Load);
			this->Resize += gcnew System::EventHandler(this, &DrawForm::DrawForm_Resize);
			this->pnl_editor_top->ResumeLayout(false);
			this->pnl_draw_container->ResumeLayout(false);
			this->tab_container->ResumeLayout(false);
			this->tab_editor->ResumeLayout(false);
			this->pnl_txt_editor_container->ResumeLayout(false);
			this->pnl_txt_editor_container->PerformLayout();
			this->pnl_editor_bottom->ResumeLayout(false);
			this->tab_scanner->ResumeLayout(false);
			this->tab_scanner->PerformLayout();
			this->tab_tree->ResumeLayout(false);
			this->pnl_syntax_top->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void DrawForm_Load(System::Object^ sender, System::EventArgs^ e);
	
	private: System::Void DrawForm_Resize(System::Object^ sender, System::EventArgs^ e);

	private: System::Void btn_generate_tree_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void pnl_draw_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);

	private: System::Void pnl_draw_container_ClientSizeChanged(System::Object^ sender, System::EventArgs^ e);

	private: System::Void updatePnlDrawLocation();

	private: System::Drawing::Size draw(Graphics^ g);

	private: Drawing::Point drawSubTree(Graphics^ g, const ParserApp::TreeNode* node, int& width, int& height);

	private: System::Void btn_export_png_Click(System::Object^ sender, System::EventArgs^ e);
	
	private: System::Void btn_load_file_Click(System::Object^ sender, System::EventArgs^ e);
	
	private: System::Void btn_save_file_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void btn_check_sntx_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void txt_editor_TextChanged(System::Object^ sender, System::EventArgs^ e);

	private: System::Void btn_new_file_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void tab_container_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	
	private: System::Void inputFileProcessing(std::string& text);

	private: System::Void outputFileProcessing(std::string& text);

	private: System::Void updateTabsSize();

	private: System::Void saveFile();

	private: bool checkSyntax();

	private: ParserApp::Tree* syntaxTree;

	private: bool shouldDraw;

	private: bool shouldShowScannerOutput;

	private: String^ openFile;

	private: bool fileModified;

};
}
