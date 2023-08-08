#include "DrawForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace CompilersProjectParser;

[STAThread]
void main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    CompilersProjectParser::DrawForm drawForm;
    Application::Run(% drawForm);
}

System::Void DrawForm::updatePnlDrawLocation()
{
	int xPos = (pnl_draw_container->ClientSize.Width / 2) - pnl_draw->ClientSize.Width / 2;
	if (xPos < 0) xPos = 0;
	int yPos = (pnl_draw_container->ClientSize.Height / 2) - pnl_draw->ClientSize.Height / 2;
	if (yPos < 0) yPos = 0;
	this->pnl_draw->Location = System::Drawing::Point(xPos, yPos);
}

System::Drawing::Size DrawForm::draw(Graphics^ g)
{
	g->SmoothingMode = Drawing::Drawing2D::SmoothingMode::HighQuality;
	std::vector<int> xShifts, yShifts;
	int width = 0, height = 0;
	drawSubTree(g, syntaxTree->getRoot(), width, height);
	System::Drawing::Size drawingSize(width, height);
	return drawingSize;
}

Drawing::Point DrawForm::drawSubTree(Graphics^ g, const ParserApp::TreeNode* node, int& width, int& height)
{
	const int xFactor = 60, yFactor = 80;
	const int padding = 30;

	int nodeWidth = 80, nodeHeight = 50;
	int nodeX = node->getPosX() * xFactor + padding;
	int nodeY = node->getPosY() * yFactor + padding;

	int nodeCenterX = nodeX + (nodeWidth / 2);
	int nodeCenterY = nodeY + (nodeHeight / 2);

	width = max(width, nodeX + nodeWidth + padding);
	height = max(height, nodeY + nodeHeight + padding);


	StringFormat^ stringFormat = gcnew Drawing::StringFormat;
	stringFormat->Alignment = StringAlignment::Center;
	stringFormat->LineAlignment = StringAlignment::Center;
	
	std::string NodeText;
	if (node->getSubTitle() == "")
	{
		NodeText = node->getTitle();
	}
	else
	{
		std::string nodeSubTitle = node->getSubTitle();
		if (node->getSubTitle().size() > 8)
		{
			nodeSubTitle = nodeSubTitle.substr(0, 6) + "...";
		}
		NodeText = node->getTitle() + "\n(" + nodeSubTitle + ")";
	}
	g->DrawString(gcnew String(NodeText.c_str()), gcnew Drawing::Font("arial", 10, FontStyle::Regular), Brushes::Black, nodeCenterX, nodeCenterY, stringFormat);

	switch (node->getType())
	{
	case ParserApp::TreeNodeType::EXP:
		g->DrawEllipse(Pens::Green, nodeX, nodeY, nodeWidth, nodeHeight);
		break;
	case ParserApp::TreeNodeType::STMT:
		g->DrawRectangle(Pens::Black, nodeX, nodeY, nodeWidth, nodeHeight);
		break;
	default:
		break;
	}

	for (size_t i = 0; i < node->getChildrenSize(); i++)
	{
		Drawing::Point childCenter = drawSubTree(g, node->getChild(i), width, height);
		int nodeArrowX = nodeCenterX;
		int nodeArrowY = nodeCenterY + (nodeHeight / 2);
		int childArrowX = childCenter.X;
		int childArrowY = node->getChild(i)->getPosY() * yFactor + padding;
		g->DrawLine(Pens::Red, Drawing::Point(nodeArrowX, nodeArrowY), Drawing::Point(childArrowX, childArrowY));
	}
	if (node->getSibling() != nullptr)
	{
		Drawing::Point siblingCenter = drawSubTree(g, node->getSibling(), width, height);
		int nodeArrowX = nodeCenterX + (nodeWidth / 2);
		int nodeArrowY = nodeCenterY;
		int siblingArrowX = node->getSibling()->getPosX() * xFactor + padding;
		int siblingArrowY = siblingCenter.Y;
		g->DrawLine(Pens::Blue, Drawing::Point(nodeArrowX, nodeArrowY), Drawing::Point(siblingArrowX, siblingArrowY));

	}
	
	return Drawing::Point(nodeCenterX, nodeCenterY);
}

