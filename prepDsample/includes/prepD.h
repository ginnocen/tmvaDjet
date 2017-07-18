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
  float               pthatweight;
  float               maxDgenpt;

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

  std::vector<float>     DjetptCorr;
  std::vector<float>     Djeteta;
  std::vector<float>     Djetphi;

  std::vector<float>     DdeltaR;
  std::vector<float>     DdeltaRref;

  int                    Gsize;
  std::vector<int>       GpdgId;
  std::vector<int>       GisSignal;
  std::vector<float>     Gy;
  std::vector<float>     Geta;
  std::vector<float>     Gphi;
  std::vector<float>     Gpt;

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
      Gsize = -99;
      pthatweight = -1;
      maxDgenpt = -1;
    }
  
  prepD(TTree* t) : prepD() 
    {
      this->create_tree(t);
    }
  
  ~prepD() {};
  
  void create_tree(TTree* t);
  void copy_variables(djet& dt, int dsize, int gsize);
  void copy_gen_index(djet& dt, int i);
  void copy_index(djet& dt, int jd, int jj, float dR, float dRref);
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
  t->Branch("pthatweight", &pthatweight, "pthatweight/F");
  t->Branch("maxDgenpt", &maxDgenpt, "maxDgenpt/F");

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

  t->Branch("DjetptCorr", &DjetptCorr);
  t->Branch("Djeteta", &Djeteta);
  t->Branch("Djetphi", &Djetphi);

  t->Branch("DdeltaR", &DdeltaR);
  t->Branch("DdeltaRref", &DdeltaRref);

  t->Branch("Gsize", &Gsize, "Gsize/I");
  t->Branch("GpdgId", &GpdgId);
  t->Branch("GisSignal", &GisSignal);
  t->Branch("Gy", &Gy);
  t->Branch("Geta", &Geta);
  t->Branch("Gphi", &Gphi);
  t->Branch("Gpt", &Gpt);
}

void prepD::copy_variables(djet& dt, int dsize, int gsize)
{
  isPP = dt.isPP;
  hiBin = dt.hiBin;
  vz = dt.vz;
  weight = dt.weight;
  pthat = dt.pthat;
  RunNo = dt.RunNo;
  EvtNo = dt.EvtNo;
  LumiNo = dt.LumiNo;
  Dsize = dsize;
  PVx = dt.PVx;
  PVy = dt.PVy;
  PVz = dt.PVz;
  PVnchi2 = dt.PVnchi2;
  Gsize = gsize;
  pthatweight = dt.pthatweight;
  maxDgenpt = dt.maxDgenpt;
}

void prepD::copy_gen_index(djet& dt, int i)
{
  GpdgId.push_back((*dt.GpdgId)[i]);
  GisSignal.push_back((*dt.GisSignal)[i]);
  Gy.push_back((*dt.Gy)[i]);
  Geta.push_back((*dt.Geta)[i]);
  Gphi.push_back((*dt.Gphi)[i]);
  Gpt.push_back((*dt.Gpt)[i]);
}

