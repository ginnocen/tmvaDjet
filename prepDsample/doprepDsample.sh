#!/bin/sh

##

#
INPUTDIR="/export/d00/scratch/ginnocen/DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1/"
INPUTSUB="merged"
OUTPUTDIR="/export/d00/scratch/jwang/Djets/data/"
OUTPUTSUB="DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1"

#
JETPT=80
JETETAMIN=0.3
JETETAMAX=1.6
MAXEVTS=-1

##

#
rt_float_to_string=-1
float_to_string()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "  \033[1;31mError:\033[0m invalid argument number - float_to_string()"
        exit 1
    fi
    part1=`echo $1 | awk -F "." '{print $1}'`
    part2=`echo $1 | awk -F "." '{print $2}'`
    rt_float_to_string=${part1:-0}p${part2:-0}
}

##

#
float_to_string $JETETAMIN
tJETETAMIN=$rt_float_to_string
float_to_string $JETETAMAX
tJETETAMAX=$rt_float_to_string
INPUTFILENAME=${INPUTDIR}/${INPUTSUB}.root
OUTPUTFILENAME=${OUTPUTDIR}/tmva_${OUTPUTSUB}_jetpt_${JETPT}_jeteta_${tJETETAMIN}_${tJETETAMAX}.root

##

root -b -q 'prepDsample.C+('\"${INPUTFILENAME}\"','\"${OUTPUTFILENAME}\"','${JETPT}','${JETETAMIN}','${JETETAMAX}','${MAXEVTS}')'
