#pragma once
#include<stdlib.h>
#include"camera.h"
#include <time.h>
#include"FeedForwardAlgorithm.h"
#include<iostream>
const int GestureNo = 1;
using namespace::std;
#include<Windows.h>
namespace GestureRecognition {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for InterFace
	/// </summary>
	public ref class InterFace : public System::Windows::Forms::Form
	{
	public:
		InterFace(void)
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
		~InterFace()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;



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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Algerian", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button1->Location = System::Drawing::Point(161, 41);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(214, 33);
			this->button1->TabIndex = 0;
			this->button1->Text = L"ابدأ التعرف";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &InterFace::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(161, 161);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(214, 20);
			this->textBox1->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Algerian", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::SystemColors::Highlight;
			this->button2->Location = System::Drawing::Point(198, 230);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(130, 28);
			this->button2->TabIndex = 2;
			this->button2->Text = L"توقف";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &InterFace::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(158, 145);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(40, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"الكلمات";
			// 
			// InterFace
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Highlight;
			this->ClientSize = System::Drawing::Size(573, 307);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"InterFace";
			this->Text = L"التعرف علي الأشارات";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		time_t t1, t2, t3;
		t1 = time(0);
				Camera cam;


		{

		};
		//	 wchar_t *WCHAR=L"محمد";
	//		 CHAR hh = 'h';

			FeedForwardAlgorithm instance;
			int gestno;
//			this->textBox1->Text = hh;

		for (int i = 0; i < GestureNo; i++){

					gestno=instance.run(cam.getGesture(), 100);
					if (gestno == 1)
						this->textBox1->Text = "aasif";
					else if (gestno == 2)
						this->textBox1->Text = "bsm allah";
					 if (gestno == 3)
						this->textBox1->Text = "sehha";
					else if (gestno == 4)
						this->textBox1->Text = "mostakbal";

					System::Media::SoundPlayer^ player=gcnew System::Media::SoundPlayer();
					player->SoundLocation = "C:\\Users\\MohamedAtta\\Documents\\Visual Studio 2013\\Projects\\sounds\\"+gestno+".wav";//path					cout << gestno;
					player->Load();
					player->Play();



		}


		t2 = time(0);
		cout << "elapsed time: " << t2 - t1 << "\n";

		
	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	exit(0);
}
};
}
