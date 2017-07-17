#ifndef _TMVAD_H
#define _TMVAD_H

#include "../uti.h"

class tmvaD
{
 private:
  float               cut_trkPt;
  float               cut_trkEta;
  float               cut_trkPtErr;
  float               cut_Dy;
  float               cut_Dsvpv;
  float               cut_Dalpha;
  float               cut_Dchi2cl;
  float               cut_Dpt_min;
  float               cut_Dpt_max;
  float               cut_DdeltaR_min;
  float               cut_DdeltaR_max;

 public:
  int                 isPP;
  int                 hiBin;
  float               vz;
  float               weight;
  float               pthatweight;
  float               maxDgenpt;
  float               pthat;
  int                 RunNo;
  int                 EvtNo;
  int                 LumiNo;
  int                 Dsize;
  float               PVx;
  float               PVy;
  float               PVz;
  float               PVnchi2;

  std::vector<int>*       Dindex;
  std::vector<float>*     Dmass;
  std::vector<float>*     Dpt;
  std::vector<float>*     Deta;
  std::vector<float>*     Dphi;
  std::vector<float>*     Dy;
  std::vector<float>*     Dchi2ndf;
  std::vector<float>*     Dchi2cl;
  std::vector<float>*     Ddtheta;
  std::vector<float>*     Dlxy;
  std::vector<float>*     Dalpha;
  std::vector<float>*     DsvpvDistance;
  std::vector<float>*     DsvpvDisErr;
  std::vector<float>*     DsvpvDistance_2D;
  std::vector<float>*     DsvpvDisErr_2D;
  std::vector<float>*     DlxyBS;
  std::vector<float>*     DlxyBSErr;
  std::vector<float>*     DMaxDoca;
  std::vector<float>*     Dtrk1Pt;
  std::vector<float>*     Dtrk2Pt;
  std::vector<float>*     Dtrk1Eta;
  std::vector<float>*     Dtrk2Eta;
  std::vector<float>*     Dtrk1Phi;
  std::vector<float>*     Dtrk2Phi;
  std::vector<float>*     Dtrk1PtErr;
  std::vector<float>*     Dtrk2PtErr;
  std::vector<float>*     Dtrk1Dxy;
  std::vector<float>*     Dtrk2Dxy;
  std::vector<float>*     Dtrk1PixelHit;
  std::vector<float>*     Dtrk2PixelHit;
  std::vector<float>*     Dtrk1StripHit;
  std::vector<float>*     Dtrk2StripHit;
  std::vector<float>*     Dtrk1nStripLayer;
  std::vector<float>*     Dtrk2nStripLayer;
  std::vector<float>*     Dtrk1nPixelLayer;
  std::vector<float>*     Dtrk2nPixelLayer;
  std::vector<float>*     Dtrk1Chi2ndf;
  std::vector<float>*     Dtrk2Chi2ndf;
  std::vector<float>*     Dtrk1MassHypo;
  std::vector<float>*     Dtrk2MassHypo;
  std::vector<int>*       Dtrk1Algo;
  std::vector<int>*       Dtrk2Algo;
  std::vector<int>*       Dtrk1originalAlgo;
  std::vector<int>*       Dtrk2originalAlgo;
  std::vector<bool>*      Dtrk1highPurity;
  std::vector<bool>*      Dtrk2highPurity;
  std::vector<float>*     Dtrk1EtaErr;
  std::vector<float>*     Dtrk2EtaErr;
  std::vector<float>*     Dtrk1PhiErr;
  std::vector<float>*     Dtrk2PhiErr;
  std::vector<float>*     Dtrk1Y;
  std::vector<float>*     Dtrk2Y;

  std::vector<float>*     Dgen;
  std::vector<int>*       DgencollisionId;

  std::vector<float>*     DdeltaR;

  int                     Gsize;
  std::vector<int>*       GpdgId;
  std::vector<int>*       GisSignal;
  std::vector<float>*     Gy;
  std::vector<float>*     Geta;
  std::vector<float>*     Gphi;
  std::vector<float>*     Gpt;

