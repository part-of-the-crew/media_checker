#include <iostream>
#include <string>
#include <map>
#include <vector>
//#include <algorithm>
#include <filesystem>
#include <fstream>

#include <memory>
#include <openssl/md5.h>

namespace fs = std::filesystem;

class FilesHash {
public:
    
    FilesHash() = delete;
    explicit FilesHash(std::vector<fs::directory_entry> &_files) : files(_files){
        this->getRepeatedFiles();
    }

    std::vector<fs::directory_entry> getRepFiles(){
        return this->repFiles;
    }
    
    std::vector<fs::directory_entry> getZeroLenFiles(){
        return this->zeroLenFiles;
    }

    friend std::ostream& operator<<(std::ostream& os, FilesHash& filesHash)
    {
        for (const auto& p : filesHash.repFiles)
            os << p.path() << std::endl;  
        return os;
    }
    ~FilesHash() = default;

private:
    const std::vector<fs::directory_entry> &files;
    std::vector<fs::directory_entry> repFiles;
    std::vector<fs::directory_entry> zeroLenFiles;
    std::map <std::string, fs::directory_entry> uniqFiles;
    char result[MD5_DIGEST_LENGTH];
    
    void getRepeatedFiles() {
        for (const auto& p : files) {
            std::ifstream fp(p.path(), std::ios::in | std::ios::binary);
            
            if (not fp.good()) {
                std::cout << "Failed to open path: "<< p.path() << std::endl;
            }
            

            //Find length of file
            fp.seekg (0, std::ios::end);
            long Length = fp.tellg();
            fp.seekg (0, std::ios::beg);    

            if (0 == Length)
            {
                std::cout << "Lengh is 0 "<< p.path() << std::endl;
                zeroLenFiles.push_back(p);
                continue;
            }
            

            std::unique_ptr<unsigned char> p1(new unsigned char [Length]);

            fp.read((char*)p1.get(), Length);

            MD5(p1.get(), Length, (unsigned char*)result);
            
            std::string resStr(result, MD5_DIGEST_LENGTH);

            if (0 == uniqFiles.count(resStr)){
                uniqFiles[resStr] = p;
            } else {
                repFiles.push_back(p);
            }

        }
    }
};



 
