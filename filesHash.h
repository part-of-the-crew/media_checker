#include <iostream>
#include <string>
#include <map>
#include <vector>
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
    explicit FilesHash(const std::vector <std::pair<std::streampos, fs::directory_entry>> &files){
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
    std::map <std::string, fs::directory_entry> uniqFiles;
    char result[MD5_DIGEST_LENGTH];
    
    void getRepeatedFiles(const std::vector <std::pair<std::streampos, fs::directory_entry>> &files) {
        for (const auto& p : files) {

            std::ifstream fp(p.second.path(), std::ios::in | std::ios::binary);
            
            std::unique_ptr<unsigned char[]> p1 =  std::make_unique<unsigned char[]>(p.first);

            fp.read((char*)p1.get(), p.first);

            MD5(p1.get(), p.first, (unsigned char*)result);
            
            std::string resStr(result, MD5_DIGEST_LENGTH);

            if (0 == uniqFiles.count(resStr)){
                uniqFiles[resStr] = p.second;
            } else {
                repFiles.push_back(p.second);
                repFiles.push_back(uniqFiles[resStr]);
            }

        }
    }
};



 
