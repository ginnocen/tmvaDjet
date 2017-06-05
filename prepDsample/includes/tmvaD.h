#ifndef _TMVAD_H
#define _TMVAD_H

using namespace std;
#include "uti.h"

class tmvaD
{
 public:

  int                 isPP;
  uint32_t            run;
  unsigned long long  evt;
  uint32_t            lumi;
  int                 hiBin;
  float               vz;
  float               weight;
  float               pthat;
  int                 RunNo;
  int                 EvtNo;
  int                 LumiNo;
  int                 Dsize;
  float               PVx;
  float               PVy;
  float               PVz;
  float               PVnchi2;  

  std::vector<int>       Dindex;
  std::vector<float>     Dmass;
  std::vector<float>     Dpt;
  std::vector<float>     Deta;
  std::vector<float>     Dphi;
  std::vector<float>     Dy;
  std::vector<float>     Dchi2ndf;
  std::vector<float>     Dchi2cl;
  std::vector<float>     Ddtheta;
  std::vector<float>     Dlxy;
  std::vector<float>     Dalpha;
  std::vector<float>     DsvpvDistance;
  std::vector<float>     DsvpvDisErr;
  std::vector<float>     DsvpvDistance_2D;
  std::vector<float>     DsvpvDisErr_2D;
  std::vector<float>     DlxyBS;
  std::vector<float>     DlxyBSErr;
  std::vector<float>     DMaxDoca;
  std::vector<float>     Dtrk1Pt;
  std::vector<float>     Dtrk2Pt;
  std::vector<float>     Dtrk1Eta;
  std::vector<float>     Dtrk2Eta;
  std::vector<float>     Dtrk1Phi;
  std::vector<float>     Dtrk2Phi;
  std::vector<float>     Dtrk1PtErr;
  std::vector<float>     Dtrk2PtErr;
  std::vector<float>     Dtrk1Dxy;
  std::vector<float>     Dtrk2Dxy;
  std::vector<float>     Dtrk1PixelHit;
  std::vector<float>     Dtrk2PixelHit;
  std::vector<float>     Dtrk1StripHit;
  std::vector<float>     Dtrk2StripHit;
  std::vector<float>     Dtrk1nStripLayer;
  std::vector<float>     Dtrk2nStripLayer;
  std::vector<float>     Dtrk1nPixelLayer;
  std::vector<float>     Dtrk2nPixelLayer;
  std::vector<float>     Dtrk1Chi2ndf;
  std::vector<float>     Dtrk2Chi2ndf;
  std::vector<float>     Dtrk1MassHypo;
  std::vector<float>     Dtrk2MassHypo;
  std::vector<int>       Dtrk1Algo;
  std::vector<int>       Dtrk2Algo;
  std::vector<int>       Dtrk1originalAlgo;
  std::vector<int>       Dtrk2originalAlgo;
  std::vector<bool>      Dtrk1highPurity;
  std::vector<bool>      Dtrk2highPurity;
  std::vector<float>     Dtrk1EtaErr;
  std::vector<float>     Dtrk2EtaErr;
  std::vector<float>     Dtrk1PhiErr;
  std::vector<float>     Dtrk2PhiErr;
  std::vector<float>     Dtrk1Y;
  std::vector<float>     Dtrk2Y;

  std::vector<float>     Dgen;
  std::vector<int>       DgencollisionId;

  // constructors
  tmvaD()
    {
      isPP = 0;
      run = 0;
      evt = 0;
      lumi = 0;
      hiBin = -1;
      vz = -99;
      weight = -1;
      pthat = -1;
      
      RunNo = -99;
      EvtNo = -99;
      LumiNo = -99;
      Dsize = -99;
      PVx = -99;
      PVy = -99;
      PVz = -99;
      PVnchi2 = -99;
    }
  /*
    tmvaD(TTree* t) : tmvaD() 
    {
    this->create_tree(t);
    }
  */
  ~tmvaD() {};
  
  void create_tree(TTree* t);


};

