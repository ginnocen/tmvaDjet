#include "fitDjets.h"

int fitDjets(TString inputmcname, TString inputdataname, TString collisionsyst,
             Float_t jetptmin, Float_t jetetamin, Float_t jetetamax)
{
  xjjrootuti::setgstyle();

  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\" - initcutval()"<<std::endl;
      return 1;
    }

  TH1D* ah[nPtBins][nDrBins];
  TH1D* ahMCSignal[nPtBins][nDrBins];
  TH1D* ahMCSwapped[nPtBins][nDrBins];
  for(int i=0;i<nPtBins;i++)
    {
      for(int j=0;j<nDrBins;j++)
        {
          ah[i][j] = new TH1D(Form("h_%d_%d",i,j),"",60,1.7,2.0);
          ahMCSignal[i][j] = new TH1D(Form("hMCSignal_%d_%d",i,j),"",60,1.7,2.0);
          ahMCSwapped[i][j] = new TH1D(Form("hMCSwapped_%d_%d",i,j),"",60,1.7,2.0);
        }
    }

  tmvaD mvaDmc;
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
          Int_t ibinpt = xjjuti::findibin(&ptBins, (*mvaDmc.Dpt)[j]);
          Int_t ibindr = xjjuti::findibin(&drBins, (*mvaDmc.DdeltaR)[j]);
          if(ibinpt<0 || ibindr<0) continue;
          Float_t ptmin = ptBins[ibinpt], ptmax = ptBins[ibinpt+1];
          Float_t drmin = drBins[ibindr], drmax = drBins[ibindr+1];
          Int_t result_initcutval = initcutval(collisionsyst, ibinpt, ibindr);
          if(result_initcutval) return result_initcutval;
          mvaDmc.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
          mvaDmc.setDcut(cutval_Dy, cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, ptmin, ptmax, drmin, drmax);
          mvaDmc.setjetcut(jetptmin, jetetamin, jetetamax);
          if(mvaDmc.isselected(j))
            {
              if((*mvaDmc.Dgen)[j]==23333) ahMCSignal[ibinpt][ibindr]->Fill((*mvaDmc.Dmass)[j]);
              if((*mvaDmc.Dgen)[j]==23344) ahMCSwapped[ibinpt][ibindr]->Fill((*mvaDmc.Dmass)[j]);
            }
        }
    }
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<nentriesmc<<"\033[0m event(s)."<<std::endl;

  tmvaD mvaDdata;
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
          Int_t ibinpt = xjjuti::findibin(&ptBins, (*mvaDdata.Dpt)[j]);
          Int_t ibindr = xjjuti::findibin(&drBins, (*mvaDdata.DdeltaR)[j]);
          if(ibinpt<0 || ibindr<0) continue;
          Float_t ptmin = ptBins[ibinpt], ptmax = ptBins[ibinpt+1];
          Float_t drmin = drBins[ibindr], drmax = drBins[ibindr+1];
          Int_t result_initcutval = initcutval(collisionsyst, ibinpt, ibindr);
          if(result_initcutval) return result_initcutval;
          mvaDdata.settrkcut(cutval_trkPt, cutval_trkEta, cutval_trkPtErr);
          mvaDdata.setDcut(cutval_Dy, cutval_Dsvpv, cutval_Dalpha, cutval_Dchi2cl, ptmin, ptmax, drmin, drmax);
          mvaDdata.setjetcut(jetptmin, jetetamin, jetetamax);
          if(mvaDdata.isselected(j))
            {
              ah[ibinpt][ibindr]->Fill((*mvaDdata.Dmass)[j]);
            }
        }
    }
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<nentriesdata<<"\033[0m event(s)."<<std::endl;
  std::cout<<std::endl;

  for(int i=0;i<nPtBins;i++)
    {
      for(int j=0;j<nDrBins;j++)
        {
          Float_t ptmin = ptBins[i], ptmax = ptBins[i+1], drmin = drBins[j], drmax = drBins[j+1];
          Float_t* results = new Float_t[2];
          TString outplotname = Form("plotfits/cmass_jetpt_%s_jeteta_%s_%s_pt_%s_%s_deltaR_%s_%s",xjjuti::number_to_string(jetptmin).c_str(),xjjuti::number_to_string(jetetamin).c_str(),xjjuti::number_to_string(jetetamax).c_str(),xjjuti::number_to_string(ptmin).c_str(),xjjuti::number_to_string(ptmax).c_str(),xjjuti::number_to_string(drmin).c_str(),xjjuti::number_to_string(drmax).c_str());
          fit(ah[i][j], ahMCSignal[i][j], ahMCSwapped[i][j], outplotname, results, collisionsyst, jetptmin, jetetamin, jetetamax, ptmin, ptmax, drmin, drmax, false);
        }
    }

  return 0;
  
}

int main(int argc, char* argv[])
{
  if(argc==7)
    {
      fitDjets(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]), atof(argv[6]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid argument number - fitD()"<<std::endl;
      return 1;
    }
}
