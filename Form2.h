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
  private: System::Windows::Forms::Button^  btPerc;
  private: System::Windows::Forms::Button^  btDist;


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
      this->btPerc = (gcnew System::Windows::Forms::Button());
      this->btDist = (gcnew System::Windows::Forms::Button());
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
      this->chart1->Location = System::Drawing::Point(5, 38);
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
      this->chart1->Size = System::Drawing::Size(939, 501);
      this->chart1->TabIndex = 19;
      this->chart1->Text = L"chart1";
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(950, 297);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(75, 23);
      this->button1->TabIndex = 20;
      this->button1->Text = L"Close";
      this->button1->UseVisualStyleBackColor = true;
      this->button1->Click += gcnew System::EventHandler(this, &Form2::button1_Click);
      // 
      // btPerc
      // 
      this->btPerc->Location = System::Drawing::Point(950, 140);
      this->btPerc->Name = L"btPerc";
      this->btPerc->Size = System::Drawing::Size(75, 23);
      this->btPerc->TabIndex = 21;
      this->btPerc->Text = L"Percentage";
      this->btPerc->UseVisualStyleBackColor = true;
      this->btPerc->Click += gcnew System::EventHandler(this, &Form2::btPerc_Click);
      // 
      // btDist
      // 
      this->btDist->Location = System::Drawing::Point(950, 111);
      this->btDist->Name = L"btDist";
      this->btDist->Size = System::Drawing::Size(75, 23);
      this->btDist->TabIndex = 22;
      this->btDist->Text = L"Distance";
      this->btDist->UseVisualStyleBackColor = true;
      this->btDist->Click += gcnew System::EventHandler(this, &Form2::btDist_Click);
      // 
      // openFileDialog1
      // 
      this->openFileDialog1->FileName = L"openFileDialog1";
      // 
      // btStart
      // 
      this->btStart->Location = System::Drawing::Point(950, 38);
      this->btStart->Name = L"btStart";
      this->btStart->Size = System::Drawing::Size(75, 23);
      this->btStart->TabIndex = 23;
      this->btStart->Text = L"Start";
      this->btStart->UseVisualStyleBackColor = true;
      this->btStart->Click += gcnew System::EventHandler(this, &Form2::btStart_Click);
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(215, 17);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(299, 13);
      this->label1->TabIndex = 24;
      this->label1->Text = L"States: 1-Empty, 2-Open, 3-Normal, 4-Crowded, 5-Stop, 6-N/A";
      // 
      // Form2
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1037, 541);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->btStart);
      this->Controls->Add(this->btDist);
      this->Controls->Add(this->btPerc);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->chart1);
      this->Name = L"Form2";
      this->Text = L"Graph";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
             this->chart1->Series["Speed"]->Points->Clear();
             this->chart1->Series["Density"]->Points->Clear();
             this->chart1->Series["State"]->Points->Clear();
             this->Close();
  }
  private: System::Void btDist_Click(System::Object^  sender, System::EventArgs^  e) {
             cout << "Choose distance file" << endl;
             openFileDialog1->Filter = "Text Files (*.txt)|*.txt";
             openFileDialog1->FilterIndex = 2;
             openFileDialog1->RestoreDirectory = true;

             if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return;
             char* dist_file = (char*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName).ToPointer();
             cout << "Distance file: " << dist_file << endl;
             std::ifstream dist(dist_file);

             this->chart1->Series["Speed"]->Points->Clear();
             double ds;
             while (dist >> ds) {
               this->chart1->Series["Speed"]->Points->AddY(ds);
             }
             dist.close();
  }
private: System::Void btPerc_Click(System::Object^  sender, System::EventArgs^  e) {
           cout << "Choose percentage file" << endl;
           openFileDialog1->Filter = "Text Files (*.txt)|*.txt";
           openFileDialog1->FilterIndex = 2;
           openFileDialog1->RestoreDirectory = true;

           if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return;
           char* filename = (char*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName).ToPointer();
           cout << "Percentage file: " << filename << endl;
           std::ifstream perc(filename);

           this->chart1->Series["Density"]->Points->Clear();
           double ds;
           while (perc >> ds) {
             this->chart1->Series["Density"]->Points->AddY(ds);
           }
           perc.close();
}
private: System::Void btStart_Click(System::Object^  sender, System::EventArgs^  e);
};
}
