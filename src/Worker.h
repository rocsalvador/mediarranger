#include <QThread>
#include <filesystem>
#include <iostream>
using namespace std;


class Worker : public QThread {
    Q_OBJECT
public:
    Worker();

    void run() override;

    void setSourceFolder(string sourceFolder);

    void setOutpuFolder(string outputFolder);

    string getSourceFolder();

    string getOutputFolder();

    void setRecursiveSearch(bool recursive);

    void arrange();

    float getPercentageDone();

    string getCurrentDirectory();
private:
    string sourceFolder;

    string outputFolder;

    bool recursiveSearch;

    int percentageDone;

    string currentDirectory;

signals:
    void percentageChanged(int);

    void directoryChanged(QString);
};
