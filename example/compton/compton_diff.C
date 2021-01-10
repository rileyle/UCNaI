
void compton_diff(TString Name){
  compton_diff(Name, 1.0);
}

void compton_diff(TString Name, Float_t scale){

  TH1F* spec1;
  TH1F* spec2;

  TString specName1 = Name;
  TString specName2 = Name + "notar";

  TString rootName1 = specName1 + ".root";
  TString rootName2 = specName2 + ".root";
  
  TFile *rF1 = new TFile(rootName1);
  rF1->GetObject(specName1, spec1);
  spec1->Rebin(16);
  
  TFile *rF2 = new TFile(rootName2);
  rF2->GetObject(specName2, spec2);
  spec2->Rebin(16);
  
  TCanvas *Spectra = new TCanvas("Spectra", "Spectra", 600, 600);
  Spectra->SetCrosshair();      //Include a crosshair cursor...
  Spectra->ToggleEventStatus(); //...and show its coordinates
  Spectra->Divide(1,2);

  Spectra->cd(1);
  //  spec1->GetXaxis()->SetRangeUser(200.,300.);
  spec1->SetLineColor(kBlue);
  spec1->Draw();
  cout << rootName1 << " blue" << endl;

  spec2->Scale(scale);
  spec2->SetLineColor(kRed);
  spec2->Draw("SAME");
  cout << rootName2 << " red" << endl;  

  Spectra->cd(2);
  TH1F *diff = (TH1F*)spec1->Clone("diff");
  diff->Add(spec2,-1.0);
  diff->SetLineColor(1);
  diff->Draw();

  cout << "Total difference (blue-red) = " << diff->Integral() << endl;

}
