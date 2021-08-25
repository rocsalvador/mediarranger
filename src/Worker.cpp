#include "Worker.h"
#include "ExifTool.h"

void Worker::run()
{
    arrange();
}


Worker::Worker()
{
    recursiveSearch = false;
    sourceFolder = "";
    outputFolder = "";
}

void Worker::setSourceFolder(string sourceFolder)
{
    this->sourceFolder = sourceFolder;
    currentDirectory = sourceFolder;
}

void Worker::setOutpuFolder(string outpuFolder)
{
    this->outputFolder = outpuFolder;
}

void Worker::setRecursiveSearch(bool recursive)
{
    recursiveSearch = recursive;
}

void Worker::arrange() {
    percentageDone = 0;
    int aux = percentageDone;

    int nFiles = 0;
    for(const auto file : filesystem::recursive_directory_iterator(sourceFolder)) {
        std::string fileName{file.path().u8string()};
        ++nFiles;
        if(filesystem::is_directory(fileName) and !recursiveSearch) break;
    }

    ExifTool et;
    int nFile = 0;
    for(const auto file : filesystem::recursive_directory_iterator(sourceFolder)) {
        string fileName{file.path().u8string()};

        ++nFile;
        percentageDone = nFile/float(nFiles)*100;
        if(percentageDone != aux) emit(percentageChanged(percentageDone));
        aux = percentageDone;

        size_t pointPos = fileName.find_last_of(".");
        if(filesystem::is_directory(fileName)) {
            if(!recursiveSearch) break;
            currentDirectory = fileName;
            emit(directoryChanged(QString::fromStdString(fileName)));
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
                        filesystem::copy(fileName, newFileName, filesystem::copy_options::update_existing);
                        cout << "Copying " << fileName << " to " << newFileName << endl;
                    }
                }
            }
        }
    }
}

float Worker::getPercentageDone()
{
    return percentageDone;
}

string Worker::getCurrentDirectory()
{
    return currentDirectory;
}

string Worker::getOutputFolder()
{
    return outputFolder;
}

string Worker::getSourceFolder()
{
    return sourceFolder;
}

