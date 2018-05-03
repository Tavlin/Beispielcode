#include "CommenHeader.h"

void DetectorRatio(TString AddName = "") {

  TCanvas *c500eventSpectrumCorrected = new TCanvas("c500eventSpectrumCorrected","",1200,1200);
  SetCanvasStandardSettings(c500eventSpectrumCorrected);

  //Open and read  pt-Spektrum-500 Event file
  TFile* P_TSpectra = new TFile("/u/mhemmer/Documents/git/Beispielcode2/P_TSpectra.root", "READ");
  if ( P_TSpectra->IsOpen() ) printf("P_TSpectra opened successfully\n");


  if(P_TSpectra->IsZombie()){
    std::cout << "ERROR: P_TSpectra File not found" << std::endl;
    return;
  }

  // get Histo from file
  TH1D* hP_TSpectrum_1 = new TH1D();
  // TH1D* hP_TSpectrum_1 = (TH1D*) P_TSpectra->Get("hP_TSpectrum");
  P_TSpectra->GetObject("hP_TSpectrum",hP_TSpectrum_1);
  // SetHistoStandardSettings(hP_TSpectrum_1);


  //Open and read Ratio File file
  TFile* pTSpectra = new TFile("/u/mhemmer/Documents/git/Beispielcode/pTSpectra.root", "READ");
  if ( pTSpectra->IsOpen() ) printf("pTSpectra opened successfully\n");

  if(P_TSpectra->IsZombie()){
    std::cout << "ERROR: pTSpectra File not found" << std::endl;
    return;
  }

  // get Histos from file
  TH1F* hgen_500event_ratio_1 = new TH1F();
  pTSpectra->GetObject("hgen_500event_ratio",hgen_500event_ratio_1);

  Int_t binlenght = GetNBinningFromHistogram(hP_TSpectrum_1);
  Double_t * binning = GetBinningFromHistogram(hP_TSpectrum_1);

  TH1F* hCorrectedPTSpectrum = new TH1F("hCorrectedPTSpectrum","",binlenght-1,binning);
  SetHistoStandardSettings(hCorrectedPTSpectrum);

  // std::cout << "binlenght = " << binlenght << std::endl;
  Double_t ratio_error, spectrum_error, ratio_bin, spe_bin;
  for (Int_t i = 1; i < binlenght; i++) {
    ratio_error = hgen_500event_ratio_1->GetBinError(i);
    ratio_bin = hgen_500event_ratio_1->GetBinContent(i);
    spectrum_error = hP_TSpectrum_1->GetBinError(i);
    spe_bin = hP_TSpectrum_1->GetBinContent(i);

    // std::cout << hP_TSpectrum_1->GetBinContent(i) << " / " << hgen_500event_ratio_1->GetBinContent(i) << " = ";

    hCorrectedPTSpectrum->SetBinContent(i,(hP_TSpectrum_1->GetBinContent(i)/hgen_500event_ratio_1->GetBinContent(i)));
    hCorrectedPTSpectrum->SetBinError(i,sqrt((spectrum_error/ratio_bin)*(spectrum_error/ratio_bin)+(ratio_error*spe_bin/(ratio_bin*ratio_bin))*(ratio_error*spe_bin/(ratio_bin*ratio_bin))));
    // std::cout  << hgen_500event_ratio_1->GetBinContent(i) << std::endl;
  }

  hCorrectedPTSpectrum->SetLineColor(kBlue+2);
  hCorrectedPTSpectrum->SetMarkerColor(kBlue+2);
  hP_TSpectrum_1->SetLineColor(kGreen+3);
  hP_TSpectrum_1->SetMarkerColor(kGreen+3);

  c500eventSpectrumCorrected->cd();
  c500eventSpectrumCorrected->SetLogy();
  c500eventSpectrumCorrected->SetLogx();
  hCorrectedPTSpectrum->GetXaxis()->SetRangeUser(1.3,10.);
  hCorrectedPTSpectrum->Draw();
  hP_TSpectrum_1->Draw("same");

  // c500eventSpectrumCorrected->Update();

  c500eventSpectrumCorrected->SaveAs(Form("Corrected/CorrectedPTSpectrum.png"));
  hCorrectedPTSpectrum->SaveAs(Form("Corrected/CorrectedPTSpectrum.root"));
  c500eventSpectrumCorrected->Clear();

  P_TSpectra->Close();
  pTSpectra->Close();































}