//Drawing::Point DrawForm::drawSubTree(Graphics^ g, const ParserApp::TreeNode* node, std::vector<int>& xShifts, std::vector<int>& yShifts, int& width, int& height)
//{
//	const int xFactor = 60, yFactor = 70;
//	const int padding = 50;
//
//	//if (xShifts.size() <= node->getPosX() / 2 + 1)
//	//{
//	//	int iterations = node->getPosX() / 2 - xShifts.size() + 2;
//	//	for (size_t i = 0; i < iterations; i++)
//	//	{
//	//		xShifts.push_back(padding);
//	//	}
//	//}
//
//	//if (yShifts.size() <= node->getPosY() + 1)
//	//{
//	//	int iterations = node->getPosY() - yShifts.size() + 2;
//	//	for (size_t i = 0; i < iterations; i++)
//	//	{
//	//		yShifts.push_back(padding);
//	//	}
//	//}
//
//	int nodeWidth = 70, nodeHeight = 40;
//	//xShifts[node->getPosX() / 2 + 1] = max(xShifts[node->getPosX() / 2 + 1], xShifts[node->getPosX() / 2] + nodeWidth - xFactor);
//	//yShifts[node->getPosY() + 1] = max(yShifts[node->getPosY() + 1], yShifts[node->getPosY()] + nodeHeight - yFactor);
//	//int nodeX = node->getPosX() * xFactor + xShifts[node->getPosX() / 2];
//	//int nodeY = node->getPosY() * yFactor + yShifts[node->getPosY()];
//	int nodeX = node->getPosX() * xFactor;
//	int nodeY = node->getPosY() * yFactor;
//
//	int nodeCenterX = nodeX + (nodeWidth / 2);
//	int nodeCenterY = nodeY + (nodeHeight / 2);
//
//	width = max(width, nodeX + nodeWidth + padding);
//	height = max(height, nodeY + nodeHeight + padding);
//
//
//	StringFormat^ stringFormat = gcnew Drawing::StringFormat;
//	stringFormat->Alignment = StringAlignment::Center;
//	stringFormat->LineAlignment = StringAlignment::Center;
//
//	//std::string xmlStr = msclr::interop::marshal_as< std::string >(this->richTextBoxInput->Text);
//	std::string NodeText;
//	if (node->getSubTitle() == "")
//	{
//		NodeText = node->getTitle();
//	}
//	else
//	{
//		NodeText = node->getTitle() + "\n(" + node->getSubTitle() + ")";
//	}
//	g->DrawString(gcnew String(NodeText.c_str()), gcnew Drawing::Font("arial", 10), Brushes::Black, nodeCenterX, nodeCenterY, stringFormat);
//
//	switch (node->getType())
//	{
//	case ParserApp::TreeNodeType::EXP:
//		g->DrawEllipse(Pens::Green, nodeX, nodeY, nodeWidth, nodeHeight);
//		break;
//	case ParserApp::TreeNodeType::STMT:
//		g->DrawRectangle(Pens::Black, nodeX, nodeY, nodeWidth, nodeHeight);
//		break;
//	default:
//		break;
//	}
//
//	for (size_t i = 0; i < node->getChildrenSize(); i++)
//	{
//		Drawing::Point childCenter = drawSubTree(g, node->getChild(i), xShifts, yShifts, width, height);
//		int nodeArrowX = nodeCenterX;
//		int nodeArrowY = nodeCenterY + (nodeHeight / 2);
//		int childArrowX = childCenter.X;
//		//int childArrowY = node->getChild(i)->getPosY() * yFactor + yShifts[node->getChild(i)->getPosY()];
//		int childArrowY = node->getChild(i)->getPosY() * yFactor;
//		g->DrawLine(Pens::Red, Drawing::Point(nodeArrowX, nodeArrowY), Drawing::Point(childArrowX, childArrowY));
//	}
//	if (node->getSibling() != nullptr)
//	{
//		//int tempXShift = ;
//		Drawing::Point siblingCenter = drawSubTree(g, node->getSibling(), xShifts, yShifts, width, height);
//		int nodeArrowX = nodeCenterX + (nodeWidth / 2);
//		int nodeArrowY = nodeCenterY;
//		//int siblingArrowX = node->getSibling()->getPosX() * xFactor + xShifts[node->getSibling()->getPosX() / 2];
//		int siblingArrowX = node->getSibling()->getPosX() * xFactor;
//		int siblingArrowY = siblingCenter.Y;
//		g->DrawLine(Pens::Blue, Drawing::Point(nodeArrowX, nodeArrowY), Drawing::Point(siblingArrowX, siblingArrowY));
//
//	}
//
//	return Drawing::Point(nodeCenterX, nodeCenterY);
//}
//

System::Void DrawForm::updateTabsSize() {
	if (this->ClientSize.Width / 3 - 2 >= 0)
		this->tab_container->ItemSize = System::Drawing::Size(this->ClientSize.Width / 3 - 2, 30);
}

