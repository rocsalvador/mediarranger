#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Worker.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    MainWindow (QMainWindow *parent=0);
  
private:
    Ui::MainWindow ui;

    QString sourceFolder;
    QString outputFolder;

    Worker* worker;

private slots:
    void sourceBrowse();

    void setSource(QString source);

    void setOutput(QString output);

    void outputBrowse();

    void setRecursive(bool recursive);

    void arrange();

    void setDirectoryLabel(QString directory);

    void setPercentage(int percentage);

    void workerFinished();
signals:
    void sourceSet(QString);

    void outputSet(QString);
};

#endif