void tmvaD::create_tree(TTree* t) 
{
  t->Branch("isPP", &isPP, "isPP/I");
  t->Branch("run", &run, "run/I");
  t->Branch("evt", &evt, "evt/l");
  t->Branch("lumi", &lumi, "lumi/i");
  t->Branch("hiBin", &hiBin, "hiBin/I");
  t->Branch("vz", &vz, "vz/F");
  t->Branch("weight", &weight, "weight/F");
  t->Branch("pthat", &pthat, "pthat/F");

  t->Branch("RunNo", &RunNo, "RunNo/I");
  t->Branch("EvtNo", &EvtNo, "EvtNo/I");
  t->Branch("LumiNo", &LumiNo, "LumiNo/I");
  t->Branch("Dsize", &Dsize, "Dsize/I");
  t->Branch("PVx", &PVx, "PVx/F");
  t->Branch("PVy", &PVy, "PVy/F");
  t->Branch("PVz", &PVz, "PVz/F");
  t->Branch("PVnchi2", &PVnchi2, "PVnchi2/F");

  t->Branch("Dindex", &Dindex);
  t->Branch("Dmass", &Dmass);
  t->Branch("Dpt", &Dpt);
  t->Branch("Deta", &Deta);
  t->Branch("Dphi", &Dphi);
  t->Branch("Dy", &Dy);
  t->Branch("Dchi2ndf", &Dchi2ndf);
  t->Branch("Dchi2cl", &Dchi2cl);
  t->Branch("Ddtheta", &Ddtheta);
  t->Branch("Dlxy", &Dlxy);
  t->Branch("Dalpha", &Dalpha);
  t->Branch("DsvpvDistance", &DsvpvDistance);
  t->Branch("DsvpvDisErr", &DsvpvDisErr);
  t->Branch("DsvpvDistance_2D", &DsvpvDistance_2D);
  t->Branch("DsvpvDisErr_2D", &DsvpvDisErr_2D);
  t->Branch("DlxyBS", &DlxyBS);
  t->Branch("DlxyBSErr", &DlxyBSErr);
  t->Branch("DMaxDoca", &DMaxDoca);
  t->Branch("Dtrk1Pt", &Dtrk1Pt);
  t->Branch("Dtrk2Pt", &Dtrk2Pt);
  t->Branch("Dtrk1Eta", &Dtrk1Eta);
  t->Branch("Dtrk2Eta", &Dtrk2Eta);
  t->Branch("Dtrk1Phi", &Dtrk1Phi);
  t->Branch("Dtrk2Phi", &Dtrk2Phi);
  t->Branch("Dtrk1PtErr", &Dtrk1PtErr);
  t->Branch("Dtrk2PtErr", &Dtrk2PtErr);
  t->Branch("Dtrk1Dxy", &Dtrk1Dxy);
  t->Branch("Dtrk2Dxy", &Dtrk2Dxy);
  t->Branch("Dtrk1PixelHit", &Dtrk1PixelHit);
  t->Branch("Dtrk2PixelHit", &Dtrk2PixelHit);
  t->Branch("Dtrk1StripHit", &Dtrk1StripHit);
  t->Branch("Dtrk2StripHit", &Dtrk2StripHit);
  t->Branch("Dtrk1nStripLayer", &Dtrk1nStripLayer);
  t->Branch("Dtrk2nStripLayer", &Dtrk2nStripLayer);
  t->Branch("Dtrk1nPixelLayer", &Dtrk1nPixelLayer);
  t->Branch("Dtrk2nPixelLayer", &Dtrk2nPixelLayer);
  t->Branch("Dtrk1Chi2ndf", &Dtrk1Chi2ndf);
  t->Branch("Dtrk2Chi2ndf", &Dtrk2Chi2ndf);
  t->Branch("Dtrk1MassHypo", &Dtrk1MassHypo);
  t->Branch("Dtrk2MassHypo", &Dtrk2MassHypo);
  t->Branch("Dtrk1Algo", &Dtrk1Algo);
  t->Branch("Dtrk2Algo", &Dtrk2Algo);
  t->Branch("Dtrk1originalAlgo", &Dtrk1originalAlgo);
  t->Branch("Dtrk2originalAlgo", &Dtrk2originalAlgo);
  t->Branch("Dtrk1highPurity", &Dtrk1highPurity);
  t->Branch("Dtrk2highPurity", &Dtrk2highPurity);
  t->Branch("Dtrk1EtaErr", &Dtrk1EtaErr);
  t->Branch("Dtrk2EtaErr", &Dtrk2EtaErr);
  t->Branch("Dtrk1PhiErr", &Dtrk1PhiErr);
  t->Branch("Dtrk2PhiErr", &Dtrk2PhiErr);
  t->Branch("Dtrk1Y", &Dtrk1Y);
  t->Branch("Dtrk2Y", &Dtrk2Y);

  t->Branch("Dgen", &Dgen);
  t->Branch("DgencollisionId", &DgencollisionId);
}


#endif
