TEMPLATE = app

QT += widgets

FORMS += src/MainWindow.ui
SOURCES += src/main.cpp src/MainWindow.cpp src/MediaArranger.cpp src/ExifTool.cpp src/ExifToolPipe.cpp src/TagInfo.cpp
HEADERS += src/MainWindow.h src/MediaArranger.h src/ExifTool.h src/ExifToolPipe.h src/TagInfo.h

MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build

DESTDIR = build

CONFIG += c++17
