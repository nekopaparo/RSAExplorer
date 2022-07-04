#pragma once

#include "MyRSA.h"

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void);
	protected:
		~Form1();
	private: 
		System::ComponentModel::IContainer^ components;

		std::vector<MyRSA::Key>* keys;
		std::vector< std::vector<unsigned int>>* record;
		std::vector<unsigned int>* uiMessage;
		int record_index;
		
		// String^ to char*
		char* StringToChar(String^ Str);
		// 加入金鑰
		void addKey(MyRSA::Key& key, String^ type);
		// 紀錄訊息
		std::vector<unsigned int>* save_uiMessage();
 
	private: System::Windows::Forms::Panel^ panel1;
	// N : 988027
	private: System::Windows::Forms::Label^ lab_N;
	private: System::Windows::Forms::Label^ lab_Nvalue;
	// Keys
	private: System::Windows::Forms::ListBox^ lstBox_KEYMenu;
	private: System::Windows::Forms::Button^ btn_enkey;
	private: System::Windows::Forms::Button^ btn_dekey;
	private: System::Windows::Forms::Button^ btn_createNewKey;
	// message
	private: System::Windows::Forms::RichTextBox^ rTBox_message;
	private: System::Windows::Forms::Button^ btn_messageSample;
	private: System::Windows::Forms::Button^ btn_messageOutput;
	private: System::Windows::Forms::Button^ btn_messagRecovery;
	// 功能表
	private: System::Windows::Forms::MenuStrip^ menu;
	private: System::Windows::Forms::ToolStripMenuItem^ menu_file;
	private: System::Windows::Forms::ToolStripMenuItem^ file_readKey;
	private: System::Windows::Forms::ToolStripMenuItem^ readKey_PublicKey;
	private: System::Windows::Forms::ToolStripMenuItem^ readKey_PrivateKey;
	private: System::Windows::Forms::ToolStripMenuItem^ file_writeKey;
	private: System::Windows::Forms::ToolStripMenuItem^ file_readMessage;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btn_messagRecovery = (gcnew System::Windows::Forms::Button());
			this->lab_Nvalue = (gcnew System::Windows::Forms::Label());
			this->btn_createNewKey = (gcnew System::Windows::Forms::Button());
			this->btn_messageOutput = (gcnew System::Windows::Forms::Button());
			this->btn_dekey = (gcnew System::Windows::Forms::Button());
			this->btn_enkey = (gcnew System::Windows::Forms::Button());
			this->rTBox_message = (gcnew System::Windows::Forms::RichTextBox());
			this->lab_N = (gcnew System::Windows::Forms::Label());
			this->lstBox_KEYMenu = (gcnew System::Windows::Forms::ListBox());
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->menu_file = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->file_readKey = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->readKey_PublicKey = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->readKey_PrivateKey = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->file_writeKey = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->file_readMessage = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->btn_messageSample = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->menu->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->btn_messagRecovery);
			this->panel1->Controls->Add(this->lab_Nvalue);
			this->panel1->Controls->Add(this->btn_createNewKey);
			this->panel1->Controls->Add(this->btn_messageOutput);
			this->panel1->Controls->Add(this->btn_dekey);
			this->panel1->Controls->Add(this->btn_enkey);
			this->panel1->Controls->Add(this->rTBox_message);
			this->panel1->Controls->Add(this->lab_N);
			this->panel1->Controls->Add(this->lstBox_KEYMenu);
			this->panel1->Location = System::Drawing::Point(12, 30);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(643, 493);
			this->panel1->TabIndex = 0;
			// 
			// btn_messagRecovery
			// 
			this->btn_messagRecovery->Enabled = false;
			this->btn_messagRecovery->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->btn_messagRecovery->Location = System::Drawing::Point(211, 46);
			this->btn_messagRecovery->Name = L"btn_messagRecovery";
			this->btn_messagRecovery->Size = System::Drawing::Size(41, 24);
			this->btn_messagRecovery->TabIndex = 9;
			this->btn_messagRecovery->Text = L"↶";
			this->btn_messagRecovery->UseVisualStyleBackColor = true;
			this->btn_messagRecovery->Click += gcnew System::EventHandler(this, &Form1::btn_messagRecovery_Click);
			// 
			// lab_Nvalue
			// 
			this->lab_Nvalue->AutoSize = true;
			this->lab_Nvalue->Font = (gcnew System::Drawing::Font(L"新細明體", 28.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lab_Nvalue->Location = System::Drawing::Point(66, 19);
			this->lab_Nvalue->Name = L"lab_Nvalue";
			this->lab_Nvalue->Size = System::Drawing::Size(158, 48);
			this->lab_Nvalue->TabIndex = 7;
			this->lab_Nvalue->Text = L"988027";
			// 
			// btn_createNewKey
			// 
			this->btn_createNewKey->Location = System::Drawing::Point(3, 439);
			this->btn_createNewKey->Name = L"btn_createNewKey";
			this->btn_createNewKey->Size = System::Drawing::Size(202, 49);
			this->btn_createNewKey->TabIndex = 6;
			this->btn_createNewKey->Text = L"產生金鑰";
			this->btn_createNewKey->UseVisualStyleBackColor = true;
			this->btn_createNewKey->Click += gcnew System::EventHandler(this, &Form1::btn_createNewKey_Click);
			// 
			// btn_messageOutput
			// 
			this->btn_messageOutput->Enabled = false;
			this->btn_messageOutput->Location = System::Drawing::Point(525, 20);
			this->btn_messageOutput->Name = L"btn_messageOutput";
			this->btn_messageOutput->Size = System::Drawing::Size(115, 47);
			this->btn_messageOutput->TabIndex = 5;
			this->btn_messageOutput->Text = L"輸出";
			this->btn_messageOutput->UseVisualStyleBackColor = true;
			this->btn_messageOutput->Click += gcnew System::EventHandler(this, &Form1::btn_messageOutput_Click);
			// 
			// btn_dekey
			// 
			this->btn_dekey->Enabled = false;
			this->btn_dekey->Location = System::Drawing::Point(404, 20);
			this->btn_dekey->Name = L"btn_dekey";
			this->btn_dekey->Size = System::Drawing::Size(115, 47);
			this->btn_dekey->TabIndex = 4;
			this->btn_dekey->Text = L"解密";
			this->btn_dekey->UseVisualStyleBackColor = true;
			this->btn_dekey->Click += gcnew System::EventHandler(this, &Form1::btn_dekey_Click);
			// 
			// btn_enkey
			// 
			this->btn_enkey->Enabled = false;
			this->btn_enkey->Location = System::Drawing::Point(283, 20);
			this->btn_enkey->Name = L"btn_enkey";
			this->btn_enkey->Size = System::Drawing::Size(115, 47);
			this->btn_enkey->TabIndex = 3;
			this->btn_enkey->Text = L"加密";
			this->btn_enkey->UseVisualStyleBackColor = true;
			this->btn_enkey->Click += gcnew System::EventHandler(this, &Form1::btn_enkey_Click);
			// 
			// rTBox_message
			// 
			this->rTBox_message->Location = System::Drawing::Point(211, 73);
			this->rTBox_message->Name = L"rTBox_message";
			this->rTBox_message->ReadOnly = true;
			this->rTBox_message->Size = System::Drawing::Size(429, 415);
			this->rTBox_message->TabIndex = 2;
			this->rTBox_message->Text = L"";
			// 
			// lab_N
			// 
			this->lab_N->AutoSize = true;
			this->lab_N->Font = (gcnew System::Drawing::Font(L"新細明體", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lab_N->Location = System::Drawing::Point(3, 10);
			this->lab_N->Name = L"lab_N";
			this->lab_N->Size = System::Drawing::Size(82, 60);
			this->lab_N->TabIndex = 1;
			this->lab_N->Text = L"N:";
			// 
			// lstBox_KEYMenu
			// 
			this->lstBox_KEYMenu->FormattingEnabled = true;
			this->lstBox_KEYMenu->ItemHeight = 15;
			this->lstBox_KEYMenu->Location = System::Drawing::Point(3, 74);
			this->lstBox_KEYMenu->Name = L"lstBox_KEYMenu";
			this->lstBox_KEYMenu->Size = System::Drawing::Size(202, 364);
			this->lstBox_KEYMenu->TabIndex = 0;
			this->lstBox_KEYMenu->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::lstBox_KEYMenu_SelectedIndexChanged);
			// 
			// menu
			// 
			this->menu->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->menu_file });
			this->menu->Location = System::Drawing::Point(0, 0);
			this->menu->Name = L"menu";
			this->menu->Size = System::Drawing::Size(665, 27);
			this->menu->TabIndex = 1;
			this->menu->Text = L"menuStrip1";
			// 
			// menu_file
			// 
			this->menu_file->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->file_readKey,
					this->file_writeKey, this->file_readMessage
			});
			this->menu_file->Name = L"menu_file";
			this->menu_file->Size = System::Drawing::Size(71, 23);
			this->menu_file->Text = L"檔案(F)";
			// 
			// file_readKey
			// 
			this->file_readKey->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->readKey_PublicKey,
					this->readKey_PrivateKey
			});
			this->file_readKey->Name = L"file_readKey";
			this->file_readKey->Size = System::Drawing::Size(152, 26);
			this->file_readKey->Text = L"讀取金鑰";
			// 
			// readKey_PublicKey
			// 
			this->readKey_PublicKey->Name = L"readKey_PublicKey";
			this->readKey_PublicKey->Size = System::Drawing::Size(152, 26);
			this->readKey_PublicKey->Text = L"讀取公鑰";
			this->readKey_PublicKey->Click += gcnew System::EventHandler(this, &Form1::readKey_PublicKey_Click);
			// 
			// readKey_PrivateKey
			// 
			this->readKey_PrivateKey->Name = L"readKey_PrivateKey";
			this->readKey_PrivateKey->Size = System::Drawing::Size(152, 26);
			this->readKey_PrivateKey->Text = L"讀取私鑰";
			this->readKey_PrivateKey->Click += gcnew System::EventHandler(this, &Form1::readKey_PrivateKey_Click);
			// 
			// file_writeKey
			// 
			this->file_writeKey->Name = L"file_writeKey";
			this->file_writeKey->Size = System::Drawing::Size(152, 26);
			this->file_writeKey->Text = L"輸出金鑰";
			this->file_writeKey->Click += gcnew System::EventHandler(this, &Form1::file_writeKey_Click);
			// 
			// file_readMessage
			// 
			this->file_readMessage->Name = L"file_readMessage";
			this->file_readMessage->Size = System::Drawing::Size(152, 26);
			this->file_readMessage->Text = L"讀取檔案";
			this->file_readMessage->Click += gcnew System::EventHandler(this, &Form1::file_readMessage_Click);
			// 
			// btn_messageSample
			// 
			this->btn_messageSample->Location = System::Drawing::Point(589, 3);
			this->btn_messageSample->Name = L"btn_messageSample";
			this->btn_messageSample->Size = System::Drawing::Size(63, 24);
			this->btn_messageSample->TabIndex = 8;
			this->btn_messageSample->Text = L"範例";
			this->btn_messageSample->UseVisualStyleBackColor = true;
			this->btn_messageSample->Click += gcnew System::EventHandler(this, &Form1::btn_messageSample_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(665, 535);
			this->Controls->Add(this->btn_messageSample);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menu);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menu;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"RSAExplorer";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
/* 事件 */
// 輸出訊息 .bin / .txt
private: System::Void btn_messageOutput_Click(System::Object^ sender, System::EventArgs^ e);
// 讀取訊息 .bin / .txt
private: System::Void file_readMessage_Click(System::Object^ sender, System::EventArgs^ e);
// 新增 key
private: System::Void btn_createNewKey_Click(System::Object^ sender, System::EventArgs^ e);
// key 選擇
private: System::Void lstBox_KEYMenu_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
// 加密
private: System::Void btn_enkey_Click(System::Object^ sender, System::EventArgs^ e);
// 解密
private: System::Void btn_dekey_Click(System::Object^ sender, System::EventArgs^ e);
// 讀取key
private: System::Void readKey_PublicKey_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void readKey_PrivateKey_Click(System::Object^ sender, System::EventArgs^ e);
// 匯出key
private: System::Void file_writeKey_Click(System::Object^ sender, System::EventArgs^ e);
// 文章範例
private: System::Void btn_messageSample_Click(System::Object^ sender, System::EventArgs^ e);
// 回復上一步
private: System::Void btn_messagRecovery_Click(System::Object^ sender, System::EventArgs^ e);
};
}
