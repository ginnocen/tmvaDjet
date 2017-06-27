#ifndef _PREPD_H
#define _PREPD_H

using namespace std;
#include "uti.h"
#include "d_jet.h"

#define MAX_XB       20000

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
 
  Int_t               Dindex[MAX_XB];
  Float_t             Dmass[MAX_XB];
  Float_t             Dpt[MAX_XB];
  Float_t             Deta[MAX_XB];
  Float_t             Dphi[MAX_XB];
  Float_t             Dy[MAX_XB];
  Float_t             Dchi2ndf[MAX_XB];
  Float_t             Dchi2cl[MAX_XB];
  Float_t             Ddtheta[MAX_XB];
  Float_t             Dlxy[MAX_XB];
  Float_t             Dalpha[MAX_XB];
  Float_t             DsvpvDistance[MAX_XB];
  Float_t             DsvpvDisErr[MAX_XB];
  Float_t             DsvpvDistance_2D[MAX_XB];
  Float_t             DsvpvDisErr_2D[MAX_XB];
  Float_t             DlxyBS[MAX_XB];
  Float_t             DlxyBSErr[MAX_XB];
  Float_t             DMaxDoca[MAX_XB];
  Float_t             Dtrk1Pt[MAX_XB];
  Float_t             Dtrk2Pt[MAX_XB];
  Float_t             Dtrk1Eta[MAX_XB];
  Float_t             Dtrk2Eta[MAX_XB];
  Float_t             Dtrk1Phi[MAX_XB];
  Float_t             Dtrk2Phi[MAX_XB];
  Float_t             Dtrk1PtErr[MAX_XB];
  Float_t             Dtrk2PtErr[MAX_XB];
  Float_t             Dtrk1Dxy[MAX_XB];
  Float_t             Dtrk2Dxy[MAX_XB];
  Float_t             Dtrk1PixelHit[MAX_XB];
  Float_t             Dtrk2PixelHit[MAX_XB];
  Float_t             Dtrk1StripHit[MAX_XB];
  Float_t             Dtrk2StripHit[MAX_XB];
  Float_t             Dtrk1nStripLayer[MAX_XB];
  Float_t             Dtrk2nStripLayer[MAX_XB];
  Float_t             Dtrk1nPixelLayer[MAX_XB];
  Float_t             Dtrk2nPixelLayer[MAX_XB];
  Float_t             Dtrk1Chi2ndf[MAX_XB];
  Float_t             Dtrk2Chi2ndf[MAX_XB];
  Float_t             Dtrk1MassHypo[MAX_XB];
  Float_t             Dtrk2MassHypo[MAX_XB];
  Int_t               Dtrk1Algo[MAX_XB];
  Int_t               Dtrk2Algo[MAX_XB];
  Int_t               Dtrk1originalAlgo[MAX_XB];
  Int_t               Dtrk2originalAlgo[MAX_XB];
  Bool_t              Dtrk1highPurity[MAX_XB];
  Bool_t              Dtrk2highPurity[MAX_XB];
  Float_t             Dtrk1EtaErr[MAX_XB];
  Float_t             Dtrk2EtaErr[MAX_XB];
  Float_t             Dtrk1PhiErr[MAX_XB];
  Float_t             Dtrk2PhiErr[MAX_XB];
  Float_t             Dtrk1Y[MAX_XB];
  Float_t             Dtrk2Y[MAX_XB];

  Float_t             Dgen[MAX_XB];
  Int_t               DgencollisionId[MAX_XB];

  Float_t             DdeltaR[MAX_XB];

  // constructors
  prepD()
    {
    }
  
  prepD(TTree* t) : prepD() 
    {
      this->create_tree(t);
    }
  
  ~prepD() {};
  
  void create_tree(TTree* t);
  void copy_variables(djet& dt);
  void copy_index(djet& dt, int i, float dR);

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

  t->Branch("Dindex", Dindex, "Dindex[Dsize]/I");
  t->Branch("Dmass", Dmass, "Dmass[Dsize]/F");
  t->Branch("Dpt", Dpt, "Dpt[Dsize]/F");
  t->Branch("Deta", Deta, "Deta[Dsize]/F");
  t->Branch("Dphi", Dphi, "Dphi[Dsize]/F");
  t->Branch("Dy", Dy, "Dy[Dsize]/F");
  t->Branch("Dchi2ndf", Dchi2ndf, "Dchi2ndf[Dsize]/F");
  t->Branch("Dchi2cl", Dchi2cl, "Dchi2cl[Dsize]/F");
  t->Branch("Ddtheta", Ddtheta, "Ddtheta[Dsize]/F");
  t->Branch("Dlxy", Dlxy, "Dlxy[Dsize]/F");
  t->Branch("Dalpha", Dalpha, "Dalpha[Dsize]/F");
  t->Branch("DsvpvDistance", DsvpvDistance, "DsvpvDistance[Dsize]/F");
  t->Branch("DsvpvDisErr", DsvpvDisErr, "DsvpvDisErr[Dsize]/F");
  t->Branch("DsvpvDistance_2D", DsvpvDistance_2D, "DsvpvDistance_2D[Dsize]/F");
  t->Branch("DsvpvDisErr_2D", DsvpvDisErr_2D, "DsvpvDisErr_2D[Dsize]/F");
  t->Branch("DlxyBS", DlxyBS, "DlxyBS[Dsize]/F");
  t->Branch("DlxyBSErr", DlxyBSErr, "DlxyBSErr[Dsize]/F");
  t->Branch("DMaxDoca", DMaxDoca, "DMaxDoca[Dsize]/F");
  t->Branch("Dtrk1Pt", Dtrk1Pt, "Dtrk1Pt[Dsize]/F");
  t->Branch("Dtrk2Pt", Dtrk2Pt, "Dtrk2Pt[Dsize]/F");
  t->Branch("Dtrk1Eta", Dtrk1Eta, "Dtrk1Eta[Dsize]/F");
  t->Branch("Dtrk2Eta", Dtrk2Eta, "Dtrk2Eta[Dsize]/F");
  t->Branch("Dtrk1Phi", Dtrk1Phi, "Dtrk1Phi[Dsize]/F");
  t->Branch("Dtrk2Phi", Dtrk2Phi, "Dtrk2Phi[Dsize]/F");
  t->Branch("Dtrk1PtErr", Dtrk1PtErr, "Dtrk1PtErr[Dsize]/F");
  t->Branch("Dtrk2PtErr", Dtrk2PtErr, "Dtrk2PtErr[Dsize]/F");
  t->Branch("Dtrk1Dxy", Dtrk1Dxy, "Dtrk1Dxy[Dsize]/F");
  t->Branch("Dtrk2Dxy", Dtrk2Dxy, "Dtrk2Dxy[Dsize]/F");
  t->Branch("Dtrk1PixelHit", Dtrk1PixelHit, "Dtrk2Dxy[Dsize]/F");
  t->Branch("Dtrk2PixelHit", Dtrk2PixelHit, "Dtrk2PixelHit[Dsize]/F");
  t->Branch("Dtrk1StripHit", Dtrk1StripHit, "Dtrk1StripHit[Dsize]/F");
  t->Branch("Dtrk2StripHit", Dtrk2StripHit, "Dtrk2StripHit[Dsize]/F");
  t->Branch("Dtrk1nStripLayer", Dtrk1nStripLayer, "Dtrk1nStripLayer[Dsize]/F");
  t->Branch("Dtrk2nStripLayer", Dtrk2nStripLayer, "Dtrk2nStripLayer[Dsize]/F");
  t->Branch("Dtrk1nPixelLayer", Dtrk1nPixelLayer, "Dtrk1nPixelLayer[Dsize]/F");
  t->Branch("Dtrk2nPixelLayer", Dtrk2nPixelLayer, "Dtrk2nPixelLayer[Dsize]/F");
  t->Branch("Dtrk1Chi2ndf", Dtrk1Chi2ndf, "Dtrk1Chi2ndf[Dsize]/F");
  t->Branch("Dtrk2Chi2ndf", Dtrk2Chi2ndf, "Dtrk2Chi2ndf[Dsize]/F");
  t->Branch("Dtrk1MassHypo", Dtrk1MassHypo, "Dtrk1MassHypo[Dsize]/F");
  t->Branch("Dtrk2MassHypo", Dtrk2MassHypo, "Dtrk2MassHypo[Dsize]/F");
  t->Branch("Dtrk1Algo", Dtrk1Algo, "Dtrk1Algo[Dsize]/I");
  t->Branch("Dtrk2Algo", Dtrk2Algo, "Dtrk2Algo[Dsize]/I");
  t->Branch("Dtrk1originalAlgo", Dtrk1originalAlgo, "Dtrk1originalAlgo[Dsize]/I");
  t->Branch("Dtrk2originalAlgo", Dtrk2originalAlgo, "Dtrk2originalAlgo[Dsize]/I");
  t->Branch("Dtrk1highPurity", Dtrk1highPurity, "Dtrk1highPurity[Dsize]/O");
  t->Branch("Dtrk2highPurity", Dtrk2highPurity, "Dtrk2highPurity[Dsize]/O");
  t->Branch("Dtrk1EtaErr", Dtrk1EtaErr, "Dtrk1EtaErr[Dsize]/F");
  t->Branch("Dtrk2EtaErr", Dtrk2EtaErr, "Dtrk2EtaErr[Dsize]/F");
  t->Branch("Dtrk1PhiErr", Dtrk1PhiErr, "Dtrk1PhiErr[Dsize]/F");
  t->Branch("Dtrk2PhiErr", Dtrk2PhiErr, "Dtrk2PhiErr[Dsize]/F");
  t->Branch("Dtrk1Y", Dtrk1Y, "Dtrk1Y[Dsize]/F");
  t->Branch("Dtrk2Y", Dtrk2Y, "Dtrk2Y[Dsize]/F");

  t->Branch("Dgen", Dgen, "Dgen[Dsize]/F");
  t->Branch("DgencollisionId", DgencollisionId, "DgencollisionId[Dsize]/I");

  t->Branch("DdeltaR", DdeltaR, "DdeltaR[Dsize]/F");
}

