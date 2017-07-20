#ifndef _FITDJETS_H_
#define _FITDJETS_H_

#include "../includes/uti.h"
#include "../includes/xjjuti.h"
#include "../includes/fit.h"
#include "../includes/tmvaD.h"

const int nPtBins = 2;
Float_t ptBins[nPtBins+1] = {4, 20, 999};
const int nDrBins = 3;
Float_t drBins[nDrBins+1] = {0, 0.1, 0.2, 0.5};
const int nCoBins = 2;
std::map<TString, int> collsyst_list = {{"pp", 0}, {"PbPb", 1}};

Float_t cutval_trkPt;
Float_t cutval_trkEta;
Float_t cutval_trkPtErr;
Float_t cutval_Dy;
Float_t cutval_Dsvpv;
Float_t cutval_Dalpha;
Float_t cutval_Dchi2cl;
//                                                       ---- 4~20 ---- pp ---- 20~999 ---   ---- 4~20 ---- PbPb --- 20~999 ----
Float_t cutval_list_trkPt[nCoBins][nPtBins][nDrBins] = {{{2.0, 2.0, 2.0}, {2.0, 2.0, 2.0}}, {{2.0, 2.0, 2.0}, {2.0, 2.0, 2.0}}};
Float_t cutval_list_trkEta[nCoBins][nPtBins][nDrBins] = {{{2.0, 2.0, 2.0}, {2.0, 2.0, 2.0}}, {{2.0, 2.0, 2.0}, {2.0, 2.0, 2.0}}};
Float_t cutval_list_trkPtErr[nCoBins][nPtBins][nDrBins] = {{{0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}}, {{0.3, 0.3, 0.3}, {0.3, 0.3, 0.3}}};
Float_t cutval_list_Dy[nCoBins][nPtBins][nDrBins] = {{{2.0, 2.0, 2.0}, {2.0, 2.0, 2.0}}, {{2.0, 2.0, 2.0}, {2.0, 2.0, 2.0}}};
Float_t cutval_list_Dsvpv[nCoBins][nPtBins][nDrBins] = {{{4.06, 4.06, 4.06}, {4.06, 4.06, 4.06}}, {{6.0, 6.0, 6.0}, {6.0, 6.0, 6.0}}};
Float_t cutval_list_Dalpha[nCoBins][nPtBins][nDrBins] = {{{0.12, 0.12, 0.12}, {0.12, 0.12, 0.12}}, {{0.12, 0.12, 0.12}, {0.12, 0.12, 0.12}}};
Float_t cutval_list_Dchi2cl[nCoBins][nPtBins][nDrBins] = {{{0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}}, {{0.1, 0.1, 0.1}, {0.1, 0.1, 0.1}}};

int initcutval(TString collisionsyst, int ipt, int idr)
{
  if(collsyst_list.find(collisionsyst)==collsyst_list.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\" - initcutval()"<<std::endl;
      return 1;
    }
  int icollsyst = collsyst_list[collisionsyst];
  cutval_trkPt = cutval_list_trkPt[icollsyst][ipt][idr];
  cutval_trkEta = cutval_list_trkEta[icollsyst][ipt][idr];
  cutval_trkPtErr = cutval_list_trkPtErr[icollsyst][ipt][idr];
  cutval_Dy = cutval_list_Dy[icollsyst][ipt][idr];
  cutval_Dsvpv = cutval_list_Dsvpv[icollsyst][ipt][idr];
  cutval_Dalpha = cutval_list_Dalpha[icollsyst][ipt][idr];
  cutval_Dchi2cl = cutval_list_Dchi2cl[icollsyst][ipt][idr];
  return 0;
}

#endif
