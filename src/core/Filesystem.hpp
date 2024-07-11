#pragma once

#include <string>
#include <ctime>
#include <fstream>


#if defined(__cplusplus)
#include <filesystem>
#endif

#if defined(__linux__) || defined(__unix__)

#if defined(__cplusplus)
extern "C"{
#endif
    #include <sys/types.h>
    #include <sys/stat.h>
#if defined(__cplusplus)
}
#endif

#elif defined(__WIN32__) || defined(MSVC)
#include <window.h>
#endif



namespace Synapse
{


class Filesystem
{
public:
    Filesystem() = default;
    ~Filesystem() = default;

    static std::string ReadFileContent(const std::string &filePath);
    static void WriteContentToFile(const std::string &filePath);

    static std::time_t FileCreationTime(const std::string &filePath);
    static std::time_t FileLastModificationTime(const std::string &filePath);
    bool WasFileModified(const std::string &filePath);

private:
    std::time_t lastModificationTime = 0;
};


}