void prepD::copy_variables(djet& dt)
{
  isPP = dt.isPP;
  hiBin = dt.hiBin;
  vz = dt.vz;
  weight = dt.weight;
  pthat = dt.pthat;
  RunNo = dt.RunNo;
  EvtNo = dt.EvtNo;
  LumiNo = dt.LumiNo;
  PVx = dt.PVx;
  PVy = dt.PVy;
  PVz = dt.PVz;
  PVnchi2 = dt.PVnchi2;
}

void prepD::copy_index(djet& dt, int i, float dR)
{
  Dindex[Dsize] = (*dt.Dindex)[i];
  Dmass[Dsize] = (*dt.Dmass)[i];
  Dpt[Dsize] = (*dt.Dpt)[i];
  Deta[Dsize] = (*dt.Deta)[i];
  Dphi[Dsize] = (*dt.Dphi)[i];
  Dy[Dsize] = (*dt.Dy)[i];
  Dchi2ndf[Dsize] = (*dt.Dchi2ndf)[i];
  Dchi2cl[Dsize] = (*dt.Dchi2cl)[i];
  Ddtheta[Dsize] = (*dt.Ddtheta)[i];
  Dlxy[Dsize] = (*dt.Dlxy)[i];
  Dalpha[Dsize] = (*dt.Dalpha)[i];
  DsvpvDistance[Dsize] = (*dt.DsvpvDistance)[i];
  DsvpvDisErr[Dsize] = (*dt.DsvpvDisErr)[i];
  DsvpvDistance_2D[Dsize] = (*dt.DsvpvDistance_2D)[i];
  DsvpvDisErr_2D[Dsize] = (*dt.DsvpvDisErr_2D)[i];
  DlxyBS[Dsize] = (*dt.DlxyBS)[i];
  DlxyBSErr[Dsize] = (*dt.DlxyBSErr)[i];
  DMaxDoca[Dsize] = (*dt.DMaxDoca)[i];
  Dtrk1Pt[Dsize] = (*dt.Dtrk1Pt)[i];
  Dtrk2Pt[Dsize] = (*dt.Dtrk2Pt)[i];
  Dtrk1Eta[Dsize] = (*dt.Dtrk1Eta)[i];
  Dtrk2Eta[Dsize] = (*dt.Dtrk2Eta)[i];
  Dtrk1Phi[Dsize] = (*dt.Dtrk1Phi)[i];
  Dtrk2Phi[Dsize] = (*dt.Dtrk2Phi)[i];
  Dtrk1PtErr[Dsize] = (*dt.Dtrk1PtErr)[i];
  Dtrk2PtErr[Dsize] = (*dt.Dtrk2PtErr)[i];
  Dtrk1Dxy[Dsize] = (*dt.Dtrk1Dxy)[i];
  Dtrk2Dxy[Dsize] = (*dt.Dtrk2Dxy)[i];
  Dtrk1PixelHit[Dsize] = (*dt.Dtrk1PixelHit)[i];
  Dtrk2PixelHit[Dsize] = (*dt.Dtrk2PixelHit)[i];
  Dtrk1StripHit[Dsize] = (*dt.Dtrk1StripHit)[i];
  Dtrk2StripHit[Dsize] = (*dt.Dtrk2StripHit)[i];
  Dtrk1nStripLayer[Dsize] = (*dt.Dtrk1nStripLayer)[i];
  Dtrk2nStripLayer[Dsize] = (*dt.Dtrk2nStripLayer)[i];
  Dtrk1nPixelLayer[Dsize] = (*dt.Dtrk1nPixelLayer)[i];
  Dtrk2nPixelLayer[Dsize] = (*dt.Dtrk2nPixelLayer)[i];
  Dtrk1Chi2ndf[Dsize] = (*dt.Dtrk1Chi2ndf)[i];
  Dtrk2Chi2ndf[Dsize] = (*dt.Dtrk2Chi2ndf)[i];
  Dtrk1MassHypo[Dsize] = (*dt.Dtrk1MassHypo)[i];
  Dtrk2MassHypo[Dsize] = (*dt.Dtrk2MassHypo)[i];
  Dtrk1Algo[Dsize] = (*dt.Dtrk1Algo)[i];
  Dtrk2Algo[Dsize] = (*dt.Dtrk2Algo)[i];
  Dtrk1originalAlgo[Dsize] = (*dt.Dtrk1originalAlgo)[i];
  Dtrk2originalAlgo[Dsize] = (*dt.Dtrk2originalAlgo)[i];
  Dtrk1highPurity[Dsize] = (*dt.Dtrk1highPurity)[i];
  Dtrk2highPurity[Dsize] = (*dt.Dtrk2highPurity)[i];
  Dtrk1EtaErr[Dsize] = (*dt.Dtrk1EtaErr)[i];
  Dtrk2EtaErr[Dsize] = (*dt.Dtrk2EtaErr)[i];
  Dtrk1PhiErr[Dsize] = (*dt.Dtrk1PhiErr)[i];
  Dtrk2PhiErr[Dsize] = (*dt.Dtrk2PhiErr)[i];
  Dtrk1Y[Dsize] = (*dt.Dtrk1Y)[i];
  Dtrk2Y[Dsize] = (*dt.Dtrk2Y)[i];

  Dgen[Dsize] = (*dt.Dgen)[i];
  DgencollisionId[Dsize] = (*dt.DgencollisionId)[i];

  DdeltaR[Dsize] = dR;
}

#endif
