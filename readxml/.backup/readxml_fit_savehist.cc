using namespace std;

#include "readxml.h"
#include "tmvaD.h"
#include "Tools.h"
#include "../uti.h"

void readxml_fit_savehist(TString inputmcname, TString inputdataname, TString outputname,
                          TString weightfile, TString collisionsyst, 
                          Float_t ptmin, Float_t ptmax, Float_t drmin, Float_t drmax)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  //read weight file
  const char* filename = weightfile;
  void *doc = TMVA::gTools().xmlengine().ParseFile(filename,TMVA::gTools().xmlenginebuffersize());
  void* rootnode = TMVA::gTools().xmlengine().DocGetRootElement(doc); // node "MethodSetup"
  TString fullMethodName("");
  TMVA::gTools().ReadAttr(rootnode, "Method", fullMethodName);

  cout<<endl;
  cout<<"  ===================================================="<<endl;
  cout<<" |                Cut Opt Configuration               |"<<endl;
  cout<<"  ----------------------------------------------------"<<endl;
  cout<<" | "<<left<<setw(10)<<"Method"<<" | "<<setw(28)<<fullMethodName<<" | "<<setw(6)<<" "<<" |"<<endl;

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

  TObjArray *marginclass = varProp.Tokenize(" ");
  std::vector<TString> margins;//avoid objarrays
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
      cout<<"  ----------------------------------------------------"<<endl;
      cout<<" | "<<left<<setw(10)<<tem<<" | "<<setw(28)<<varname<<" | "<<setw(6)<<margins[k]<<" |"<<endl;
      var = TMVA::gTools().GetNextChild(var);
      varnames.push_back(varname);
    }
  cout<<"  ===================================================="<<endl;
    
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
  for(n=0;n<NEff;n++)
    {
      ahMass[n] = new TH1D(Form("hMass_%d",n),"",60,1.7,2.0);
      ahMassMCSignal[n] = new TH1D(Form("hMassMCSignal_%d",n),"",60,1.7,2.0);
      ahMassMCSwapped[n] = new TH1D(Form("hMassMCSwapped_%d",n),"",60,1.7,2.0);
    }

  tmvaD mvaDmc;
  mvaDmc.settrkcut(2.0, 2.0, 0.3);
  mvaDmc.setDcut(2.0, 0.0, 0.2, 0.05, ptmin, ptmax, drmin, drmax);
  TFile* inputmc = TFile::Open(inputmcname);
  TTree* ntmc = (TTree*)inputmc->Get("tmvadjt");
  mvaDmc.setbranchaddress(ntmc);
  Int_t nentriesmc = ntmc->GetEntries();
  cout<<endl;
  cout<<"  Filling invariant mass histograms - MC..."<<endl;
  for(int i=0;i<nentriesmc;i++)
    {
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
		}
	    }
	}
    }

  tmvaD mvaDdata;
  mvaDdata.settrkcut(2.0, 2.0, 0.3);
  mvaDdata.setDcut(2.0, 0.0, 0.2, 0.05, ptmin, ptmax, drmin, drmax);
  TFile* inputdata = TFile::Open(inputdataname);
  TTree* ntdata = (TTree*)inputdata->Get("tmvadjt");
  mvaDdata.setbranchaddress(ntdata);
  Int_t nentriesdata = ntdata->GetEntries();
  cout<<"  Filling invariant mass histograms - data..."<<endl;
  for(int i=0;i<nentriesdata;i++)
    {
      ntdata->GetEntry(i);
      for(int j=0;j<mvaDdata.Dsize;j++)
	{
	  for(n=0;n<NEff;n++)
	    {
	      mvaDdata.settmvacut(varmaxs[n].at(0),varmins[n].at(1));
	      if(mvaDdata.isselected(j))
		{
		  ahMass[n]->Fill((*mvaDdata.Dmass)[j]);
		}
	    }
	}
    }

  TFile* outf = new TFile(Form("%s_%s.root",outputsavehist.Data(),outputname.Data()),"recreate");
  outf->cd();
  for(n=0;n<NEff;n++)
    {
      ahMass[n]->Write();
      ahMassMCSignal[n]->Write();
      ahMassMCSwapped[n]->Write();
    }
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==10)
    {
      readxml_fit_savehist(argv[1],argv[2],argv[3],argv[4],argv[5],atof(argv[6]),atof(argv[7]),atof(argv[8]),atof(argv[9]));
      return 0;
    }
  else
    {
      cout<<"  Error: invalid argument number - readxml_savehist"<<endl;
      return 1;
    }
}
