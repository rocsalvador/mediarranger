#include "Worker.h"
#include "ExifTool.h"

void Worker::run()
{
    arrange();
}

Worker::Worker()
{
    supportedFileExtensions = {".jpg", ".JPG", ".jpeg", ".JPEG", ".mp4", ".MP4"};
    recursiveSearch = false;
    moveFiles = false;
    sourceFolder = "";
    outputFolder = "";
}

void Worker::setSourceFolder(const string& sourceFolder)
{
    cout << "Source folder set to " << sourceFolder << endl;
    this->sourceFolder = sourceFolder;
    currentDirectory = sourceFolder;
}

void Worker::setOutpuFolder(const string& outputFolder)
{
    cout << "Output folder set to " << outputFolder << endl;
    this->outputFolder = outputFolder;
}

void Worker::setRecursiveSearch(bool recursive)
{
    cout << "Recursive search set to " << recursive << endl;
    recursiveSearch = recursive;
}

void Worker::arrange() {
    int percentageDone = 0;
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
            if(supportedFileExtensions.find(fileExtension) != supportedFileExtensions.end()) {
                TagInfo* info = et.ImageInfo(fileName.c_str());
                if(info) {
                    TagInfo *createdPointer = nullptr, *modifiedPointer = nullptr, *j = nullptr;
                    for(TagInfo *i=info; i; i=i->next) {
                        string name = i->name;
                        cout << i->name << endl;
                        if(name == "CreateDate") createdPointer = i;
                        else if(name == "FileModifyDate") modifiedPointer = i;
                    }

                    if(modifiedPointer and createdPointer) {
                        string dateModified = modifiedPointer->value;
                        int yearModified = stoi(dateModified.substr(0,4));
                        int monthModified = stoi(dateModified.substr(5,2));
                        int dayModified = stoi(dateModified.substr(8,2));

                        string dateCreated = createdPointer->value;
                        int yearCreated = stoi(dateCreated.substr(0,4));
                        int monthCreated = stoi(dateCreated.substr(5,2));
                        int dayCreated = stoi(dateCreated.substr(8,2));

                        if(yearModified > yearCreated) j = createdPointer;
                        else if(yearModified == yearCreated) {
                            if(monthModified > monthCreated) j = createdPointer;
                            else if(monthModified == monthCreated) {
                                if(dayModified > dayCreated) j = createdPointer;
                                else if(dayModified == dayCreated) j = modifiedPointer;
                                else j = modifiedPointer;
                            }
                            else j = modifiedPointer;
                        }
                        else j = modifiedPointer;
                    }
                    else if(createdPointer) j = createdPointer;
                    else if(modifiedPointer) j = modifiedPointer;


                    if(j) {
                        string date = j->value;
                        string year = date.substr(0,4);
                        string month = date.substr(5,2);
                        string day = date.substr(8,2);
                        string relativePath = "/" + year + "/" +  month;

                        filesystem::create_directories(outputFolder + relativePath);
                        string newFileName = outputFolder + relativePath + fileName.substr(fileName.find_last_of("/"), fileName.length()- fileName.find_last_of("/"));

                        if(not filesystem::exists(newFileName))
                            filesystem::copy(fileName, newFileName);
                        if(moveFiles) {
                            filesystem::remove(fileName);
                            cout << "Moving " << fileName << " to " << newFileName << endl;
                        }
                        else cout << "Copying " << fileName << " to " << newFileName << endl;
                    }
                    else cout << "Could not find date info in " << fileName << endl;
                }
            }
        }
    }
    cout << "Done!" << endl;
}

string Worker::getOutputFolder()
{
    return outputFolder;
}

string Worker::getSourceFolder()
{
    return sourceFolder;
}

void Worker::setMoveFiles(bool moveFiles)
{
    cout << "Move files set to " << moveFiles << endl;
    this->moveFiles = moveFiles;
}
