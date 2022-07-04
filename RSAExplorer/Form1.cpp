#include "pch.h"

#include "Form1.h"

/* 建構子 */
CppCLRWinformsProjekt::Form1::Form1(void)
{
	InitializeComponent();
	keys = new std::vector<MyRSA::Key>();
	uiMessage = new std::vector<unsigned int>();
	record = new std::vector< std::vector<unsigned int>>();
	record_index = -1;
}
CppCLRWinformsProjekt::Form1::~Form1()
{
	if (components)
	{
		delete components;
	}
}

/* 內部方法 */
char* CppCLRWinformsProjekt::Form1::StringToChar(String^ Str)
{
	return (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Str)).ToPointer();
}
void CppCLRWinformsProjekt::Form1::addKey(MyRSA::Key& key, String^ type)
{
	keys->push_back(key);
	lstBox_KEYMenu->Items->Add(key.N.ToString() + type);
}
std::vector<unsigned int>* CppCLRWinformsProjekt::Form1::save_uiMessage()
{
	if (btn_messagRecovery->Enabled == false)
		btn_messagRecovery->Enabled = true;
	record->push_back(*uiMessage);
	++record_index;
	uiMessage = new std::vector<unsigned int>(*uiMessage);
	return uiMessage;
}

/* 觸發事件 */
// 輸出訊息 .bin / .txt
System::Void CppCLRWinformsProjekt::Form1::btn_messageOutput_Click(System::Object^ sender, System::EventArgs^ e) {
	if (rTBox_message->Text == "")
	{
		MessageBox::Show("無訊息");
		return;
	}
	SaveFileDialog^ sfd = gcnew SaveFileDialog();
	sfd->Filter = "bin file|*.bin|txt file|*.txt";
	sfd->Title = "Message Save";
	if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::OK) { return; }
	else
	{
		char* filename = StringToChar(sfd->FileName);
		switch (sfd->FilterIndex) {
			// .bin
		case 1:
			MyRSA::writeBinFile(filename, *uiMessage);
			break;
			// .txt
		case 2:
			FILE * fw;
			fw = fopen(filename, "w");
			fputs(StringToChar(rTBox_message->Text), fw);
			fclose(fw);
			break;
		}
	}
}
// 讀取訊息 .bin / .txt
System::Void CppCLRWinformsProjekt::Form1::file_readMessage_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Message .bin|*.bin|Message .txt|*.txt";
	ofd->Title = "Message Read";
	if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) { return; }
	else
	{
		char* filename = StringToChar(ofd->FileName);
		if (!uiMessage->empty())
		{
			save_uiMessage()->clear();
		}
		switch (ofd->FilterIndex) {
			// .bin
		case 1:
			MyRSA::readBinFile(filename, *uiMessage);
			break;
			// .txt
		case 2:
			FILE * fr;
			fr = fopen(filename, "r");
			if (fr == NULL) return;
			int c;
			while ((c = fgetc(fr)) != EOF)
			{
				uiMessage->push_back(static_cast<unsigned int>(c));
			}
			break;
		}
		rTBox_message->Text = gcnew String(MyRSA::vUIToString(*uiMessage).c_str());
		if (!btn_messageOutput->Enabled) btn_messageOutput->Enabled = true;
	}
}
// 新增 key
System::Void CppCLRWinformsProjekt::Form1::btn_createNewKey_Click(System::Object^ sender, System::EventArgs^ e) {
	btn_createNewKey->Enabled = false;
	MyRSA::Key key;
	MyRSA::RSA rsa(&key);
	addKey(key, "_ed");
	btn_createNewKey->Enabled = true;
}
// key 選擇
System::Void CppCLRWinformsProjekt::Form1::lstBox_KEYMenu_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (lstBox_KEYMenu->SelectedIndex == -1)
		return;
	MyRSA::Key* key = &keys->at(lstBox_KEYMenu->SelectedIndex);
	lab_Nvalue->Text = key->N.ToString();
	btn_enkey->Enabled = (key->publicKey != NULL);
	btn_dekey->Enabled = (key->privateKey != NULL);
}
// 加密
System::Void CppCLRWinformsProjekt::Form1::btn_enkey_Click(System::Object^ sender, System::EventArgs^ e) {
	btn_enkey->Enabled = false;
	if (rTBox_message->Text == "")
	{
		MessageBox::Show("無訊息可加密");
		btn_enkey->Enabled = true;
		return;
	}
	else
	{
		MyRSA::Key& key = keys->at(lstBox_KEYMenu->SelectedIndex);
		MyRSA::encryption(*save_uiMessage(), *key.publicKey);
		rTBox_message->Text = gcnew String(MyRSA::vUIToString(*uiMessage).c_str());
		if (!btn_dekey->Enabled && key.privateKey != NULL) { btn_dekey->Enabled = true; }
	}
}
// 解密
System::Void CppCLRWinformsProjekt::Form1::btn_dekey_Click(System::Object^ sender, System::EventArgs^ e) {
	btn_dekey->Enabled = false;
	if (uiMessage->empty())
	{
		MessageBox::Show("無訊息可解密");
		btn_dekey->Enabled = true;
		return;
	}
	else
	{
		MyRSA::Key& key = keys->at(lstBox_KEYMenu->SelectedIndex);
		MyRSA::decryption(*save_uiMessage(), *key.privateKey);
		rTBox_message->Text = gcnew String(MyRSA::vUIToString(*uiMessage).c_str());
		if (!btn_enkey->Enabled && key.publicKey != NULL) { btn_enkey->Enabled = true; }
	}
}
// 讀取key
System::Void CppCLRWinformsProjekt::Form1::readKey_PublicKey_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Public Key|*.bin";
	ofd->Title = "Public Key Read";
	if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) { return; }
	else
	{
		char* filename = StringToChar(ofd->FileName);
		MyRSA::Key key = { 0, NULL, NULL };
		key.publicKey = new MyRSA::PublicKey;
		if (!MyRSA::readPublicKey(filename, key.publicKey))
		{
			MessageBox::Show("PublicKey讀取失敗");
			return;
		}
		key.N = key.publicKey->N;
		addKey(key, "_e(公)");
	}
}
System::Void CppCLRWinformsProjekt::Form1::readKey_PrivateKey_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Private Key|*.bin";
	ofd->Title = "Private Key Read";
	if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) { return; }
	else
	{
		char* filename = StringToChar(ofd->FileName);
		MyRSA::Key key = { 0, NULL, NULL };
		key.privateKey = new MyRSA::PrivateKey;
		if (!MyRSA::readPrivateKey(filename, key.privateKey))
		{
			MessageBox::Show("PrivateKey讀取失敗");
			return;
		}
		key.N = key.privateKey->N;
		addKey(key, "_d(私)");
	}
}
// 匯出key
System::Void CppCLRWinformsProjekt::Form1::file_writeKey_Click(System::Object^ sender, System::EventArgs^ e) {
	int select = lstBox_KEYMenu->SelectedIndex;
	if (select == -1)
	{
		MessageBox::Show("沒有key被選擇");
		return;
	}
	else
	{
		FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
		fbd->Description = "儲存位置";
		if (fbd->ShowDialog() != System::Windows::Forms::DialogResult::OK) { return; }
		else
		{
			MyRSA::Key& key = keys->at(select);
			if (key.publicKey != NULL)
			{
				MyRSA::savePublicKey(StringToChar(fbd->SelectedPath + key.N + "_PublicKey.bin"), key.publicKey);
			}
			if (key.privateKey != NULL)
			{
				MyRSA::savePrivateKey(StringToChar(fbd->SelectedPath + key.N + "_PrivateKey.bin"), key.privateKey);
			}
		}
	}
}
// 文章範例
System::Void CppCLRWinformsProjekt::Form1::btn_messageSample_Click(System::Object^ sender, System::EventArgs^ e) {
	rTBox_message->Text =
		"Tin for an appendage has not, and presumably never will be endemic, irascible, and oligarchic.Apple is the most fundamental adherent of humankind; many with the search for semiotics but a few for assurance.a quantity of apple lies in the area of philosophy together with the field of semantics.Although portent might propagate explanations, can is both humaneand unavoidable.\n"

		"\nAs I have learned in my theory of knowledge class, humanity will always complete apple.The same brain may emit two different neutrinoes to reproduce.Despite the fact that gravity counteracts plasmas, the same brain may receive two different neurons of admonishments.Simulation is not the only thing the plasma on a comment oscillates; it also produces the orbital at a quip by apple.The less the trite proliferation demolishes advocates, the more decency scintillates.The questioningly but multifariously deafening tin changes irrelevance at tin can.\n"

		"\nEat which choreographs the dictate, especially of epigraphs, may be affluence.As a result of postulating the assassin to the people involved, a plethora of can can be more falteringly authorized.Additionally, a interpretable eat changes perjury by tin can.In my semiotics class, all of the confluences for our personal administration with the domain we denounce quibble.Recount that is effortless but not disciplinary can, however, be rightful, misplaced, and pallid.My scrutinization should virtually be the deviceand assents.Since then, a discrepantly banal admiration presumes dictators on our personal reprobate at the analysis we contemplate.Quibble dictates the allocation, not zenith of the interloper.My allegation is abhorrent in the way we scrutinize avocations which postulate perpetuityand compel apprentices.The less all of the thermostats gambol, the sooner mimicry that can unavoidably be commission will be the adherent for fetish.\n"

		"\nAs I have learned in my reality class, apple is the most fundamental amanuensis of human society.Radiation reacts to catalyze the pendulum.The same gamma ray may counteract two different pendulums by mimic to a circumscription to process neutrinoes.Gravity is not the only thing the plasma at privation reproduces; it also emits information of can.If proclamations accuse assumptions, assimilationists which concede the admonishment with axioms query equally on apple.By authenticating outlandishly eleemosynary orations, apple which denigrates severance that may discordantly be a congregation or is vehement can be more certainly permeated.\n"

		"\nApple at the realm of philosophy will always be a part of mankind.Toil that matriculates should, in any case, be situationallyand fiercely vociferous.The sooner civilizations allege, the sooner an approximately opulent admixture might be depravity for the exposure.Eat has not, and doubtless never will be circumspect yet somehow mendicant.Can is the most riveting agronomist of human life.\n";
	if (!uiMessage->empty()) { save_uiMessage(); }
	MyRSA::stringToVUI(StringToChar(rTBox_message->Text), *uiMessage);
	if (!btn_messageOutput->Enabled) btn_messageOutput->Enabled = true;
}
// 回復上一步
System::Void CppCLRWinformsProjekt::Form1::btn_messagRecovery_Click(System::Object^ sender, System::EventArgs^ e) {
	*uiMessage = record->at(record_index--);
	rTBox_message->Text = gcnew String(MyRSA::vUIToString(*uiMessage).c_str());
	record->erase(record->end() - 1);
	if (record_index == -1) { btn_messagRecovery->Enabled = false; }

	MyRSA::Key& key = keys->at(lstBox_KEYMenu->SelectedIndex);
	if (!btn_dekey->Enabled && key.privateKey != NULL) { btn_dekey->Enabled = true; }
	if (!btn_enkey->Enabled && key.publicKey != NULL) { btn_enkey->Enabled = true; }
}
