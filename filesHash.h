#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cassert>

#include <openssl/md5.h>

namespace fs = std::filesystem;


class FilesHash {
    public:
    const std::filesystem::directory_entry dirEntry;

    ~FilesHash()
    {
        //Clean up
        delete [] InFileData;
    }
    explicit FilesHash(const std::filesystem::directory_entry _dirEntry) : dirEntry(_dirEntry)
    {
        std::ifstream fp(p.path(), std::ios::in | std::ios::binary);
        if (not fp.good()) {
            std::cout << "Failed to open path: "<< p.path() << std::endl;
        }
        
        //std::cout << p.path() << std::endl;

        std::cout << "extension: " << p.path().extension() << std::endl;

        //Find length of file
        fp.seekg (0, std::ios::end);
        long Length = fp.tellg();
        fp.seekg (0, std::ios::beg);    

        if (0 == Length)
        continue;

        //read in the data from your file
        char * InFileData = new char[Length];
        fp.read(InFileData, Length);


    }


}

class FilesPath {
    public:
        explicit FilesPath(const std::filesystem::directory_iterator it);
        
        
        std::vector <std::string> getKnownProducts();
        std::vector <OrderBookEntry> getOrders (OrderBookType type, const std::string& product, const std::string&  time);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        std::string getEarliestTime();
        std::string getNextTime(const std::string& timestamp);

        void insertOrder (OrderBookEntry& order);

    private:
        unsigned char result[MD5_DIGEST_LENGTH];
        
        std::vector <OrderBookEntry> orders;

};



 
