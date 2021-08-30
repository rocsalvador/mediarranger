#include <QFileDialog>

#include "MainWindow.h"


MainWindow::MainWindow (QMainWindow* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lineEdit_3->hide();
    ui.lineEdit_4->hide();
    ui.lineEdit_5->hide();
    ui.label_5->hide();
    ui.label_6->hide();
    worker = new Worker;

    connect(worker, SIGNAL(percentageChanged(int)), this, SLOT(setPercentage(int)));
    connect(worker, SIGNAL(directoryChanged(QString)), this, SLOT(setDirectoryLabel(QString)));
    connect(worker, SIGNAL(finished()), this, SLOT(workerFinished()));

    connect(ui.checkBox_3, SIGNAL(clicked(bool)), worker, SLOT(setMoveFiles(bool)));
}

void MainWindow::setSource(QString source)
{
    worker->setOutpuFolder(source.toStdString());
}


void MainWindow::setOutput(QString output)
{
    worker->setOutpuFolder(output.toStdString());
}


void MainWindow::sourceBrowse()
{
    sourceFolder = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             "/home",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
    if(sourceFolder != "") {
        ui.lineEdit->setStyleSheet(("QLineEdit { background-color : white); }"));
        worker->setSourceFolder(sourceFolder.toStdString());
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
        worker->setOutpuFolder(outputFolder.toStdString());
        emit(outputSet(outputFolder));
    }
}

void MainWindow::setRecursive(bool recursive)
{
    worker->setRecursiveSearch(recursive);
}

void MainWindow::arrange()
{
    if(worker->getSourceFolder() == "") {
        ui.lineEdit->setStyleSheet(("QLineEdit { background-color : rgb(255, 176, 176); }"));
    }
    if(worker->getOutputFolder() == "") {
        ui.lineEdit_2->setStyleSheet(("QLineEdit { background-color : rgb(255, 176, 176); }"));
    }
    if(worker->getOutputFolder() != "" and worker->getSourceFolder() != "") {
        ui.pushButton_3->setEnabled(false);
        worker->start();
    }
}

void MainWindow::setDirectoryLabel(QString directory)
{
    ui.label_4->setText("Searching media in " + directory);
}

void MainWindow::setPercentage(int percentage)
{
    ui.progressBar->setValue(percentage);
}

void MainWindow::workerFinished()
{
    ui.label_4->setText("Done!");
    ui.pushButton_3->setEnabled(true);
}