  //
  tmvaD() 
    {
      cut_trkPt = -99;
      cut_trkEta = -99;
      cut_trkPtErr = -99;
      cut_Dy = -99;
      cut_Dsvpv = -99;
      cut_Dalpha = -99;
      cut_Dchi2cl = -99;
      cut_Dpt_min = -99;
      cut_Dpt_max = -99;
      cut_DdeltaR_min = -99;
      cut_DdeltaR_max = -99;
    }
  ~tmvaD() {};

  void init();
  void setbranchaddress(TTree* nt);
  void settrkcut(float _cut_trkPt, float _cut_trkEta, float _cut_trkPtErr);
  void setDcut(float _cut_Dy, float _cut_Dsvpv, float _cut_Dalpha, float _cut_Dchi2cl, float _cut_Dpt_min, float _cut_Dpt_max, float _cut_DdeltaR_min, float _cut_DdeltaR_max);
  void settmvacut(float _cut_Dalpha, float _cut_Dsvpv); // update
  bool isselected(int j);
};

void tmvaD::init()
{
  isPP = -99;
  hiBin = -99;
  vz = -99;
  weight = -99;
  pthat = -99;
  pthatweight = -99;
  maxDgenpt = -99;
  RunNo = -99;
  EvtNo = -99;
  LumiNo = -99;
  Dsize = -99;
  PVx = -99;
  PVy = -99;
  PVz = -99;
  PVnchi2 = -99;
  Gsize = -99;

  Dindex = 0;
  Dmass = 0;
  Dpt = 0;
  Deta = 0;
  Dphi = 0;
  Dy = 0;
  Dchi2ndf = 0;
  Dchi2cl = 0;
  Ddtheta = 0;
  Dlxy = 0;
  Dalpha = 0;
  DsvpvDistance = 0;
  DsvpvDisErr = 0;
  DsvpvDistance_2D = 0;
  DsvpvDisErr_2D = 0;
  DlxyBS = 0;
  DlxyBSErr = 0;
  DMaxDoca = 0;
  Dtrk1Pt = 0;
  Dtrk2Pt = 0;
  Dtrk1Eta = 0;
  Dtrk2Eta = 0;
  Dtrk1Phi = 0;
  Dtrk2Phi = 0;
  Dtrk1PtErr = 0;
  Dtrk2PtErr = 0;
  Dtrk1Dxy = 0;
  Dtrk2Dxy = 0;
  Dtrk1PixelHit = 0;
  Dtrk2PixelHit = 0;
  Dtrk1StripHit = 0;
  Dtrk2StripHit = 0;
  Dtrk1nStripLayer = 0;
  Dtrk2nStripLayer = 0;
  Dtrk1nPixelLayer = 0;
  Dtrk2nPixelLayer = 0;
  Dtrk1Chi2ndf = 0;
  Dtrk2Chi2ndf = 0;
  Dtrk1MassHypo = 0;
  Dtrk2MassHypo = 0;
  Dtrk1Algo = 0;
  Dtrk2Algo = 0;
  Dtrk1originalAlgo = 0;
  Dtrk2originalAlgo = 0;
  Dtrk1highPurity = 0;
  Dtrk2highPurity = 0;
  Dtrk1EtaErr = 0;
  Dtrk2EtaErr = 0;
  Dtrk1PhiErr = 0;
  Dtrk2PhiErr = 0;
  Dtrk1Y = 0;
  Dtrk2Y = 0;

  Dgen = 0;
  DgencollisionId = 0;

  DdeltaR = 0;

  GpdgId = 0;
  GisSignal = 0;
  Gy = 0;
  Geta = 0;
  Gphi = 0;
  Gpt = 0;
}

