#ifndef _READXML_H
#define _READXML_H

#include "../uti.h"

const int NEff = 100;
Double_t effSft[NEff], effBft[NEff], aSft[NEff], aBft[NEff], aSigft[NEff];
Double_t effSfo[NEff], effBfo[NEff], aSfo[NEff], aBfo[NEff], aSigfo[NEff];
const int NFonll = 4000;
Double_t MINFonll = 0;
Double_t MAXFonll = 1000;
Double_t fpt[NFonll], fcentral[NFonll];

TString outputsavehist = "rootfiles/fmass";
TString outputfit = "plotfits/cmass";
TString outputsignificance = "plots/csignificance";
TString outputfitmax = "plots/cmass";
TString outputresult = "results/significance";
TString outputfonll = "plots/cfonll";

Float_t massD = 1.8649;
Float_t dmassDsignal = 0.045;
Float_t dmassDsidband1 = 0.01;
Float_t dmassDsidband2 = 0.015;
Float_t masssignal1 = massD - dmassDsignal;
Float_t masssignal2 = massD + dmassDsignal;

Double_t BR = 0.0387;
Double_t deltapt = 0.25;

void fit(TH1D* h, TH1D* hMCSignal, TH1D* hMCSwapped, 
	 TString outputname, Float_t* results, TString collisionsyst, 
	 Float_t ptmin, Float_t ptmax, Float_t drmin, Float_t drmax,
	 Bool_t ifsethmaximum = true)
{

  Double_t setparam0 = 100.;
  Double_t setparam1 = 1.865;
  Double_t setparam2 = 0.03;
  Double_t setparam10 = 0.005;
  Double_t setparam8 = 0.1;
  Double_t setparam9 = 0.1;
  Double_t fixparam1 = 1.865;

  Double_t minhisto = 1.7;
  Double_t maxhisto = 2.0;
  Double_t nbinsmasshisto = 60;
  Double_t binwidthmass = (maxhisto-minhisto)/nbinsmasshisto;

  TCanvas* c = new TCanvas("c","",600,600);

  TF1* f = new TF1("f","[0]*([7]*([9]*TMath::Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*TMath::Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*TMath::Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);
  
  f->SetParLimits(4,-1000,1000);
  f->SetParLimits(10,0.001,0.05);
  f->SetParLimits(2,0.01,0.5);
  f->SetParLimits(8,0.02,0.2);
  f->SetParLimits(7,0,1);
  f->SetParLimits(9,0,1);
  
  f->SetParameter(0,setparam0);
  f->SetParameter(1,setparam1);
  f->SetParameter(2,setparam2);
  f->SetParameter(10,setparam10);
  f->SetParameter(9,setparam9);

  f->FixParameter(8,setparam8);
  f->FixParameter(7,1);
  f->FixParameter(1,fixparam1);
  f->FixParameter(3,0);
  f->FixParameter(4,0);
  f->FixParameter(5,0);
  f->FixParameter(6,0);
  f->FixParameter(11,0);
  h->GetEntries();
  
  hMCSignal->Fit("f","q","",minhisto,maxhisto);
  hMCSignal->Fit("f","q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  hMCSignal->Fit("f","L q","",minhisto,maxhisto);
  hMCSignal->Fit("f","L q","",minhisto,maxhisto);
  hMCSignal->Fit("f","L m","",minhisto,maxhisto);
  
  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit("f","L q","",minhisto,maxhisto);
  hMCSwapped->Fit("f","L q","",minhisto,maxhisto);
  hMCSwapped->Fit("f","L q","",minhisto,maxhisto);
  hMCSwapped->Fit("f","L m","",minhisto,maxhisto);
  
  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);

  f->SetLineColor(kRed);
  
  h->Fit("f","q","",minhisto,maxhisto);
  h->Fit("f","q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  f->SetParLimits(1,1.86,1.87);
  f->ReleaseParameter(11);
  f->SetParLimits(11,-0.5,0.5);
  h->Fit("f","L q","",minhisto,maxhisto);
  h->Fit("f","L q","",minhisto,maxhisto);
  h->Fit("f","L q","",minhisto,maxhisto);
  h->Fit("f","L m","",minhisto,maxhisto);
  
  TF1* background = new TF1("background","[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1("mass","[0]*([3]*([4]*TMath::Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*TMath::Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(11));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(7));
  mass->SetParError(4,f->GetParError(9));
  mass->SetParError(5,f->GetParError(10));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);
  
  TF1* massSwap = new TF1("massSwap","[0]*(1-[2])*TMath::Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8),f->GetParameter(11));
  massSwap->SetParError(0,f->GetParError(0));
  massSwap->SetParError(1,f->GetParError(1));
  massSwap->SetParError(2,f->GetParError(7));
  massSwap->SetParError(3,f->GetParError(8));
  massSwap->SetFillColor(kGreen+4);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineColor(kGreen+4);
  massSwap->SetLineWidth(3);
  massSwap->SetLineStyle(1);

  TF1* backgroundnSwap = new TF1("backgroundnSwap","[0]*(1-[2])*TMath::Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))+[5]+[6]*x+[7]*x*x+[8]*x*x*x");
  backgroundnSwap->SetParameters(massSwap->GetParameter(0),massSwap->GetParameter(1),massSwap->GetParameter(2),massSwap->GetParameter(3),massSwap->GetParameter(4),background->GetParameter(0),background->GetParameter(1),background->GetParameter(2),background->GetParameter(3));
  backgroundnSwap->SetLineStyle(2);
  backgroundnSwap->SetLineWidth(2);
  backgroundnSwap->SetLineColor(12);
  backgroundnSwap->Draw();
  
  h->SetXTitle("m_{#piK} (GeV/c^{2})");
  h->SetYTitle("Entries / (5 MeV/c^{2})");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  if(ifsethmaximum) h->SetAxisRange(0,h->GetMaximum()*1.4*1.2,"Y");
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitleOffset(1.8);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->GetXaxis()->SetTitleSize(0.045);
  h->GetYaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  h->SetStats(0);
  h->Draw("e");

  background->SetRange(minhisto,maxhisto);
  background->Draw("same");   
  mass->SetRange(minhisto,maxhisto);
  mass->Draw("same");
  massSwap->SetRange(minhisto,maxhisto);
  massSwap->Draw("same");
  backgroundnSwap->SetRange(masssignal1,masssignal2);
  backgroundnSwap->Draw("same");
  f->Draw("same");

  TLine* lineSignal1 = new TLine(masssignal1, 0, masssignal1, f->Eval(masssignal1));
  lineSignal1->SetLineStyle(2);
  lineSignal1->SetLineWidth(2);
  lineSignal1->SetLineColor(12);
  lineSignal1->Draw();
  TLine* lineSignal2 = new TLine(masssignal2, 0, masssignal2, f->Eval(masssignal2));
  lineSignal2->SetLineStyle(2);
  lineSignal2->SetLineWidth(2);
  lineSignal2->SetLineColor(12);
  lineSignal2->Draw();
  
  TLegend* leg = new TLegend(0.65,0.58,0.82,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();

  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collisionsyst.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

  TLatex* texpt = new TLatex(0.22,0.78,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  texpt->SetNDC();
  texpt->SetTextFont(42);
  texpt->SetTextSize(0.04);
  texpt->SetLineWidth(2);
  texpt->Draw();
  TLatex* texdr = new TLatex(0.22,0.73,Form("%.2f < #DeltaR < %.2f",drmin,drmax));
  texdr->SetNDC();
  texdr->SetTextFont(42);
  texdr->SetTextSize(0.04);
  texdr->SetLineWidth(2);
  texdr->Draw();

  TLatex* texrap = new TLatex(0.22,0.83,"|y| < 2.0");
  texrap->SetNDC();
  texrap->SetTextFont(42);
  texrap->SetTextSize(0.04);
  texrap->SetLineWidth(2);
  texrap->Draw();
  
  c->SaveAs(Form("%s.pdf",outputname.Data()));


  Double_t yield = mass->Integral(minhisto,maxhisto)/binwidthmass;
  Double_t yieldErr = mass->Integral(minhisto,maxhisto)/binwidthmass*mass->GetParError(0)/mass->GetParameter(0);
  
  results[0] = mass->Integral(masssignal1,masssignal2)/binwidthmass;
  results[1] = background->Integral(masssignal1,masssignal2)/binwidthmass + massSwap->Integral(masssignal2,masssignal2)/binwidthmass;

  delete c;

}

#endif
