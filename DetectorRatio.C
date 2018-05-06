#include "CommenHeader.h"

void DetectorRatio(TString AddName = "") {

  TLatex* poweektex = new TLatex();
  Float_t pi = TMath::Pi();

  TLegend *leg_pt = new TLegend(0.55,0.8,0.9,0.9);
  leg_pt->SetFillStyle(0);
  leg_pt->SetBorderSize(0);
  leg_pt->SetTextFont(43);
  leg_pt->SetTextSize(25);

  TLegend *leg_pt_corr = new TLegend(0.55,0.8,0.9,0.9);
  leg_pt_corr->SetFillStyle(0);
  leg_pt_corr->SetBorderSize(0);
  leg_pt_corr->SetTextFont(43);
  leg_pt_corr->SetTextSize(25);

  TCanvas *c500eventSpectrumCorrected = new TCanvas("c500eventSpectrumCorrected","",1200,1200);
  SetCanvasStandardSettings(c500eventSpectrumCorrected);

  //Open and read  pt-Spektrum-500 Event file
  TFile* P_TSpectra = new TFile("/home/marvin/Dokumente/git/Beispielcode2/P_TSpectra.root", "READ"); //homi
  // TFile* P_TSpectra = new TFile("/u/mhemmer/Documents/git/Beispielcode2/P_TSpectra.root", "READ"); //uni
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
  TFile* pTSpectra = new TFile("/home/marvin/Dokumente/git/Beispielcode/pTSpectra.root", "READ"); //homi
  // TFile* pTSpectra = new TFile("/u/mhemmer/Documents/git/Beispielcode/pTSpectra.root", "READ"); //uni
  if ( pTSpectra->IsOpen() ) printf("pTSpectra opened successfully\n");

  if(P_TSpectra->IsZombie()){
    std::cout << "ERROR: pTSpectra File not found" << std::endl;
    return;
  }

  // get Histos from file
  TH1F* hgen_500event_ratio_1 = new TH1F();
  pTSpectra->GetObject("hgen_500event_ratio",hgen_500event_ratio_1);


  // Angelinas Histogramme einlesen und einbauen:
  TFile* P_TSpectra_angi = new TFile("/home/marvin/Dokumente/git/Beispielcode/ExtractSignal_korr_angi.root", "READ"); //homi
  // TFile* P_TSpectra_angi = new TFile("/u/mhemmer/Documents/git/Beispielcode/ExtractSignal_korr_angi.root", "READ"); //uni
  if ( P_TSpectra_angi->IsOpen() ) printf("P_TSpectra_angi opened successfully\n");


  if(P_TSpectra_angi->IsZombie()){
    std::cout << "ERROR: P_TSpectra_angi File not found" << std::endl;
    return;
  }

  // get Histo from file
  TH1D* hP_TSpectrum_angi = new TH1D();
  P_TSpectra_angi->GetObject("pT",hP_TSpectrum_angi);

  TH1D* hP_TSpectrum_angi_korr = new TH1D();
  P_TSpectra_angi->GetObject("pT_korr",hP_TSpectrum_angi_korr);

  // Skalieren auf Anzahl Eents (hier 500)!
  hP_TSpectrum_angi->Scale(1/500.);
  hP_TSpectrum_angi_korr->Scale(1/500.);
  hP_TSpectrum_angi->SetMarkerStyle(21);

  hP_TSpectrum_angi->SetLineColor(kGreen+2);
  hP_TSpectrum_angi_korr->SetLineColor(kViolet);
  hP_TSpectrum_angi->SetMarkerColor(kGreen+2);
  hP_TSpectrum_angi_korr->SetMarkerColor(kViolet);

  Int_t binlenght = GetNBinningFromHistogram(hP_TSpectrum_1);
  Double_t * binning = GetBinningFromHistogram(hP_TSpectrum_1);

  TH1F* hCorrectedPTSpectrum = new TH1F("hCorrectedPTSpectrum","",binlenght-1,binning);
  SetHistoStandardSettings(hCorrectedPTSpectrum);

  Double_t ratio_error, spectrum_error, ratio_bin, spe_bin;

  // making the correction for eta
  for (Int_t i = 1; i < binlenght; i++) {
    ratio_error = hgen_500event_ratio_1->GetBinError(i);
    ratio_bin = hgen_500event_ratio_1->GetBinContent(i);
    spectrum_error = hP_TSpectrum_1->GetBinError(i);
    spe_bin = hP_TSpectrum_1->GetBinContent(i);


    hCorrectedPTSpectrum->SetBinContent(i,(hP_TSpectrum_1->GetBinContent(i)/hgen_500event_ratio_1->GetBinContent(i)));
    hCorrectedPTSpectrum->SetBinError(i,sqrt((spectrum_error/ratio_bin)*(spectrum_error/ratio_bin)+(ratio_error*spe_bin/(ratio_bin*ratio_bin))*(ratio_error*spe_bin/(ratio_bin*ratio_bin))));
  }

  hCorrectedPTSpectrum->SetLineColor(kRed+2);
  hCorrectedPTSpectrum->SetMarkerColor(kRed+2);
  hP_TSpectrum_1->SetLineColor(kBlue+1);
  hP_TSpectrum_1->SetMarkerColor(kBlue+1);
  hCorrectedPTSpectrum->Scale(1/(2.*pi));
  hP_TSpectrum_1->Scale(1/(2.*pi));

  // normalizing to 1/pT for corrected spectrum
  for (Int_t i = 1; i < binlenght; i++) {
    Double_t DivPtError = hCorrectedPTSpectrum->GetBinWidth(i);
    Double_t DivPt = hCorrectedPTSpectrum->GetBinCenter(i);
    Double_t BinCon = hCorrectedPTSpectrum->GetBinContent(i);
    Double_t BinErr = hCorrectedPTSpectrum->GetBinError(i);
    Double_t lefterr = (BinErr/DivPt)*(BinErr/DivPt);
    Double_t righterr = ((BinCon*DivPtError)/(DivPt*DivPt))*((BinCon*DivPtError)/(DivPt*DivPt));

    Double_t TotalError = sqrt(lefterr+righterr);
    hCorrectedPTSpectrum->SetBinContent(i,BinCon/DivPt);
    hCorrectedPTSpectrum->SetBinError(i,TotalError);
  }

  // normalizing to 1/pT for uncorrected spectrum
  for (Int_t i = 1; i < binlenght; i++) {
    Double_t DivPtError = hP_TSpectrum_1->GetBinWidth(i);
    Double_t DivPt = hP_TSpectrum_1->GetBinCenter(i);
    Double_t BinCon = hP_TSpectrum_1->GetBinContent(i);
    Double_t BinErr = hP_TSpectrum_1->GetBinError(i);
    Double_t lefterr = (BinErr/DivPt)*(BinErr/DivPt);
    Double_t righterr = ((BinCon*DivPtError)/(DivPt*DivPt))*((BinCon*DivPtError)/(DivPt*DivPt));

    Double_t TotalError = sqrt(lefterr+righterr);
    hP_TSpectrum_1->SetBinContent(i,BinCon/DivPt);
    hP_TSpectrum_1->SetBinError(i,TotalError);
  }


  hCorrectedPTSpectrum->SetXTitle("#it{p}_{T} (GeV/#it{c})");
  hP_TSpectrum_angi_korr->SetXTitle("#it{p}_{T} (GeV/#it{c})");
  hP_TSpectrum_1->SetXTitle("#it{p}_{T} (GeV/#it{c})");
  hP_TSpectrum_angi->SetXTitle("#it{p}_{T} (GeV/#it{c})");
  hCorrectedPTSpectrum->SetYTitle("#frac{1}{2#pi N_{evt}} #frac{dN}{#it{p}_{T}d#it{p}_{T}} (GeV/#it{c})^{-2}");
  hP_TSpectrum_angi_korr->SetYTitle("#frac{1}{2#pi N_{evt}} #frac{dN}{#it{p}_{T}d#it{p}_{T}} (GeV/#it{c})^{-2}");
  hP_TSpectrum_1->SetYTitle("#frac{1}{2#pi N_{evt}} #frac{dN}{#it{p}_{T}d#it{p}_{T}} (GeV/#it{c})^{-2}");
  hP_TSpectrum_angi->SetYTitle("#frac{1}{2#pi N_{evt}} #frac{dN}{#it{p}_{T}d#it{p}_{T}} (GeV/#it{c})^{-2}");



  leg_pt->AddEntry(hP_TSpectrum_1, "uncorrected spectrum by Marvin");
  leg_pt_corr->AddEntry(hCorrectedPTSpectrum, "corrected spectrum by Marvin");
  leg_pt->AddEntry(hP_TSpectrum_angi, "uncorrected spectrum by Angelina");
  leg_pt_corr->AddEntry(hP_TSpectrum_angi_korr, "corrected spectrum by Angelina");

  c500eventSpectrumCorrected->cd();
  c500eventSpectrumCorrected->SetLogy();
  c500eventSpectrumCorrected->SetLogx();
  hCorrectedPTSpectrum->GetXaxis()->SetRangeUser(1.3,10.);
  hCorrectedPTSpectrum->Draw();
  hP_TSpectrum_angi_korr->Draw("same");
  leg_pt_corr->Draw("same");
  poweektex->SetTextSize(0.04);
  poweektex->DrawLatexNDC(0.25,0.4,poweek_str);
  poweektex->DrawLatexNDC(0.25,0.35,pi0togamma_str);

  c500eventSpectrumCorrected->SaveAs(Form("Corrected/CorrectedPTSpectrumComp.png"));
  hCorrectedPTSpectrum->SaveAs(Form("Corrected/CorrectedPTSpectrum.root"));
  c500eventSpectrumCorrected->Clear();

  c500eventSpectrumCorrected->SetLogx(0);
  hP_TSpectrum_1->Draw("");
  hP_TSpectrum_angi->Draw("same");
  leg_pt->Draw("same");
  poweektex->SetTextSize(0.04);
  poweektex->DrawLatexNDC(0.25,0.4,poweek_str);
  poweektex->DrawLatexNDC(0.25,0.35,pi0togamma_str);
  c500eventSpectrumCorrected->Update();
  c500eventSpectrumCorrected->SaveAs(Form("Corrected/UncorrectedPTSpectrumComp.png"));



  P_TSpectra->Close();
  pTSpectra->Close();































}
