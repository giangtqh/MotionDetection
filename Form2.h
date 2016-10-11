#pragma once
#include <iostream>
#include <fstream>

namespace MotionDetection {
  using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
  using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Form2
	/// </summary>
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
    Form2(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
    ~Form2();
  private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
  protected:
  private: System::Windows::Forms::Button^  button1;
  private: System::Windows::Forms::Button^  btDensity;

  private: System::Windows::Forms::Button^  btSpeed;



  private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
  private: System::Windows::Forms::Button^  btStart;
  private: System::Windows::Forms::Label^  label1;

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
      System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
      System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
      System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
      System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
      System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
      this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->btDensity = (gcnew System::Windows::Forms::Button());
      this->btSpeed = (gcnew System::Windows::Forms::Button());
      this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
      this->btStart = (gcnew System::Windows::Forms::Button());
      this->label1 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
      this->SuspendLayout();
      // 
      // chart1
      // 
      chartArea1->Name = L"ChartArea1";
      this->chart1->ChartAreas->Add(chartArea1);
      legend1->Name = L"Legend1";
      this->chart1->Legends->Add(legend1);
      this->chart1->Location = System::Drawing::Point(3, 41);
      this->chart1->Margin = System::Windows::Forms::Padding(4);
      this->chart1->Name = L"chart1";
      series1->ChartArea = L"ChartArea1";
      series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
      series1->Legend = L"Legend1";
      series1->Name = L"Speed";
      series1->YValuesPerPoint = 4;
      series2->ChartArea = L"ChartArea1";
      series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
      series2->Legend = L"Legend1";
      series2->Name = L"Density";
      series3->ChartArea = L"ChartArea1";
      series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StepLine;
      series3->Legend = L"Legend1";
      series3->Name = L"State";
      this->chart1->Series->Add(series1);
      this->chart1->Series->Add(series2);
      this->chart1->Series->Add(series3);
      this->chart1->Size = System::Drawing::Size(1302, 661);
      this->chart1->TabIndex = 19;
      this->chart1->Text = L"chart1";
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(1205, 5);
      this->button1->Margin = System::Windows::Forms::Padding(4);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(100, 28);
      this->button1->TabIndex = 20;
      this->button1->Text = L"Close";
      this->button1->UseVisualStyleBackColor = true;
      this->button1->Click += gcnew System::EventHandler(this, &Form2::button1_Click);
      // 
      // btDensity
      // 
      this->btDensity->Location = System::Drawing::Point(955, 5);
      this->btDensity->Margin = System::Windows::Forms::Padding(4);
      this->btDensity->Name = L"btDensity";
      this->btDensity->Size = System::Drawing::Size(100, 28);
      this->btDensity->TabIndex = 21;
      this->btDensity->Text = L"Density";
      this->btDensity->UseVisualStyleBackColor = true;
      this->btDensity->Click += gcnew System::EventHandler(this, &Form2::btDensity_Click);
      // 
      // btSpeed
      // 
      this->btSpeed->Location = System::Drawing::Point(847, 5);
      this->btSpeed->Margin = System::Windows::Forms::Padding(4);
      this->btSpeed->Name = L"btSpeed";
      this->btSpeed->Size = System::Drawing::Size(100, 28);
      this->btSpeed->TabIndex = 22;
      this->btSpeed->Text = L"Speed";
      this->btSpeed->UseVisualStyleBackColor = true;
      this->btSpeed->Click += gcnew System::EventHandler(this, &Form2::btSpeed_Click);
      // 
      // openFileDialog1
      // 
      this->openFileDialog1->FileName = L"openFileDialog1";
      // 
      // btStart
      // 
      this->btStart->Location = System::Drawing::Point(1097, 5);
      this->btStart->Margin = System::Windows::Forms::Padding(4);
      this->btStart->Name = L"btStart";
      this->btStart->Size = System::Drawing::Size(100, 28);
      this->btStart->TabIndex = 23;
      this->btStart->Text = L"Start";
      this->btStart->UseVisualStyleBackColor = true;
      this->btStart->Click += gcnew System::EventHandler(this, &Form2::btStart_Click);
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(235, 11);
      this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(442, 17);
      this->label1->TabIndex = 24;
      this->label1->Text = L"Traffic states: 0-Empty, 1-Open, 2-Normal, 3-Crowded, 4-Stop, 5-N/A";
      // 
      // Form2
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1308, 700);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->btStart);
      this->Controls->Add(this->btSpeed);
      this->Controls->Add(this->btDensity);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->chart1);
      this->Margin = System::Windows::Forms::Padding(4);
      this->Name = L"Form2";
      this->Text = L"Graph";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void btSpeed_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btDensity_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btStart_Click(System::Object^  sender, System::EventArgs^  e);
};
}
