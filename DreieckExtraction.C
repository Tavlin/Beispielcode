#include "CommenHeader.h"


void DreieckExtraction(TString AddName = "") {

  TH2F* hNPi0_gen_minv_pt = new TH2F("hNPi0_gen_minv_pt","generated pi0: minv vs. pT",300,0.,3.,300,0.,3.);
  SetHistoStandardSettings2(hNPi0_gen_minv_pt);

  TFile* File = new TFile("pTSpectra.root", "READ");
  if (File->IsOpen() ) printf("pTSpectra.root opened successfully\n");

  if(File->IsZombie()){
    std::cout << "ERROR: Data File not found" << std::endl;
    return;
  }

  File->GetObject("hNPi0_gen_minv_pt",hNPi0_gen_minv_pt);

  TCanvas* c1 = new TCanvas("c1","",1200,1200);
  SetCanvasStandardSettings(c1);

  TH1D* minv_pt_projections[300];
  TLatex* tex = new TLatex();
  SetLatexSettings(tex);

  c1->cd();

  // for the graph:
  Double_t x[300], y[300];
  for (size_t i = 0; i < 300; i++) {

    minv_pt_projections[i] = hNPi0_gen_minv_pt->ProjectionX(Form("minv_pt_projections[%lu]",i),i,i+1);
    SetHistoStandardSettings(minv_pt_projections[i]);
    minv_pt_projections[i]->SetYTitle("#it{counts}");
    minv_pt_projections[i]->SetXTitle(minv_str);
    x[i] = minv_pt_projections[i]->FindLastBinAbove(0.,1);
    y[i] = (0.01*(2*i+1.))/2.; //BinCenter of Projected Y-Axis (p_T) Bin!

    c1->Clear();
    minv_pt_projections[i]->Draw();
    tex->DrawLatexNDC(0.2,0.8,Form("%1.3lf #leq #it{p}_{T} (GeV/#it{c}) < %1.3lf",i*0.01,(i+1)*0.01));
    c1->Update();
    c1->SaveAs(Form("DreieckExtraction/Projection%lu.png",i));

  }

  TLegend *leg_pt = new TLegend(0.5,0.75,0.9,0.95);
  leg_pt->SetFillStyle(0);
  leg_pt->SetBorderSize(0);
  leg_pt->SetTextFont(42);
  leg_pt->SetTextSize(4);
  TGraph* pt_minv_graph = new TGraph(300,x,y);
  pt_minv_graph->SetTitle(";#it{m}_{inv} (GeV/#it{c})^{2};#it{p}_{T} (GeV/#it{c})");
  pt_minv_graph->SetLineColor(kRed);
  pt_minv_graph->SetLineWidth(3);
  pt_minv_graph->SetMarkerSize(2);
  pt_minv_graph->SetMarkerStyle(33);
  pt_minv_graph->SetMarkerColor(kRed);
  TF1* f = new TF1("fit","[0]+[1]*x+[2]*x^2");
  f->SetLineColor(kBlue+2);
  f->SetLineWidth(2);
  pt_minv_graph->Fit("fit","M","",0,300);

  leg_pt->AddEntry(pt_minv_graph,"Maximum values of respected pT");
  leg_pt->AddEntry(f,"Fit of TGraph");

  c1->Clear();
  pt_minv_graph->Draw("ACP");
  f->Draw("SAMEL");
  c1->SaveAs("DreieckExtraction/FitPlot.png");
  c1->Clear();


  f->Delete();
  pt_minv_graph->Delete();
  tex->Delete();
  for (size_t i = 0; i < 300; i++) {
    minv_pt_projections[i]->Delete();
  }




}
