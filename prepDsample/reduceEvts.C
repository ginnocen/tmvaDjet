#include <iostream>
#include <iomanip>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

int reduceEvts(TString ifname, TString ofname, Float_t size=0.1)
{
  if(ifname==ofname)
    {
      std::cout<<"    Error: Input file will be overwritten."<<std::endl;
      return 1;
    }
  if(size>1)
    {
      std::cout<<"    Error: Float_t size should be < 1"<<std::endl;
      return 0;
    }

  TFile* inf = TFile::Open(ifname);
  TTree* intree = (TTree*)inf->Get("tmvadjt");
  TFile* outf = TFile::Open(ofname,"recreate");
  TTree* outtree = intree->CloneTree(0);

  Long64_t nentries = intree->GetEntries();
  Int_t interval = (int)(1./size);
  for(Long64_t i=0;i<nentries;i+=interval)
    {
      if(i%1000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<nentries<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/nentries)<<"%\033[0m"<<"\r"<<std::flush;
      intree->GetEntry(i);
      outtree->Fill();
    }
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<nentries<<"\033[0m event(s)."<<std::endl;
  outf->Write();
  outf->Close();

  return 0;

}

int main(int argc, char* argv[])
{
  if(argc==4)
    {
      reduceEvts(argv[1], argv[2], atof(argv[3]));
      return 0;
    }
  else
    {
      std::cout<<"  Error: invalid arguments number - reduceEvts()"<<std::endl;
      return 1;
    }
}
