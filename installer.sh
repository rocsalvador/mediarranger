#!/bin/bash

if [ $USER != root ]; then
    echo !! You must be root
    exit 1
fi

if [ "$1" = "-r" ]; then
    if [ ! -f /usr/bin/mediarrenger ]; then
        echo "mediarrenger is not installed"
        exit
    fi

    rm /usr/bin/mediarrenger
    rm /usr/share/applications/mediarrenger.desktop
    if [ $? -eq 0 ]; then
        echo mediarrenger uninstalled successfully
    else
        echo !! Failed to uninstall mediarrenger
        exit 1
    fi
else
    if [ -f /usr/bin/mediarrenger ]; then
        echo "mediarrenger is already installed"
        exit
    fi

    cp mediarrenger.sh /usr/bin/mediarrenger

    echo "[Desktop Entry]
Version=1.0
Type=Application
Terminal=true
Exec=mediarrenger
Name=mediarrenger
Icon=image-jpeg
Categories=System" > /usr/share/applications/mediarrenger.desktop
    if [ $? -eq 0 ]; then
        echo mediarrenger installed successfully
    else
        echo !! Failed to install mediarrenger
        exit 1
    fi
fi
