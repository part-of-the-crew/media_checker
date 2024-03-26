#include <iostream>
//#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class FilesBase {
public:
    
    FilesBase() = default;
    ~FilesBase() = default;

    std::vector<fs::directory_entry> getSelectedFiles(){
        return this->SelectedFiles;
    }  

    friend std::ostream& operator<<(std::ostream& os, const FilesBase& FilesBase)
    {
        os << "Selected files:\n";
        for (const auto& p : FilesBase.SelectedFiles)
            os << p.path() << "\n";
        os << std::endl;
        return os;
    }
    
protected:
    std::vector<fs::directory_entry> SelectedFiles;
};



 
