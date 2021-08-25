TEMPLATE = app

QT += widgets

FORMS += src/MainWindow.ui
SOURCES += src/main.cpp src/MainWindow.cpp src/ExifTool.cpp src/ExifToolPipe.cpp src/TagInfo.cpp src/Worker.cpp
HEADERS += src/MainWindow.h src/ExifTool.h src/ExifToolPipe.h src/TagInfo.h src/Worker.h

MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build

DESTDIR = build

CONFIG += c++17