System::Void DrawForm::saveFile()
{
	if (!fileModified)
		return;
	if (openFile->Length != 0)
	{
		String^ fileName = openFile;
		std::string savePathStr = msclr::interop::marshal_as< std::string>(fileName);
		std::string saveTxt = msclr::interop::marshal_as< std::string >(txt_editor->Text);
		std::ofstream file;
		outputFileProcessing(saveTxt);
		file.open(savePathStr);
		file << saveTxt;
		file.close();
		MessageBox::Show("File " + openFile + " saved successfully", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
		fileModified = false;
		lbl_file_name->Text = lbl_file_name->Text->Substring(0, lbl_file_name->Text->Length - 1);
		return;
	}
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
	saveFileDialog->Filter = "TXT Files (*.txt)|*.txt";
	saveFileDialog->FilterIndex = 1;
	saveFileDialog->RestoreDirectory = true;
	saveFileDialog->FileName = (gcnew String(NEW_FILE_INIT_NAME))->Replace("*", "");
	if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ savePath = saveFileDialog->FileName;
		try
		{
			std::string savePathStr = msclr::interop::marshal_as< std::string >(savePath);
			std::string saveTxt = msclr::interop::marshal_as< std::string >(txt_editor->Text);
			outputFileProcessing(saveTxt);
			std::ofstream file;
			file.open(savePathStr);
			file << saveTxt;
			file.close();
			openFile = savePath;
			lbl_file_name->Text = openFile;
			MessageBox::Show("File " + openFile + " saved successfully", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			fileModified = false;
		}
		catch (Exception^ err)
		{
			MessageBox::Show(err->ToString());
		}
	}
}

bool DrawForm::checkSyntax()
{
	shouldDraw = false;
	std::string programString = msclr::interop::marshal_as< std::string >(txt_editor->Text);
	outputFileProcessing(programString);
	ParserApp::Parser parser(programString);
	std::vector<std::string> errorMsgs;
	ParserApp::Tree* currentSyntaxTree = parser.parse(errorMsgs);
	bool syntaxCorrect = errorMsgs.size() == 0;
	if (syntaxTree != nullptr)
	{
		delete syntaxTree;
	}
	if (syntaxCorrect)
	{
		syntaxTree = currentSyntaxTree;
		shouldShowScannerOutput = true;

		ParserApp::Scanner* scanner = ParserApp::Scanner::getInstance();
		scanner->setProgramString(programString);
		ParserApp::Token token = scanner->getNextToken();

		txt_scanner_str->Text = "";
		while (token.getTokenType() != ParserApp::TokenType::END_FILE)
		{
			txt_scanner_str->Text += "Line: ";
			txt_scanner_str->Text += scanner->getCurrentLine();
			txt_scanner_str->Text += "\r\n";
			std::string tokenStr = token.toString();
			inputFileProcessing(tokenStr);
			txt_scanner_str->Text += gcnew String(tokenStr.c_str());
			txt_scanner_str->Text += "\r\n\r\n";
			token = scanner->getNextToken();
		}

		return true;
	}
	else
	{
		syntaxTree = nullptr;
		String^ errorList = "";
		for (size_t i = 0; i < errorMsgs.size(); i++)
		{
			errorList += gcnew String(errorMsgs[i].c_str());
			if (i != errorMsgs.size() - 1)
			{
				errorList += "\n\n";
			}
		}
		MessageBox::Show(errorList, "Error", MessageBoxButtons::OK, MessageBoxIcon::Stop);
	}
	return false;
}

System::Void DrawForm::inputFileProcessing(std::string& text)
{
	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] == '\n')
		{
			if (i == 0)
			{
				text.replace(i, 1, "\r\n");
			}
			else if (text[i - 1] != '\r')
			{
				
				text.replace(i, 1, "\r\n");
			}
		}
	}
}

System::Void DrawForm::outputFileProcessing(std::string& text)
{
	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] == '\r')
		{
			text.replace(i, 1, "");
		}
	}
}

/********** Event Handlers **********/ 

System::Void DrawForm::DrawForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	updateTabsSize();
	updatePnlDrawLocation();
	lbl_file_name->Text = NEW_FILE_INIT_NAME;
}

System::Void DrawForm::DrawForm_Resize(System::Object^ sender, System::EventArgs^ e)
{
	updateTabsSize();
	pnl_draw_container->AutoScroll = false;
	pnl_draw_container->AutoScroll = true;
}

