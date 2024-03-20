#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <array> 
//#include <algorithm>
#include <filesystem>
#include <fstream>

#include <utility>

#include <memory>
#include <openssl/md5.h>

namespace fs = std::filesystem;

class FilesHash {
public:
    
    FilesHash() = delete;
    FilesHash(const std::vector <std::pair<std::streampos, fs::directory_entry>> &files){
        this->getRepeatedFiles(files);
    }

    std::vector<fs::directory_entry> getRepFiles(){
        return this->repFiles;
    }
    
    std::vector<fs::directory_entry> getZeroLenFiles(){
        return this->zeroLenFiles;
    }

    friend std::ostream& operator<<(std::ostream& os, const FilesHash& filesHash)
    {
        for (const auto& p : filesHash.repFiles)
            os << p.path() << std::endl;  
        return os;
    }
    ~FilesHash() = default;

private:
    //const std::vector <std::streampos, fs::directory_entry> &files;
    //const std::vector<fs::directory_entry> &files;
    std::vector<fs::directory_entry> repFiles;
    std::vector<fs::directory_entry> zeroLenFiles;
    std::map <std::array<unsigned char, MD5_DIGEST_LENGTH>, fs::directory_entry> uniqFiles;
    std::array<unsigned char, MD5_DIGEST_LENGTH> arr_res;

    void getRepeatedFiles(const std::vector <std::pair<std::streampos, fs::directory_entry>> &files) {
        for (const auto& p : files) {

            std::ifstream fp(p.second.path(), std::ios::in | std::ios::binary);

            auto p_unique = std::make_unique<unsigned char[]>(p.first);

            fp.read(reinterpret_cast<char*>(p_unique.get()), p.first);

            MD5(p_unique.get(), p.first, arr_res.data());
            

            if (0 == uniqFiles.count(arr_res)){
                uniqFiles[std::move(arr_res)] = std::move(p.second);
            } else {
                repFiles.push_back(std::move(p.second));
                repFiles.push_back(uniqFiles[arr_res]);
            }

        }
    }
};



 
