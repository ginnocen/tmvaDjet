#include "fitD.h"

int fitD(TString inputmcname, TString inputdataname, TString outplotname,
         TString collisionsyst,
         Float_t jetptmin, Float_t jetetamin, Float_t jetetamax,
         Float_t ptmin, Float_t ptmax, Float_t drmin, Float_t drmax)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  Int_t result_initcutval = initcutval(collisionsyst);
  if(result_initcutval!=0) return result_initcutval;

  TH1D* h = new TH1D("h","",60,1.7,2.0);
  TH1D* hMCSignal = new TH1D("hMCSignal","",60,1.7,2.0);
  TH1D* hMCSwapped = new TH1D("hMCSwapped","",60,1.7,2.0);

  tmvaD mvaDmc;
  mvaDmc.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
  mvaDmc.setDcut(cutval_Dy, cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, ptmin, ptmax, drmin, drmax);
  mvaDmc.setjetcut(jetptmin, jetetamin, jetetamax);
  TFile* inputmc = TFile::Open(inputmcname);
  TTree* ntmc = (TTree*)inputmc->Get("tmvadjt");
  mvaDmc.setbranchaddress(ntmc);
  Int_t nentriesmc = ntmc->GetEntries();
  std::cout<<std::endl;
  std::cout<<"  Filling invariant mass histograms - MC..."<<std::endl;
  for(int i=0;i<nentriesmc;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<nentriesmc<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/nentriesmc)<<"%\033[0m"<<"\r"<<std::flush;
      ntmc->GetEntry(i);
      for(int j=0;j<mvaDmc.Dsize;j++)
        {
          if(mvaDmc.isselected(j))
            {
              if((*mvaDmc.Dgen)[j]==23333) hMCSignal->Fill((*mvaDmc.Dmass)[j]);
              if((*mvaDmc.Dgen)[j]==23344) hMCSwapped->Fill((*mvaDmc.Dmass)[j]);
            }
        }
    }
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<nentriesmc<<"\033[0m event(s)."<<std::endl;

  tmvaD mvaDdata; 
  mvaDdata.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
  mvaDdata.setDcut(cutval_Dy, cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, ptmin, ptmax, drmin, drmax);
  mvaDdata.setjetcut(jetptmin, jetetamin, jetetamax);
  TFile* inputdata = TFile::Open(inputdataname);
  TTree* ntdata = (TTree*)inputdata->Get("tmvadjt");
  mvaDdata.setbranchaddress(ntdata);
  Int_t nentriesdata = ntdata->GetEntries();
  std::cout<<"  Filling invariant mass histograms - data..."<<std::endl;
  for(int i=0;i<nentriesdata;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<nentriesdata<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/nentriesdata)<<"%\033[0m"<<"\r"<<std::flush;
      ntdata->GetEntry(i);
      for(int j=0;j<mvaDdata.Dsize;j++)
        {
          if(mvaDdata.isselected(j))
            {
              h->Fill((*mvaDdata.Dmass)[j]);
            }
        }
    }
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<nentriesdata<<"\033[0m event(s)."<<std::endl;
  std::cout<<std::endl;

  Float_t* results = new Float_t[2];
  fit(h, hMCSignal, hMCSwapped, outplotname, results, collisionsyst, jetptmin, jetetamin, jetetamax, ptmin, ptmax, drmin, drmax, false);

  return 0;
  
}

int main(int argc, char* argv[])
{
  if(argc==12)
    {
      fitD(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]), atof(argv[11]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid argument number - fitD()"<<std::endl;
      return 1;
    }
}