System::Void DrawForm::pnl_draw_container_ClientSizeChanged(System::Object^ sender, System::EventArgs^ e)
{
	updatePnlDrawLocation();
}

System::Void DrawForm::pnl_draw_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	Graphics^ g = e->Graphics;
	if (syntaxTree != nullptr && shouldDraw)
	{
		pnl_draw->Size = draw(g);
		
	}
}

System::Void DrawForm::btn_load_file_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (fileModified && (openFile != "" || (openFile == "" && txt_editor->Text != "")))
	{
		System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to save current file ?", "Loading File", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);
		if (result == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}
		else if (result == System::Windows::Forms::DialogResult::Yes)
		{
			saveFile();
		}
	}
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
	openFileDialog->Filter = "TXT Files (*.txt)|*.txt";
	openFileDialog->FilterIndex = 1;
	openFileDialog->RestoreDirectory = true;
	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ openPath = openFileDialog->FileName;
		try
		{
			std::string openPathStr = msclr::interop::marshal_as< std::string >(openPath);
			std::ifstream file;
			file.open(openPathStr);
			std::string loadedString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			file.close();
			inputFileProcessing(loadedString);
			txt_editor->Text = gcnew String(loadedString.c_str());;
			openFile = openPath;
			lbl_file_name->Text = openFile;
			fileModified = false;
		}
		catch (Exception^ err)
		{
			MessageBox::Show(err->ToString());
		}
	}

}

System::Void DrawForm::btn_save_file_Click(System::Object^ sender, System::EventArgs^ e)
{
	saveFile();
}

System::Void DrawForm::btn_check_sntx_Click(System::Object^ sender, System::EventArgs^ e)
{
	if(checkSyntax())
	{
		MessageBox::Show("Syntax is correct", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}

System::Void DrawForm::btn_generate_tree_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!checkSyntax())
		return;

	syntaxTree->updateTreeNodesPos();
	shouldDraw = true;
	pnl_draw->Refresh();
	updatePnlDrawLocation();
	tab_container->SelectTab(2);
}

System::Void DrawForm::btn_export_png_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ imgSaveDialog = gcnew SaveFileDialog();
	imgSaveDialog->Filter = "PNG (*.png)|*.png";
	if (imgSaveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ savePath = imgSaveDialog->FileName;
		try
		{
			Bitmap^ bitmap = gcnew Bitmap(Convert::ToInt32(pnl_draw->Size.Width * 5), Convert::ToInt32(pnl_draw->Size.Height * 5), System::Drawing::Imaging::PixelFormat::Format32bppArgb);
			Graphics^ g = Graphics::FromImage(bitmap);
			g->PixelOffsetMode = Drawing::Drawing2D::PixelOffsetMode::HighQuality;
			g->SmoothingMode = Drawing::Drawing2D::SmoothingMode::HighQuality;
			g->CompositingQuality = Drawing::Drawing2D::CompositingQuality::HighQuality;
			g->ScaleTransform(5, 5);
			g->FillRectangle(Brushes::White, 0, 0, pnl_draw->Size.Width, pnl_draw->Size.Height);
			int width = 0, height = 0;
			drawSubTree(g, syntaxTree->getRoot(), width, height);
			bitmap->Save(savePath, Imaging::ImageFormat::Png);
		}
		catch (Exception^ err)
		{
			MessageBox::Show(err->ToString());
		}
	}
}

System::Void DrawForm::txt_editor_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!fileModified || (fileModified && openFile == "" && lbl_file_name->Text->IndexOf("*") == -1))
	{
		lbl_file_name->Text += "*";
	}
	fileModified = true;
}

System::Void DrawForm::btn_new_file_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (fileModified && (openFile != "" || (openFile == "" && txt_editor->Text != "")))
	{
		System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to save current file ?", "Creating New File", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);
		if (result == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}
		else if (result == System::Windows::Forms::DialogResult::Yes)
		{
			saveFile();
		}
	}
	txt_editor->Text = "";
	openFile = "";
	fileModified = true;
	lbl_file_name->Text = NEW_FILE_INIT_NAME;
}

System::Void DrawForm::tab_container_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (tab_container->SelectedIndex == 2 && shouldDraw == false) {
		tab_container->SelectTab(0);
		MessageBox::Show("Please generate a syntax tree first.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Stop);
	}
	else if (tab_container->SelectedIndex == 1 && shouldShowScannerOutput == false) {
		tab_container->SelectTab(0);
		MessageBox::Show("Please click check syntax first.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Stop);
	}
}