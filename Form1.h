#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <windows.h>
#define PORT 666
#define SERVERADDR "127.0.0.1"



namespace echo_client1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(15, 49);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(244, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(74, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"You message:";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(15, 106);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(69, 29);
			this->button1->TabIndex = 2;
			this->button1->Text = L"send!";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::Window;
			this->textBox2->Location = System::Drawing::Point(312, 49);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(295, 274);
			this->textBox2->TabIndex = 3;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(15, 276);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(114, 44);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Connect to server";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(149, 276);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(110, 47);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Disconnect";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(632, 359);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();
			

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			
			char buff[1024];
			char* tmp = "qwrr";
			String^ mess;
			mess = (String^) tmp;
			//String^ buff;
			this->textBox2->Text += "TCP DEMO CLIENT\n";
			
			// Шаг 1  инициализация библиотеки Winsock

			WSAStartup(0x0202,(WSADATA *)&buff);
			
			// Шаг 2  создание сокета
			SOCKET my_sock;
			my_sock=socket(AF_INET,SOCK_STREAM,0);
			if (my_sock < 0)
			{
				this->textBox2->Text = "  Socket error";
			}

			// Шаг 3 установка соединения
			//заполнение структуры sockaddr_in указание адреса и порта сервера
			sockaddr_in dest_addr;
			dest_addr.sin_family = AF_INET;
			dest_addr.sin_port = htons(PORT);// преобразование в сетевой формат
			HOSTENT *hst;
			// преобразование IP адреса из символьного в сетевой формат
			if (inet_addr(SERVERADDR)!=INADDR_NONE)
				dest_addr.sin_addr.s_addr=inet_addr(SERVERADDR);
			else
			// попытка получить IP адрес по доменному имени сервера
				if (hst=gethostbyname(SERVERADDR))
					// hst>h_addr_list содержит не массив адресов,
					// а массив указателей на адреса
					((unsigned long *)&dest_addr.sin_addr)[0]=
					((unsigned long **)hst->h_addr_list)[0][0];
				else 
				{
					this->textBox2->Text += "Invalid address";
					closesocket(my_sock);
					WSACleanup();
				}
			// адрес сервера получен – пытаемся установить соединение 
			if (connect(my_sock,(sockaddr *)&dest_addr,sizeof(dest_addr)))
			{
				this->textBox2->Text += "   Connect error   ";
			}
			this->textBox2->Text += "   Connection found. Type quit for exit   ";
			
			//Шаг 4 чтение и передача сообщений
			int nsize;
			while((nsize=recv(my_sock,&buff[0],sizeof(buff)-1,0))!=SOCKET_ERROR)
			{
			  // ставим завершающий ноль в конце строки 
			  buff[nsize]=0;

			  // выводим на экран 
			  this->textBox2->Text += "S=>C:";
			  this->textBox2->Text += mess;//11111111111111111111111111111111buff
			//  printf("S=>C:%s",buff);

			  // читаем пользовательский ввод с клавиатуры
			  this->textBox2->Text += "S<=C:"; 
			  //fgets(&buff[0],sizeof(buff)-1,stdin);
			  mess = "test";
			  this->textBox2->Text += mess;
			  // проверка на "quit"
			 // if (!strcmp(&buff[0],"quit\n"))
			 // {
				//// Корректный выход
				//this->textBox2->Text = "exit...";
				//closesocket(my_sock);
				//WSACleanup();
			 // }

			  // передаем строку клиента серверу
			  send(my_sock,&buff[0],nsize,0);
			}
			this->textBox2->Text += "Recv error...";
			//printf("Recv error %d\n",WSAGetLastError());
			closesocket(my_sock);
			WSACleanup();

			
			 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

			/*this->textBox2->Text = "close connection\n";
			closesocket(my_sock);
			WSACleanup();*/
		 }


private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

