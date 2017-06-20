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
  int rnentries = (maxevt>0&&istest&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%100000==0) cout<<left<<"  "<<setw(10)<<i<<" / "<<rnentries<<" , "<<nentries<<endl;
      pd.clear_vectors();
      //
      djt.fChain->GetEntry(i);
      //
      //if(!(djt.Dsize>0 && djt.njet_akpu3pf)) continue;

      int dsize = 0;
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
		  dsize++;
		}
	    }
	}

      int gsize = 0;
      for(int jd=0;jd<djt.Gsize;jd++)
	{
          pd.copy_gen_index(djt,jd);
          gsize++;
	}

      pd.copy_variables(djt,dsize,gsize);
      outtree->Fill();
    }

  outf->cd();
  outtree->Write();
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==7)
    {
      prepDsample(argv[1], argv[2], atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]));
      return 0;
    }
  else
    {
      cout<<"  Error: invalid arguments number - prepDsample()"<<endl;
      return 1;
    }
}
