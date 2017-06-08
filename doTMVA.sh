#!/bin/bash

DOTMVA=1
DOREADXML=0

#
PTMIN=(6)
PTMAX=(1000)
DRBIN=(0 0.05 0.1 0.2 0.5)
COLSYST=('pp')
MVA='CutsSA'
#
INPUTSNAME=('/export/d00/scratch/jwang/Djets/MC/tmva_vector_DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight_jetpt_80_jeteta_0p3_1p6.root')
INPUTBNAME=('/export/d00/scratch/jwang/Djets/data/tmva_vector_DjetFiles_HighPtJet80_pp_5TeV_Dfinder_2april_v1_jetpt_80_jeteta_0p3_1p6.root')
CUT=('TMath::Abs(Dtrk1Eta)<2.0&&TMath::Abs(Dtrk2Eta)<2.0&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(Dtrk1PtErr/Dtrk1Pt)<0.3&&(Dtrk2PtErr/Dtrk2Pt)<0.3&&Dtrk1highPurity&&Dtrk2highPurity&&fabs(Dy)<2.0&&(DsvpvDistance/DsvpvDisErr)>0.0&&Dalpha<0.2&&Dchi2cl>0.05')
MYCUTS=("${CUT[0]}&&Dgen==23333")
MYCUTB=("${CUT[0]}&&TMath::Abs(Dmass-1.865)>0.1&&TMath::Abs(Dmass-1.865)<0.15")

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
        echo "  Error: invalid argument number - float_to_string()"
        exit 1
    fi
    part1=`echo $1 | awk -F "." '{print $1}'`
    part2=`echo $1 | awk -F "." '{print $2}'`
    rt_float_to_string=${part1:-0}p${part2:-0}
}

#
FOLDERS=("myTMVA/weights" "myTMVA/ROOT")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]
    then
	mkdir -p $i
    fi
done

##

# TMVAClassification.C #
if [ $DOTMVA -eq 1 ]; then
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
		echo "-- Processing pT bin: ${PTMIN[i]} - ${PTMAX[i]} GeV/c"
		echo
		#./TMVAClassification.exe ${INPUTSNAME[j]} ${INPUTBNAME[j]} ${MYCUTS[j]} ${MYCUTB[j]} ${COLSYST[j]} ${PTMIN[i]} ${PTMAX[i]} ${DRBIN[l]} ${DRBIN[l+1]}
		root -l -b -q 'TMVAClassification.C+('\"${INPUTSNAME[j]}\"','\"${INPUTBNAME[j]}\"','\"${MYCUTS[j]}\"','\"${MYCUTB[j]}\"','\"${COLSYST[j]}\"','${PTMIN[i]}','${PTMAX[i]}','${DRBIN[l]}','${DRBIN[l+1]}')'
		mv weights/TMVAClassification_${MVA[k]}.weights.xml weights/TMVA_${MVA[k]}_${COLSYST[j]}_pt_${tPTMIN}_${tPTMAX}_deltaR_${tDRMIN}_${tDRMAX}.weights.xml
		mv weights/TMVAClassification_${MVA[k]}.class.C weights/TMVA_${MVA[k]}_${COLSYST[j]}_pt_${tPTMIN}_${tPTMAX}_deltaR_${tDRMIN}_${tDRMAX}.class.C
		cd ..
		l=$(($l+1))
	    done    
	    i=$(($i+1))
        done
        j=$(($j+1))
    done    
fi

# readxml.cc #
if [ $DOREADXML -eq 1 ]; then
    j=0
    while ((j<$nCOL))
    do
        i=0
        while ((i<$nPT))
        do
            k=0
            while ((k<$nMVA))
            do
                cd readxml/
                echo "-- Processing pT bin: ${PTBIN[i]} - ${PTBIN[i+1]} GeV/c"
                echo
                root -l -b -q 'readxml.cc+('\"../myTMVA/weights/TMVA_${MVA[k]}_${COLSYST[j]}_${PTBIN[i]}_${PTBIN[i+1]}.weights.xml\"','\"${MVA[k]}\"','\"${COLSYST[j]}\"','${PTBIN[i]}','${PTBIN[i+1]}','${LUMI[j]}','${RAA[i]}','${NSKIM[j]}')'
                k=$(($k+1))
                cd ..
            done
            i=$(($i+1))
        done
        j=$(($j+1))
    done
fi