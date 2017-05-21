#!/usr/bin/env bash

if [ $# -lt 1 ]
then
clear
echo ""
echo " +----------------------------------------------------+"
echo " |   This script allows to select list of stars to    |"
echo " |              calculate the PSF model               |"
echo " |                                                    |"
echo " |  * Version 2017-05-21                              |"
echo " |  * Licensed under the MIT license:                 |"
echo " |    http://opensource.org/licenses/MIT              |"
echo " |  * Copyright (c) 2017 Przemysław Bruś              |"
echo " +----------------------------------------------------+"
echo " | Script generates the best list of stars which can  |"
echo " | be used to calculate the PSF model. As input param.|"
echo " | it requires a fits image and a list of all stars   |"
echo " | found on this frame.                               |"
echo " +----------------------------------------------------+"
echo " | Required additional software:                      |"
echo " | 1. demulos (written in C)                          |"
echo " | 2. peak from ESO eclipse library                   |"
echo " | 3. fwhm_av.py by Zbigniew Kołaczkowski             |"
echo " +----------------------------------------------------+"
echo " | Before use set parameters in this script inside    |"
echo " | the == SET PARAMETERS == section                   |"
echo " +----------------------------------------------------+"
echo " |                      Usage:                        |"
echo " | demulos.bash --list listName --image imageName     |"
echo " +----------------------------------------------------+"
echo ""
exit 0
fi

# ===================== SET PARAMETERS =====================
# set variables describing the structure of the list file
# with all stars and size of the header

headerSize=0
columnWithId=1
columnWithXCorrdinate=2
columnWithYCoordinate=3
columnWithMagnitude=4
columnWithMagnitudeError=5

# set the number of stars to create the initial list of stars
# to a PSF model

numberOfStarsToInitialList=200

# set a one parameter to demulos. The rest of arguments is
# calculated based on the list with stars and image

differenceOfMagnitudes=3.0

# set a maximum error of brightness. It's needed
# to determine the faintest star on the image

maxErrorOfReliableMagnitude=0.2

# To see more info about two last parameters please run the
# program with --help option: demulos --help
# ==========================================================



iterator=0

for arg in $@
do
    iterator=$((iterator + 1))

    if [ "$arg" == "--list" ]
    then
        listFile=${@:$((iterator + 1)):1}
    elif [ "$arg" == "--image" ]
    then
        imageFile=${@:$((iterator + 1)):1}
    fi
done

if [ -z "$listFile" ] || [ -z "$imageFile" ]
then
    echo "$0: Check the labels of arguments!"
    exit
else
    if [ ! -e $listFile ]
    then
        echo "$0: $listFile doesn't exist"
        exit
    fi

    if [ ! -e $imageFile ]
    then
        echo "$0: $imageFile doesn't exist"
        exit
    fi
fi

peak -F -P '8 25 35' -m clip -k 3 $imageFile | grep -v "nan\|#" > demulos_fwhm.stars
numberOfFwhmMeasurements=`cat demulos_fwhm.stars | wc -l`
if [ $numberOfFwhmMeasurements -lt 10 ]
then
    echo "$0: Too small number of stars for reliable fwhm measurements"
    rm demulos_fwhm.stars
    exit
else
    seeingValue=`fwhm_av.py demulos_fwhm.stars | awk '{print $4}'`
fi

awk \
-v hs=$headerSize \
-v id=$columnWithId \
'NR > hs {printf("%d %s\n", ++i, $id)}' $listFile > demulos_id.stars

awk \
-v hs=$headerSize \
-v x=$columnWithXCorrdinate \
-v y=$columnWithYCoordinate \
-v mag=$columnWithMagnitude \
'NR > hs {\
    printf("%10d %11.4lf %10.4lf %9.4lf\n", ++i, $x, $y, $mag)
}' $listFile > demulos_all.stars

LANG=C sort -n -k 4 demulos_all.stars | awk \
'{if ($2 > 0.0 && $3 > 0.0) print $0}' | \
head -n $numberOfStarsToInitialList > demulos_psf.stars

limitOfMagnitude=`awk \
-v mag=$columnWithMagnitude \
-v err=$columnWithMagnitudeError \
-v merr=$maxErrorOfReliableMagnitude \
'NR > hs {\
    if ($err <= merr) printf("%lf\n", $mag)
}' $listFile | LANG=C sort -n | tail -n 1`

demulos demulos_psf.stars demulos_all.stars --seeing $seeingValue --diff-mag $differenceOfMagnitudes --max-mag $limitOfMagnitude > demulos_ouput.stars

awk 'BEGIN {while (getline < "demulos_id.stars") num[$1] = $2} {print num[$1]}' demulos_ouput.stars > demulos_psf_id.stars

awk \
-v hs=$headerSize \
-v id=$columnWithId \
'BEGIN {while (getline < "demulos_psf_id.stars") num[$1] = $1} \
NR <= hs \
{
    print $0
}
NR > hs \
{
    if ($id == num[$id])
    {
        print $0
    }
}' $listFile > ${listFile}-demulos

rm demulos_*.stars
