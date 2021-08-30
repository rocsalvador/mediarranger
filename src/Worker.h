#include <QThread>
#include <filesystem>
#include <iostream>
#include <unordered_set>
using namespace std;


class Worker : public QThread {
    Q_OBJECT
public:
    Worker();

    void run() override;

    void setSourceFolder(const string& sourceFolder);

    void setOutpuFolder(const string& outputFolder);

    string getSourceFolder();

    string getOutputFolder();

    void setRecursiveSearch(bool recursive);

    void arrange();
private:
    string sourceFolder;

    string outputFolder;

    bool recursiveSearch;

    bool moveFiles;

    string currentDirectory;

    unordered_set<string> supportedFileExtensions;

public slots:
    void setMoveFiles(bool moveFiles);

signals:
    void percentageChanged(int);

    void directoryChanged(QString);
};
