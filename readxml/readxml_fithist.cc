using namespace std;

#include "readxml.h"
#include "../uti.h"

void readxml_fithist(TString inputname, TString outputname,
		     TString collisionsyst, 
		     Float_t ptmin, Float_t ptmax, Float_t drmin, Float_t drmax)
{
  Bool_t isPbPb = collisionsyst=="PbPb"?true:false;

  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  TFile* inf = TFile::Open(Form("%s_%s.root",outputsavehist.Data(),inputname.Data()));
  TH1D** ahMass = new TH1D*[NEff];
  TH1D** ahMassMCSignal = new TH1D*[NEff];
  TH1D** ahMassMCSwapped = new TH1D*[NEff];
  Float_t maxsig = 0;
  Int_t maxindex = 0;
  for(int n=0;n<NEff;n++)
    {
      ahMass[n] = (TH1D*)inf->Get(Form("hMass_%d",n));
      ahMassMCSignal[n] = (TH1D*)inf->Get(Form("hMassMCSignal_%d",n));
      ahMassMCSwapped[n] = (TH1D*)inf->Get(Form("hMassMCSwapped_%d",n));
      Float_t* results = new Float_t[2];
      fit(ahMass[n], ahMassMCSignal[n], ahMassMCSwapped[n], Form("%s_%s_%d",outputfit.Data(),outputname.Data(),n), results, collisionsyst, ptmin, ptmax, drmin, drmax);
      effS[n] = n/100.;
      aS[n] = results[0];
      aB[n] = results[1];
      if((aS[n]+aB[n])==0) aSig[n] = 0;
      else aSig[n] = aS[n]/TMath::Sqrt(aS[n]+aB[n]);
      if(aSig[n]>maxsig)
	{
	  maxsig = aSig[n];
	  maxindex = n;
	}
    }
  Float_t* resultmax = new Float_t[2];
  fit(ahMass[maxindex], ahMassMCSignal[maxindex], ahMassMCSwapped[maxindex], Form("%s_%s_%d",outputfitmax.Data(),outputname.Data(),maxindex), resultmax, collisionsyst, ptmin, ptmax, drmin, drmax, false);

  cout<<endl;
  cout<<"  =================================================="<<endl;
  cout<<" |                     Opt Result                   |"<<endl;
  cout<<"  --------------------------------------------------"<<endl;
  cout<<" | "<<setiosflags(ios::left)<<setw(8)<<"S"<<" | "<<setiosflags(ios::left)<<setw(9)<<Form("%.0f",aS[maxindex])<<" | "<<setiosflags(ios::left)<<setw(12)<<"B"<<" | "<<setiosflags(ios::left)<<setw(10)<<Form("%.0f",aB[maxindex])<<" |"<<endl;
  cout<<"  --------------------------------------------------"<<endl;
  cout<<" | "<<setiosflags(ios::left)<<setw(8)<<"Sig eff"<<" | "<<setiosflags(ios::left)<<setw(9)<<effS[maxindex]<<" | "<<setiosflags(ios::left)<<setw(12)<<"S/sqrt(S+B)"<<" | "<<setiosflags(ios::left)<<setw(10)<<Form("%.2f",aSig[maxindex])<<" |"<<endl;
  //cout<<"  --------------------------------------------------"<<endl;
  /*
  for(unsigned int m=0;m<nVar;m++)
    {
      if(m) cout<<"  --------------------------------------------------"<<endl;
      cout<<" | "<<setiosflags(ios::left)<<setw(27)<<varval[m]<<" | "<<setiosflags(ios::left)<<setw(18)<<cutval[m].at(maxindex)<<" |"<<endl;
    }
  */
  cout<<"  =================================================="<<endl;
  cout<<endl;

  TH2F* hempty = new TH2F("hempty","",50,0,1.,10,0.,aSig[maxindex]*1.4);
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitle("Signal efficiency");
  hempty->GetYaxis()->SetTitle("S / #sqrt{S+B}");
  hempty->GetXaxis()->SetTitleOffset(1.0);
  hempty->GetYaxis()->SetTitleOffset(1.5);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);
  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collisionsyst.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);

  TLatex* texD = new TLatex(0.22,0.855, "D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
  texD->SetNDC();
  texD->SetTextAlign(12);
  texD->SetTextSize(0.04);
  texD->SetTextFont(42);
  TLatex* texY = new TLatex(0.22,0.79, "|y| < 1");
  texY->SetNDC();
  texY->SetTextAlign(12);
  texY->SetTextSize(0.04);
  texY->SetTextFont(42);
  TLatex* texPt = new TLatex(0.92,0.84, Form("%.0f < p_{T} < %.0f GeV/c",ptmin,ptmax));
  texPt->SetNDC();
  texPt->SetTextAlign(32);
  texPt->SetTextSize(0.04);
  texPt->SetTextFont(42);
  TLatex* texDr = new TLatex(0.92,0.79, Form("%.2f < #DeltaR < %.2f",drmin,drmax));
  texDr->SetNDC();
  texDr->SetTextAlign(32);
  texDr->SetTextSize(0.04);
  texDr->SetTextFont(42);

  TGraph* gsig = new TGraph(100, effS, aSig);
  gsig->SetName("gsig");
  TCanvas* csig = new TCanvas("csig","",600,600);
  hempty->Draw();
  texCms->Draw();
  texCol->Draw();
  texD->Draw();
  texY->Draw();
  texPt->Draw();
  texDr->Draw();
  gsig->Draw("same*");
  csig->SaveAs(Form("%s_%s.pdf",outputsignificance.Data(),outputname.Data()));
  
}

int main(int argc, char* argv[])
{
  if(argc==8)
    {
      readxml_fithist(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
      return 0;
    }
  else
    {
      cout<<"  Error: invalid argument number - readxml_fithist"<<endl;
      return 1;
    }
}
