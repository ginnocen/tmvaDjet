#!/bin/bash
# doTMVA.sh #

# -1: loop all bins
jCOLSYST=-1
iPT=-1
lDR=-1
#
DOTMVA=0
DOREADXML_SAVEHIST=0
DOREADXML_USEHIST=1

##
# nCOL loop
COLSYST=('pp' 'pp' 'PbPb')
LUMI=(27.4 27.4 15.5) # need to update
JETPTMIN=(40 80 40)
JETETAMIN=(0 0 0)
JETETAMAX=(2.0 2.0 2.0)
# nPT loop
PTMIN=(4 20 6)
PTMAX=(20 999 999)
RAA=(1 1 1)
# nDR loop
DRMIN=(0 0.1 0.2)
DRMAX=(0.1 0.2 0.5)
#
MVA='CutsSA'

##
INPUTSNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_40_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_40_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170510_PbPb_5TeV_TuneCUETP8M1_Dfinder_MC_20170508_pthatweight_jetpt_40_jeteta_0p0_2p0.root')
INPUTBNAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_20170619_pp_5TeV_HighPtLowerJets_dPt4tkPt1p5Alpha0p2Decay2_D0Dstar_20170614_jetpt_40_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1_jetpt_80_jeteta_0p0_2p0.root'
    '/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HIHardProbes_PbPb_5TeV_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1_jetpt_40_jeteta_0p0_2p0_evt1per.root')
CUT=('TMath::Abs(Dtrk1Eta)<2.0&&TMath::Abs(Dtrk2Eta)<2.0&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(Dtrk1PtErr/Dtrk1Pt)<0.3&&(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dtrk1highPurity&&Dtrk2highPurity&&fabs(Dy)<2.0&&(DsvpvDistance/DsvpvDisErr)>0.0&&Dalpha<0.2&&Dchi2cl>0.05'
    'TMath::Abs(Dtrk1Eta)<2.0&&TMath::Abs(Dtrk2Eta)<2.0&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(Dtrk1PtErr/Dtrk1Pt)<0.3&&(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dtrk1highPurity&&Dtrk2highPurity&&fabs(Dy)<2.0&&(DsvpvDistance/DsvpvDisErr)>0.0&&Dalpha<0.2&&Dchi2cl>0.05'
    'TMath::Abs(Dtrk1Eta)<2.0&&TMath::Abs(Dtrk2Eta)<2.0&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(Dtrk1PtErr/Dtrk1Pt)<0.3&&(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dtrk1highPurity&&Dtrk2highPurity&&fabs(Dy)<2.0&&(DsvpvDistance/DsvpvDisErr)>0.0&&Dalpha<0.2&&Dchi2cl>0.05')
MYCUTS=("${CUT[0]}&&Dgen==23333"
    "${CUT[1]}&&Dgen==23333"
    "${CUT[2]}&&Dgen==23333")
MYCUTB=("${CUT[0]}&&TMath::Abs(Dmass-1.865)>0.1&&TMath::Abs(Dmass-1.865)<0.15"
    "${CUT[1]}&&TMath::Abs(Dmass-1.865)>0.1&&TMath::Abs(Dmass-1.865)<0.15"
    "${CUT[2]}&&TMath::Abs(Dmass-1.865)>0.1&&TMath::Abs(Dmass-1.865)<0.15")

INPUTMCNAME=("${INPUTSNAME[0]}"
    "${INPUTSNAME[1]}"
    "${INPUTSNAME[2]}")
INPUTDANAME=("${INPUTBNAME[0]}"
    "${INPUTBNAME[1]}"
    '/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HIHardProbes_PbPb_5TeV_Dfinder_skimmed_1unit_part1_2_3_4_26March_finalMerge2April_v1_jetpt_40_jeteta_0p0_2p0.root')

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
FOLDERS=("myTMVA/weights" "myTMVA/ROOT" "readxml/rootfiles" "readxml/plotfits" "readxml/plots" "readxml/results")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]
    then
	mkdir -p $i
    fi
done

##

# TMVAClassification.C #
if [ $DOTMVA -eq 1 ]
then
    cd myTMVA/
    g++ TMVAClassification.C $(root-config --cflags --libs) -l TMVA -g -o TMVAClassification.exe
    j=0
    while ((j<$nCOL))
    do 
        if [ $(run_this_bin $j $jCOLSYST) -eq 1 ]
        then
           tJET=jetpt_$(float_to_string ${JETPTMIN[j]})_jeteta_$(float_to_string ${JETETAMIN[j]})_$(float_to_string ${JETETAMAX[j]})
            i=0
            while ((i<$nPT))
            do
                if [ $(run_this_bin $i $iPT) -eq 1 ]
                then
                    tPT=pt_$(float_to_string ${PTMIN[i]})_$(float_to_string ${PTMAX[i]})
	            l=0
	            while ((l<$nDR))
	            do
                        if [ $(run_this_bin $l $lDR) -eq 1 ]
                        then
                            tDR=deltaR_$(float_to_string ${DRMIN[l]})_$(float_to_string ${DRMAX[l]})
                            TEND=TMVA_${MVA}_${COLSYST[j]}_${tJET}_${tPT}_${tDR}
		            echo -e "-- Processing \033[1;33mTMVAClassification.C ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRMIN[l]} - ${DRMAX[l]}${NC}"
                            set -x
		            ./TMVAClassification.exe "${INPUTSNAME[j]}" "${INPUTBNAME[j]}" "${COLSYST[j]}" "${MYCUTS[j]}" "${MYCUTB[j]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} ${PTMIN[i]} ${PTMAX[i]} ${DRMIN[l]} ${DRMAX[l]}
		            mv weights/TMVAClassification_${MVA}.weights.xml weights/${TEND}.weights.xml
		            mv weights/TMVAClassification_${MVA}.class.C weights/${TEND}.class.C
                            mv ROOT/TMVA.root ROOT/${TEND}.root
                            set +x
		            echo
                        fi
		        l=$(($l+1))
	            done
                fi
	        i=$(($i+1))
            done
        fi
        j=$(($j+1))
    done
    rm TMVAClassification.exe
    cd ..
