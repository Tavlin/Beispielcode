#include "CommenHeader.h"

void DetectorRatio(TString AddName = "") {

  //Open and read file
  TFile* P_TSpectra = new TFile("/u/mhemmer/Documents/git/Beispielcode2/P_TSpectra.root", "READ");
  if ( P_TSpectra->IsOpen() ) printf("P_TSpectra opened successfully\n");
  //gFile = HistoFile;

  if(P_TSpectra->IsZombie()){
    std::cout << "ERROR: P_TSpectra File not found" << std::endl;
    return;
  }

  // get Histos from file
  TH1F* hP_TSpectrum = new TH1F();
  SetHistoStandardSettings(hP_TSpectrum);
  gDirectory->GetObject("hP_TSpectrum",hP_TSpectrum);

  P_TSpectra->Close();

  //Open and read file
  TFile* pTSpectra = new TFile("/u/mhemmer/Documents/git/Beispielcode/pTSpectra.root", "READ");
  if ( pTSpectra->IsOpen() ) printf("pTSpectra opened successfully\n");
  //gFile = HistoFile;

  if(P_TSpectra->IsZombie()){
    std::cout << "ERROR: pTSpectra File not found" << std::endl;
    return;
  }

  // get Histos from file
  TH1F* hgen_500event_ratio= new TH1F();
  SetHistoStandardSettings(hgen_500event_ratio);
  gDirectory->GetObject("hgen_500event_ratio",hgen_500event_ratio);

  pTSpectra->Close();































}
