#!/bin/bash

DOVARIABLES=1

#
PTMIN=(4 4 10 30)
PTMAX=(10 20 30 1000)
DRBIN=(0 0.05 0.1 0.2 0.5)
COLSYST=('pp')
VAR=('(DsvpvDistance/DsvpvDisErr)' 'Dchi2cl' 'Dalpha' 'Dtrk1Pt' 'Dtrk2Pt')
VARNAME=('decaylength' 'vprob' 'alpha' 'trk1pt' 'trk2pt')
VARLATEX=('d_{0}/Err(d_{0})' 'vertexProbability' '#alpha' 'trk1pt' 'trk2pt')
VARN=(50 50 50 50 50)
VARMIN=(0 0 0 0 0)
VARMAX=(15 1 0.2 20 20)
OUTPUT='plots/variables'
#
INPUTSNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_80_jeteta_0p3_1p6.root')
INPUTBNAME=('/export/d00/scratch/jwang/Djets/data/tmva_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1_jetpt_80_jeteta_0p3_1p6.root')
CUT=('TMath::Abs(Dtrk1Eta)<2.0&&TMath::Abs(Dtrk2Eta)<2.0&&Dtrk1Pt>2.0&&Dtrk2Pt>1.5&&(Dtrk1PtErr/Dtrk1Pt)<0.3&&(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dtrk1highPurity&&Dtrk2highPurity&&fabs(Dy)<2.0&&(DsvpvDistance/DsvpvDisErr)>0.0&&Dalpha<0.2&&Dchi2cl>0.05')
MYCUTS=("${CUT[0]}&&Dgen==23333")
MYCUTB=("${CUT[0]}&&TMath::Abs(Dmass-1.865)>0.1&&TMath::Abs(Dmass-1.865)<0.15")

##
nPT=$((${#PTMIN[@]}))
nDR=$((${#DRBIN[@]}-1))
nCOL=${#COLSYST[@]}
nVAR=${#VAR[@]}

#
NC='\033[0m'

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

#
g++ variables.C $(root-config --cflags --libs) -Werror -Wall -O2 -o variables.exe

#
FOLDERS=("plots")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]
    then
	mkdir -p $i
    fi
done

##
if [ $DOVARIABLES -eq 1 ]; then
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
		k=0
		while ((k<$nVAR))
		do
                    echo -e "-- Processing \033[1;33mvariables.C ${NC} pT bin: \033[1;32m${PTMIN[i]} - ${PTMAX[i]} GeV/c${NC}, deltaR bin: \033[1;32m${DRBIN[l]} - ${DRBIN[l+1]}${NC}, variable: \033[1;34m${VAR[k]}${NC}"
		    OUTPUTNAME=${OUTPUT}_${COLSYST[j]}_pt_${tPTMIN}_${tPTMAX}_deltaR_${tDRMIN}_${tDRMAX}
		    ./variables.exe ${INPUTSNAME[j]} ${INPUTBNAME[j]} $OUTPUTNAME ${MYCUTS[j]} ${MYCUTB[j]} ${VAR[k]} ${VARNAME[k]} ${VARLATEX[k]} ${VARN[k]} ${VARMIN[k]} ${VARMAX[k]} ${COLSYST[j]} ${PTMIN[i]} ${PTMAX[i]} ${DRBIN[l]} ${DRBIN[l+1]}
                    #root -l -b -q 'variables.C+('\"${VAR[k]}\"','\"${VARNAME[k]}\"','\"${VARLATEX[k]}\"','${VARN[k]}','${VARMIN[k]}','${VARMAX[k]}','\"${COLSYST[j]}\"','${PTBIN[i]}','${PTBIN[i+1]}')'
                    echo
                    k=$(($k+1))
		done
		l=$(($l+1))
	    done
            i=$(($i+1))
        done
        j=$(($j+1))
    done
fi

rm variables.exe