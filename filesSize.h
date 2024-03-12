#include <iostream>
#include <string>
#include <map>
#include <vector>
//#include <algorithm>
#include <filesystem>
#include <fstream>

#include <utility>


namespace fs = std::filesystem;

class FilesSize {
public:
    
    FilesSize() = delete;
    explicit FilesSize(const std::vector<fs::directory_entry> &_files) : files(_files){
        this->getSameSizeFiles();
    }

    auto getRepFiles(){
        return this->repFiles;
    }
    
    std::vector<fs::directory_entry> getZeroLenFiles(){
        return this->zeroLenFiles;
    }

    ~FilesSize() = default;

    friend std::ostream& operator<<(std::ostream& out, const FilesSize& filesSize)
    {
        for (const auto& p : filesSize.repFiles)
            out << p.second.path() << std::endl;  
        return out;
    }

private:
    const std::vector<fs::directory_entry> &files;
    std::vector <std::pair<std::streampos, fs::directory_entry>> repFiles;
    std::vector<fs::directory_entry> failedOpenFiles;
    std::vector<fs::directory_entry> zeroLenFiles;
    std::map <std::streampos, fs::directory_entry> uniqFiles;
    
    void getSameSizeFiles() {
        for (const auto& p : files) {
            std::ifstream fp(p.path(), std::ios::in | std::ios::binary);
            
            if (not fp.good()) {
                failedOpenFiles.push_back(p);
                continue;
            }
            

            //Find size of file
            fp.seekg (0, std::ios::end);
            
            auto sizeOfFile = fp.tellg();
            fp.seekg (0, std::ios::beg);    

            if (0 == sizeOfFile)
            {
                zeroLenFiles.push_back(p);
                continue;
            }

            if (0 == uniqFiles.count(sizeOfFile)){
                uniqFiles[sizeOfFile] = p;
            } else {
                repFiles.emplace_back(sizeOfFile, p);
                repFiles.emplace_back(sizeOfFile, uniqFiles[sizeOfFile]);
            }

        }
    }
};




 
