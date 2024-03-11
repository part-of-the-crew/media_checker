#include <iostream>
#include <string>
#include <vector>

#include <filesystem>
#include <fstream>


#include "filesPath.h"
#include "filesHash.h"

int main()
{
    std::vector<std::string> exts{".JPG", ".PNG"};

    FilesPath filesPath(exts);

    //std::cout << "filesPath:\n" << filesPath << std::endl;

    auto p = filesPath.getFiles();
    FilesHash filesHash(p);

    std::cout << "Repetative:\n" << filesHash << std::endl;
 
}
