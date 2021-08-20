#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QIcon>

#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("../icons/icon.png"));

    MainWindow w;
    w.show();

    return app.exec();
}
