#!/bin/sh

##

#
INPUTDIR="/export/d00/scratch/jwang/Djets/MC/"
INPUTSUB="DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight"
OUTPUTDIR="/export/d00/scratch/jwang/Djets/MC/"
OUTPUTSUB="DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight"

#
ISMC=0
JETPT=60
JETETAMIN=0.0
JETETAMAX=2.0
MAXEVTS=-1

##

# Don't modify the content below, if you don't know what they mean. #

#
g++ prepDsample.C $(root-config --cflags --libs) -g -o prepDsample.exe

#
function float_to_string()
{
    rt_float_to_string=-1
    if [[ $# -ne 1 ]]
    then
        echo -e "  \033[1;31mError:\033[0m invalid argument number - float_to_string()"
        exit 1
    fi
    part1=`echo $1 | awk -F "." '{print $1}'`
    part2=`echo $1 | awk -F "." '{print $2}'`
    rt_float_to_string=${part1:-0}p${part2:-0}
    echo $rt_float_to_string
}

##

#
tJETETAMIN=$(float_to_string $JETETAMIN)
tJETETAMAX=$(float_to_string $JETETAMAX)
INPUTFILENAME=${INPUTDIR}/${INPUTSUB}.root
OUTPUTFILENAME=${OUTPUTDIR}/tmva_${OUTPUTSUB}_jetpt_${JETPT}_jeteta_${tJETETAMIN}_${tJETETAMAX}.root

##

./prepDsample.exe ${INPUTFILENAME} ${OUTPUTFILENAME} ${ISMC} ${JETPT} ${JETETAMIN} ${JETETAMAX} ${MAXEVTS}
rm prepDsample.exe

##

#INPUTDIR="/export/d00/scratch/jwang/Djets/MC/"
#INPUTSUB="DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight"
#OUTPUTDIR="/export/d00/scratch/jwang/Djets/MC/"
#OUTPUTSUB="DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight"

#INPUTDIR="/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1/"
#INPUTSUB="merged"
#OUTPUTDIR="/export/d00/scratch/jwang/Djets/data/"
#OUTPUTSUB="DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1"

#INPUTDIR="/export/d00/scratch/jwang/Djets/data/"
#INPUTSUB="DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614"
#OUTPUTDIR="/export/d00/scratch/jwang/Djets/data/"
#OUTPUTSUB="DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614"