void tmvaD::setbranchaddress(TTree* nt)
{
  init();
  nt->SetBranchAddress("isPP", &isPP);
  nt->SetBranchAddress("hiBin", &hiBin);
  nt->SetBranchAddress("vz", &vz);
  nt->SetBranchAddress("weight", &weight);
  nt->SetBranchAddress("pthat", &pthat);
  nt->SetBranchAddress("pthatweight", &pthatweight);
  nt->SetBranchAddress("maxDgenpt", &maxDgenpt);
  nt->SetBranchAddress("RunNo", &RunNo);
  nt->SetBranchAddress("EvtNo", &EvtNo);
  nt->SetBranchAddress("LumiNo", &LumiNo);
  nt->SetBranchAddress("Dsize", &Dsize);
  nt->SetBranchAddress("PVx", &PVx);
  nt->SetBranchAddress("PVy", &PVy);
  nt->SetBranchAddress("PVz", &PVz);
  nt->SetBranchAddress("PVnchi2", &PVnchi2);
  nt->SetBranchAddress("Dindex", &Dindex);
  nt->SetBranchAddress("Dmass", &Dmass);
  nt->SetBranchAddress("Dpt", &Dpt);
  nt->SetBranchAddress("Deta", &Deta);
  nt->SetBranchAddress("Dphi", &Dphi);
  nt->SetBranchAddress("Dy", &Dy);
  nt->SetBranchAddress("Dchi2ndf", &Dchi2ndf);
  nt->SetBranchAddress("Dchi2cl", &Dchi2cl);
  nt->SetBranchAddress("Ddtheta", &Ddtheta);
  nt->SetBranchAddress("Dlxy", &Dlxy);
  nt->SetBranchAddress("Dalpha", &Dalpha);
  nt->SetBranchAddress("DsvpvDistance", &DsvpvDistance);
  nt->SetBranchAddress("DsvpvDisErr", &DsvpvDisErr);
  nt->SetBranchAddress("DsvpvDistance_2D", &DsvpvDistance_2D);
  nt->SetBranchAddress("DsvpvDisErr_2D", &DsvpvDisErr_2D);
  nt->SetBranchAddress("DlxyBS", &DlxyBS);
  nt->SetBranchAddress("DlxyBSErr", &DlxyBSErr);
  nt->SetBranchAddress("DMaxDoca", &DMaxDoca);
  nt->SetBranchAddress("Dtrk1Pt", &Dtrk1Pt);
  nt->SetBranchAddress("Dtrk2Pt", &Dtrk2Pt);
  nt->SetBranchAddress("Dtrk1Eta", &Dtrk1Eta);
  nt->SetBranchAddress("Dtrk2Eta", &Dtrk2Eta);
  nt->SetBranchAddress("Dtrk1Phi", &Dtrk1Phi);
  nt->SetBranchAddress("Dtrk2Phi", &Dtrk2Phi);
  nt->SetBranchAddress("Dtrk1PtErr", &Dtrk1PtErr);
  nt->SetBranchAddress("Dtrk2PtErr", &Dtrk2PtErr);
  nt->SetBranchAddress("Dtrk1Dxy", &Dtrk1Dxy);
  nt->SetBranchAddress("Dtrk2Dxy", &Dtrk2Dxy);
  nt->SetBranchAddress("Dtrk1PixelHit", &Dtrk1PixelHit);
  nt->SetBranchAddress("Dtrk2PixelHit", &Dtrk2PixelHit);
  nt->SetBranchAddress("Dtrk1StripHit", &Dtrk1StripHit);
  nt->SetBranchAddress("Dtrk2StripHit", &Dtrk2StripHit);
  nt->SetBranchAddress("Dtrk1nStripLayer", &Dtrk1nStripLayer);
  nt->SetBranchAddress("Dtrk2nStripLayer", &Dtrk2nStripLayer);
  nt->SetBranchAddress("Dtrk1nPixelLayer", &Dtrk1nPixelLayer);
  nt->SetBranchAddress("Dtrk2nPixelLayer", &Dtrk2nPixelLayer);
  nt->SetBranchAddress("Dtrk1Chi2ndf", &Dtrk1Chi2ndf);
  nt->SetBranchAddress("Dtrk2Chi2ndf", &Dtrk2Chi2ndf);
  nt->SetBranchAddress("Dtrk1MassHypo", &Dtrk1MassHypo);
  nt->SetBranchAddress("Dtrk2MassHypo", &Dtrk2MassHypo);
  nt->SetBranchAddress("Dtrk1Algo", &Dtrk1Algo);
  nt->SetBranchAddress("Dtrk2Algo", &Dtrk2Algo);
  nt->SetBranchAddress("Dtrk1originalAlgo", &Dtrk1originalAlgo);
  nt->SetBranchAddress("Dtrk2originalAlgo", &Dtrk2originalAlgo);
  nt->SetBranchAddress("Dtrk1highPurity", &Dtrk1highPurity);
  nt->SetBranchAddress("Dtrk2highPurity", &Dtrk2highPurity);
  nt->SetBranchAddress("Dtrk1EtaErr", &Dtrk1EtaErr);
  nt->SetBranchAddress("Dtrk2EtaErr", &Dtrk2EtaErr);
  nt->SetBranchAddress("Dtrk1PhiErr", &Dtrk1PhiErr);
  nt->SetBranchAddress("Dtrk2PhiErr", &Dtrk2PhiErr);
  nt->SetBranchAddress("Dtrk1Y", &Dtrk1Y);
  nt->SetBranchAddress("Dtrk2Y", &Dtrk2Y);
  nt->SetBranchAddress("Dgen", &Dgen);
  nt->SetBranchAddress("DgencollisionId", &DgencollisionId);
  nt->SetBranchAddress("DdeltaR", &DdeltaR);

  nt->SetBranchAddress("Gsize", &Gsize);
  nt->SetBranchAddress("GpdgId", &GpdgId);
  nt->SetBranchAddress("GisSignal", &GisSignal);
  nt->SetBranchAddress("Gy", &Gy);
  nt->SetBranchAddress("Geta", &Geta);
  nt->SetBranchAddress("Gphi", &Gphi);
  nt->SetBranchAddress("Gpt", &Gpt);

}

