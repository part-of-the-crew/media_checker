#include <iostream>
#include <string>
#include <vector>

#include <filesystem>
#include <fstream>


#include "filesPath.h"
#include "filesSize.h"
#include "filesHash.h"

int main()
{
    std::vector<std::string> exts{".JPG", ".PNG"};

    FilesPath filesPath(exts);

    //std::cout << "filesPath:\n" << filesPath << std::endl;

    auto p = filesPath.getFiles();

    FilesSize filesSize(p);

    std::cout << "\nFiles with same size:\n" << filesSize << std::endl;

    auto s = filesSize.getRepFiles();

    FilesHash filesHash(s);

    std::cout << "Repetative:\n" << filesHash << std::endl;
 
}
