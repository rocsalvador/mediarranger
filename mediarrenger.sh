#!/bin/bash

ca_months=("Gener" "Febrer" "Març" "Abril" "Maig" "Juny" "Juliol" "Agost" "Setembre" "Octubre" "Novembre" "Desembre")
en_months=("January" "February" "March" "April" "May" "June" "July" "August" "September" "October" "November" "December")

arrangemedia() {
    if [ "$month" -lt  10 ]; then
        monthindex=${month:1}
    fi

    monthname=${monthsarray[$((monthindex-1))]}

    if [ ! -d "$ODIR$year/$month-$monthname" ]; then
        mkdir -p "$ODIR$year/$month-$monthname"
    fi

    mv "$file" "$ODIR$year/$month-$monthname" 2> /dev/null

    np=$(( np + 1 ))
}

checksdir() {
    if [ "${SDIR: -1}" != "/" ]; then
        SDIR=$SDIR/
    fi

    echo "Searching and arranging media in $SDIR..."

    for file in "$SDIR"*
    do
        if [ -f "$file" ]; then
            if [[ $file == *.jpg ]]; then
                date=$(exif "$file" 2> /dev/null | grep "Date and Time  ")
                year=$(echo $date | cut -b 16-19)
                month=$(echo $date | cut -b 21-22)
                monthindex=$month

                if [ "$date" != "" ]; then
                    arrangemedia
                else
                    echo "$file" metadata does not contain date info or it is not compatible
                    tp=$(( tp + 1 ))
                fi
            elif [[ $file == *.mp4 ]] || [[ $file == *.MP4 ]]; then
                date=$(mediainfo "$file" 2> /dev/null | grep "Tagged date")
                year=$(echo $date | cut -b 19-22)
                month=$(echo $date | cut -b 24-25)
                monthindex=$month

                if [ "$date" != "" ]; then
                    arrangemedia
                else
                    echo "$file" metadata does not contain date info or it is not compatible
                    tp=$(( tp + 1 ))
                fi
            fi
        elif [ "$RECURSIVE" -eq 1 ] && [ -d "$file" ]; then
            SDIR=$file
            checksdir
        fi
    done
}

usage() {
    echo "USAGE:"
    echo "mediarranger -s /path/to/source/dir -o /path/to/output/dir [OPTIONAL ARGUMENTS]"
    echo
    echo "OPTIONAL ARGUMENTS:"
    echo "-r | --recursive      All subdirectories of source directory will be checked"
}


RECURSIVE=0
OFLAG=0
SFLAG=0

while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
    -r|--recursive)
        RECURSIVE=1
        shift # past argument
        ;;
    -s|--sourcepath)
        SDIR="$2"
        if [ ! -d "$SDIR" ]; then
            echo "ERROR: invalid source path"
            exit 1
        fi
        SFLAG=1
        shift # past argument
        shift # past value
        ;;
    -o|--outputpath)
        ODIR="$2"
        if [ ! -d "$ODIR" ]; then
            echo "ERROR: invalid output path"
            exit 1
        fi
        OFLAG=1
        shift # past argument
        shift # past value
        ;;
    -h|--help)
        usage
        exit
        ;;
    *)    # unknown option
        echo "Unknown option $1, ignoring it"
        shift # past argument
        ;;
    esac
done

if [ $OFLAG -eq 0 ] || [ $SFLAG -eq 0 ]; then
    usage
    exit
fi

np=0
tp=0
if [ "$LANG" = "ca_ES.UTF-8" ]; then
    monthsarray=("${ca_months[@]}")
else
    monthsarray=("${en_months[@]}")
fi

checksdir

echo
tp=$(( np + tp ))
echo "Done! $np media files of $tp have been arranged correctly"
echo "Press return to exit"
read -r
