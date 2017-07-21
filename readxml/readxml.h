#ifndef _READXML_H
#define _READXML_H

#include "../includes/uti.h"
#include "../includes/xjjuti.h"
#include "../includes/cfout.h"
#include "../includes/fit.h"
#include "../includes/tmvaD.h"
#include "../includes/TMVAClassification.h"

const int NEff = 100;
Double_t effS[NEff], effB[NEff];
Double_t aSfit[NEff], aBfit[NEff], aSigfit[NEff];
Double_t aSfonll[NEff], aBfonll[NEff], aSigfonll[NEff];
const int NFonll = 4000;
Double_t MINFonll = 0;
Double_t MAXFonll = 1000;
Double_t fpt[NFonll], fcentral[NFonll];

TString outputsavehist = "rootfiles/fmass";
TString outputfit = "plotfits/cmass";
TString outputsignificance = "plots/csignificance";
TString outputfitmax = "plots/cmass";
TString outputresult = "results/significance";
TString outputfonll = "plots/cfonll";

Double_t norm = 0.557; // FF of D->D0
Double_t BR = 0.0387;
Double_t deltapt = 0.25;

#endif
