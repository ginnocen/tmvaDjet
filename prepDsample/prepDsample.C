using namespace std;
#include "includes/uti.h"
#include "includes/d_jet.h"
#include "includes/d_jet.C"
#include "includes/prepD.h"

Bool_t istest = false;
void prepDsample(string inputname="", string outputname="", Float_t jetptcut=80, Float_t jetetamincut=0.3, Float_t jetetamaxcut=1.6, Int_t maxevt=-1)
{
  if(istest)
    {
      inputname = "/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root";
      outputname = "test.root";
      jetptcut = 80;
      jetetamincut = 0.3;
      jetetamaxcut = 1.6;
      maxevt = 100000;
    }

  djet djt(inputname);

  TFile* outf = new TFile(outputname.c_str(), "recreate");
  TTree* outtree = new TTree("tmvadjt","");
  prepD pd(outtree);

  int64_t nentries = djt.fChain->GetEntriesFast();
  nentries = (maxevt>0&&istest)?maxevt:nentries;
  for(int i=0;i<nentries;i++)
    {
      if(i%100000==0) cout<<left<<"  "<<setw(10)<<i<<" / "<<nentries<<endl;
      pd.clear_vectors();
      //
      djt.fChain->GetEntry(i);
      //
      if(!(djt.Dsize>0 && djt.njet_akpu3pf)) continue;
      int size = 0;
      for(int jd=0;jd<djt.Dsize;jd++)
	{
	  for(int jj=0;jj<djt.njet_akpu3pf;jj++)
	    {
	      if((*djt.jetptCorr_akpu3pf)[jj] > jetptcut && fabs((*djt.jeteta_akpu3pf)[jj]) > jetetamincut && fabs((*djt.jeteta_akpu3pf)[jj]) < jetetamaxcut)
		{
		  Float_t deltaphi = TMath::ACos(TMath::Cos((*djt.Dphi)[jd] - (*djt.jetphi_akpu3pf)[jj]));
		  Float_t deltaeta = (*djt.Deta)[jd] - (*djt.jeteta_akpu3pf)[jj];
		  Float_t deltaR = TMath::Sqrt(pow(deltaphi, 2) + pow(deltaeta, 2));
		  pd.copy_index(djt,jd,deltaR);
		  size++;
		}
	    }
	}
      pd.copy_variables(djt,size);
      outtree->Fill();
    }

  outf->cd();
  outtree->Write();
  outf->Write();
  outf->Close();

}
