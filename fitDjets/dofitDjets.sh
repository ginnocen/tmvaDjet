#!/bin/bash
# dofitDjets.sh #

# -1: loop all bins
jCOLSYST=2

# nCOL loop
COLSYST=('pp' 'pp' 'PbPb')
JETPTMIN=(40 80 40)
JETETAMIN=(0 0 0)
JETETAMAX=(2.0 2.0 2.0)

INPUTMCNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_40_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_40_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight_jetpt_40_jeteta_0p0_2p0.root')
INPUTDANAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_jetpt_40_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1_jetpt_80_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HIHardProbes_PbPb_5TeV_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1_jetpt_40_jeteta_0p0_2p0.root')

# Do not touch the macros below if you don't know what they mean #
#
nCOL=${#COLSYST[@]}

#
NC='\033[0m'

#
function run_this_bin()
{
    if [[ $# -ne 2 ]]
    then
        echo -e "\033[1;31merror:${NC} invalid argument number - run_this_bin()"
        exit 1
    fi
    rt_run_this_bin=0
    if [ $1 -eq $2 ] || [ $2 -eq -1 ]
    then
        rt_run_this_bin=1
    fi
    echo $rt_run_this_bin
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

# fitDjets.C #
g++ fitDjets.C $(root-config --cflags --libs) -g -o fitDjets.exe
j=0
while ((j<$nCOL))
do
    if [ $(run_this_bin $j $jCOLSYST) -eq 1 ]
    then
        echo -e "-- Processing \033[1;33mfitDjets.C${NC}"
        set -x
        ./fitDjets.exe "${INPUTMCNAME[j]}" "${INPUTDANAME[j]}" "${COLSYST[j]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]}
        set +x
        echo
    fi
    j=$(($j+1))
done
rm fitDjets.exe


##

# INPUTDANAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1_jetpt_80_jeteta_0p0_2p0.root')
# INPUTMCNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_40_jeteta_0p0_2p0.root')
# INPUTDANAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_jetpt_40_jeteta_0p0_2p0.root')
