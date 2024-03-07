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





  for (const auto& p : std::filesystem::directory_iterator("./")) {
//const std::filesystem::path::value_type
//p.
        std::ifstream fp(p.path(), std::ios::in | std::ios::binary);
        if (not fp.good()) {
            std::cout << "Failed to open path: "<< p.path() << std::endl;
        }
        
        std::cout << p.path() << std::endl;

        std::cout << "extension: " << p.path().extension() << std::endl;
        if (p.path().extension() != ".o")
        {
            std::cout << "skip..." << std::endl;
            continue;
        }

        //Find length of file
    fp.seekg (0, std::ios::end);
    long Length = fp.tellg();
    fp.seekg (0, std::ios::beg);    

    if (0 == Length)
      continue;

    //read in the data from your file
    char * InFileData = new char[Length];
    fp.read(InFileData, Length);

    //Calculate MD5 hash
    MD5((const unsigned char*)InFileData,Length, result);
    //std::cout << Temp.c_str() << std::endl;

    std::cout << "hash: ";
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            printf("%02x",result[i]);
    }
    std::cout << std::endl;

    //Clean up
    delete [] InFileData;
        
    }

}



 
