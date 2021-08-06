#!/bin/bash

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
                if [ $month -eq 1 ]; then
                    month="Gener"
                elif [ $month -eq 2 ]; then
                    month="Febrer"
                elif [ $month -eq 3 ]; then
                    month="Març"
                elif [ $month -eq 4 ]; then
                    month="Abril"
                elif [ $month -eq 5 ]; then
                    month="Maig"
                elif [ $month -eq 6 ]; then
                    month="Juny"
                elif [ $month -eq 7 ]; then
                    month="Juliol"
                elif [ $month -eq 8 ]; then
                    month="Agost"
                elif [ $month -eq 9 ]; then
                    month="Setembre"
                elif [ $month -eq 10 ]; then
                    month="Octubre"
                elif [ $month -eq 11 ]; then
                    month="Novembre"
                elif [ $month -eq 12 ]; then
                    month="Desembre"
                fi

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
arrangeimages

echo
tp=$(( np + tp ))
echo Done! $np images of $tp have been arranged correctly
echo Press return to exit
read
