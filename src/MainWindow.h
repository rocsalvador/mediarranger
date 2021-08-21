#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "MediaArranger.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    MainWindow (QMainWindow *parent=0);
  
private:
    Ui::MainWindow ui;

    QString sourceFolder;
    QString outputFolder;

    MediaArranger *arranger;

    void dialogSetter();

private slots:
    void sourceBrowse();

    void setSource(QString source);

    void setOutput(QString output);

    void outputBrowse();

    void setRecursive(bool recursive);

    void arrange();
signals:
    void sourceSet(QString);
    void outputSet(QString);
};

#endif
