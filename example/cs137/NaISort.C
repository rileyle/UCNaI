#include "Riostream.h"
#include "iostream"
#include "TRandom.h"
#include "TFile.h"

// These are global for loadSim()
Float_t sigmaPar1, sigmaPar2, sigma2Frac, a, b, c;
Int_t Nphotopeak;

// Read NaI resolution parameters
void loadNaI(TString fileName) {

  char line[1000];
  Float_t fBuffer[4];
  Int_t   iBuffer[4];
  TString sBuffer[8];

  if(fileName == "") {
    fileName = "NaI.dat";
  }

  ifstream fp;
  fp.open(fileName);

  // Read resolution and calibration parameters
  fp >> sigmaPar1;
  fp.getline(line,1000);  // Advance to next line.
  fp >> sigmaPar2;
  fp.getline(line,1000);  // Advance to next line.
  fp >> sigma2Frac;
  fp.getline(line,1000);  // Advance to next line.
  fp >> a;
  fp.getline(line,1000);  // Advance to next line.
  fp >> b;
  fp.getline(line,1000);  // Advance to next line.
  fp >> c;
  fp.close();

}

// Read simulation data and sort into a histogram matching the
// calibration given.
TH1F *loadSim(TString fileName) {

  char line[1000];
  Float_t fBuffer[4];
  Int_t   iBuffer[4];
  TString sBuffer[8];

  ifstream fp;
  fp.open(fileName);

  Int_t nChannels     = 1024;
  Int_t lo = 0;
  Int_t hi = nChannels;

  TString Name = fileName.Copy();
  Name.Replace(Name.Index(".out",4,0,0),4,"",0);
  TH1F *data = new TH1F(Name,"", nChannels, float(lo), float(hi));
  
  Nphotopeak = 0;
  while(1) {
    fp >> fBuffer[0] >> fBuffer[1] >> fBuffer[2] >> fBuffer[3] >> iBuffer[0];

    if(!(fp.good())) break;

    Nphotopeak += iBuffer[0];

    // Simulate intrinsic detector resolution.
    Float_t Elab  = fBuffer[0];
    Float_t sigma1 = sigmaPar1*sqrt(Elab);
    Float_t sigma2 = sigmaPar2*sqrt(Elab);
    if(gRandom->Rndm() > sigma2Frac)
      Elab += gRandom->Gaus(0,sigma1);
    else
      Elab += gRandom->Gaus(0,sigma2);

    fp.getline(line,1000);  // Move on to the next line.

    // De-calibrate to match measured histogram
    Elab = -b/2/c+sqrt(pow(b/2/c,2)-(a-Elab)/c);

    data->Fill(Elab);

  }

  fp.close();

  return data;

};

void NaISort(TString simFile, TString NaIFile) {

  TString rootFile = simFile.Copy();
  rootFile.Replace(rootFile.Index(".out",4,0,0),4,".root",5);
  TFile *rF = new TFile(rootFile,"recreate");

  cout << "\n... loading resolution parameters ...\n" << endl;
  loadNaI(NaIFile);

  cout << "\n... sorting events in " << simFile << " ...\n" << endl;
  TH1F *sim;
  sim = loadSim(simFile);

  cout << "\n... writing Spectrum to " << rootFile << endl;

  rF->Write();

  cout << "\n " << Nphotopeak << " photopeak events." << endl;

  return;

}
