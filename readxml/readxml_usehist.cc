#include "readxml.h"

void readxml_usehist(TString inputname, TString outputname,
                     TString weightfile, TString collisionsyst,
                     Float_t jetptmin, Float_t jetetamin, Float_t jetetamax,
                     Float_t ptmin, Float_t ptmax, Float_t drmin, Float_t drmax,
                     Float_t lumi, Float_t raa=1)
{
  xjjrootuti::setgstyle();

  std::ofstream ofresult(Form("%s_%s.txt",outputresult.Data(),outputname.Data()),std::ofstream::out);
  cfout cfresult(std::cout, ofresult);

  // read weight file
  const char* filename = weightfile;
  void *doc = TMVA::gTools().xmlengine().ParseFile(filename,TMVA::gTools().xmlenginebuffersize());
  void* rootnode = TMVA::gTools().xmlengine().DocGetRootElement(doc); // node "MethodSetup"
  TString fullMethodName("");
  TMVA::gTools().ReadAttr(rootnode, "Method", fullMethodName);
  
  cfresult<<std::endl;
  cfresult<<"  ===================================================="<<std::endl;
  cfresult<<" |                Cut Opt Configuration               |"<<std::endl;
  cfresult<<"  ----------------------------------------------------"<<std::endl;
  cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(10)<<"Method"<<" | "<<std::setw(28)<<fullMethodName<<" | "<<std::setw(6)<<" "<<" |"<<std::endl;

  void* opts = TMVA::gTools().GetChild(rootnode,"Options");
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
      cfresult<<"  ----------------------------------------------------"<<std::endl;
      cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(10)<<tem<<" | "<<std::setw(28)<<varname<<" | "<<std::setw(6)<<margins[k]<<" |"<<std::endl;
      var = TMVA::gTools().GetNextChild(var);
      varnames.push_back(varname);
    }
  cfresult<<"  ===================================================="<<std::endl;
    
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

  // Fit mass
  TFile* inf = TFile::Open(Form("%s_%s.root",outputsavehist.Data(),inputname.Data()));
  TH1D** ahMass = new TH1D*[NEff];
  TH1D** ahMassMCSignal = new TH1D*[NEff];
  TH1D** ahMassMCSwapped = new TH1D*[NEff];
  Float_t maxsig_fit = 0;
  Int_t maxindex_fit = 0;
  for(n=0;n<NEff;n++)
    {
      ahMass[n] = (TH1D*)inf->Get(Form("hMass_%d",n));
      ahMassMCSignal[n] = (TH1D*)inf->Get(Form("hMassMCSignal_%d",n));
      ahMassMCSwapped[n] = (TH1D*)inf->Get(Form("hMassMCSwapped_%d",n));
      Float_t* results = new Float_t[2];
      fit(ahMass[n], ahMassMCSignal[n], ahMassMCSwapped[n], Form("%s_%s_%d",outputfit.Data(),outputname.Data(),n), results, collisionsyst, jetptmin, jetetamin, jetetamax, ptmin, ptmax, drmin, drmax, false);
      aSfit[n] = results[0];
      aBfit[n] = results[1];
      if(aSfit[n]<=0 || aBfit[n]<=0 || n<2) aSigfit[n] = 0; // set some limits
      else aSigfit[n] = aSfit[n]/TMath::Sqrt(aSfit[n]+aBfit[n]);
      if(aSigfit[n]>maxsig_fit)
	{
	  maxsig_fit = aSigfit[n];
	  maxindex_fit = n;
	}
    }
  Float_t* resultmax = new Float_t[2];
  fit(ahMass[maxindex_fit], ahMassMCSignal[maxindex_fit], ahMassMCSwapped[maxindex_fit], Form("%s_%s_%d",outputfitmax.Data(),outputname.Data(),maxindex_fit), resultmax, collisionsyst, jetptmin, jetetamin, jetetamax, ptmin, ptmax, drmin, drmax, false, false);

  // fonll prediction
  std::ifstream getdata("fonlls/fo_Dzero_5p02TeV_y2.dat");
  if(!getdata.is_open()) std::cout<<"Opening the file fails"<<std::endl;
  for(int i=0;i<NFonll;i++) getdata>>fpt[i]>>fcentral[i];
  TH1D* hfonll = new TH1D("hfonll",";D p_{T} (GeV/c);FONLL differential xsection",NFonll,MINFonll,MAXFonll);
  Double_t iptmin = -1, iptmax = -1;
  for(int i=0;i<NFonll;i++)
    {
      if(fpt[i]==ptmin) iptmin = i;
      if(fpt[i]==ptmax) iptmax = i;
      hfonll->SetBinContent(i,fcentral[i]);
    }
  if(iptmin<0 || iptmax<0)
    {
      std::cout<<" Error: invalid FONLL binning"<<std::endl;
      return;
    }
  /*
  TCanvas* cfonll = new TCanvas("cfonll","",600,600);
  cfonll->SetLogy();
  hfonll->Draw();
  cfonll->SaveAs(Form("%s_%s.pdf",outputfonll.Data(),outputname.Data()));
  */

  TH1D** ahPtEffSignal = new TH1D*[NEff];
  TH1D** ahPtRecoSignal = new TH1D*[NEff];
  TH1D* hSideband = (TH1D*)inf->Get("hSideband");
  Float_t maxsig_fonll = 0;
  Int_t maxindex_fonll = 0;
  for(n=0;n<NEff;n++)
    {
      ahPtEffSignal[n] = (TH1D*)inf->Get(Form("hPtEffSignal_%d",n));
      ahPtRecoSignal[n] = new TH1D(Form("hPtRecoSigna_%d",n),"",NFonll,MINFonll,MAXFonll);
      ahPtRecoSignal[n]->Multiply(hfonll,ahPtEffSignal[n],1,1,"B");
      aSfonll[n] = ahPtRecoSignal[n]->Integral(iptmin+1,iptmax+1)*lumi*norm*BR*deltapt*raa*2;//2: D0+D0bar
      aBfonll[n] = hSideband->GetBinContent(n+1)*dmassDsignal/(dmassDsidband2-dmassDsidband1);
      aSigfonll[n] = aSfonll[n]/TMath::Sqrt(aSfonll[n]+aBfonll[n]);
      if(aSigfit[n]>maxsig_fonll)
        {
          maxsig_fonll = aSigfonll[n];
          maxindex_fonll = n;
        }
    }

  // Print out opt results
  cfresult<<std::endl;
  cfresult<<"  =========================================================="<<std::endl;
  cfresult<<" |                         Opt Result                       |"<<std::endl;
  cfresult<<"  ----------------------------------------------------------"<<std::endl;
  cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(15)<<"pT"<<" | "<<std::setw(38)<<Form("%.0f - %.0f GeV/c",ptmin,ptmax)<<" |"<<std::endl;
  cfresult<<"  ----------------------------------------------------------"<<std::endl;
  cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(15)<<"delta R"<<" | "<<std::setw(38)<<Form("%.2f - %.2f",drmin,drmax)<<" |"<<std::endl;
  cfresult<<"  ----------------------------------------------------------"<<std::endl;
  cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(15)<<"S (fit)"<<" | "<<std::setw(9)<<Form("%.0f",aSfit[maxindex_fit])<<" | "<<std::setw(13)<<"B (fit)"<<" | "<<std::setw(10)<<Form("%.0f",aBfit[maxindex_fit])<<" |"<<std::endl;
  cfresult<<"  ----------------------------------------------------------"<<std::endl;
  cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(15)<<"effS (fit)"<<" | "<<std::setw(9)<<effS[maxindex_fit]<<" | "<<std::setw(13)<<"sig (fit)"<<" | "<<std::setw(10)<<Form("%.2f",aSigfit[maxindex_fit])<<" |"<<std::endl;
  cfresult<<"  ----------------------------------------------------------"<<std::endl;
  for(unsigned int m=0;m<nVar;m++)
    {
      if(m) cfresult<<"  ----------------------------------------------------------"<<std::endl;
      cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(35)<<varnames.at(m)<<" | "<<std::setw(18)<<varmins[maxindex_fit].at(m)<<" |"<<std::endl;
      cfresult<<"  ----------------------------------------------------------"<<std::endl;
      cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(35)<<" "<<" | "<<std::setw(18)<<varmaxs[maxindex_fit].at(m)<<" |"<<std::endl;
    }
  cfresult<<"  ----------------------------------------------------------"<<std::endl;
  cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(15)<<"S (fonll)"<<" | "<<std::setw(9)<<Form("%.0f",aSfonll[maxindex_fonll])<<" | "<<std::setw(13)<<"B (fonll)"<<" | "<<std::setw(10)<<Form("%.0f",aBfonll[maxindex_fonll])<<" |"<<std::endl;
  cfresult<<"  ----------------------------------------------------------"<<std::endl;
  cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(15)<<"effS (fonll)"<<" | "<<std::setw(9)<<effS[maxindex_fonll]<<" | "<<std::setw(13)<<"sig (fonll)"<<" | "<<std::setw(10)<<Form("%.2f",aSigfonll[maxindex_fonll])<<" |"<<std::endl;
  cfresult<<"  ----------------------------------------------------------"<<std::endl;
  for(unsigned int m=0;m<nVar;m++)
    {
      if(m) cfresult<<"  ----------------------------------------------------------"<<std::endl;
      cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(35)<<varnames.at(m)<<" | "<<std::setw(18)<<varmins[maxindex_fonll].at(m)<<" |"<<std::endl;
      cfresult<<"  ----------------------------------------------------------"<<std::endl;
      cfresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(35)<<" "<<" | "<<std::setw(18)<<varmaxs[maxindex_fonll].at(m)<<" |"<<std::endl;
    }
  cfresult<<"  =========================================================="<<std::endl;
  cfresult<<std::endl;
  
  // test region
  ofresult<<"  ======================================================================================================="<<std::endl;
  ofresult<<" |                                              Test Region                                              |"<<std::endl;
  ofresult<<"  -------------------------------------------------------------------------------------------------------"<<std::endl;
  ofresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(15)<<"aSfit"<<"| "<<std::setw(15)<<"aSfonll"<<"| "<<std::setw(15)<<"aSfonll/aSfit"<<"||  "<<std::setw(15)<<"aBfit"<<"| "<<std::setw(15)<<"aBfonll"<<"| "<<std::setw(15)<<"aBfonll/aBfit"<<"|"<<std::endl;
  for(n=0;n<NEff;n++)
    {
      ofresult<<" | "<<std::setiosflags(std::ios::left)<<std::setw(15)<<aSfit[n]<<"| "<<std::setw(15)<<aSfonll[n]<<"| "<<std::setw(15)<<aSfonll[n]/aSfit[n]<<"||  "<<std::setw(15)<<aBfit[n]<<"| "<<std::setw(15)<<aBfonll[n]<<"| "<<std::setw(15)<<aBfonll[n]/aBfit[n]<<"|"<<std::endl;
    }
  ofresult<<"  ======================================================================================================="<<std::endl;

  ofresult.close();

  // final plots
  TH2F* hempty = new TH2F("hempty",";Signal efficiency;S / #sqrt{S+B}",50,0,1.,10,0.,aSigfit[maxindex_fit]*1.4);
  xjjrootuti::sethempty(hempty);

  TLatex* texD = new TLatex(0.22,0.855, "D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
  xjjrootuti::settex(texD, 0.04, 12);
  TLatex* texJeteta = new TLatex(0.22,0.79, Form("%s < |#eta^{jet}| < %s",xjjuti::number_remove_zero(jetetamin).c_str(),xjjuti::number_remove_zero(jetetamax).c_str()));
  xjjrootuti::settex(texJeteta, 0.04, 12);
  TLatex* texJetpt = new TLatex(0.22,0.725, Form("|p_{T}^{jet}| > %s",xjjuti::number_remove_zero(jetptmin).c_str()))
  xjjrootuti::settex(texJetpt, 0.04, 12);  
  TLatex* texPt = new TLatex(0.92,0.84, Form("%s < p_{T}^{D} < %s GeV/c",xjjuti::number_remove_zero(ptmin).c_str(),xjjuti::number_remove_zero(ptmax).c_str()));
  xjjrootuti::settex(texPt, 0.04, 32);
  TLatex* texY = new TLatex(0.92,0.79, "|y^{D}| < 2");
  xjjrootuti::settex(texY, 0.04, 32);
  TLatex* texDr = new TLatex(0.92,0.725, Form("%s < #DeltaR < %s",xjjuti::number_remove_zero(drmin).c_str(),xjjuti::number_remove_zero(drmax).c_str()));
  xjjrootuti::settex(texDr, 0.04, 32);

  TGraph* gsig_fit = new TGraph(NEff, effS, aSigfit);
  gsig_fit->SetName("gsig");
  gsig_fit->SetMarkerColor(kBlack);
  TGraph* gsig_fonll = new TGraph(NEff, effS, aSigfonll);
  gsig_fonll->SetName("gsig");
  gsig_fonll->SetMarkerColor(kRed);
  TCanvas* csig = new TCanvas("csig","",600,600);
  hempty->Draw();
  xjjrootuti::drawCMS(collisionsyst);
  texD->Draw();
  texY->Draw();
  texPt->Draw();
  texDr->Draw();
  texJetpt->Draw();
  texJeteta->Draw();
  gsig_fit->Draw("same*");
  //gsig_fonll->Draw("same*");
  csig->SaveAs(Form("%s_%s.pdf",outputsignificance.Data(),outputname.Data()));
  
}

int main(int argc, char* argv[])
{
  if(argc==14)
    {
      readxml_usehist(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]), atof(argv[11]), atof(argv[12]), atof(argv[13]));
      return 0;
    }
  else if(argc==13)
    {
      readxml_usehist(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]), atof(argv[11]), atof(argv[12]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid argument number - readxml_usehist"<<std::endl;
      return 1;
    }
}
