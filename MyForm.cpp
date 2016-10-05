// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyForm.h"
#include "Form2.h"

#define TIMER
//using namespace std;
//using namespace System::String;
namespace MotionDetection {

  // Global declaration
  char* MaskFilename;
  VideoCapture cap;
  VideoCapture inputVideo;
  Mat resizeFrame, fg, bgBuilt;
  Mat frame, frame1, frame2, frameMask, frame1Mask, frame2Mask, mask1, mask2, flow, output;
  Mat foreground1, foreground2, background;
  Mat foreOut1, foreOut2;
  unsigned int frame_count = 0;
  ofstream percentage;
  ofstream dist;
  Mat object_bg;

  bool is_BuildBGModel = false;
  bool gIsSaveFrame = false;
  double g_frameNumbers = 0;

  const char* cFgPath = "courseForeground/cfg-%06d.jpg";
  const char* outputPath = "OutputImage/%06d-out.jpg";
  const char* bgPath = "D:/Study/HCMUT/Nam 5/LVTN/Dataset/Output/4917-5_70/bg-%06d.jpg";
  const char* fgPath = "D:/Study/HCMUT/Nam 5/LVTN/Dataset/Output/4917-5_70/%06d-fg.jpg";
  //const char* outputPath = "D:/Study/HCMUT/Nam 5/LVTN/Dataset/Output/4917-5_70/mask1/%06d-out.jpg";

  /* For Fuzzy logic
  */
  double sp1_ = 0.075;
  double sp2_ = 0.15;
  double sp3_ = 0.25;
  double sp4_ = 0.5;
  double sp5_ = 0.75;

  double ds1_ = 0.1;
  double ds2_ = 0.2;
  double ds3_ = 0.4;
  double ds4_ = 0.5;
  double ds5_ = 0.6;

  const std::string kEmpty = "Empty";
  const std::string kOpen = "Open";
  const std::string kNormal = "Normal";
  const std::string kCrowded = "Crowded";
  const std::string kStop = "Stop";
  const std::string kNA = "N/A";

  std::map<std::string, double> state_map;
  std::string traffic_state = "Begin";

  struct LessBySecond
  {
    template <typename Lhs, typename Rhs>
    bool operator()(const Lhs& lhs, const Rhs& rhs) const
    {
      return lhs.second < rhs.second;
    }
  };

  //Goi ham Background Subtractor
  Ptr<BackgroundSubtractorMOG2> bgsub;

  // Motion detection function definition
  bool MyForm::ForegroundProcess(const Mat& coarseForeground, Mat& thresholdImage)
  {
    //imshow("Coarse Foreground", coarseForeground);
    //imwrite("000001-cfg.jpg", coarseForeground);
    Mat noShadowImage, blurImage;
    //threshold(coarseForeground, noShadowImage, 128, 255, THRESH_BINARY);
    //imshow("No Shadow", noShadowImage);
    //Lam mo de loai nhieu
    GaussianBlur(coarseForeground, blurImage, cv::Size(11, 11), 4.0, 4.0);
    //imshow("Blur", blurImage);
    //Lay nguong de loai bo nhieu
    threshold(blurImage, thresholdImage, 144, 255, THRESH_BINARY);
    return(thresholdImage.data != NULL);
  }

  bool MyForm::highlightObjects(const Mat& colorInput, Mat& mask, Mat& colorOutput)
  {
    Mat channels[3];
    split(colorInput, channels);
    for (int i = 0; i < mask.rows; i++)
    {
      for (int j = 0; j < mask.cols; j++)
      {
        if (mask.at<uchar>(i, j) == 255)
        {
          channels[2].at<uchar>(i, j) = 255;
        }
      }
    }
    merge(channels, 3, colorOutput);
    return (colorOutput.data != NULL);
  }

