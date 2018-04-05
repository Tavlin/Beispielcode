#include "TLatex.h"
#include "TLegend.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TStyle.h"
#include "TString.h"
#include "TMath.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TRandom.h"
#include <TSystem.h>
#include <iostream>

const Int_t kMaxHit = 2000;


Float_t fCalcInvMass(Float_t px1, Float_t py1, Float_t pz1, Float_t px2, Float_t py2, Float_t pz2, Float_t e_gamma_1, Float_t e_gamma_2){
  
  
  return sqrt(2.*e_gamma_1*e_gamma_2*(1.-(px1*px2+py1*py2+pz1*pz2)/(sqrt(px1*px1+py1*py1+pz1*pz1)*sqrt(px2*px2+py2*py2+pz2*pz2))));
}

Float_t fEnergySmear(Float_t energy){
  
  return gRandom->Gaus(energy,0.03/sqrt(energy));
}


Float_t fCalcPT(Float_t e_lab, Float_t m, Float_t y_lab){
    return sqrt((e_lab*e_lab)/cosh(y_lab)-m*m);
}

Bool_t fCheckAcc(Float_t phi1, Float_t phi2, Float_t eta1, Float_t eta2, Float_t phi_detec){
    if (fabs(phi1)<= phi_detec  && fabs(phi2)<=phi_detec){
      if (fabs(eta1) < 0.5 && fabs(eta2) < 0.5){
           
        return true;
      }
    }
    return false;
}   


void RotateToLabSystem(const float& theta, const float& phi,
		       const float& p1, const float& p2, const float& p3,
		       float& p1rot, float& p2rot, float& p3rot) {

  Float_t st = sin(theta);
  Float_t ct = cos(theta);
  Float_t sp = sin(phi);
  Float_t cp = cos(phi);

  p1rot = cp*ct*p1 - p2*sp + cp*p3*st;
  p2rot = cp*p2 + ct*p1*sp + p3*sp*st;
  p3rot = ct*p3 - p1*st;

}


class DataTree{
  private:
    Float_t pxdata[kMaxHit];
    Float_t pydata[kMaxHit];
    Float_t pzdata[kMaxHit];
    Int_t iNCluster;
    Int_t NEvents;
    TTree* tClusters;

  public:
    DataTree(TFile* fDaten){
      tClusters = (TTree*) fDaten->Get("ntu");
      NEvents = tClusters->GetEntries();
      tClusters->SetBranchAddress("nhit", &iNCluster);
      tClusters->SetBranchAddress("px", pxdata);
      tClusters->SetBranchAddress("py", pydata);
      tClusters->SetBranchAddress("pz", pzdata);
    }

    void GetEvent(Int_t iEvt){
      tClusters->GetEntry(iEvt);
    }

    Float_t GetPX(Int_t iEvt, Int_t iHit){
      GetEvent(iEvt);
      return pxdata[iHit];
    }

    Float_t GetPY(Int_t iEvt, Int_t iHit){
      GetEvent(iEvt);
      return pydata[iHit];
    }

    Float_t GetPZ(Int_t iEvt, Int_t iHit){
      GetEvent(iEvt);
      return pzdata[iHit];
    }
    Float_t GetNCluster(Int_t iEvt){
      GetEvent(iEvt);
      return iNCluster;
    }

    Int_t GetNEvents(){
      return NEvents;
    }
};




void SetCanvasStandardSettings(TCanvas *cCanv){
  gStyle->SetOptStat(0); // <- das hier macht dies box rechts oben weg
  cCanv->SetTopMargin(0.025);
  cCanv->SetBottomMargin(0.15);
  cCanv->SetRightMargin(0.15);
  cCanv->SetLeftMargin(0.15);
  cCanv->SetTickx();
  cCanv->SetTicky();
  cCanv->SetLogy(0); //counts besser log, da sonst nicht anschaulich
  cCanv->SetLogx(0);
}


