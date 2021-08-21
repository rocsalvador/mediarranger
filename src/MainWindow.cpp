#include <QDebug>
#include <QFileDialog>
#include <thread>
#include "MainWindow.h"


MainWindow::MainWindow (QMainWindow* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    arranger = new MediaArranger();
}

void MainWindow::setSource(QString source)
{
    arranger->setOutpuFolder(source.toStdString());
}


void MainWindow::setOutput(QString output)
{
    arranger->setOutpuFolder(output.toStdString());
}


void MainWindow::sourceBrowse()
{
    sourceFolder = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             "/home",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
    if(sourceFolder != "") {
        ui.lineEdit->setStyleSheet(("QLineEdit { background-color : white); }"));
        arranger->setSourceFolder(sourceFolder.toStdString());
        emit(sourceSet(sourceFolder));
    }
}

void MainWindow::outputBrowse()
{
    outputFolder = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             "/home",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
    if(outputFolder != "") {
        ui.lineEdit_2->setStyleSheet(("QLineEdit { background-color : white); }"));
        arranger->setOutpuFolder(outputFolder.toStdString());
        emit(outputSet(outputFolder));
    }
}

void MainWindow::setRecursive(bool recursive)
{
    arranger->setRecursiveSearch(recursive);
}

void MainWindow::arrange()
{
    if(arranger->getSourceFolder() == "") {
        ui.lineEdit->setStyleSheet(("QLineEdit { background-color : rgb(255, 176, 176); }"));
    }
    if(arranger->getOutputFolder() == "") {
        ui.lineEdit_2->setStyleSheet(("QLineEdit { background-color : rgb(255, 176, 176); }"));
    }
    if(arranger->getOutputFolder() != "" and arranger->getSourceFolder() != "") {
        ui.pushButton_3->setEnabled(false);
        std::thread t1(&MainWindow::dialogSetter, this);
        std::thread t2(&MediaArranger::arrange, arranger);
        t1.join();
        t2.join();
        ui.pushButton_3->setEnabled(true);
    }
}

void MainWindow::dialogSetter()
{
    int percentageDone = 0;
    string currentDirectory = arranger->getCurrentDirectory();
    while(percentageDone < 100) {
        while(arranger->getPercentageDone() == percentageDone);
        ui.progressBar->setValue(percentageDone);
        ui.label_4->setText("Searching media in " + QString::fromStdString(currentDirectory));
        percentageDone = arranger->getPercentageDone();
        currentDirectory = arranger->getCurrentDirectory();
    }
    ui.progressBar->setValue(100);
    ui.label_4->setText("Done!");
}


