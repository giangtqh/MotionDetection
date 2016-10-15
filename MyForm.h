#ifndef _MYFORM_
#define _MYFORM_
#pragma once

#include "stdafx.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2\core\core.hpp>

#include <math.h>
#include <algorithm>
#include <map>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>

namespace MotionDetection {
  using namespace std;
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace cv;
  using namespace System::Runtime::InteropServices;

  /// <summary>
  /// Summary for MyForm
  /// </summary>
  public ref class MyForm : public System::Windows::Forms::Form
  {
  public:
    MyForm(void)
    {
      InitializeComponent();
      //
      //TODO: Add the constructor code here
      //
    }
    int MyForm::StringToState(const std::string& state);
    int Fuzzy(const double& speed_est, const double& density_est);
  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~MyForm()
    {
      if (components)
      {
        delete components;
      }
    }
  private: System::Windows::Forms::Button^  btvOpen;
  protected:
  private: System::Windows::Forms::Label^  label4;
  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::Label^  label5;
  private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::PictureBox^  picOutput;

  private: System::Windows::Forms::PictureBox^  picFg;

  private: System::Windows::Forms::PictureBox^  picBg;

  private: System::Windows::Forms::PictureBox^  picInput;
  private: System::Windows::Forms::Button^  btvStart;

  private: System::Windows::Forms::OpenFileDialog^  dlgOpenVideo;
  private: System::Windows::Forms::Button^  btPause;


  private: System::Windows::Forms::CheckBox^  ckbox_sFrame;
  private: System::Windows::Forms::Timer^  timer1;
  private: System::Windows::Forms::Button^  btMask;
  private: System::Windows::Forms::OpenFileDialog^  dialogOpenMask;


  private: System::Windows::Forms::TextBox^  txtFuzzy;
  private: System::Windows::Forms::Button^  btLoadChart;
  private: System::Windows::Forms::CheckBox^  cboxEnDebug;
  private: System::Windows::Forms::TextBox^  txtSpMax;
  private: System::Windows::Forms::Label^  label6;

  private: System::ComponentModel::IContainer^  components;

  protected:

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    bool ForegroundProcess(const Mat& coarseForeground, Mat& thresholdImage);
    void motion_processing();
    void origin_motion_processing();
    void build_background_model();
    void DrawCVImage(System::Windows::Forms::Control^ control, cv::Mat& colorImage, bool isGray);
    void SaveImage(const char*& filenameFormat, unsigned int& indexNumber, Mat& img);
    double PixelPercentage(const Mat& img);
    double calcDistance(const Mat& flow, const Mat& cflowmap, int step);
    void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color);
    bool highlightObjects(const Mat& colorInput, const Mat& mask, Mat& colorOutput);
    const std::string& MyForm::StateToString(int state);

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      this->components = (gcnew System::ComponentModel::Container());
      this->btvOpen = (gcnew System::Windows::Forms::Button());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->picOutput = (gcnew System::Windows::Forms::PictureBox());
      this->picFg = (gcnew System::Windows::Forms::PictureBox());
      this->picBg = (gcnew System::Windows::Forms::PictureBox());
      this->picInput = (gcnew System::Windows::Forms::PictureBox());
      this->btvStart = (gcnew System::Windows::Forms::Button());
      this->dlgOpenVideo = (gcnew System::Windows::Forms::OpenFileDialog());
      this->btPause = (gcnew System::Windows::Forms::Button());
      this->ckbox_sFrame = (gcnew System::Windows::Forms::CheckBox());
      this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
      this->btMask = (gcnew System::Windows::Forms::Button());
      this->dialogOpenMask = (gcnew System::Windows::Forms::OpenFileDialog());
      this->txtFuzzy = (gcnew System::Windows::Forms::TextBox());
      this->btLoadChart = (gcnew System::Windows::Forms::Button());
      this->cboxEnDebug = (gcnew System::Windows::Forms::CheckBox());
      this->txtSpMax = (gcnew System::Windows::Forms::TextBox());
      this->label6 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picOutput))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFg))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBg))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picInput))->BeginInit();
      this->SuspendLayout();
      // 
      // btvOpen
      // 
      this->btvOpen->Location = System::Drawing::Point(691, 30);
      this->btvOpen->Name = L"btvOpen";
      this->btvOpen->Size = System::Drawing::Size(75, 29);
      this->btvOpen->TabIndex = 0;
      this->btvOpen->Text = L"Open Video";
      this->btvOpen->UseVisualStyleBackColor = true;
      this->btvOpen->Click += gcnew System::EventHandler(this, &MyForm::btvOpen_Click);
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Location = System::Drawing::Point(459, 514);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(39, 13);
      this->label4->TabIndex = 7;
      this->label4->Text = L"Output";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Location = System::Drawing::Point(122, 514);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(61, 13);
      this->label3->TabIndex = 8;
      this->label3->Text = L"Foreground";
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Location = System::Drawing::Point(709, 14);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(34, 13);
      this->label5->TabIndex = 9;
      this->label5->Text = L"Video";
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point(459, 255);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(65, 13);
      this->label2->TabIndex = 10;
      this->label2->Text = L"Background";
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(140, 255);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(31, 13);
      this->label1->TabIndex = 11;
      this->label1->Text = L"Input";
      // 
      // picOutput
      // 
      this->picOutput->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->picOutput->Location = System::Drawing::Point(349, 271);
      this->picOutput->Name = L"picOutput";
      this->picOutput->Size = System::Drawing::Size(320, 240);
      this->picOutput->TabIndex = 3;
      this->picOutput->TabStop = false;
      // 
      // picFg
      // 
      this->picFg->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->picFg->Location = System::Drawing::Point(12, 271);
      this->picFg->Name = L"picFg";
      this->picFg->Size = System::Drawing::Size(320, 240);
      this->picFg->TabIndex = 4;
      this->picFg->TabStop = false;
      // 
      // picBg
      // 
      this->picBg->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->picBg->Location = System::Drawing::Point(349, 12);
      this->picBg->Name = L"picBg";
      this->picBg->Size = System::Drawing::Size(320, 240);
      this->picBg->TabIndex = 5;
      this->picBg->TabStop = false;
      // 
      // picInput
      // 
      this->picInput->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->picInput->Location = System::Drawing::Point(12, 12);
      this->picInput->Name = L"picInput";
      this->picInput->Size = System::Drawing::Size(320, 240);
      this->picInput->TabIndex = 6;
      this->picInput->TabStop = false;
      // 
      // btvStart
      // 
      this->btvStart->Location = System::Drawing::Point(691, 101);
      this->btvStart->Name = L"btvStart";
      this->btvStart->Size = System::Drawing::Size(75, 29);
      this->btvStart->TabIndex = 12;
      this->btvStart->Text = L"Start";
      this->btvStart->UseVisualStyleBackColor = true;
      this->btvStart->Click += gcnew System::EventHandler(this, &MyForm::btvStart_Click);
      // 
      // dlgOpenVideo
      // 
      this->dlgOpenVideo->FileName = L"openFileDialog1";
      // 
      // btPause
      // 
      this->btPause->Location = System::Drawing::Point(691, 136);
      this->btPause->Name = L"btPause";
      this->btPause->Size = System::Drawing::Size(75, 29);
      this->btPause->TabIndex = 12;
      this->btPause->Text = L"Pause";
      this->btPause->UseVisualStyleBackColor = true;
      this->btPause->Click += gcnew System::EventHandler(this, &MyForm::btPause_Click);
      // 
      // ckbox_sFrame
      // 
      this->ckbox_sFrame->AutoSize = true;
      this->ckbox_sFrame->Location = System::Drawing::Point(691, 468);
      this->ckbox_sFrame->Name = L"ckbox_sFrame";
      this->ckbox_sFrame->Size = System::Drawing::Size(83, 17);
      this->ckbox_sFrame->TabIndex = 13;
      this->ckbox_sFrame->Text = L"Save Frame";
      this->ckbox_sFrame->UseVisualStyleBackColor = true;
      this->ckbox_sFrame->CheckedChanged += gcnew System::EventHandler(this, &MyForm::ckbox_sFrame_CheckedChanged);
      // 
      // timer1
      // 
      this->timer1->Interval = 30;
      this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
      // 
      // btMask
      // 
      this->btMask->Location = System::Drawing::Point(691, 65);
      this->btMask->Name = L"btMask";
      this->btMask->Size = System::Drawing::Size(75, 29);
      this->btMask->TabIndex = 14;
      this->btMask->Text = L"Mask";
      this->btMask->UseVisualStyleBackColor = true;
      this->btMask->Click += gcnew System::EventHandler(this, &MyForm::btMask_Click);
      // 
      // dialogOpenMask
      // 
      this->dialogOpenMask->FileName = L"openMaskdialog";
      // 
      // txtFuzzy
      // 
      this->txtFuzzy->Location = System::Drawing::Point(691, 444);
      this->txtFuzzy->Name = L"txtFuzzy";
      this->txtFuzzy->Size = System::Drawing::Size(75, 20);
      this->txtFuzzy->TabIndex = 16;
      // 
      // btLoadChart
      // 
      this->btLoadChart->Location = System::Drawing::Point(691, 409);
      this->btLoadChart->Name = L"btLoadChart";
      this->btLoadChart->Size = System::Drawing::Size(75, 29);
      this->btLoadChart->TabIndex = 18;
      this->btLoadChart->Text = L"Load chart";
      this->btLoadChart->UseVisualStyleBackColor = true;
      this->btLoadChart->Click += gcnew System::EventHandler(this, &MyForm::btLoadChart_Click);
      // 
      // cboxEnDebug
      // 
      this->cboxEnDebug->AutoSize = true;
      this->cboxEnDebug->Location = System::Drawing::Point(691, 492);
      this->cboxEnDebug->Name = L"cboxEnDebug";
      this->cboxEnDebug->Size = System::Drawing::Size(94, 17);
      this->cboxEnDebug->TabIndex = 19;
      this->cboxEnDebug->Text = L"Enable Debug";
      this->cboxEnDebug->UseVisualStyleBackColor = true;
      this->cboxEnDebug->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cboxEnDebug_CheckedChanged);
      // 
      // txtSpMax
      // 
      this->txtSpMax->Location = System::Drawing::Point(691, 383);
      this->txtSpMax->Name = L"txtSpMax";
      this->txtSpMax->Size = System::Drawing::Size(75, 20);
      this->txtSpMax->TabIndex = 20;
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Location = System::Drawing::Point(688, 367);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(58, 13);
      this->label6->TabIndex = 21;
      this->label6->Text = L"SpeedMax";
      // 
      // MyForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(784, 532);
      this->Controls->Add(this->label6);
      this->Controls->Add(this->txtSpMax);
      this->Controls->Add(this->cboxEnDebug);
      this->Controls->Add(this->btLoadChart);
      this->Controls->Add(this->txtFuzzy);
      this->Controls->Add(this->btMask);
      this->Controls->Add(this->ckbox_sFrame);
      this->Controls->Add(this->btPause);
      this->Controls->Add(this->btvStart);
      this->Controls->Add(this->label4);
      this->Controls->Add(this->label3);
      this->Controls->Add(this->label5);
      this->Controls->Add(this->label2);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->picOutput);
      this->Controls->Add(this->picFg);
      this->Controls->Add(this->picBg);
      this->Controls->Add(this->picInput);
      this->Controls->Add(this->btvOpen);
      this->Name = L"MyForm";
      this->Text = L"Motion Detection";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picOutput))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFg))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBg))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picInput))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion

    //Form action controler
  private: System::Void btvOpen_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void btvStart_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);
  private: System::Void btPause_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void ckbox_sFrame_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
  private: System::Void btMask_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void btLoadChart_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void cboxEnDebug_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
};
}

#endif  // _MYFORM_