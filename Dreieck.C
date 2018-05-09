#include "CommenHeader.h"


void Dreieck(TString AddName = "") {

  TFile* minv_pt_spectra = new TFile("minv_pt_spectra.root", "RECREATE");

  Float_t pi = TMath::Pi(); /* besser vor dem loop? */
  TLatex* poweektex = new TLatex();


  // create a canvas to draw in:
  TCanvas *c1 = new TCanvas("cNPi0_pt","",1200,1200);
  SetCanvasStandardSettings(c1);
  c1->SetRightMargin(0.15);
  c1->SetLogz(1);

  //create array of histos:
  TH2F* hNPi0_gen_minv_pt[20];
  TH2F* hWinkelAbdeckung[20];

  //create TLatex for providing information in Histos:
  TLatex* tex = new TLatex();

  Float_t m = 0.135; // pi0 mass

  // generate a certain number of pi0
  const Int_t Npi0 = 1.e6;

  // pT distribution
  TF1* fpt = new TF1("fpt","x*exp(-x/0.2)",0.,10.);

  // rapidity distribution
  TF1* fy = new TF1("fy", "gaus", -0.5, 0.5);
  fy->SetParameters(1., 0., 4.);

  for (Int_t i = 0; i < 20; i++) {

    std::cout << "Running Toy-Monte-Carlo-Simulation for " << i*0.1 << " <= p_T <" << (i+1)*0.1 << std::endl;

    hNPi0_gen_minv_pt[i] = new TH2F(Form("hNPi0_gen_minv_pt[%d]",i),"generated pi0: minv vs. pT",300,0.,1.,300,0.,1.);
    SetHistoStandardSettings2(hNPi0_gen_minv_pt[i]);



    hWinkelAbdeckung[i] = new TH2F(Form("hWinkelAbdeckung[%d]",i),"Winkelabdeckung same events",100,-1.,1.,180,-1.*pi,1.0001*pi);
    SetHistoStandardSettings2(hWinkelAbdeckung[i]);
    hWinkelAbdeckung[i]->SetXTitle("#it{#eta}");
    hWinkelAbdeckung[i]->SetYTitle("#it{#phi}");
    hWinkelAbdeckung[i]->GetYaxis()->SetBit(TAxis::kLabelsVert);
    hWinkelAbdeckung[i]->GetYaxis()->SetBinLabel(1,"0");
    hWinkelAbdeckung[i]->GetYaxis()->SetBinLabel(hWinkelAbdeckung[i]->GetYaxis()->FindBin(pi), "#pi");
    hWinkelAbdeckung[i]->GetYaxis()->SetBinLabel(hWinkelAbdeckung[i]->GetYaxis()->FindBin(pi/2.),"#frac{#pi}{2}");
    hWinkelAbdeckung[i]->GetYaxis()->SetBinLabel(hWinkelAbdeckung[i]->GetYaxis()->FindBin(0.),"0");
    hWinkelAbdeckung[i]->GetYaxis()->SetBinLabel(hWinkelAbdeckung[i]->GetYaxis()->FindBin(-pi), "-#pi");
    hWinkelAbdeckung[i]->GetYaxis()->SetBinLabel(hWinkelAbdeckung[i]->GetYaxis()->FindBin(-pi/2.),"#frac{-#pi}{2}");
    hWinkelAbdeckung[i]->GetXaxis()->SetNdivisions(5);


    for (int ip=0; ip < Npi0; ip++) {
      printProgress( ((Double_t)ip) / ((Double_t)Npi0) );


      // set pT, rapidity, ...
      Float_t pt_lab = 0; //gRandom->Uniform(i*0.0005,(i+1.)*0.0005);
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
      Float_t phi1_test = atan2(p1y,p1x);

      Float_t pt2 = sqrt(p2x*p2x + p2y*p2y);
      Float_t theta2 = atan2(pt2,p2z);
      Float_t eta2 = -log(tan(theta2/2.));
      Float_t phi2_test = atan2(p2y,p2x);



      ///////////////////////////////////////////////

      // Implementiere eine Energieverschmierung
      Float_t e_gamma_1 = sqrt(p1x*p1x+p1y*p1y+p1z*p1z);
      Float_t e_gamma_2 = sqrt(p2x*p2x+p2y*p2y+p2z*p2z);
      e_gamma_1 = fEnergySmear(e_gamma_1);
      e_gamma_2 = fEnergySmear(e_gamma_2);

      // berechne den Transversalimpuls neu
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

      // Test für Winkelabdeckung:
      hWinkelAbdeckung[i]->Fill(eta1, phi1_test);
      hWinkelAbdeckung[i]->Fill(eta2, phi2_test);

      /////////////////////////////////////////////
      //without acc
      hNPi0_gen_minv_pt[i]->Fill(minv,pt_lab,fpt->Eval(pt_lab));

      ///////////////////////////////////////////////

    }

    // changing and clearing Canvas
    c1->cd();
    c1->Clear();
    hWinkelAbdeckung[i]->Draw("colz");
    hWinkelAbdeckung[i]->GetZaxis()->SetRangeUser(1.e0,1.e3);
    c1->Update();
    c1->SaveAs(Form("Dreieck/Winkelabdeckung[%d].png", i));
    hWinkelAbdeckung[i]->Write(Form("Winkelabdeckung %1.4lf #leq p_{T} < %1.4lf",i*0.0005, (i+1)*0.0005));

    c1->Clear();
    hNPi0_gen_minv_pt[i]->Scale(1./Npi0);
    hNPi0_gen_minv_pt[i]->GetZaxis()->SetTitle("relative probability");
    hNPi0_gen_minv_pt[i]->Draw("colz");
    tex->DrawLatexNDC(0.3,0.8, Form("%1.4lf #leq p_{T} (GeV/#it{c}) < %1.4lf",i*0.0005, (i+1)*0.0005));
    hNPi0_gen_minv_pt[i]->GetZaxis()->SetRangeUser(1.e-10,1.e0);
    c1->Update();

    c1->SaveAs(Form("Dreieck/minv_pT_Spektrum[%d].png", i));
    hNPi0_gen_minv_pt[i]->Write(Form("hNPi0_gen_minv_pt %lf #leq p_{T} < %lf",i*0.0005, (i+1)*0.0005));

    c1->Clear();

      std::cout <<std::endl << "Finished Toy-Monte-Carlo-Simulation for " << i*0.1 << " <= p_T <" << (i+1)*0.1 << std::endl << std::endl;

  }

  for(Int_t k = 0; k < 20; k++){
    hWinkelAbdeckung[k]->Delete();
    hNPi0_gen_minv_pt[k]->Delete();
  }

  tex->Delete();
  //c1->Delete();
  minv_pt_spectra->Close();
  cout << endl;
}
