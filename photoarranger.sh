#!/bin/bash

ca_months=("Gener" "Febrer" "Març" "Abril" "Maig" "Juny" "Juliol" "Agost" "Setembre" "Octubre" "Novembre" "Desembre")
en_months=("January" "February" "March" "April" "May" "June" "July" "August" "September" "October" "November" "December")

arrangeimages() {
    if [ "${PDIR: -1}" != "/" ]; then
        PDIR=$PDIR/
    fi

    echo Searching and arranging photos in $PDIR...

    for file in $PDIR*
    do
        if [ -f $file ] && [[ $file == *.jpg ]]; then
            date=$(exif $file 2> /dev/null | grep "Date and Time  ")
            if [ "$date" != "" ]; then
                year=$(echo $date | cut -b 16-19)
                month=$(echo $date | cut -b 21-22)
                if [ $month -lt  10 ]; then
                    month=${month:1}
                fi

                month=${monthsarray[$((month-1))]}

                if [ ! -d $BDIR$year/$month ]; then
                    mkdir -p $BDIR$year/$month
                fi

                mv $file $BDIR$year/$month 2> /dev/null

                np=$(( np + 1 ))
            else
                echo $file metadata does not contain date info or it is not compatible
                tp=$(( tp + 1 ))
            fi
        elif [ -d $file ]; then
            PDIR=$file
            arrangeimages
        fi
    done
}

echo -n "Directory where photos will be stored: "
read BDIR
if [ "${BDIR: -1}" != "/" ]; then
    BDIR=$BDIR/
fi
echo -n "Directory where the photos are located: "
read PDIR

np=0
tp=0
if [ "$LANG" = "ca_ES.UTF-8" ]; then
    monthsarray=("${ca_months[@]}")
else
    monthsarray=("${en_months[@]}")
fi

arrangeimages

echo
tp=$(( np + tp ))
echo Done! $np images of $tp have been arranged correctly
echo Press return to exit
read
