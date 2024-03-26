#include <iostream>

#include <string>
#include <vector>

#include <algorithm>

#include <filesystem>
#include <fstream>

#include "filesBase.h"



namespace fs = std::filesystem;

class FilesPath : public FilesBase{
public:

    FilesPath() = delete;
    ~FilesPath() = default;
    
    FilesPath(const std::vector<std::string>& exts) : exts_tolower(exts){
        // write to the same location
        for (const auto& e : exts) {
            std::string insert_ext;
            std::transform(e.cbegin(), e.cend(), std::back_inserter(insert_ext), 
                        [](unsigned char c) { return std::tolower(c); });

            exts_tolower.push_back(insert_ext);
        }

        std::cout << "checked extensions:\n";
        for (const auto& e : exts_tolower) {
            std::cout << e << std::endl;
        }
    

        for (const auto& f : this->dirIt) {
            for (const auto& e : exts_tolower) {
                if (f.path().extension() == e)
                {
                    this->SelectedFiles.push_back(f);  
                }
           
            }
        }
    }
    
    std::vector<fs::directory_entry> getAllFiles(){
        return this->allFiles;
    }


private:
    const fs::recursive_directory_iterator dirIt{"./"};
    std::vector<std::string> exts_tolower;
    std::vector<fs::directory_entry> allFiles;


};



 
