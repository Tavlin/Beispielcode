#include "CommenHeader.h"


Float_t xbins_pt[nbins_pt+1];

void Pi0Simulation(TString AddName = "") {
  for (size_t j = 0; j < 62; j++) {
    xbins_pt[j] = j*0.1;
  }
  xbins_pt[62] = 6.2;
  xbins_pt[63] = 6.5;
  xbins_pt[64] = 7;
  xbins_pt[65] = 7.9;
  xbins_pt[66] = 10;

  // Wir definieren ein Canvas auf das wir malen können
  TCanvas *cNPi0_pt = new TCanvas("cNPi0_pt","",1200,1200);
  // Wir stellen ein paar grundlegende Settings ein
  SetCanvasStandardSettings(cNPi0_pt);// (diese Funktion ist in ExtractSignal.h definiert)

  TCanvas *cNPi0_minv = new TCanvas("cNPi0_minv","",1200,1200);
  SetCanvasStandardSettings(cNPi0_minv);

  TCanvas *cNPi0_theta_pt = new TCanvas("cNPi0_theta_pt","",800,800);
  SetCanvasStandardSettings(cNPi0_theta_pt);

  TCanvas *cNPi0_costheta_pt = new TCanvas("cNPi0_costheta_pt","",800,800);
  SetCanvasStandardSettings(cNPi0_costheta_pt);

  TCanvas *cE1E2 = new TCanvas("cE1E2","",800,800);
  SetCanvasStandardSettings(cE1E2);

  TCanvas *cNPi0_gen_minv_pt = new TCanvas("cNPi0_gen_minv_pt","",800,800);
  SetCanvasStandardSettings(cNPi0_gen_minv_pt);

  TCanvas *cNPi0_acc_minv_pt_60 = new TCanvas("cNPi0_acc_minv_pt_60","",800,800);
  SetCanvasStandardSettings(cNPi0_acc_minv_pt_60);

  TCanvas *cNPi0_acc_minv_pt_90 = new TCanvas("cNPi0_acc_minv_pt_90","",800,800);
  SetCanvasStandardSettings(cNPi0_acc_minv_pt_90);

  TCanvas *cNPi0_acc_minv_comp = new TCanvas("cNPi0_acc_minv_comp","",800,800);


  Float_t m = 0.135; // pi0 mass

  // generate a certain number of pi0
  const Int_t Npi0 = 100000;

  // pT distribution
  TF1* fpt = new TF1("fpt","x*exp(-x/0.2)",0.,10.);

  // rapidity distribution
  TF1* fy = new TF1("fy", "gaus", -0.5, 0.5);
  fy->SetParameters(1., 0., 4.);

  // histograms for generated and accepted pi0's
  TH1F* hNPi0_gen_pt = new TH1F("hNPi0_gen_pt","generated pi0 pT spectrum",nbins_pt,xbins_pt); //edit mehr und nur bis 5 statt 20,0.,10.
  SetHistoStandardSettings(hNPi0_gen_pt);

  TH1F* hNPi0_gen_minv = new TH1F("hNPi0_gen_minv","generated pi0 minv spectrum",100,0.,0.5);
  SetHistoStandardSettings(hNPi0_gen_minv);

  TH1F* hNPi0_acc_minv_60 = new TH1F("hNPi0_acc_minv_60","accepted pi0 minv spectrum",100,0.,0.5);
  SetHistoStandardSettings(hNPi0_acc_minv_60);

  TH1F* hNPi0_acc_minv_90 = new TH1F("hNPi0_acc_minv_90","accepted pi0 minv spectrum",100,0.,0.5);
  SetHistoStandardSettings(hNPi0_acc_minv_90);


  TH2F* hNPi0_gen_minv_pt = new TH2F("hNPi0_gen_minv_pt","generated pi0: minv vs. pT",100,0.,1.,100,0.,7.);
  SetHistoStandardSettings2(hNPi0_gen_minv_pt);

  TH2F* hNPi0_acc_minv_pt_60 = new TH2F("hNPi0_acc_minv_pt_60","accepted pi0: minv vs. pT",100,0.,1.,100,0.,5.);
  SetHistoStandardSettings2(hNPi0_acc_minv_pt_60);

  TH2F* hNPi0_acc_minv_pt_90 = new TH2F("hNPi0_acc_minv_pt_90","accepted pi0: minv vs. pT",100,0.,1.,100,0.,5.);
  SetHistoStandardSettings2(hNPi0_acc_minv_pt_90);

  // pi0 accepted by VCal (eta coverage |eta| < 0.5 and phi 60º)
  TH1F* hNPi0_acc_60 = new TH1F("hNPi0_acc_60","accepted pi0 pT spectrum with 60º",nbins_pt,xbins_pt);
  SetHistoStandardSettings(hNPi0_acc_60);

  // pi0 accepted by VCal (eta coverage |eta| < 0.5 and phi 90º)
  TH1F* hNPi0_acc_90 = new TH1F("hNPi0_acc_90","accepted pi0 pT spectrum with 90º",nbins_pt,xbins_pt);
  SetHistoStandardSettings(hNPi0_acc_90);

  TH1F* hNPi0_acc_minv_high_pt = new TH1F("hNPi0_acc_minv_high_pt","accepted pi0 minv spectrum",100,0.,0.5);
  SetHistoStandardSettings(hNPi0_acc_minv_high_pt);

  TH1F* hNPi0_acc_minv_mid_pt = new TH1F("hNPi0_acc_minv_mid_pt","accepted pi0 minv spectrum",100,0.,0.5);
  SetHistoStandardSettings(hNPi0_acc_minv_mid_pt);

  TH1F* hNPi0_acc_minv_low_pt = new TH1F("hNPi0_acc_minv_low_pt","accepted pi0 minv spectrum",100,0.,0.5);
  SetHistoStandardSettings(hNPi0_acc_minv_low_pt);

  TH2F* hNPi0_gen_theta_pt = new TH2F("hNPi0_gen_theta_pt","",180,0.,180.,100,0.,7.);
  SetHistoStandardSettings2(hNPi0_gen_theta_pt);

  TH2F* hNPi0_gen_costheta_pt = new TH2F("hNPi0_gen_costheta_pt","",100,-1.,1.,100,0.,7.);
  SetHistoStandardSettings2(hNPi0_gen_costheta_pt);

  TH2F* hE1E2_minv = new TH2F("hE1E2_minv","",100,0.,1.,100,0.,10.);
  SetHistoStandardSettings2(hE1E2_minv);

  TH2F* hE1E2_theta = new TH2F("hE1E2_theta","",180,0.,180.,100,0.,10.);
  SetHistoStandardSettings2(hE1E2_theta);

  TH2F* hE1E2_cosTheta = new TH2F("hE1E2_cosTheta","",100,-1.,1.,100,0.,10.);
  SetHistoStandardSettings2(hE1E2_cosTheta);


  for (int ip=0; ip < Npi0; ip++) {
    printProgress( ((Double_t)ip) / ((Double_t)Npi0) );

    Float_t pi = TMath::Pi(); /* besser vor dem loop? */

    // set pT, rapidity, ...
    Float_t pt_lab = gRandom->Uniform(7.);
    Float_t phi_lab = gRandom->Uniform(2.*pi);
    Float_t y_lab = fy->GetRandom();


    Float_t mt_lab = sqrt(m*m + pt_lab*pt_lab);
    Float_t e_lab = mt_lab * cosh(y_lab);
    Float_t px_lab = pt_lab * cos(phi_lab);
    Float_t py_lab = pt_lab * sin(phi_lab);
    Float_t pz_lab = mt_lab * sinh(y_lab);
    Float_t p_lab  = sqrt(e_lab*e_lab - m*m);
    Float_t theta_lab = atan2(pt_lab,pz_lab);

    // draw cosine of the decay angle in the CMS from uniform distribution
    Float_t cos_theta_star = gRandom->Uniform(0.,1.);
    Float_t phi_star = gRandom->Uniform(2.*pi);
    Float_t sin_theta_star = sqrt(1. - cos_theta_star*cos_theta_star);

    // rest frame of the pi0
    Float_t p1x_star = m/2. * sin_theta_star * cos(phi_star);
    Float_t p1y_star = m/2. * sin_theta_star * sin(phi_star);
    Float_t p1z_star = m/2. * cos_theta_star;

    Float_t p2x_star = - p1x_star;
    Float_t p2y_star = - p1y_star;
    Float_t p2z_star = - p1z_star;

    Float_t beta = 1./sqrt(1.+(m*m)/(p_lab*p_lab));
    Float_t gamma = 1./sqrt(1.-beta*beta);

    // Lorentz transform of the momentum vectors of the two decay photons
    Float_t p1x = p1x_star;
    Float_t p1y = p1y_star;
    Float_t p1z = gamma*(p1z_star + beta * m/2.);

    Float_t p2x = p2x_star;
    Float_t p2y = p2y_star;
    Float_t p2z = gamma*(p2z_star + beta * m/2.);

    // 3D rotation to lab system
    Float_t p1xrot, p1yrot, p1zrot;
    Float_t p2xrot, p2yrot, p2zrot;

    RotateToLabSystem(theta_lab,phi_lab,p1x,p1y,p1z,p1xrot,p1yrot,p1zrot);
    RotateToLabSystem(theta_lab,phi_lab,p2x,p2y,p2z,p2xrot,p2yrot,p2zrot);

    p1x = p1xrot;
    p1y = p1yrot;
    p1z = p1zrot;

    p2x = p2xrot;
    p2y = p2yrot;
    p2z = p2zrot;

    // calculate phi and eta for the two decay photons
    Float_t pt1 = sqrt(p1x*p1x + p1y*p1y);
    Float_t theta1 = atan2(pt1,p1z);
    Float_t eta1 = -log(tan(theta1/2.));

    Float_t pt2 = sqrt(p2x*p2x + p2y*p2y);
    Float_t theta2 = atan2(pt2,p2z);
    Float_t eta2 = -log(tan(theta2/2.));



///////////////////////////////////////////////

    // Implementiere eine Energieverschmierung
    Float_t e_gamma_1 = sqrt(p1x*p1x+p1y*p1y+p1z*p1z);
    Float_t e_gamma_2 = sqrt(p2x*p2x+p2y*p2y+p2z*p2z);
    e_gamma_1 = fEnergySmear(e_gamma_1);
    e_gamma_2 = fEnergySmear(e_gamma_2);

    // und berechne den Transversalimpuls neu
    //pt_lab = fCalcPT(p1x,p1y,p2x,p2y);
    pt_lab = fCalcPT(e_gamma_1+e_gamma_2, m, y_lab);

///////////////////////////////////////////////

    // Berechne die invariante Masse
    // fCalcInvMass im header
    Float_t minv;
    minv = fCalcInvMass(p1x,p1y,p1z,p2x,p2y,p2z,e_gamma_1,e_gamma_2);

///////////////////////////////////////////////

  // Berechnen der Wikel phi1 und phi2
  Float_t phi1, phi2;
  phi1 = atan2(p1y,p1x)+pi; //atan2 liefert Ergebnis zwischen [-pi,pi]!
  phi2 = atan2(p2y,p2x)+pi;


///////////////////////////////////////////////



    hNPi0_gen_pt->Fill(pt_lab, fpt->Eval(pt_lab));
    // Implementiere eine endliche Detektorakzeptanz in phi

    //pt
    //60º Detector

    if(fCheckAcc(phi1, phi2, eta1, eta2, pi/3.)){
      hNPi0_acc_60->Fill(pt_lab, fpt->Eval(pt_lab));
    }

    //90º Detector

    if(fCheckAcc(phi1, phi2, eta1, eta2, pi/2.)){
      hNPi0_acc_90->Fill(pt_lab, fpt->Eval(pt_lab));
    }

    hNPi0_gen_minv->Fill(minv);

    ///////////////////////////////////////////////
    //invariante Masse:
    //60º Detector
    if(fCheckAcc(phi1, phi2, eta1, eta2, pi/3.)){
      hNPi0_acc_minv_60->Fill(minv);
    }

    //90º Detector
    if(fCheckAcc(phi1, phi2, eta1, eta2, pi/2.)){
      hNPi0_acc_minv_90->Fill(minv);
    }

    /////////////////////////////////////////////
    //minv vs pt
    //60º Detector

    if(fCheckAcc(phi1, phi2, eta1, eta2, pi/3.)){
      hNPi0_acc_minv_pt_60->Fill(minv,pt_lab,fpt->Eval(pt_lab));
    }

    //90º Detector
    if(fCheckAcc(phi1, phi2, eta1, eta2, pi/2.)){
      hNPi0_acc_minv_pt_90->Fill(minv,pt_lab,fpt->Eval(pt_lab));
    }

    //without acc
    hNPi0_gen_minv_pt->Fill(minv,pt_lab,fpt->Eval(pt_lab));


    //comparison between high, mid and low pt m_inv
    if(pt_lab > 3.32 && pt_lab <= 5.){
      hNPi0_acc_minv_high_pt->Fill(minv);
    }

    if(pt_lab > 1.66 && pt_lab <= 3.32){
      hNPi0_acc_minv_mid_pt->Fill(minv);
    }

    if(pt_lab <= 1.66 && pt_lab > 0.){
      hNPi0_acc_minv_low_pt->Fill(minv);
    }

    // Winkelverteilung
    Float_t theta_calct = acos(1-(minv*minv)/(2*e_gamma_1*e_gamma_2))*180/pi;
    // Float_t pt_test = fabs(e_gamma_1-e_gamma_2)/cosh(y_lab);

    hNPi0_gen_theta_pt->Fill(theta_calct,pt_lab,fpt->Eval(pt_lab));

    // cos WInkelverteilung
    Float_t cos_theta_calct = (1-(minv*minv)/(2*e_gamma_1*e_gamma_2));
    hNPi0_gen_costheta_pt->Fill(cos_theta_calct,pt_lab,fpt->Eval(pt_lab));

    Float_t E_multpl = e_gamma_1*e_gamma_2;
    hE1E2_minv->Fill(minv,E_multpl);
    hE1E2_theta->Fill(theta_calct,E_multpl);
    hE1E2_cosTheta->Fill(cos_theta_calct,E_multpl);
    hE1E2_minv->SetYTitle("E_{#gamma_{1}}#dotE_{#gamma_{2}}");
    hE1E2_theta->SetYTitle("E_{#gamma_{1}}#dotE_{#gamma_{2}}");
    hE1E2_cosTheta->SetYTitle("E_{#gamma_{1}}#dotE_{#gamma_{2}}");

    hE1E2_minv->SetXTitle("#it{m}_{inv} (Gev/c^{2})");
    hE1E2_theta->SetXTitle("#theta (#circ)");
    hE1E2_cosTheta->SetXTitle("cos(#theta)");



///////////////////////////////////////////////

  }


  //Correct Bin with for normalization still missing!!!!!!


  cNPi0_theta_pt->cd();

  cNPi0_theta_pt->SetRightMargin(0.175);
  cNPi0_theta_pt->SetBottomMargin(0.125);
  gPad->SetLogz();
  hNPi0_gen_theta_pt->Scale(150./(Npi0));
  hNPi0_gen_theta_pt->GetZaxis()->SetRangeUser(1.e-12,1.);

  hNPi0_gen_theta_pt->SetTitle("");
  hNPi0_gen_theta_pt->SetXTitle("beam width (#circ)");
  hNPi0_gen_theta_pt->GetXaxis()->SetTitleOffset(1.4);
  hNPi0_gen_theta_pt->SetYTitle("#it{p}_{T} (GeV/#it{c})");
  hNPi0_gen_theta_pt->GetYaxis()->SetTitleOffset(1.4);
  hNPi0_gen_theta_pt->SetZTitle("#it{relative probability}");
  hNPi0_gen_theta_pt->GetZaxis()->SetTitleOffset(1.4);
  hNPi0_gen_theta_pt->Draw("colz");


  cNPi0_costheta_pt->cd();

  cNPi0_costheta_pt->SetRightMargin(0.175);
  cNPi0_costheta_pt->SetBottomMargin(0.125);
  gPad->SetLogz();
  hNPi0_gen_costheta_pt->Scale(150./(Npi0));
  hNPi0_gen_costheta_pt->GetZaxis()->SetRangeUser(1.e-12,1.);

  hNPi0_gen_costheta_pt->SetTitle("");
  hNPi0_gen_costheta_pt->SetXTitle("cos(#theta)");
  hNPi0_gen_costheta_pt->GetXaxis()->SetTitleOffset(1.4);
  hNPi0_gen_costheta_pt->SetYTitle("#it{p}_{T} (GeV/#it{c})");
  hNPi0_gen_costheta_pt->GetYaxis()->SetTitleOffset(1.4);
  hNPi0_gen_costheta_pt->SetZTitle("#it{relative probability}");
  hNPi0_gen_costheta_pt->GetZaxis()->SetTitleOffset(1.4);
  hNPi0_gen_costheta_pt->Draw("colz");


  //pt Drawing
  cNPi0_pt->cd();

  gPad->SetTopMargin(0.02);
  cNPi0_pt->SetRightMargin(0.025);


  hNPi0_gen_pt->SetLineColor(kRed);
  hNPi0_gen_pt->SetMarkerColor(kRed);
  hNPi0_gen_pt->SetMarkerStyle(20);
  hNPi0_gen_pt->SetMarkerSize(1);
  fpt->SetLineColor(kBlack);

  hNPi0_acc_60->SetLineColor(kBlue);
  hNPi0_acc_60->SetMarkerColor(kBlue);
  hNPi0_acc_60->SetMarkerStyle(21);
  hNPi0_acc_60->SetMarkerSize(1);

  hNPi0_acc_90->SetLineColor(kGreen+2);
  hNPi0_acc_90->SetMarkerColor(kGreen+2);
  hNPi0_acc_90->SetMarkerStyle(33);
  hNPi0_acc_90->SetMarkerSize(1.5); //1.5

  hNPi0_gen_pt->SetTitle("");


  //achte auf Reihenfolge weil es die Farbe einfach DRUEBER malt!
  hNPi0_gen_pt->Scale(150./(Npi0));
  hNPi0_acc_90->Scale(150./(Npi0));
  hNPi0_acc_60->Scale(150./(Npi0));
  hNPi0_gen_pt->Draw("pe");
  hNPi0_acc_90->Draw("pe,same");
  hNPi0_acc_60->Draw("pe,same");
  fpt->Draw("same");
  cout << "Fehler vom 5 Bin bei 90 Grad Detektor " << hNPi0_acc_90->GetBinError(5)/hNPi0_acc_90->GetBinContent(5) << endl;
  cout << "Fehler vom 90 Bin bei 90 Grad Detektor  " << hNPi0_acc_90->GetBinError(90)/hNPi0_acc_90->GetBinContent(90) << endl;
  cout << "Content vom 90 Bin bei 90 Grad Detektor  " << hNPi0_acc_90->GetBinContent(90) << endl;

  cNPi0_pt->SetLogy();

  TLatex* lNPi0_gen_pt = new TLatex();
  lNPi0_gen_pt->SetTextSize(0.04);
  lNPi0_gen_pt->DrawLatex(0.2,0.00000001,"#splitline{#pi^{0} Toy-Monte-Carlo-}{Simulation}");

  hNPi0_gen_pt->SetXTitle("#it{p}_{T} (GeV/#it{c})");
  hNPi0_gen_pt->GetXaxis()->SetTitleOffset(1.4);
  hNPi0_gen_pt->SetYTitle("#it{relative probability}");
  hNPi0_gen_pt->GetYaxis()->SetTitleOffset(1.4);

  TLegend *leg_pt = new TLegend(0.5,0.75,0.9,0.95);
  leg_pt->SetFillStyle(0);
  leg_pt->SetBorderSize(0);
  leg_pt->SetTextFont(43);
  leg_pt->SetTextSize(25);
  leg_pt->AddEntry(hNPi0_gen_pt, "reconstructed #it{p}_{T} spectrum", "p");
  leg_pt->AddEntry(hNPi0_acc_90, "90#circ detector #it{p}_{T} spectrum", "p");
  leg_pt->AddEntry(hNPi0_acc_60, "60#circ detector #it{p}_{T} spectrum", "p");
  leg_pt->AddEntry(fpt, "param: x*exp(-x/0.2)", "l");
  leg_pt->Draw("same");


  //invariante Masse Drawing:
  TGaxis::SetMaxDigits(3);
  cNPi0_minv->cd();
  cNPi0_minv->SetRightMargin(0.025);
  cNPi0_minv->SetTopMargin(0.05);

  hNPi0_acc_minv_90->SetLineColor(kGreen+2);
  hNPi0_acc_minv_90->SetMarkerColor(kGreen+2);
  hNPi0_acc_minv_90->SetMarkerStyle(20);
  hNPi0_acc_minv_90->SetMarkerSize(1);
  hNPi0_acc_minv_90->SetXTitle("#it{m}_{inv} (GeV/#it{c}^{2})");
  hNPi0_acc_minv_90->GetXaxis()->SetTitleOffset(1.4);
  hNPi0_acc_minv_90->SetYTitle("#it{counts}");
  hNPi0_acc_minv_90->GetYaxis()->SetTitleOffset(1.4);

  hNPi0_acc_minv_60->SetLineColor(kBlue);
  hNPi0_acc_minv_60->SetMarkerColor(kBlue);
  hNPi0_acc_minv_60->SetMarkerStyle(21);
  hNPi0_acc_minv_60->SetMarkerSize(1);
  hNPi0_acc_minv_60->SetLineColor(kBlue);
  hNPi0_acc_minv_90->SetLineColor(kGreen+2);
  hNPi0_acc_minv_90->SetTitle("");
  hNPi0_acc_minv_60->SetLineWidth(3);
  hNPi0_acc_minv_90->SetLineWidth(3);


  hNPi0_acc_minv_60->SetLineWidth(4);
  hNPi0_acc_minv_90->SetLineWidth(4);

  TLegend *leg_minv = new TLegend(0.5,0.75,0.9,0.95);
  leg_minv->SetFillStyle(0);
  leg_minv->SetBorderSize(0);
  leg_minv->SetTextFont(43);
  leg_minv->SetTextSize(25);
  leg_minv->AddEntry(hNPi0_acc_minv_90, "90#circ detector #it{m}_{inv} spectrum", "p");
  leg_minv->AddEntry(hNPi0_acc_minv_60, "60#circ detector #it{m}_{inv} spectrum", "p");

  hNPi0_acc_minv_90->Draw("pe");
  hNPi0_acc_minv_60->Draw("pe,same");
  leg_minv->Draw("same");


  //pt gegen minv
  //generiertes ohne akzeptanz
  cNPi0_gen_minv_pt->cd();
  cNPi0_gen_minv_pt->SetRightMargin(0.175);
  cNPi0_gen_minv_pt->SetBottomMargin(0.125);
  gPad->SetLogz();
  hNPi0_gen_minv_pt->Scale(150./(Npi0));
  hNPi0_gen_minv_pt->GetZaxis()->SetRangeUser(1.e-12,1.);

  hNPi0_gen_minv_pt->SetTitle("");
  hNPi0_gen_minv_pt->SetXTitle("#it{m}_{inv} (GeV/#it{c}^{2})");
  hNPi0_gen_minv_pt->GetXaxis()->SetTitleOffset(1.4);
  hNPi0_gen_minv_pt->SetYTitle("#it{p}_{T} (GeV/#it{c})");
  hNPi0_gen_minv_pt->GetYaxis()->SetTitleOffset(1.4);
  hNPi0_gen_minv_pt->SetZTitle("#it{relative probability}");
  hNPi0_gen_minv_pt->GetZaxis()->SetTitleOffset(1.4);
  hNPi0_gen_minv_pt->Draw("colz");

  //mit Akzeptanz von 90 Grad
  cNPi0_acc_minv_pt_90->cd();
  cNPi0_acc_minv_pt_90->SetRightMargin(0.175);
  cNPi0_acc_minv_pt_90->SetBottomMargin(0.125);
  gPad->SetLogz();
  hNPi0_acc_minv_pt_90->Scale(150./(Npi0));
  hNPi0_acc_minv_pt_90->GetZaxis()->SetRangeUser(1.e-12,1.);

  hNPi0_acc_minv_pt_90->SetTitle("");


  hNPi0_acc_minv_pt_90->SetXTitle("#it{m}_{inv} (GeV/#it{c}^{2})");
  hNPi0_acc_minv_pt_90->GetXaxis()->SetTitleOffset(1.4);
  hNPi0_acc_minv_pt_90->SetYTitle("#it{p}_{T} (GeV/#it{c})");
  hNPi0_acc_minv_pt_90->GetYaxis()->SetTitleOffset(1.4);
  hNPi0_acc_minv_pt_90->SetZTitle("#it{relative probability}");
  hNPi0_acc_minv_pt_90->GetZaxis()->SetTitleOffset(1.4);
  hNPi0_acc_minv_pt_90->Draw("colz");

  //mit Akzeptanz von 60 Grad
  cNPi0_acc_minv_pt_60->cd();
  cNPi0_acc_minv_pt_60->SetRightMargin(0.175);
  cNPi0_acc_minv_pt_60->SetBottomMargin(0.125);
  gPad->SetLogz();
  hNPi0_acc_minv_pt_60->Scale(150./(Npi0));
  hNPi0_acc_minv_pt_60->GetZaxis()->SetRangeUser(1.e-12,1.);

  hNPi0_acc_minv_pt_60->SetTitle("");

  hNPi0_acc_minv_pt_60->SetXTitle("#it{m}_{inv} (GeV/#it{c}^{2})");
  hNPi0_acc_minv_pt_60->GetXaxis()->SetTitleOffset(1.4);
  hNPi0_acc_minv_pt_60->SetYTitle("#it{p}_{T} (GeV/#it{c})");
  hNPi0_acc_minv_pt_60->GetYaxis()->SetTitleOffset(1.4);
  hNPi0_acc_minv_pt_60->SetZTitle("#it{relative probability}");
  hNPi0_acc_minv_pt_60->GetZaxis()->SetTitleOffset(1.4);
  hNPi0_acc_minv_pt_60->Draw("colz");


  //minv vergleich bei verschiedenen pt's
  cNPi0_acc_minv_comp->cd();
  cNPi0_acc_minv_comp->SetTopMargin(0.05);
  cNPi0_acc_minv_comp->SetRightMargin(0.05);


  hNPi0_acc_minv_high_pt->SetLineColor(kRed);
  hNPi0_acc_minv_low_pt->SetLineColor(kBlue);
  hNPi0_acc_minv_mid_pt->SetLineColor(kGreen+2);
  hNPi0_acc_minv_high_pt->SetTitle("");
  hNPi0_acc_minv_high_pt->SetLineWidth(2);
  hNPi0_acc_minv_mid_pt->SetLineWidth(2);
  hNPi0_acc_minv_low_pt->SetLineWidth(2);

  hNPi0_acc_minv_high_pt->SetLineWidth(4);
  hNPi0_acc_minv_mid_pt->SetLineWidth(4);
  hNPi0_acc_minv_low_pt->SetLineWidth(4);

  hNPi0_acc_minv_high_pt->SetXTitle("#it{m}_{inv} (GeV/#it{c}^{2})");
  hNPi0_acc_minv_high_pt->GetXaxis()->SetTitleOffset(1.4);
  hNPi0_acc_minv_high_pt->SetYTitle("#it{counts}");
  hNPi0_acc_minv_high_pt->GetYaxis()->SetTitleOffset(1.4);

  TLegend *leg_minv_comp = new TLegend(0.37,0.5,0.9,0.9);
  leg_minv_comp->SetFillStyle(0);
  leg_minv_comp->SetBorderSize(0);
  leg_minv_comp->SetTextFont(43);
  leg_minv_comp->SetTextSize(20);
  leg_minv_comp->AddEntry(hNPi0_acc_minv_high_pt, "#splitline{#it{m}_{inv} spectrum}{for 3.32GeV/#it{c} < #it{p}_{T} <= 5GeV/#it{c}}", "l");
  leg_minv_comp->AddEntry(hNPi0_acc_minv_mid_pt, "#splitline{#it{m}_{inv} spectrum}{for 1.66GeV/#it{c} < #it{p}_{T} <= 3.32GeV/#it{c}}", "l");
  leg_minv_comp->AddEntry(hNPi0_acc_minv_low_pt, "#splitline{#it{m}_{inv} spectrum}{for 0GeV/#it{c} < #it{p}_{T} <= 1.66GeV/#it{c}}", "l");

  hNPi0_acc_minv_high_pt->Draw("");
  hNPi0_acc_minv_mid_pt->Draw("same");
  hNPi0_acc_minv_low_pt->Draw("same");
  leg_minv_comp->Draw("same");




  cNPi0_pt->SaveAs(Form("Simulation/TransversalImpuls%s.png", AddName.Data()));
  cNPi0_minv->SaveAs(Form("Simulation/InvarianteMasse%s.png", AddName.Data()));
  cNPi0_gen_minv_pt->SaveAs(Form("Simulation/InvarianteMasseTransversalImpulsSignal%s.png", AddName.Data()));
  cNPi0_acc_minv_pt_90->SaveAs(Form("Simulation/InvarianteMasseTransversalImpuls90Grad%s.png", AddName.Data()));
  cNPi0_acc_minv_pt_60->SaveAs(Form("Simulation/InvarianteMasseTransversalImpuls60Grad%s.png", AddName.Data()));
  cNPi0_acc_minv_comp->SaveAs(Form("Simulation/IvanrianteMasseVergleich%s.png", AddName.Data()));
  cNPi0_theta_pt->SaveAs(Form("Simulation/Theta_PT%s.png", AddName.Data()));
  cNPi0_costheta_pt->SaveAs(Form("Simulation/CosTheta_PT%s.png", AddName.Data()));
  hNPi0_gen_pt->SaveAs(Form("pi0ptSpectrum4pi%s.root", AddName.Data()));
  hNPi0_acc_90->SaveAs(Form("pi0ptSpectrum90Grad%s.root", AddName.Data()));
  hNPi0_acc_60->SaveAs(Form("pi0ptSpectrum60Grad%s.root", AddName.Data()));


  cE1E2->cd();
  gPad->SetLogz();
  hE1E2_minv->Scale(150./(Npi0));
  hE1E2_minv->GetZaxis()->SetRangeUser(1.e-3,1.e2);
  hE1E2_minv->SetZTitle("");
  hE1E2_minv->Draw("colz");
  hE1E2_minv->Scale(150./(Npi0));
  hE1E2_minv->GetZaxis()->SetRangeUser(1.e-3,1.e2);
  cE1E2->SaveAs(Form("Simulation/E_minv%s.png", AddName.Data()));
  cE1E2->Clear();
  hE1E2_minv->Delete();

  hE1E2_theta->Scale(150./(Npi0));
  hE1E2_theta->GetZaxis()->SetRangeUser(1.e-3,1.e2);
  hE1E2_theta->SetZTitle("");
  hE1E2_theta->Draw("colz");
  cE1E2->SaveAs(Form("Simulation/E_theta%s.png", AddName.Data()));
  cE1E2->Clear();
  hE1E2_theta->Delete();

  hE1E2_cosTheta->Scale(150./(Npi0));
  hE1E2_cosTheta->GetZaxis()->SetRangeUser(1.e-3,1.e2);
  hE1E2_cosTheta->SetZTitle("");
  hE1E2_cosTheta->Draw("colz");
  cE1E2->SaveAs(Form("Simulation/E_cosTheta%s.png", AddName.Data()));
  cE1E2->Clear();
  hE1E2_cosTheta->Delete();

  cout << endl;
}
