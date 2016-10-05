#include "stdafx.h"
#include "Form2.h"
#include "MyForm.h"
#include <numeric>

namespace MotionDetection {

  int sigma = 100;
  int fil_length = 3;
  std::vector<double> gs;
  double gs_sum = 0;
  std::vector<double> ds_in;
  std::vector<double> sp_in;
  //these two parameters need to be verified
  double density_max = 0;
  double speed_max = 0;
  int old_state = 0;

  void genGs() {
    for (int i = -fil_length; i <= fil_length; ++i) {
      gs.push_back(exp(-pow(i, 2) / (2 * pow(sigma, 2))));
    }
  }

  template<typename T>
  std::vector<T>
    conv(std::vector<T> const &f, std::vector<T> const &g) {
      size_t const nf = f.size();
      size_t const ng = g.size();
      size_t const n = nf + ng - 1;
      std::vector<T> out(n, T());
      for (auto i(0); i < n; ++i) {
        size_t const jmn = (i >= ng - 1) ? i - (ng - 1) : 0;
        size_t const jmx = (i < nf - 1) ? i : nf - 1;
        for (auto j(jmn); j <= jmx; ++j) {
          out[i] += (f[j] * g[i - j]);
        }
      }
      return out;
    }

  Form2::Form2(void)
  {
    //cout << "Form2: ctor" << endl;
    InitializeComponent();
    //
    //TODO: Add the constructor code here
    //
    std::ifstream speed("distance.txt");
    std::ifstream density("percentage.txt");
    ds_in.clear();
    sp_in.clear();
    ds_in.reserve(1000);
    sp_in.reserve(1000);
    double sp, ds;
    if (speed) {
      while (speed >> sp) {
        ds_in.push_back(sp);
      }
    }
    speed.close();
    if (density) {
      while (density >> ds) {
        sp_in.push_back(ds);
      }
    }
    density.close();
    gs.clear();
    genGs();
    gs_sum = std::accumulate(gs.begin(), gs.end(), 0LL);
  }
  Form2::~Form2()
  {
    cout << "Form2 Dtor" << endl;
    if (components)
    {
      delete components;
    }
    this->chart1->Series["Speed"]->Points->Clear();
    this->chart1->Series["Density"]->Points->Clear();
    this->chart1->Series["State"]->Points->Clear();
  }

  System::Void Form2::btStart_Click(System::Object^  sender, System::EventArgs^  e) {
    cout << "Start" << endl;
    this->chart1->Series["Speed"]->Points->Clear();
    this->chart1->Series["Density"]->Points->Clear();
    this->chart1->Series["State"]->Points->Clear();

    MyForm mForm;
    // Convolution and normalize
    std::vector<double> ds_tmp = conv(ds_in, gs);
    std::vector<double> sp_tmp = conv(sp_in, gs);
    //cout << "ds_tmp: " << ds_tmp.size() << ", sp_tmp: " << sp_tmp.size() << endl;

    density_max = *std::max_element(ds_tmp.begin(), ds_tmp.end());
    speed_max = *std::max_element(sp_tmp.begin(), sp_tmp.end());
    //cout << "density_max: " << density_max << ", speed_max: " << speed_max << endl;

    for (size_t i = 0; i < ds_tmp.size(); ++i) {
      ds_tmp[i] = ds_tmp[i] / (gs_sum * density_max);
    }
    for (size_t i = 0; i < sp_tmp.size(); ++i) {
      sp_tmp[i] = sp_tmp[i] / (gs_sum * speed_max);
    }
    // Get center part
    std::vector<double> ds_out;
    if (ds_in.size() % 2 != 0) {
      for (size_t i = (gs.size() - 1) / 2 + 1; i < ds_tmp.size() - (gs.size() - 1) / 2; ++i) {
        ds_out.push_back(ds_tmp[i]);
      }
    }
    else {
      for (size_t i = (gs.size() - 1) / 2; i < ds_tmp.size() - (gs.size() - 1) / 2; ++i) {
        ds_out.push_back(ds_tmp[i]);
      }
    }
    std::vector<double> sp_out;
    if (sp_in.size() % 2 != 0) {
      for (size_t i = (gs.size() - 1) / 2 + 1; i < sp_tmp.size() - (gs.size() - 1) / 2; ++i) {
        sp_out.push_back(sp_tmp[i]);
      }
    }
    else {
      for (size_t i = (gs.size() - 1) / 2; i < sp_tmp.size() - (gs.size() - 1) / 2; ++i) {
        sp_out.push_back(sp_tmp[i]);
      }
    }
    //cout << "ds_out: " << ds_out.size() << ", sp_out: " << sp_out.size() << endl;

    // Apply Fuzzy
    for (size_t i = 0; i < ds_out.size(); ++i) {
      int new_state = mForm.StringToState(mForm.Fuzzy(ds_out[i], sp_out[i]));
      if (new_state != old_state) {
        old_state = new_state;
        this->chart1->Series["State"]->Points->AddXY(i, new_state);
      }
      this->chart1->Series["Density"]->Points->AddY(ds_out[i]);
      this->chart1->Series["Speed"]->Points->AddY(sp_out[i]);
    }
  }

System::Void Form2::button1_Click(System::Object^  sender, System::EventArgs^  e) {
  cout << "Close." << endl;
  this->chart1->Series["Speed"]->Points->Clear();
  this->chart1->Series["Density"]->Points->Clear();
  this->chart1->Series["State"]->Points->Clear();
  ds_in.clear();
  sp_in.clear();
  //cout << "ds_in: " << ds_in.size() << ", sp_in: " << sp_in.size() << endl;
  this->Close();
}
System::Void Form2::btDist_Click(System::Object^  sender, System::EventArgs^  e) {
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
System::Void Form2::btPerc_Click(System::Object^  sender, System::EventArgs^  e) {
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

}  // end namespace

