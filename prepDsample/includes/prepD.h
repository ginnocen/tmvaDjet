#ifndef _PREPD_H
#define _PREPD_H

using namespace std;
#include "uti.h"
#include "d_jet.h"

class prepD
{
 public:

  int                 isPP;
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

  std::vector<float>     DdeltaR;

  // constructors
  prepD()
    {
      isPP = 0;
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
  
  prepD(TTree* t) : prepD() 
    {
      this->create_tree(t);
    }
  
  ~prepD() {};
  
  void create_tree(TTree* t);
  void copy_variables(djet dt, int size);
  void copy_index(djet dt, int i, float dR);
  void clear_vectors();

};

void prepD::create_tree(TTree* t) 
{
  t->Branch("isPP", &isPP, "isPP/I");
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

  t->Branch("DdeltaR", &DdeltaR);
}

void prepD::copy_variables(djet dt, int size)
{
  isPP = dt.isPP;
  hiBin = dt.hiBin;
  vz = dt.vz;
  weight = dt.weight;
  pthat = dt.pthat;
  RunNo = dt.RunNo;
  EvtNo = dt.EvtNo;
  LumiNo = dt.LumiNo;
  Dsize = size;
  PVx = dt.PVx;
  PVy = dt.PVy;
  PVz = dt.PVz;
  PVnchi2 = dt.PVnchi2;
}

void prepD::copy_index(djet dt, int i, float dR)
{
  Dindex.push_back((*dt.Dindex)[i]);
  Dmass.push_back((*dt.Dmass)[i]);
  Dpt.push_back((*dt.Dpt)[i]);
  Deta.push_back((*dt.Deta)[i]);
  Dphi.push_back((*dt.Dphi)[i]);
  Dy.push_back((*dt.Dy)[i]);
  Dchi2ndf.push_back((*dt.Dchi2ndf)[i]);
  Dchi2cl.push_back((*dt.Dchi2cl)[i]);
  Ddtheta.push_back((*dt.Ddtheta)[i]);
  Dlxy.push_back((*dt.Dlxy)[i]);
  Dalpha.push_back((*dt.Dalpha)[i]);
  DsvpvDistance.push_back((*dt.DsvpvDistance)[i]);
  DsvpvDisErr.push_back((*dt.DsvpvDisErr)[i]);
  DsvpvDistance_2D.push_back((*dt.DsvpvDistance_2D)[i]);
  DsvpvDisErr_2D.push_back((*dt.DsvpvDisErr_2D)[i]);
  DlxyBS.push_back((*dt.DlxyBS)[i]);
  DlxyBSErr.push_back((*dt.DlxyBSErr)[i]);
  DMaxDoca.push_back((*dt.DMaxDoca)[i]);
  Dtrk1Pt.push_back((*dt.Dtrk1Pt)[i]);
  Dtrk2Pt.push_back((*dt.Dtrk2Pt)[i]);
  Dtrk1Eta.push_back((*dt.Dtrk1Eta)[i]);
  Dtrk2Eta.push_back((*dt.Dtrk2Eta)[i]);
  Dtrk1Phi.push_back((*dt.Dtrk1Phi)[i]);
  Dtrk2Phi.push_back((*dt.Dtrk2Phi)[i]);
  Dtrk1PtErr.push_back((*dt.Dtrk1PtErr)[i]);
  Dtrk2PtErr.push_back((*dt.Dtrk2PtErr)[i]);
  Dtrk1Dxy.push_back((*dt.Dtrk1Dxy)[i]);
  Dtrk2Dxy.push_back((*dt.Dtrk2Dxy)[i]);
  Dtrk1PixelHit.push_back((*dt.Dtrk1PixelHit)[i]);
  Dtrk2PixelHit.push_back((*dt.Dtrk2PixelHit)[i]);
  Dtrk1StripHit.push_back((*dt.Dtrk1StripHit)[i]);
  Dtrk2StripHit.push_back((*dt.Dtrk2StripHit)[i]);
  Dtrk1nStripLayer.push_back((*dt.Dtrk1nStripLayer)[i]);
  Dtrk2nStripLayer.push_back((*dt.Dtrk2nStripLayer)[i]);
  Dtrk1nPixelLayer.push_back((*dt.Dtrk1nPixelLayer)[i]);
  Dtrk2nPixelLayer.push_back((*dt.Dtrk2nPixelLayer)[i]);
  Dtrk1Chi2ndf.push_back((*dt.Dtrk1Chi2ndf)[i]);
  Dtrk2Chi2ndf.push_back((*dt.Dtrk2Chi2ndf)[i]);
  Dtrk1MassHypo.push_back((*dt.Dtrk1MassHypo)[i]);
  Dtrk2MassHypo.push_back((*dt.Dtrk2MassHypo)[i]);
  Dtrk1Algo.push_back((*dt.Dtrk1Algo)[i]);
  Dtrk2Algo.push_back((*dt.Dtrk2Algo)[i]);
  Dtrk1originalAlgo.push_back((*dt.Dtrk1originalAlgo)[i]);
  Dtrk2originalAlgo.push_back((*dt.Dtrk2originalAlgo)[i]);
  Dtrk1highPurity.push_back((*dt.Dtrk1highPurity)[i]);
  Dtrk2highPurity.push_back((*dt.Dtrk2highPurity)[i]);
  Dtrk1EtaErr.push_back((*dt.Dtrk1EtaErr)[i]);
  Dtrk2EtaErr.push_back((*dt.Dtrk2EtaErr)[i]);
  Dtrk1PhiErr.push_back((*dt.Dtrk1PhiErr)[i]);
  Dtrk2PhiErr.push_back((*dt.Dtrk2PhiErr)[i]);
  Dtrk1Y.push_back((*dt.Dtrk1Y)[i]);
  Dtrk2Y.push_back((*dt.Dtrk2Y)[i]);

  Dgen.push_back((*dt.Dgen)[i]);
  DgencollisionId.push_back((*dt.DgencollisionId)[i]);

  DdeltaR.push_back(dR);
}

void prepD::clear_vectors()
{
  Dindex.clear();
  Dmass.clear();
  Dpt.clear();
  Deta.clear();
  Dphi.clear();
  Dy.clear();
  Dchi2ndf.clear();
  Dchi2cl.clear();
  Ddtheta.clear();
  Dlxy.clear();
  Dalpha.clear();
  DsvpvDistance.clear();
  DsvpvDisErr.clear();
  DsvpvDistance_2D.clear();
  DsvpvDisErr_2D.clear();
  DlxyBS.clear();
  DlxyBSErr.clear();
  DMaxDoca.clear();

  Dtrk1Pt.clear();
  Dtrk2Pt.clear();
  Dtrk1Eta.clear();
  Dtrk2Eta.clear();
  Dtrk1Phi.clear();
  Dtrk2Phi.clear();
  Dtrk1PtErr.clear();
  Dtrk2PtErr.clear();
  Dtrk1Dxy.clear();
  Dtrk2Dxy.clear();
  Dtrk1PixelHit.clear();
  Dtrk2PixelHit.clear();
  Dtrk1StripHit.clear();
  Dtrk2StripHit.clear();
  Dtrk1nStripLayer.clear();
  Dtrk2nStripLayer.clear();
  Dtrk1nPixelLayer.clear();
  Dtrk2nPixelLayer.clear();
  Dtrk1Chi2ndf.clear();
  Dtrk2Chi2ndf.clear();
  Dtrk1MassHypo.clear();
  Dtrk2MassHypo.clear();
  Dtrk1Algo.clear();
  Dtrk2Algo.clear();
  Dtrk1originalAlgo.clear();
  Dtrk2originalAlgo.clear();
  Dtrk1highPurity.clear();
  Dtrk2highPurity.clear();
  Dtrk1EtaErr.clear();
  Dtrk2EtaErr.clear();
  Dtrk1PhiErr.clear();
  Dtrk2PhiErr.clear();
  Dtrk1Y.clear();
  Dtrk2Y.clear();

  Dgen.clear();
  DgencollisionId.clear();
  DdeltaR.clear();

}

#endif