void tmvaD::settrkcut(float _cut_trkPt, float _cut_trkEta, float _cut_trkPtErr)
{
  cut_trkPt = _cut_trkPt;
  cut_trkEta = _cut_trkEta;
  cut_trkPtErr = _cut_trkPtErr;
}

void tmvaD::setDcut(float _cut_Dy, float _cut_Dsvpv, float _cut_Dalpha, float _cut_Dchi2cl, float _cut_Dpt_min, float _cut_Dpt_max, float _cut_DdeltaR_min, float _cut_DdeltaR_max)
{
  cut_Dy = _cut_Dy;
  cut_Dsvpv = _cut_Dsvpv;
  cut_Dalpha = _cut_Dalpha;
  cut_Dchi2cl = _cut_Dchi2cl;
  cut_Dpt_min = _cut_Dpt_min;
  cut_Dpt_max = _cut_Dpt_max;
  cut_DdeltaR_min = _cut_DdeltaR_min;
  cut_DdeltaR_max = _cut_DdeltaR_max;
}

void tmvaD::settmvacut(float _cut_Dalpha, float _cut_Dsvpv)
{
  cut_Dalpha = _cut_Dalpha;
  cut_Dsvpv = _cut_Dsvpv;
}


bool tmvaD::isselected(int j)
{
  if((*Dtrk1Pt)[j] > cut_trkPt && (*Dtrk2Pt)[j] > cut_trkPt &&
     TMath::Abs((*Dtrk1Eta)[j]) < cut_trkEta && TMath::Abs((*Dtrk2Eta)[j]) < cut_trkEta &&
     ((*Dtrk1PtErr)[j]/(*Dtrk1Pt)[j]) < cut_trkPtErr && ((*Dtrk2PtErr)[j]/(*Dtrk2Pt)[j]) < cut_trkPtErr &&
     (*Dtrk1highPurity)[j] && (*Dtrk2highPurity)[j] &&
     TMath::Abs((*Dy)[j]) < cut_Dy &&
     ((*DsvpvDistance)[j]/(*DsvpvDisErr)[j]) > cut_Dsvpv &&
     (*Dalpha)[j] < cut_Dalpha &&
     (*Dchi2cl)[j] >cut_Dchi2cl &&
     (*Dpt)[j] > cut_Dpt_min && (*Dpt)[j] < cut_Dpt_max &&
     (*DdeltaR)[j] > cut_DdeltaR_min && (*DdeltaR)[j] < cut_DdeltaR_max) return true;
  else return false;
}


#endif
