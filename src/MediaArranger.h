#include <filesystem>
using namespace std;

class MediaArranger {
public:
    MediaArranger();

    void setSourceFolder(string sourceFolder);

    void setOutpuFolder(string outputFolder);

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