  void MyForm::drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color)
  {
    for (int y = 0; y < cflowmap.rows; y += step)
    {
      for (int x = 0; x < cflowmap.cols; x += step)
      {
        const Point2f& fxy = flow.at<Point2f>(y, x);
        line(cflowmap, cv::Point(x, y), cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), color);
        circle(cflowmap, cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), 1, color, -1);
      }
    }
  }

  double MyForm::calcDistance(const Mat& flow, Mat& cflowmap, int step)
  {
    double distance = 0, sum = 0;
    for (int y = 0; y < cflowmap.rows; y += step)
    {
      for (int x = 0; x < cflowmap.cols; x += step)
      {
        const Point2f& fxy = flow.at<Point2f>(y, x);
        distance = sqrt(fxy.x*fxy.x + fxy.y*fxy.y);
        sum += distance;
      }
    }
    return((double)sum / (step*step));
  }

  double MyForm::PixelPercentage(const Mat& img)
  {
    //Mat mask = imread("mask3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat mask = imread(MaskFilename, CV_LOAD_IMAGE_GRAYSCALE);
    resize(mask, mask, cv::Size(320, 240));
    bitwise_not(mask, mask, Mat());
    int totalPix = countNonZero(mask);
    bitwise_and(img, mask, img, Mat());
    int whitePix = countNonZero(img);
    return (((double)whitePix / totalPix) * 100);
  }

  void MyForm::SaveImage(const char*& filenameFormat, unsigned int& indexNumber, Mat& img)
  {
    char namebuff[256];
    sprintf(namebuff, filenameFormat, indexNumber);//luu filenameFormat vao chuoi namebuff
    imwrite(namebuff, img);
    //std::string filename(filenameFormat + indexNumber);
    //imwrite(filename, img);
  }

  //end Motion detection function definition

  void MyForm::DrawCVImage(System::Windows::Forms::Control^ control, cv::Mat& colorImage, bool isGray)
  {
    System::Drawing::Graphics^ graphics = control->CreateGraphics();
    System::IntPtr ptr(colorImage.ptr());
    System::Drawing::RectangleF rect(0, 0, control->Width, control->Height);
    if (!isGray)
    {
      System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(colorImage.cols, colorImage.rows, colorImage.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
      graphics->DrawImage(b, rect);
    }
    else
    {
      System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(colorImage.cols, colorImage.rows, colorImage.step, System::Drawing::Imaging::PixelFormat::Format8bppIndexed, ptr);
      graphics->DrawImage(b, rect);
    }
    delete graphics;
  }

  void MyForm::build_background_model()
  {
    if (!is_BuildBGModel)
    {
      cout << "Start processing ... " << endl;
      is_BuildBGModel = true;
      cout << "Build background model ... " << endl;

      /*mask1 = imread("mask3.jpg", CV_LOAD_IMAGE_COLOR);
      mask2 = imread("mask3.jpg", CV_LOAD_IMAGE_GRAYSCALE);*/
      mask1 = imread(MaskFilename, CV_LOAD_IMAGE_COLOR);
      mask2 = imread(MaskFilename, CV_LOAD_IMAGE_GRAYSCALE);
      resize(mask1, mask1, cv::Size(320, 240));
      resize(mask2, mask2, cv::Size(320, 240));

      //Build Background Model
      bgsub = new BackgroundSubtractorMOG2(200, 100.0, false);

      g_frameNumbers = cap.get(CV_CAP_PROP_FRAME_COUNT);
      for (int frameCount = 1; frameCount <= g_frameNumbers; ++frameCount)
      {
        //Lay frame
        cap.read(frame);
        if (frame.empty())
        {
          cout << "[Build BGM] Done, Number of frames: " << frameCount << endl;
          break;
          //continue;
        }
        resize(frame, resizeFrame, cv::Size(320, 240));

        //Tach foreground va cap nhat mo hinh background
        bgsub->operator()(resizeFrame, fg, 0.02);
        if (0 == (frameCount % 50))
          cout << "Da them frame so " << frameCount << " vao ham Background Subtraction" << endl;
      }

      cap.set(CV_CAP_PROP_POS_AVI_RATIO, 0);
      bgsub->getBackgroundImage(bgBuilt);
      bgsub->operator()(bgBuilt, fg);
    }
    else cout << "Resume processing" << endl;
  }

  const std::string& MyForm::Fuzzy(const double& density_est, const double& speed_est)
  {
    //double flogic_sp, flogic_ds;

    double sp1 = std::max<double>(0, std::min<double>(1, (speed_est - sp2_) / (sp1_ - sp2_)));
    double sp2 = std::max<double>(0, std::min<double>((speed_est - sp1_) / (sp2_ - sp1_), (speed_est - sp3_) / (sp2_ - sp3_)));
    double sp3 = std::max<double>(0, std::min<double>((speed_est - sp2_) / (sp3_ - sp2_), (speed_est - sp4_) / (sp3_ - sp4_)));
    double sp4 = std::max<double>(0, std::min<double>((speed_est - sp3_) / (sp4_ - sp3_), (speed_est - sp5_) / (sp4_ - sp5_)));
    double sp5 = std::max<double>(0, std::min<double>(1, (speed_est - sp4_) / (sp5_ - sp4_)));

    double ds1 = std::max<double>(0, std::min<double>(1, (density_est - ds2_) / (ds1_ - ds2_)));
    double ds2 = std::max<double>(0, std::min<double>((density_est - ds1_) / (ds2_ - ds1_), (density_est - ds3_) / (ds2_ - ds3_)));
    double ds3 = std::max<double>(0, std::min<double>((density_est - ds2_) / (ds3_ - ds2_), (density_est - ds4_) / (ds3_ - ds4_)));
    double ds4 = std::max<double>(0, std::min<double>((density_est - ds3_) / (ds4_ - ds3_), (density_est - ds5_) / (ds4_ - ds5_)));
    double ds5 = std::max<double>(0, std::min<double>(1, (density_est - ds4_) / (ds5_ - ds4_)));

    double A = std::max<double>(ds1*sp1, std::max<double>(ds1*sp2, ds2*sp1));
    double B = std::max<double>(std::max<double>(ds5*sp1, std::max<double>(ds3*sp1, ds4*sp1)), std::max<double>(ds4*sp3, std::max<double>(ds5*sp2, ds4*sp2)));
    double C = std::max<double>(std::max<double>(ds2*sp3, std::max<double>(ds2*sp2, ds3*sp2)), std::max<double>(ds3*sp3, std::max<double>(ds3*sp4, ds4*sp4)));
    double D = std::max<double>(ds2*sp4, std::max<double>(ds2*sp5, ds3*sp5));
    double E = std::max<double>(ds1*sp3, std::max<double>(ds1*sp4, ds2*sp5));

    state_map.clear();
    state_map[kEmpty] = A;
    state_map[kOpen] = B;
    state_map[kNormal] = C;
    state_map[kCrowded] = D;
    state_map[kStop] = E;
    auto x = std::max_element(state_map.begin(), state_map.end(), LessBySecond());
    return x->first;
  }

  void MyForm::motion_processing()
  {
    //clock_t begin = clock();
    {
      cap.read(frame);
      if (frame.empty())
      {
        return;
      }
      else frame_count++;
      resize(frame, frame1, cv::Size(320, 240));
      add(frame1, mask1, frameMask, Mat());
      bgsub->operator()(frame1, foreground1, 0.0007);
      if (gIsSaveFrame)
      {
        SaveImage(cFgPath, frame_count, foreground1);
      }
      ForegroundProcess(foreground1, foreOut1);

      cap.read(frame);
      if (frame.empty())
      {
        return;
      }
      else
      {
        frame_count++;
        DrawCVImage(picInput, frame, false);
      }
      resize(frame, frame2, cv::Size(320, 240));
      bgsub->operator()(frame2, foreground2, 0.0007);
      if (gIsSaveFrame)
      {
        SaveImage(cFgPath, frame_count, foreground1);
      }
      ForegroundProcess(foreground2, foreOut2);

      bgsub->getBackgroundImage(background);
      highlightObjects(frame2, foreOut2, object_bg);
      DrawCVImage(picBg, object_bg, false);

      add(foreOut1, mask2, frame1Mask, Mat());
      add(foreOut2, mask2, frame2Mask, Mat());

      DrawCVImage(picFg, frame1Mask, true);

      // Xu ly 2 foreground bang Dense Optical Flow(Farneback)
      double pyr_scale = .25;
      int levels = 5;
      int winsize = 15;
      int iterations = 3;
      int poly_n = 7;
      double poly_sigma = 1.5;

      calcOpticalFlowFarneback(frame1Mask, frame2Mask, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, 0);

      int step = 4;
      for (int y = 0; y < frameMask.rows; y += step)
      {
        for (int x = 0; x < frameMask.cols; x += step)
        {
          const Point2f& fxy = flow.at<Point2f>(y, x);
          line(frameMask, cv::Point(x, y), cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), CV_RGB(0, 255, 0));
          circle(frameMask, cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), 1, CV_RGB(0, 255, 0), -1);
        }
      }

      //drawOptFlowMap(flow, frameMask, 4, CV_RGB(0, 255, 0)); //replaced by two for loops above
      highlightObjects(frameMask, frame1Mask, frameMask);
      DrawCVImage(picOutput, frameMask, false);

      double ds = PixelPercentage(frame1Mask);
      double sp = calcDistance(flow, frameMask, 4);
     
      // Write values to file
      percentage << ds << endl;
      dist << sp << endl;

      std::string new_state = Fuzzy(ds, sp);
      if (new_state.compare(traffic_state)) {
        traffic_state = new_state;
        txtFuzzy->Text = gcnew System::String(traffic_state.c_str());
      }

      if (gIsSaveFrame)
      {
        SaveImage(outputPath, frame_count, frameMask);
      }

      if ((frame_count % 50 == 0))
      {
        bgsub->getBackgroundImage(background);
        //imshow("Background", background);
        //if (!frame.empty())
        //DrawCVImage(picBg, background, false); //reload background every 50 frames
        //SaveImage(bgPath, frameCount, background);
      }
    }
    if (frame_count >= g_frameNumbers)
    {
      timer1->Stop();
      cout << "Finished!" << endl;
      frame_count = 0;
    }

    //clock_t end = clock();
    //double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    //cout << "Process time/frame: " << elapsed_secs << endl;
  }

  void MyForm::origin_motion_processing()
  {
    unsigned int frameCount = 0;
    for (;;)
    {
      clock_t begin = clock();
      cap.read(frame);
      if (frame.empty())
      {
        cout << "Khong tim thay frame so " << frameCount << endl;
        break;
      }
      else frameCount++;
      resize(frame, frame1, cv::Size(320, 240));
      add(frame1, mask1, frameMask, Mat());
      bgsub->operator()(frame1, foreground1, 0.0007);
      if (gIsSaveFrame)
      {
        SaveImage(cFgPath, frameCount, foreground1);
      }
      ForegroundProcess(foreground1, foreOut1);

      cap.read(frame);
      if (frame.empty())
      {
        cout << "Khong tim thay frame so " << frameCount << endl;
        break;
      }
      {
        frame_count++;
        DrawCVImage(picInput, frame, false);
      }
      resize(frame, frame2, cv::Size(320, 240));
      bgsub->operator()(frame2, foreground2, 0.0007);
      if (gIsSaveFrame)
      {
        SaveImage(cFgPath, frameCount, foreground1);
      }
      ForegroundProcess(foreground2, foreOut2);

      Mat object_bg;
      bgsub->getBackgroundImage(background);
      highlightObjects(frame2, foreOut2, object_bg);
      DrawCVImage(picBg, object_bg, false);


      add(foreOut1, mask2, frame1Mask, Mat());
      add(foreOut2, mask2, frame2Mask, Mat());

      //imshow("Foreground 1", frame1Mask);
      //DrawCVImage(picFg, frame1Mask);
      DrawCVImage(picFg, frame1Mask, true);

      // Xu ly 2 foreground bang Dense Optical Flow(Farneback)
      double pyr_scale = .25;
      int levels = 5;
      int winsize = 15;
      int iterations = 3;
      int poly_n = 7;
      double poly_sigma = 1.5;

      calcOpticalFlowFarneback(frame1Mask, frame2Mask, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, 0);

      //Ve mui ten the hien chieu chuyen dong
      drawOptFlowMap(flow, frameMask, 4, CV_RGB(0, 255, 0));
      highlightObjects(frameMask, frame1Mask, frameMask);
      //imshow("Output", frameMask);
      DrawCVImage(picOutput, frameMask, false);

      cout << "Frame " << frameCount << endl;
      percentage << PixelPercentage(frame1Mask) << endl;
      dist << calcDistance(flow, frameMask, 4) << endl;

      //SaveImage(fgPath, frameCount, frame1Mask);
      //SaveImage(outputPath, frameCount, frameMask);
      if (gIsSaveFrame)
      {
        SaveImage(outputPath, frameCount, frameMask);
      }

      if ((frameCount % 50 == 0))
      {
        bgsub->getBackgroundImage(background);
        //imshow("Background", background);
        //DrawCVImage(picBg, background, false);
        //SaveImage(bgPath, frameCount, background);
      }
      clock_t end = clock();
      //double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      //cout << "Process time/frame: " << elapsed_secs << endl;
    }
  }

  const std::string& MyForm::StateToString(int state) {
    switch (state)
    {
    case 1: return kEmpty;
    case 2: return kOpen;
    case 3: return kNormal;
    case 4: return kCrowded;
    case 5: return kStop;
    default: return kNA;
    }
  }

  int MyForm::StringToState(const std::string& state) {
    if (!state.compare(kEmpty)) return 1;
    else if (!state.compare(kOpen)) return 2;
    else if (!state.compare(kNormal)) return 3;
    else if (!state.compare(kCrowded)) return 4;
    else if (!state.compare(kStop)) return 5;
    else return 0;
  }

