#!/bin/sh

DOTMVA=0
DOREADXML_SAVEHIST=0
DOREADXML_USEHIST=1

##
#
COLSYST=('pp')
LUMI=(27.4) # need to update
#
JETPTMIN=80
JETETAMIN=0
JETETAMAX=0.2
MVA='CutsSA'
#
PTMIN=(4 20 6)
PTMAX=(20 999 999)
RAA=(1 1 1)
#
DRMIN=(0 0 0.1 0.2)
DRMAX=(0.05 0.1 0.2 0.5)

##
INPUTSNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_60_jeteta_0p0_2p0.root')
INPUTBNAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1_jetpt_80_jeteta_0p0_2p0.root')
CUT=('TMath::Abs(Dtrk1Eta)<2.0&&TMath::Abs(Dtrk2Eta)<2.0&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(Dtrk1PtErr/Dtrk1Pt)<0.3&&(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dtrk1highPurity&&Dtrk2highPurity&&fabs(Dy)<2.0&&(DsvpvDistance/DsvpvDisErr)>0.0&&Dalpha<0.2&&Dchi2cl>0.05')
MYCUTS=("${CUT[0]}&&Dgen==23333")
MYCUTB=("${CUT[0]}&&TMath::Abs(Dmass-1.865)>0.1&&TMath::Abs(Dmass-1.865)<0.15")

INPUTMCNAME=("${INPUTSNAME[0]}")
INPUTDANAME=("${INPUTBNAME[0]}")

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
FOLDERS=("myTMVA/weights" "myTMVA/ROOT" "readxml/rootfiles" "readxml/plotfits" "readxml/plots" "readxml/results")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]
    then
	mkdir -p $i
    fi
done

##
tJET=jetpt_$(float_to_string ${JETPTMIN})_jeteta_$(float_to_string ${JETETAMIN})_$(float_to_string ${JETETAMAX})

# TMVAClassification.C #
if [ $DOTMVA -eq 1 ]
then
    cd myTMVA/
    g++ TMVAClassification.C $(root-config --cflags --libs) -l TMVA -g -o TMVAClassification.exe
    j=0
    while ((j<$nCOL))
    do
        i=0
        while ((i<$nPT))
        do
            tPT=pt_$(float_to_string ${PTMIN[i]})_$(float_to_string ${PTMAX[i]})
	    l=0
	    while ((l<$nDR))
	    do
                tDR=deltaR_$(float_to_string ${DRMIN[l]})_$(float_to_string ${DRMAX[l]})
                TEND=TMVA_${MVA}_${COLSYST[j]}_${tJET}_${tPT}_${tDR}
		echo -e "-- Processing \033[1;33mTMVAClassification.C ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRMIN[l]} - ${DRMAX[l]}${NC}"
                set -x
		./TMVAClassification.exe "${INPUTSNAME[j]}" "${INPUTBNAME[j]}" "${COLSYST[j]}" "${MYCUTS[j]}" "${MYCUTB[j]}" ${JETPTMIN} ${JETETAMIN} ${JETETAMAX} ${PTMIN[i]} ${PTMAX[i]} ${DRMIN[l]} ${DRMAX[l]}
		mv weights/TMVAClassification_${MVA}.weights.xml weights/${TEND}.weights.xml
		mv weights/TMVAClassification_${MVA}.class.C weights/${TEND}.class.C
                mv ROOT/TMVA.root ROOT/${TEND}.root
                set +x
		echo
		l=$(($l+1))
	    done    
	    i=$(($i+1))
        done
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
        i=0
        while ((i<$nPT))
        do
            tPT=pt_$(float_to_string ${PTMIN[i]})_$(float_to_string ${PTMAX[i]})
	    l=0
	    while ((l<$nDR))
            do
                tDR=deltaR_$(float_to_string ${DRMIN[l]})_$(float_to_string ${DRMAX[l]})
                TEND=TMVA_${MVA}_${COLSYST[j]}_${tJET}_${tPT}_${tDR}
		echo -e "-- Processing \033[1;33mreadxml_savehist.cc ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRMIN[l]} - ${DRMAX[l]}${NC}"
		if [ -f "../myTMVA/weights/${TEND}.weights.xml" ]
		then
                    set -x
		    ./readxml_savehist.exe "${INPUTMCNAME[j]}" "${INPUTDANAME[j]}" "${TEND}" "../myTMVA/weights/${TEND}.weights.xml" "${COLSYST[j]}" ${JETPTMIN} ${JETETAMIN} ${JETETAMAX} ${PTMIN[i]} ${PTMAX[i]} ${DRMIN[l]} ${DRMAX[l]}
                    set +x
		else
		    echo -e "\033[1;31merror:${NC} no weight file: ../myTMVA/weights/${TEND}.weights.xml"
		fi
		echo
		l=$(($l+1))
            done
            i=$(($i+1))
        done
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
        i=0
        while ((i<$nPT))
        do
            tPT=pt_$(float_to_string ${PTMIN[i]})_$(float_to_string ${PTMAX[i]})
	    l=0
	    while ((l<$nDR))
            do
                tDR=deltaR_$(float_to_string ${DRMIN[l]})_$(float_to_string ${DRMAX[l]})
                TEND=TMVA_${MVA}_${COLSYST[j]}_${tJET}_${tPT}_${tDR}
		echo -e "-- Processing \033[1;33mreadxml_usehist.cc ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRMIN[l]} - ${DRMAX[l]}${NC}"
		if [ -f "rootfiles/fmass_${TEND}.root" ]
		then
                    set -x
		    ./readxml_usehist.exe "${TEND}" "${TEND}" "../myTMVA/weights/${TEND}.weights.xml" "${COLSYST[j]}" ${PTMIN[i]} ${PTMAX[i]} ${DRMIN[l]} ${DRMAX[l]} ${LUMI[j]} ${RAA[i]}
                    set +x
		else
		    echo -e "\033[1;31merror:${NC} no savehist file: rootfiles/fmass_${TEND}.root"
		fi
		echo
		l=$(($l+1))
            done
            i=$(($i+1))
        done
        j=$(($j+1))
    done
    rm readxml_usehist.exe
    cd ..
fi