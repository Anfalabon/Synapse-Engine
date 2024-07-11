#include "Filesystem.hpp"

#include <iostream>


namespace Synapse
{



std::string Filesystem::ReadFileContent(const std::string &filePath)
{
    std::ifstream inputFileStream(filePath);

    if(inputFileStream.fail())
    {
        std::cout << "didn't find file!" << '\n';
        std::cout << "File name: " << filePath << '\n';
        //std::cin.get();    //this is definately bad for doing
        return "";
    }

    std::string fileContent = "";

    std::string fileLine;
    while ( std::getline(inputFileStream, fileLine) )
        fileContent += fileLine + '\n';

    inputFileStream.close();

    return fileContent;
}



void Filesystem::WriteContentToFile(const std::string &filePath, const std::string &content, WRITE_MODE placeToWrite){}
std::time_t Filesystem::FileCreationTime(const std::string &filePath){}


std::time_t Filesystem::FileLastModificationTime(const std::string &filePath)
{
    if(struct stat fileInfo; stat(filePath.c_str(), &fileInfo) == 0)
    {
        return fileInfo.st_mtime;
    }
    return -1;
}



bool Filesystem::WasFileModified(const std::string &filePath)
{
    if(struct stat fileInfo; stat(filePath.c_str(), &fileInfo) == 0)
    {
        if(fileInfo.st_mtime > lastModificationTime)
        {
            lastModificationTime = fileInfo.st_mtime;
            return true;
        }
    }

    return false;
}


}