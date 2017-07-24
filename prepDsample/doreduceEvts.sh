#!/bin/bash

#
INPUTFILENAME="/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HIHardProbes_PbPb_5TeV_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1_jetpt_40_jeteta_0p0_2p0.root"
OUTPUTFILENAME="/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HIHardProbes_PbPb_5TeV_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1_jetpt_40_jeteta_0p0_2p0_evt1per.root"
SKIMSIZE=0.01

# Don't modify the content below, if you don't know what they mean. #

#
g++ reduceEvts.C $(root-config --cflags --libs) -g -o reduceEvts.exe


echo
set -x
./reduceEvts.exe $INPUTFILENAME $OUTPUTFILENAME $SKIMSIZE
set +x

rm reduceEvts.exe