fi

# readxml_savehist.cc #
if [ $DOREADXML_SAVEHIST -eq 1 ]
then
    cd readxml/                
    g++ readxml_savehist.cc $(root-config --cflags --libs) -l TMVA -l XMLIO -g -o readxml_savehist.exe
    j=0
    while ((j<$nCOL))
    do
        if [ $(run_this_bin $j $jCOLSYST) -eq 1 ]
        then
            tJET=jetpt_$(float_to_string ${JETPTMIN[j]})_jeteta_$(float_to_string ${JETETAMIN[j]})_$(float_to_string ${JETETAMAX[j]})
            i=0
            while ((i<$nPT))
            do
                if [ $(run_this_bin $i $iPT) -eq 1 ]
                then
                    tPT=pt_$(float_to_string ${PTMIN[i]})_$(float_to_string ${PTMAX[i]})
	            l=0
	            while ((l<$nDR))
                    do
                        if [ $(run_this_bin $l $lDR) -eq 1 ]
                        then
                            tDR=deltaR_$(float_to_string ${DRMIN[l]})_$(float_to_string ${DRMAX[l]})
                            TEND=TMVA_${MVA}_${COLSYST[j]}_${tJET}_${tPT}_${tDR}
		            echo -e "-- Processing \033[1;33mreadxml_savehist.cc ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRMIN[l]} - ${DRMAX[l]}${NC}"
		            if [ -f "../myTMVA/weights/${TEND}.weights.xml" ]
		            then
                                set -x
		                ./readxml_savehist.exe "${INPUTMCNAME[j]}" "${INPUTDANAME[j]}" "${TEND}" "../myTMVA/weights/${TEND}.weights.xml" "${COLSYST[j]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} ${PTMIN[i]} ${PTMAX[i]} ${DRMIN[l]} ${DRMAX[l]}
                                set +x
		            else
		                echo -e "\033[1;31merror:${NC} no weight file: ../myTMVA/weights/${TEND}.weights.xml"
		            fi
		            echo
                        fi
		        l=$(($l+1))
                    done
                fi
                i=$(($i+1))
            done
        fi
        j=$(($j+1))
    done
    rm readxml_savehist.exe
    cd ..
fi

# readxml_usehist.cc #
if [ $DOREADXML_USEHIST -eq 1 ]
then
    cd readxml/                
    g++ readxml_usehist.cc $(root-config --cflags --libs) -l TMVA -l XMLIO -g -o readxml_usehist.exe
    j=0
    while ((j<$nCOL))
    do
        if [ $(run_this_bin $j $jCOLSYST) -eq 1 ]
        then
            tJET=jetpt_$(float_to_string ${JETPTMIN[j]})_jeteta_$(float_to_string ${JETETAMIN[j]})_$(float_to_string ${JETETAMAX[j]})
            i=0
            while ((i<$nPT))
            do
                if [ $(run_this_bin $i $iPT) -eq 1 ]
                then
                    tPT=pt_$(float_to_string ${PTMIN[i]})_$(float_to_string ${PTMAX[i]})
	            l=0
	            while ((l<$nDR))
                    do
                        if [ $(run_this_bin $l $lDR) -eq 1 ]
                        then
                            tDR=deltaR_$(float_to_string ${DRMIN[l]})_$(float_to_string ${DRMAX[l]})
                            TEND=TMVA_${MVA}_${COLSYST[j]}_${tJET}_${tPT}_${tDR}
		            echo -e "-- Processing \033[1;33mreadxml_usehist.cc ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRMIN[l]} - ${DRMAX[l]}${NC}"
		            if [ -f "rootfiles/fmass_${TEND}.root" ]
		            then
                                set -x
		                ./readxml_usehist.exe "${TEND}" "${TEND}" "../myTMVA/weights/${TEND}.weights.xml" "${COLSYST[j]}" ${JETPTMIN[j]} ${JETETAMIN[j]} ${JETETAMAX[j]} ${PTMIN[i]} ${PTMAX[i]} ${DRMIN[l]} ${DRMAX[l]} ${LUMI[j]} ${RAA[i]}
                                set +x
		            else
		                echo -e "\033[1;31merror:${NC} no savehist file: rootfiles/fmass_${TEND}.root"
		            fi
		            echo
                        fi
		        l=$(($l+1))
                    done
                fi
                i=$(($i+1))
            done
        fi
        j=$(($j+1))
    done
    rm readxml_usehist.exe
    cd ..
fi