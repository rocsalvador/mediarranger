#!/bin/bash

SCRIPTPATH="/usr/bin/mediarranger"
DESKTPATH="/usr/share/applications/mediarranger.desktop"

if [ $USER != root ]; then
    echo !! You must be root
    exit 1
fi

if [ "$1" = "-r" ]; then
    if [ ! -f $SCRIPTPATH ]; then
        echo "mediarranger is not installed"
        exit
    fi

    rm $SCRIPTPATH
    rm $DESKTPATH
    if [ $? -eq 0 ]; then
        echo mediarranger uninstalled successfully
    else
        echo !! Failed to uninstall mediarranger
        exit 1
    fi
else
    if [ -f $SCRIPTPATH ]; then
        echo "mediarranger is already installed"
        exit
    fi

    cp mediarranger.sh $SCRIPTPATH

    echo "[Desktop Entry]
Version=1.0
Type=Application
Terminal=true
Exec=mediarranger
Name=mediarranger
Icon=image-jpeg
Categories=System" > $DESKTPATH
    if [ $? -eq 0 ]; then
        echo mediarranger installed successfully
    else
        echo !! Failed to install mediarranger
        exit 1
    fi
fi
