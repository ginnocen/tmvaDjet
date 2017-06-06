#!/bin/sh

##
INPUTDIR="/export/d00/scratch/jwang/Djets/data/"
INPUTSUB="DjetFiles_pp_5TeV_HeavyFlavor_Dfinder_Data_20170405_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar"
OUTPUTDIR="/export/d00/scratch/jwang/Djets/data/"
OUTPUTSUB="DjetFiles_pp_5TeV_HeavyFlavor_Dfinder_Data_20170405_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar"

JETPT=80
JETETAMIN=0.3
JETETAMAX=1.6
MAXEVTS=-1

##
#
tETAMIN1=`echo $JETETAMIN | awk -F "." '{print $1}'`
tETAMIN2=`echo $JETETAMIN | awk -F "." '{print $2}'`
tETAMAX1=`echo $JETETAMAX | awk -F "." '{print $1}'`
tETAMAX2=`echo $JETETAMAX | awk -F "." '{print $2}'`
#
INPUTFILENAME=${INPUTDIR}/${INPUTSUB}.root
tJETETAMIN=${tETAMIN1:-0}p${tETAMIN2:-0}
tJETETAMAX=${tETAMAX1:-0}p${tETAMAX2:-0}
OUTPUTFILENAME=${OUTPUTDIR}/tmva_${OUTPUTSUB}_jetpt_${JETPT}_jeteta_${tJETETAMIN}_${tJETETAMAX}.root

##
root -b -q 'prepDsample.C+('\"${INPUTFILENAME}\"','\"${OUTPUTFILENAME}\"','${JETPT}','${JETETAMIN}','${JETETAMAX}','${MAXEVTS}')'