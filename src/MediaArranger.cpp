#include "MediaArranger.h"
#include "ExifTool.h"


MediaArranger::MediaArranger()
{
    recursiveSearch = false;
    sourceFolder = "";
    outputFolder = "";
}

void MediaArranger::setSourceFolder(string sourceFolder)
{
    this->sourceFolder = sourceFolder;
    currentDirectory = sourceFolder;
}

void MediaArranger::setOutpuFolder(string outpuFolder)
{
    this->outputFolder = outpuFolder;
}

void MediaArranger::setRecursiveSearch(bool recursive)
{
    recursiveSearch = recursive;
}

void MediaArranger::arrange() {
    percentageDone = 0;

    int nFiles = 0;
    for(const auto file : filesystem::recursive_directory_iterator(sourceFolder)) {
        std::string fileName{file.path().u8string()};
        ++nFiles;
        if(filesystem::is_directory(fileName) and !recursiveSearch) break;
    }

    ExifTool et;
    int nFile = 0;
    for(const auto file : filesystem::recursive_directory_iterator(sourceFolder)) {
        std::string fileName{file.path().u8string()};

        ++nFile;
        percentageDone = nFile/float(nFiles)*100.0;

        size_t pointPos = fileName.find_last_of(".");
        if(filesystem::is_directory(fileName)) {
            if(!recursiveSearch) break;
            currentDirectory = fileName;
        }
        else if(pointPos != string::npos) {
            string fileExtension = fileName.substr(pointPos, fileName.length()-1);
            if(fileExtension == ".jpg") {
                TagInfo* info = et.ImageInfo(fileName.c_str());
                if(info) {
                    TagInfo* i;
                    for(i=info; i; i=i->next) {
                        string name = i->name;
                        if(name == "FileModifyDate") break;
                    }
                    if(i) {
                        string date = i->value;
                        string year = date.substr(0,4);
                        string month = date.substr(5,2);
                        string day = date.substr(8,2);
                        string relativePath = "/" + year + "/" +  month;
                        filesystem::create_directories(outputFolder + relativePath);
                        string newFileName = outputFolder + relativePath + fileName.substr(fileName.find_last_of("/"), fileName.length()- fileName.find_last_of("/"));
                        filesystem::rename(fileName, newFileName);
                    }
                }
            }
        }
    }
}

float MediaArranger::getPercentageDone()
{
    return percentageDone;
}

string MediaArranger::getCurrentDirectory()
{
    return currentDirectory;
}

string MediaArranger::getOutputFolder()
{
    return outputFolder;
}

string MediaArranger::getSourceFolder()
{
    return sourceFolder;
}




