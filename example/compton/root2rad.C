#include "Riostream.h"
#include "iostream"
#include "TFile.h"

void root2rad(TString simFile, TString simName) {
  
  TFile *sF = new TFile(simFile);
  TH1F *sim;
  sF->GetObject(simName,sim);

  TString radFile = simFile.Copy();
  radFile.Replace(radFile.Index(".root",5,0,0),5,".rad",4);
  ofstream rF;
  rF.open(radFile, ios::trunc);

  // Write header line
  TString title = simFile.Copy();
  title.Resize(8);
  Int_t nChan = sim->GetNbinsX();
  rF << title;
  cout << title;
  rF << setw(10) << nChan;
  cout << setw(10) << nChan;
  rF << "         1         1         1" << endl;
  cout << "         1         1         1" << endl;

  Int_t i = 0;
  for(int n=0;n<nChan;n++) {
    
    //rF << std::setbase(10) << std::setw(10) << std::right << sim->GetBinContent(n);
    rF << setw(10) << sim->GetBinContent(n);
    if(++i == 8) {
      rF << endl;
      i=0;
    }

  }

}
