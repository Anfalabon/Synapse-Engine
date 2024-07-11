#include <iostream>
#include <sys/stat.h>
#include <ctime>


std::time_t lastModificationTime = 0;



bool wasFileModified(const std::string &filePathStr)
{
    const char *filePath = filePathStr.c_str();
    struct stat fileInfo;
    std::time_t currentLastModificationTime;

    if(stat(filePath, &fileInfo) == 0)
    {
        currentLastModificationTime = fileInfo.st_mtime;
    }

    if(currentLastModificationTime > lastModificationTime)
    {
        lastModificationTime = currentLastModificationTime;
        return true;
    }
    else
    {
        return false;
    }
}



int main()
{

    while(true)
    {
        if(wasFileModified("hello.lua"))
        {
            //std::cin.get();
            std::cout << "File was modified" << '\n';
        }
    }

    return 0;
}