#ifndef MEDIAARRENGER_H
#define MEDIAARRENGER_H

#include <iostream>
#include <filesystem>
using namespace std;

class MediaArranger {
public:
    MediaArranger();

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

    float percentageDone;

    string currentDirectory;
};

#endif
