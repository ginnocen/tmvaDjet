using namespace std;
#include "../uti.h"

void variables(TString inputSname, TString inputBname, TString outputname,
	       TString mycuts, TString mycutb,
	       TString variable, TString varname, TString varlatex, 
	       Int_t varn, Float_t varmin, Float_t varmax,
               TString collisionsyst, Float_t ptmin, Float_t ptmax, Float_t drmin, Float_t drmax)
{
  setgstyle();
  Bool_t isPbPb = collisionsyst=="PbPb"?true:false;

  TFile* inputS = TFile::Open(inputSname);
  TFile* inputB = TFile::Open(inputBname);

  TTree* signal = (TTree*)inputS->Get("tmvadjt");
  TTree* background = (TTree*)inputB->Get("tmvadjt");

  TString sels = isPbPb?Form("(%s)&&Dpt>%f&&Dpt<%f&&DdeltaR>%f&&DdeltaR<%f&&hiBin>=0&&hiBin<=200",mycuts.Data(),ptmin,ptmax,drmin,drmax):Form("(%s)&&Dpt>%f&&Dpt<%f&&DdeltaR>%f&&DdeltaR<%f",mycuts.Data(),ptmin,ptmax,drmin,drmax);
  TString selb = isPbPb?Form("(%s)&&Dpt>%f&&Dpt<%f&&DdeltaR>%f&&DdeltaR<%f&&hiBin>=0&&hiBin<=200",mycutb.Data(),ptmin,ptmax,drmin,drmax):Form("(%s)&&Dpt>%f&&Dpt<%f&&DdeltaR>%f&&DdeltaR<%f",mycutb.Data(),ptmin,ptmax,drmin,drmax);

  TH1D* hSgl = new TH1D("hSgl",Form(";%s;Probability",varlatex.Data()),varn,varmin,varmax);
  setth1d(hSgl);
  hSgl->GetXaxis()->SetLabelSize(0.045);
  hSgl->GetYaxis()->SetLabelSize(0.045);
  hSgl->GetYaxis()->SetTitleOffset(1.60);
  hSgl->GetXaxis()->SetTitleOffset(1.10);
  TH1D* hBkg = new TH1D("hBkg",Form(";%s;Probability",varlatex.Data()),varn,varmin,varmax);
  setth1d(hBkg);
  hBkg->GetXaxis()->SetLabelSize(0.045);
  hBkg->GetYaxis()->SetLabelSize(0.045);
  hBkg->GetYaxis()->SetTitleOffset(1.60);
  hBkg->GetXaxis()->SetTitleOffset(1.10);

  signal->Project("hSgl",variable,Form("%s",sels.Data()));
  background->Project("hBkg",variable,Form("%s",selb.Data()));
  cout<<hBkg->Integral()<<" "<<hSgl->Integral()<<endl;
  
  hBkg->Scale(1./hBkg->Integral());
  hSgl->Scale(1./hSgl->Integral()); 

  TCanvas* c = new TCanvas("c","",600,600);
  hBkg->SetMaximum(max(hBkg->GetMaximum(),hSgl->GetMaximum())*1.4);

  hBkg->SetLineColor(kBlue+1);
  hBkg->SetFillStyle(1001);
  hBkg->SetFillColor(kBlue-9);
  hBkg->SetLineWidth(3);
  hBkg->SetStats(0);

  hSgl->SetLineColor(kRed);
  hSgl->SetFillStyle(3004);
  hSgl->SetFillColor(kRed);
  hSgl->SetLineWidth(3);
  hSgl->SetStats(0);

  hBkg->Draw();
  hSgl->Draw("same");
  
  TLatex* texD = new TLatex(0.22,0.87, "D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
  settex(texD,0.04,12);
  TLatex* texY = new TLatex(0.22,0.81, "|y| < 2.0");
  settex(texY,0.04,12);
  TLatex* texpt = new TLatex(0.92,0.85,Form("%.0f < p_{T} < %.0f GeV",ptmin,ptmax));
  settex(texpt,0.04,32);
  TLatex* texdr = new TLatex(0.92,0.81,Form("%.2f < #DeltaR < %.2f",drmin,drmax));
  settex(texdr,0.04,32);
  TLegend *leg = new TLegend(0.64,0.68,1.05,0.78);

  setleg(leg);
  leg->AddEntry(hBkg,"Background","f");
  leg->AddEntry(hSgl,"Signal","f");
  texD->Draw();
  texY->Draw();
  texpt->Draw();
  texdr->Draw();
  leg->Draw("same");
  
  drawCMS(collisionsyst);

  c->SaveAs(Form("%s_%s.pdf",outputname.Data(),varname.Data()));
}

int main(int argc, char* argv[])
{
  if(argc==17)
    {
      variables(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8],atoi(argv[9]),atof(argv[10]),atof(argv[11]),argv[12],atof(argv[13]),atof(argv[14]),atof(argv[15]),atof(argv[16]));
      return 0;
    }
  else
    {
      cout<<"  Error: invalid argument number - variables()"<<endl;
      return 1;
    }
}
