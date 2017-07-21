#!/bin/bash
# dofitD.sh #

##
COLSYST=('pp')
JETPTMIN=(40)
JETETAMIN=(0)
JETETAMAX=(2.0)
#
PTMIN=(6 4 20)
PTMAX=(999 20 999)
#
DRMIN=(0. 0.1 0.2)
DRMAX=(0.1 0.2 0.5)
#
INPUTMCNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_40_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_40_jeteta_0p0_2p0.root')
INPUTDANAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_jetpt_40_jeteta_0p0_2p0.root')

# Do not touch the macros below if you don't know what they mean #
##
nPT=$((${#PTMIN[@]}))
nDR=$((${#DRMIN[@]}))
nCOL=${#COLSYST[@]}

#
NC='\033[0m'

#
function float_to_string()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - float_to_string()"
        exit 1
    fi
    part1=`echo $1 | awk -F "." '{print $1}'`
    part2=`echo $1 | awk -F "." '{print $2}'`
    rt_float_to_string=${part1:-0}p${part2:-0}
    echo $rt_float_to_string
}

#
FOLDERS=("plotfits")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]
    then
	mkdir -p $i
    fi
done

##

# fitD.C #
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe
j=0
while ((j<$nCOL))
do
    tJET=jetpt_$(float_to_string ${JETPTMIN})_jeteta_$(float_to_string ${JETETAMIN})_$(float_to_string ${JETETAMAX})
    i=0
    while ((i<$nPT))
    do
        tPT=pt_$(float_to_string ${PTMIN[i]})_$(float_to_string ${PTMAX[i]})
	l=0
	while ((l<$nDR))
        do
            tDR=deltaR_$(float_to_string ${DRMIN[l]})_$(float_to_string ${DRMAX[l]})            
	    TEND=${COLSYST[j]}_${tJET}_pt_${tPT}_${tDR}
            echo -e "-- Processing \033[1;33mfitD.C${NC}, \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, dR \033[1;32m${DRMIN[l]} - ${DRMAX[l]}${NC}"
            set -x
	    ./fitD.exe "${INPUTMCNAME[j]}" "${INPUTDANAME[j]}" "plotfits/cmass_${TEND}" "${COLSYST[j]}" ${JETPTMIN} ${JETETAMIN} ${JETETAMAX} ${PTMIN[i]} ${PTMAX[i]} ${DRMIN[l]} ${DRMAX[l]}
            set +x
	    l=$(($l+1))
	    echo
        done
        i=$(($i+1))
    done
    j=$(($j+1))
done
rm fitD.exe


##

# INPUTDANAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1_jetpt_80_jeteta_0p0_2p0.root')
# INPUTMCNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_40_jeteta_0p0_2p0.root')
# INPUTDANAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_jetpt_40_jeteta_0p0_2p0.root')
