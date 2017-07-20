#include "includes/uti.h"
#include "includes/d_jet.h"
#include "includes/d_jet.C"
#include "includes/prepD.h"

Bool_t istest = false;
void prepDsample(string inputname="", string outputname="", Int_t isMC=1, Float_t jetptcut=80, Float_t jetetamincut=0.0, Float_t jetetamaxcut=2.0, Int_t maxevt=-1)
{
  if(istest)
    {
      inputname = "/export/d00/scratch/jwang/Djets/MC/DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root";
      outputname = "test.root";
      isMC = 1;
      jetptcut = 80;
      jetetamincut = 0.3;
      jetetamaxcut = 1.6;
      maxevt = 100000;
    }

  std::cout<<std::endl;
  djet djt(inputname);

  TFile* outf = new TFile(outputname.c_str(), "recreate");
  TTree* outtree = new TTree("tmvadjt","");
  prepD pd(outtree);

  int64_t nentries = djt.fChain->GetEntriesFast();
  int rnentries = (maxevt>0&&istest&&maxevt<=nentries)?maxevt:nentries;
  for(int i=0;i<rnentries;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<rnentries<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/rnentries)<<"%\033[0m"<<"\r"<<std::flush;
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
		  Float_t deltaetaref = (*djt.Deta)[jd] + (*djt.jeteta_akpu3pf)[jj];
		  Float_t deltaRref = TMath::Sqrt(pow(deltaphi, 2) + pow(deltaetaref, 2));
		  pd.copy_index(djt,jd,jj,deltaR,deltaRref);
		  dsize++;
		}
	    }
	}

      int gsize = 0;
      if(isMC)
        {
          for(int jd=0;jd<djt.Gsize;jd++)
            {
              pd.copy_gen_index(djt,jd);
              gsize++;
            }
        }

      pd.copy_variables(djt,dsize,gsize);
      outtree->Fill();
    }
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<rnentries<<"\033[0m out of\033[1;31m "<<nentries<<"\033[0m event(s)."<<std::endl;

  outf->cd();
  outtree->Write();
  outf->Write();
  outf->Close();

}

int main(int argc, char* argv[])
{
  if(argc==8)
    {
      prepDsample(argv[1], argv[2], atoi(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atoi(argv[7]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - prepDsample()"<<std::endl;
      return 1;
    }
}
