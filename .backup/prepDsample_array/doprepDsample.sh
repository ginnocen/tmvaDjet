#!/bin/sh

##
INPUTDIR="/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1/"
INPUTSUB="merged"
OUTPUTDIR="/export/d00/scratch/jwang/Djets/data/"
OUTPUTSUB="vector_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1"

#INPUTDIR="/export/d00/scratch/jwang/Djets/MC/"
#INPUTSUB="DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight"
#OUTPUTDIR="/export/d00/scratch/jwang/Djets/MC/"
#OUTPUTSUB="vector_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight"

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