System::Void MyForm::btvOpen_Click(System::Object^  sender, System::EventArgs^  e) {
  cout << "Open video" << endl;
  dlgOpenVideo->Filter = "AVI Files (*.avi)|*.avi";
  dlgOpenVideo->FilterIndex = 2;
  dlgOpenVideo->RestoreDirectory = true;

  if (dlgOpenVideo->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return;

  is_BuildBGModel = false; //rebuild background model for new video
  frame_count = 0;

  for each (System::String^ OpenFileName in dlgOpenVideo->FileNames)
  {
    char* OpenFilePtr;
    OpenFilePtr = (char*)Marshal::StringToHGlobalAnsi(OpenFileName).ToPointer();
    cout << "File: " << OpenFilePtr << endl;
    //CvCapture* cap = cvCaptureFromFile(OpenFilePtr);

    inputVideo.open(OpenFilePtr);
    cap.open(OpenFilePtr);

    Marshal::FreeHGlobal((IntPtr)OpenFilePtr);

    if (!inputVideo.isOpened())  // check if we succeeded
    {
      // The file doesn't exist or can't be captured as a video file.
      cout << "Video could not load!!\n";
    }
    else
    {
      cout << "Video loaded succesfully." << endl;
    }
  }
}

System::Void MyForm::btvStart_Click(System::Object^  sender, System::EventArgs^  e) {
  if (!inputVideo.isOpened())  // check if we succeeded
  {
    cout << "Please open video first, then click Start button again." << endl;
    btvOpen_Click(sender, e);
  }
  else
  {
    build_background_model();
    percentage.open("percentage.txt", std::ios_base::out);
    dist.open("distance.txt", std::ios_base::out);
#ifdef TIMER
    //genGs();
    //for (size_t i = 0; i < gs.size(); ++i) {
    //  gs_sum += gs[i];
    //}
    //ds_in.reserve(1000);
    //sp_in.reserve(1000);
    timer1->Start();
#else
    origin_motion_processing();
#endif
  }
}

System::Void MyForm::timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
  try
  {
    /*Mat inputFrame;
    if (inputVideo.read(inputFrame))
    DrawCVImage(picInput, inputFrame, false);*/
    //cout << "timer1_Tick" << endl;
    motion_processing();
  }
  catch (...){}
}
System::Void MyForm::btvStop_Click(System::Object^  sender, System::EventArgs^  e) {
    cout << "Stop processing." << endl;
    timer1->Stop();
}
System::Void MyForm::ckbox_sFrame_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  gIsSaveFrame = !gIsSaveFrame;
  cout << (gIsSaveFrame ? "Save Frame is checked\n" : "Save Frame is unchecked\n");
}
System::Void MyForm::btMask_Click(System::Object^  sender, System::EventArgs^  e) {
  cout << "Choose mask" << endl;
  dialogOpenMask->Filter = "Image Files (*.bmp, *.jpg)|*.bmp;*.jpg";
  dialogOpenMask->FilterIndex = 2;
  dialogOpenMask->RestoreDirectory = true;

  if (dialogOpenMask->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return;

  MaskFilename = (char*)Marshal::StringToHGlobalAnsi(dialogOpenMask->FileName).ToPointer();
  cout << "Mask file: " << MaskFilename << endl;
}
System::Void MyForm::btResume_Click(System::Object^  sender, System::EventArgs^  e) {
  cout << "Resume processing" << endl;
  timer1->Start();
}
System::Void MyForm::btLoadChart_Click(System::Object^  sender, System::EventArgs^  e) {
  cout << "Generate graph" << endl;
  Form2^ f2 = gcnew Form2();
  f2->ShowDialog();
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
  // Enabling Windows XP visual effects before any controls are created
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);

  // Create the main window and run it
  Application::Run(gcnew MyForm());
  return 0;
}

}