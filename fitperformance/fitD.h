#ifndef _FITD_H_
#define _FITD_H_

#include "../includes/uti.h"
#include "../includes/fit.h"
#include "../includes/tmvaD.h"

Float_t cutval_trkPt;
Float_t cutval_trkEta;
Float_t cutval_trkPtErr;
Float_t cutval_Dy;
Float_t cutval_Dsvpv;
Float_t cutval_Dalpha;
Float_t cutval_Dchi2cl;

std::map<TString, Float_t> cutval_list_trkPt = {{"pp", 2.0}, {"PbPb", 2.0}};
std::map<TString, Float_t> cutval_list_trkEta = {{"pp", 2.0}, {"PbPb", 2.0}};
std::map<TString, Float_t> cutval_list_trkPtErr = {{"pp", 0.3}, {"PbPb", 0.3}};
std::map<TString, Float_t> cutval_list_Dy = {{"pp", 2.0}, {"PbPb", 2.0}};
std::map<TString, Float_t> cutval_list_Dsvpv = {{"pp", 4.06}, {"PbPb", 6.0}};
std::map<TString, Float_t> cutval_list_Dalpha = {{"pp", 0.12}, {"PbPb", 0.12}};
std::map<TString, Float_t> cutval_list_Dchi2cl = {{"pp", 0.1}, {"PbPb", 0.1}};

int initcutval(TString collisionsyst)
{
  
  if(cutval_list_trkPt.find(collisionsyst)==cutval_list_trkPt.end() ||
     cutval_list_trkEta.find(collisionsyst)==cutval_list_trkEta.end() ||
     cutval_list_trkPtErr.find(collisionsyst)==cutval_list_trkPtErr.end() ||
     cutval_list_Dy.find(collisionsyst)==cutval_list_Dy.end() ||
     cutval_list_Dsvpv.find(collisionsyst)==cutval_list_Dsvpv.end() ||
     cutval_list_Dalpha.find(collisionsyst)==cutval_list_Dalpha.end() ||
     cutval_list_Dchi2cl.find(collisionsyst)==cutval_list_Dchi2cl.end())
    {
      std::cout<<"\033[1;31merror:\033[0m invalid \"collisionsyst\" - initcutval()"<<std::endl;
      return 1;
    }
  cutval_trkPt = cutval_list_trkPt[collisionsyst];
  cutval_trkEta = cutval_list_trkEta[collisionsyst];
  cutval_trkPtErr = cutval_list_trkPtErr[collisionsyst];
  cutval_Dy = cutval_list_Dy[collisionsyst];
  cutval_Dsvpv = cutval_list_Dsvpv[collisionsyst];
  cutval_Dalpha = cutval_list_Dalpha[collisionsyst];
  cutval_Dchi2cl = cutval_list_Dchi2cl[collisionsyst];
  return 0;
}

#endif