void SetHistoStandardSettings(TH1* histo, Double_t XOffset = 1.2, Double_t YOffset = 1.){
  histo->GetXaxis()->SetTitleOffset(XOffset);
  histo->GetYaxis()->SetTitleOffset(YOffset);
  histo->GetXaxis()->SetTitleSize(30);
  histo->GetYaxis()->SetTitleSize(30);
  histo->GetXaxis()->SetLabelSize(30);
  histo->GetYaxis()->SetLabelSize(30);
  histo->GetXaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetTitleFont(43);
  histo->GetXaxis()->SetTitleFont(43);

  


  histo->SetMarkerStyle(20);
  histo->SetMarkerSize(1.5);
  histo->SetLineWidth(1.5);
  histo->SetLineColor(kBlack);
  histo->SetMarkerColor(kBlack);
}

void SetHistoStandardSettings2(TH2* histo, Double_t XOffset = 1.2, Double_t YOffset = 1.){
  histo->GetXaxis()->SetTitleOffset(XOffset);
  histo->GetYaxis()->SetTitleOffset(YOffset);
  histo->GetXaxis()->SetTitleSize(30);
  histo->GetYaxis()->SetTitleSize(30);
  histo->GetZaxis()->SetTitleSize(30);
  histo->GetXaxis()->SetLabelSize(30);
  histo->GetYaxis()->SetLabelSize(30);
  histo->GetZaxis()->SetLabelSize(20);
  histo->GetXaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetLabelFont(43);
  histo->GetZaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetTitleFont(43);
  histo->GetXaxis()->SetTitleFont(43);
  histo->GetZaxis()->SetTitleFont(43);
}


void SetLegendSettigns(TLegend* leg){
  leg->SetTextSize(50);
  leg->SetTextFont(43);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->SetLineColor(0);
  leg->SetMargin(0.15);
}



// gStyle->SetCanvasColor(0);
// gStyle->SetPadColor(0);
// gStyle->SetCanvasBorderMode(0);
// gStyle->SetPadBorderMode(0);
//
// gStyle->SetTitleXOffset(1.4);
// gStyle->SetTitleYOffset(1.8);
//
// gStyle->SetPadLeftMargin(0.17);
// gStyle->SetPadRightMargin(0.1);      // 0.1 = root default
// gStyle->SetPadTopMargin(0.1);
// gStyle->SetPadBottomMargin(0.14);






void printProgress (Double_t progress)
{
  int barWidth = 50;
  std::cout.flush();
  std::cout << "["<< int(progress * 100.0) << "%]" << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
      if (i < pos) std::cout << "|";
      else std::cout << " ";
  }
  std::cout << "]\r";
}










//// Advanced

void DrawLabelALICE(Double_t startTextX         = 0.13, Double_t startTextY         = 0.9, Double_t textHeight         = 0.02, Double_t textSize         = 40){
  TString textAlice       = "ALICE work in progress";
  TString textEvents      = "Data";

  Double_t differenceText     = textHeight*1.5;
  TLatex *alice               = new TLatex(startTextX, startTextY, Form("%s",textAlice.Data()));
  TLatex *energy             = new TLatex(startTextX, (startTextY-1.*differenceText), "pp, #sqrt{s} = 5.02 TeV, 113M events");

  TLatex *detprocess          = new TLatex(startTextX, (startTextY-2.*differenceText), "#pi^{0}#rightarrow#gamma#gamma, #gamma's rec. with DCal ");

  // TLatex *pt          = new TLatex(startTextX, (startTextY-1*differenceText), Form("%3.1f GeV/#it{c} #leq %s < %3.1f GeV/#it{c}",startPt,ptLabel.Data(),endPt));

  alice->SetNDC();
  alice->SetTextColor(1);
  alice->SetTextFont(43);
  alice->SetTextSize(textSize*1.3);
  alice->Draw();

  energy->SetNDC();
  energy->SetTextColor(1);
  energy->SetTextSize(textSize);
  energy->SetTextFont(43);
  energy->Draw();


  detprocess->SetNDC();
  detprocess->SetTextColor(1);
  detprocess->SetTextSize(textSize);
  detprocess->SetTextFont(43);
  detprocess->Draw();

  // pt->SetNDC();
  // pt->SetTextColor(1);
  // pt->SetTextSize(textSize);
  // pt->SetTextFont(43);
  // pt->Draw();
}
