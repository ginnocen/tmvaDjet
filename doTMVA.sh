#!/bin/bash

DOTMVA=1
DOREADXML_SAVEHIST=1
DOREADXML_FITHIST=1

#
PTMIN=(4)
PTMAX=(10)
DRBIN=(0 0.05 0.1 0.2 0.5)
COLSYST=('pp')
MVA='CutsSA'
#
INPUTSNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_80_jeteta_0p3_1p6.root')
INPUTBNAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1_jetpt_80_jeteta_0p3_1p6.root')
CUT=('TMath::Abs(Dtrk1Eta)<2.0&&TMath::Abs(Dtrk2Eta)<2.0&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(Dtrk1PtErr/Dtrk1Pt)<0.3&&(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dtrk1highPurity&&Dtrk2highPurity&&fabs(Dy)<2.0&&(DsvpvDistance/DsvpvDisErr)>0.0&&Dalpha<0.2&&Dchi2cl>0.05')
MYCUTS=("${CUT[0]}&&Dgen==23333")
MYCUTB=("${CUT[0]}&&TMath::Abs(Dmass-1.865)>0.1&&TMath::Abs(Dmass-1.865)<0.15")

INPUTMCNAME=("${INPUTSNAME[0]}")
INPUTDANAME=("${INPUTBNAME[0]}")

# Do not touch the macros below if you don't know what they mean #
##
nPT=$((${#PTMIN[@]}))
nDR=$((${#DRBIN[@]}-1))
nCOL=${#COLSYST[@]}

#
rt_float_to_string=-1
float_to_string()
{
    if [[ $# -ne 1 ]]
    then
        echo -e "  \033[1;31mError:${NC} invalid argument number - float_to_string()"
        exit 1
    fi
    part1=`echo $1 | awk -F "." '{print $1}'`
    part2=`echo $1 | awk -F "." '{print $2}'`
    rt_float_to_string=${part1:-0}p${part2:-0}
}
NC='\033[0m'

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
    j=0
    while ((j<$nCOL))
    do
        i=0
        while ((i<$nPT))
        do
	    float_to_string ${PTMIN[i]}
            tPTMIN=$rt_float_to_string
            float_to_string ${PTMAX[i]}
            tPTMAX=$rt_float_to_string
	    l=0
	    while ((l<$nDR))
	    do
		float_to_string ${DRBIN[l]}
                tDRMIN=$rt_float_to_string
                float_to_string ${DRBIN[l+1]}
                tDRMAX=$rt_float_to_string

		cd myTMVA/
		echo -e "-- Processing \033[1;33mTMVAClassification.C ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRBIN[l]} - ${DRBIN[l+1]}${NC}"
		root -l -b -q 'TMVAClassification.C+('\"${INPUTSNAME[j]}\"','\"${INPUTBNAME[j]}\"','\"${MYCUTS[j]}\"','\"${MYCUTB[j]}\"','\"${COLSYST[j]}\"','${PTMIN[i]}','${PTMAX[i]}','${DRBIN[l]}','${DRBIN[l+1]}')'
		mv weights/TMVAClassification_${MVA[k]}.weights.xml weights/TMVA_${MVA[k]}_${COLSYST[j]}_pt_${tPTMIN}_${tPTMAX}_deltaR_${tDRMIN}_${tDRMAX}.weights.xml
		mv weights/TMVAClassification_${MVA[k]}.class.C weights/TMVA_${MVA[k]}_${COLSYST[j]}_pt_${tPTMIN}_${tPTMAX}_deltaR_${tDRMIN}_${tDRMAX}.class.C
		cd ..
		echo

		l=$(($l+1))
	    done    
	    i=$(($i+1))
        done
        j=$(($j+1))
    done    
fi

# readxml.cc #
if [[ $DOREADXML_SAVEHIST -eq 1 || $DOREADXML_FITHIST -eq 1 ]]
then
    j=0
    while ((j<$nCOL))
    do
        i=0
        while ((i<$nPT))
        do
	    float_to_string ${PTMIN[i]}
            tPTMIN=$rt_float_to_string
            float_to_string ${PTMAX[i]}
            tPTMAX=$rt_float_to_string
	    l=0
	    while ((l<$nDR))
            do
                float_to_string ${DRBIN[l]}
                tDRMIN=$rt_float_to_string
                float_to_string ${DRBIN[l+1]}
                tDRMAX=$rt_float_to_string

                cd readxml/
		TEND=TMVA_${MVA[k]}_${COLSYST[j]}_pt_${tPTMIN}_${tPTMAX}_deltaR_${tDRMIN}_${tDRMAX}

		if [ $DOREADXML_SAVEHIST -eq 1 ]
		then
		    echo -e "-- Processing \033[1;33mreadxml_savehist.cc ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRBIN[l]} - ${DRBIN[l+1]}${NC}"
		    if [ -f "../myTMVA/weights/${TEND}.weights.xml" ]
		    then
			root -b -q 'readxml_savehist.cc+('\"${INPUTMCNAME[j]}\"','\"${INPUTDANAME[j]}\"','\"${TEND}\"','\"../myTMVA/weights/${TEND}.weights.xml\"','\"${COLSYST[j]}\"','${PTMIN[i]}','${PTMAX[i]}','${DRBIN[l]}','${DRBIN[l+1]}')'
		    else
			echo -e "  \033[1;31mError:${NC} no weight file: ../myTMVA/weights/${TEND}.weights.xml"
		    fi
		    echo
		fi

		if [ $DOREADXML_FITHIST -eq 1 ]
		then
		    echo -e "-- Processing \033[1;33mreadxml_fithist.cc ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR range: \033[1;32m${DRBIN[l]} - ${DRBIN[l+1]}${NC}"
		    if [ -f "rootfiles/fmass_${TEND}.root" ]
		    then
			root -b -q 'readxml_fithist.cc+('\"${TEND}\"','\"${TEND}\"','\"../myTMVA/weights/${TEND}.weights.xml\"','\"${COLSYST[j]}\"','${PTMIN[i]}','${PTMAX[i]}','${DRBIN[l]}','${DRBIN[l+1]}')'
		    else
			echo -e "  \033[1;31mError:${NC} no savehist file: rootfiles/fmass_${TEND}.root"
		    fi
		    echo
		fi

                cd ..

		l=$(($l+1))
            done
            i=$(($i+1))
        done
        j=$(($j+1))
    done
fi