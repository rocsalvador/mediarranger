TEMPLATE = app

QT += widgets

FORMS += MainWindow.ui
SOURCES += main.cpp MainWindow.cpp BrowseButton.cpp MediaArranger.cpp ExifTool.cpp ExifToolPipe.cpp TagInfo.cpp
HEADERS += MainWindow.h BrowseButton.h MediaArranger.h ExifTool.h ExifToolPipe.h TagInfo.h

MOC_DIR = build
OBJECTS_DIR = build
UI_DIR =

DESTDIR = build

CONFIG += c++17
