#include "readxml.h"

void readxml_savehist(TString inputmcname, TString inputdataname, TString outputname,
                      TString weightfile, TString collisionsyst, 
                      Float_t jetptmin, Float_t jetetamin, Float_t jetetamax,
                      Float_t ptmin, Float_t ptmax, Float_t drmin, Float_t drmax)
{
  xjjrootuti::setgstyle();

  // read weight file
  const char* filename = weightfile;
  void *doc = TMVA::gTools().xmlengine().ParseFile(filename,TMVA::gTools().xmlenginebuffersize());
  void* rootnode = TMVA::gTools().xmlengine().DocGetRootElement(doc); //node "MethodSetup"
  TString fullMethodName("");
  TMVA::gTools().ReadAttr(rootnode, "Method", fullMethodName);

  std::cout<<std::endl;
  std::cout<<"  ===================================================="<<std::endl;
  std::cout<<" |                Cut Opt Configuration               |"<<std::endl;
  std::cout<<"  ----------------------------------------------------"<<std::endl;
  std::cout<<" | "<<std::setiosflags(std::ios::left)<<std::setw(10)<<"Method"<<" | "<<std::setw(28)<<fullMethodName<<" | "<<std::setw(6)<<" "<<" |"<<std::endl;

  void *opts = TMVA::gTools().GetChild(rootnode,"Options");
  void* opt = TMVA::gTools().GetChild(opts,"Option");

  TString varProp("");
  while(opt)
    {
      TString optname("");
      TMVA::gTools().ReadAttr(opt, "name", optname);
      if(optname=="VarProp") varProp = TMVA::gTools().GetContent(opt);
      opt = TMVA::gTools().GetNextChild(opt);
    }

  TObjArray* marginclass = varProp.Tokenize(" ");
  std::vector<TString> margins; //avoid objarrays
  for(int i=0;i<marginclass->GetEntries();i++)
    {
      margins.push_back(((TObjString *)(marginclass->At(i)))->String());
    }
  void* variables = TMVA::gTools().GetChild(rootnode,"Variables");
  UInt_t nVar=0;
  std::vector<TString> varnames;
  std::vector<double> varmins[NEff];
  std::vector<double> varmaxs[NEff];
  TMVA::gTools().ReadAttr(variables, "NVar", nVar);

  void* var = TMVA::gTools().GetChild(variables,"Variable");
  for(unsigned int k=0;k<nVar;k++)
    {
      TString varname("");
      TMVA::gTools().ReadAttr(var, "Expression", varname);
      TString tem = Form("Variable%i",k);
      std::cout<<"  ----------------------------------------------------"<<std::endl;
      std::cout<<" | "<<std::setiosflags(std::ios::left)<<std::setw(10)<<tem<<" | "<<std::setw(28)<<varname<<" | "<<std::setw(6)<<margins[k]<<" |"<<std::endl;
      var = TMVA::gTools().GetNextChild(var);
      varnames.push_back(varname);
    }
  std::cout<<"  ===================================================="<<std::endl;
    
  void* weight = TMVA::gTools().GetChild(rootnode,"Weights");
  void* eff = TMVA::gTools().GetChild(weight,"Bin");
  int n=0;
  while(eff)
    {
      TMVA::gTools().ReadAttr(eff, "effS", effS[n]);
      TMVA::gTools().ReadAttr(eff, "effB", effB[n]);
      void* cutsnode = TMVA::gTools().GetChild(eff,"Cuts");

      for(ULong_t l=0;l<varnames.size();l++)
	{
	  Double_t vmin,vmax;
	  TMVA::gTools().ReadAttr(cutsnode, TString("cutMin_")+l, vmin);
	  TMVA::gTools().ReadAttr(cutsnode, TString("cutMax_")+l, vmax);
	  varmins[n].push_back(vmin);
	  varmaxs[n].push_back(vmax);
	}
      eff = TMVA::gTools().GetNextChild(eff);
      n++;
    }
  TMVA::gTools().xmlengine().FreeDoc(doc);
  
  // prepare histograms
  TH1D** ahMass = new TH1D*[NEff];
  TH1D** ahMassMCSignal = new TH1D*[NEff];
  TH1D** ahMassMCSwapped = new TH1D*[NEff];
  TH1D** ahPtEffSignal = new TH1D*[NEff];
  TH1D** ahPtMCSignal = new TH1D*[NEff];
  TH1D* hPtGenSignal = new TH1D("hPtGenSignal","",NFonll,MINFonll,MAXFonll);
  TH1D* hSideband = new TH1D("hSideband","",NEff,0,1);

  for(n=0;n<NEff;n++)
    {
      ahMass[n] = new TH1D(Form("hMass_%d",n),"",60,1.7,2.0);
      ahMassMCSignal[n] = new TH1D(Form("hMassMCSignal_%d",n),"",60,1.7,2.0);
      ahMassMCSwapped[n] = new TH1D(Form("hMassMCSwapped_%d",n),"",60,1.7,2.0);
      ahPtMCSignal[n] = new TH1D(Form("hPtMCSignal_%d",n),"",NFonll,MINFonll,MAXFonll);
    }

  // fill histograms
  tmvaD mvaDmc;
  mvaDmc.settrkcut(2.0, 2.0, 0.3);
  mvaDmc.setDcut(2.0, 0.0, 0.2, 0.05, ptmin, ptmax, drmin, drmax);
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
	  for(n=0;n<NEff;n++)
	    {
	      mvaDmc.settmvacut(varmaxs[n].at(0),varmins[n].at(1));
	      if(mvaDmc.isselected(j))
		{
		  if((*mvaDmc.Dgen)[j]==23333) ahMassMCSignal[n]->Fill((*mvaDmc.Dmass)[j]);
		  if((*mvaDmc.Dgen)[j]==23344) ahMassMCSwapped[n]->Fill((*mvaDmc.Dmass)[j]);
                  if((*mvaDmc.Dgen)[j]==23333 && (*mvaDmc.Dmass)[j]>masssignal1 && (*mvaDmc.Dmass)[j]<masssignal2) ahPtMCSignal[n]->Fill((*mvaDmc.Dpt)[j]);
		}
	    }
	}
      for(int j=0;j<mvaDmc.Gsize;j++)
        {
          if((TMath::Abs((*mvaDmc.GisSignal)[j])==1 || TMath::Abs((*mvaDmc.GisSignal)[j])==2) && TMath::Abs((*mvaDmc.Gy)[j])<2.0) hPtGenSignal->Fill((*mvaDmc.Gpt)[j]);
        }
    }
  for(n=0;n<NEff;n++)
    {
      ahPtEffSignal[n] = (TH1D*)ahPtMCSignal[n]->Clone(Form("hPtEffSignal_%d",n));
      ahPtEffSignal[n]->Divide(hPtGenSignal);
    }
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<nentriesmc<<"\033[0m event(s)."<<std::endl;

  tmvaD mvaDdata;
  mvaDdata.settrkcut(2.0, 2.0, 0.3);
  mvaDdata.setDcut(2.0, 0.0, 0.2, 0.05, ptmin, ptmax, drmin, drmax);
  mvaDdata.setjetcut(jetptmin, jetetamin, jetetamax);
  TFile* inputdata = TFile::Open(inputdataname);
  TTree* ntdata = (TTree*)inputdata->Get("tmvadjt");
  mvaDdata.setbranchaddress(ntdata);
  Int_t nentriesdata = ntdata->GetEntries();
  std::cout<<"  Filling invariant mass histograms - data..."<<std::endl;
  Int_t* ctSideband = new Int_t[NEff];
  for(n=0;n<NEff;n++) ctSideband[n] = 0;
  for(int i=0;i<nentriesdata;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<nentriesdata<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/nentriesdata)<<"%\033[0m"<<"\r"<<std::flush;
      ntdata->GetEntry(i);
      for(int j=0;j<mvaDdata.Dsize;j++)
	{
	  for(n=0;n<NEff;n++)
	    {
	      mvaDdata.settmvacut(varmaxs[n].at(0),varmins[n].at(1));
	      if(mvaDdata.isselected(j))
		{
		  ahMass[n]->Fill((*mvaDdata.Dmass)[j]);
                  if(TMath::Abs((*mvaDdata.Dmass)[j]-massD)>dmassDsidband1 && TMath::Abs((*mvaDdata.Dmass)[j]-massD)<dmassDsidband2) ctSideband[n]++;
		}
	    }
	}
    }
  for(n=0;n<NEff;n++)
    {
      hSideband->SetBinContent(n+1,ctSideband[n]);      
    }
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<nentriesdata<<"\033[0m event(s)."<<std::endl;
  std::cout<<std::endl;

  // write into the output file
  TFile* outf = new TFile(Form("%s_%s.root",outputsavehist.Data(),outputname.Data()),"recreate");
  outf->cd();
  for(n=0;n<NEff;n++)
    {
      ahMass[n]->Write();
      ahMassMCSignal[n]->Write();
      ahMassMCSwapped[n]->Write();
      ahPtEffSignal[n]->Write();
      ahPtMCSignal[n]->Write();      
    }
  hPtGenSignal->Write();
  hSideband->Write();  
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==13)
    {
      readxml_savehist(argv[1], argv[2], argv[3], argv[4], argv[5], atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]), atof(argv[11]), atof(argv[12]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid argument number - readxml_savehist"<<std::endl;
      return 1;
    }
}