void prepD::copy_index(djet& dt, int jd, int jj, float dR, float dRref)
{
  Dindex.push_back((*dt.Dindex)[jd]);
  Dmass.push_back((*dt.Dmass)[jd]);
  Dpt.push_back((*dt.Dpt)[jd]);
  Deta.push_back((*dt.Deta)[jd]);
  Dphi.push_back((*dt.Dphi)[jd]);
  Dy.push_back((*dt.Dy)[jd]);
  Dchi2ndf.push_back((*dt.Dchi2ndf)[jd]);
  Dchi2cl.push_back((*dt.Dchi2cl)[jd]);
  Ddtheta.push_back((*dt.Ddtheta)[jd]);
  Dlxy.push_back((*dt.Dlxy)[jd]);
  Dalpha.push_back((*dt.Dalpha)[jd]);
  DsvpvDistance.push_back((*dt.DsvpvDistance)[jd]);
  DsvpvDisErr.push_back((*dt.DsvpvDisErr)[jd]);
  DsvpvDistance_2D.push_back((*dt.DsvpvDistance_2D)[jd]);
  DsvpvDisErr_2D.push_back((*dt.DsvpvDisErr_2D)[jd]);
  DlxyBS.push_back((*dt.DlxyBS)[jd]);
  DlxyBSErr.push_back((*dt.DlxyBSErr)[jd]);
  DMaxDoca.push_back((*dt.DMaxDoca)[jd]);
  Dtrk1Pt.push_back((*dt.Dtrk1Pt)[jd]);
  Dtrk2Pt.push_back((*dt.Dtrk2Pt)[jd]);
  Dtrk1Eta.push_back((*dt.Dtrk1Eta)[jd]);
  Dtrk2Eta.push_back((*dt.Dtrk2Eta)[jd]);
  Dtrk1Phi.push_back((*dt.Dtrk1Phi)[jd]);
  Dtrk2Phi.push_back((*dt.Dtrk2Phi)[jd]);
  Dtrk1PtErr.push_back((*dt.Dtrk1PtErr)[jd]);
  Dtrk2PtErr.push_back((*dt.Dtrk2PtErr)[jd]);
  Dtrk1Dxy.push_back((*dt.Dtrk1Dxy)[jd]);
  Dtrk2Dxy.push_back((*dt.Dtrk2Dxy)[jd]);
  Dtrk1PixelHit.push_back((*dt.Dtrk1PixelHit)[jd]);
  Dtrk2PixelHit.push_back((*dt.Dtrk2PixelHit)[jd]);
  Dtrk1StripHit.push_back((*dt.Dtrk1StripHit)[jd]);
  Dtrk2StripHit.push_back((*dt.Dtrk2StripHit)[jd]);
  Dtrk1nStripLayer.push_back((*dt.Dtrk1nStripLayer)[jd]);
  Dtrk2nStripLayer.push_back((*dt.Dtrk2nStripLayer)[jd]);
  Dtrk1nPixelLayer.push_back((*dt.Dtrk1nPixelLayer)[jd]);
  Dtrk2nPixelLayer.push_back((*dt.Dtrk2nPixelLayer)[jd]);
  Dtrk1Chi2ndf.push_back((*dt.Dtrk1Chi2ndf)[jd]);
  Dtrk2Chi2ndf.push_back((*dt.Dtrk2Chi2ndf)[jd]);
  Dtrk1MassHypo.push_back((*dt.Dtrk1MassHypo)[jd]);
  Dtrk2MassHypo.push_back((*dt.Dtrk2MassHypo)[jd]);
  Dtrk1Algo.push_back((*dt.Dtrk1Algo)[jd]);
  Dtrk2Algo.push_back((*dt.Dtrk2Algo)[jd]);
  Dtrk1originalAlgo.push_back((*dt.Dtrk1originalAlgo)[jd]);
  Dtrk2originalAlgo.push_back((*dt.Dtrk2originalAlgo)[jd]);
  Dtrk1highPurity.push_back((*dt.Dtrk1highPurity)[jd]);
  Dtrk2highPurity.push_back((*dt.Dtrk2highPurity)[jd]);
  Dtrk1EtaErr.push_back((*dt.Dtrk1EtaErr)[jd]);
  Dtrk2EtaErr.push_back((*dt.Dtrk2EtaErr)[jd]);
  Dtrk1PhiErr.push_back((*dt.Dtrk1PhiErr)[jd]);
  Dtrk2PhiErr.push_back((*dt.Dtrk2PhiErr)[jd]);
  Dtrk1Y.push_back((*dt.Dtrk1Y)[jd]);
  Dtrk2Y.push_back((*dt.Dtrk2Y)[jd]);

  DjetptCorr.push_back((*dt.jetptCorr_akpu3pf)[jj]);
  Djeteta.push_back((*dt.jeteta_akpu3pf)[jj]);
  Djetphi.push_back((*dt.jetphi_akpu3pf)[jj]);

  Dgen.push_back((*dt.Dgen)[jd]);
  DgencollisionId.push_back((*dt.DgencollisionId)[jd]);

  DdeltaR.push_back(dR);
  DdeltaRref.push_back(dRref);
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

  DjetptCorr.clear();
  Djeteta.clear();
  Djetphi.clear();

  DdeltaR.clear();
  DdeltaRref.clear();
  
  GpdgId.clear();
  GisSignal.clear();
  Gy.clear();
  Geta.clear();
  Gphi.clear();
  Gpt.clear();

}

#endif
