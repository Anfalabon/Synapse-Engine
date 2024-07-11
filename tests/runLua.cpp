#include <lua.hpp>
#include <lualib.h>

#include <iostream>
#include <sys/stat.h>
#include <ctime>

std::time_t lastModificationTime = 0;


static bool WasFileModified(const std::string &filePathStr)
{
    //const char *filePath = filePathStr.c_str();
    struct stat fileInfo;
    std::time_t currentLastModificationTime;

    if(struct stat fileInfo; stat(filePathStr.c_str(), &fileInfo) == 0)
    {
        currentLastModificationTime = fileInfo.st_mtime;
        if(fileInfo.st_mtime > lastModificationTime)
        {
            lastModificationTime = fileInfo.st_mtime;
            return true;
        }
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

    lua_State* L = luaL_newstate();
    lua_pushstring(L, "Anfal");
    lua_setglobal(L, "str");
    luaL_openlibs(L);
//    if(luaL_dofile(L, "hello.lua"))
//    {
//        std::cout << "Error: " << lua_tostring(L, -1) << "\n";
//    }

    while(true)
    {
        if(WasFileModified("hello.lua"))
        {
            //std::cin.get();
            if(luaL_dofile(L, "hello.lua"))
            {
                std::cout << "Error: " << lua_tostring(L, -1) << "\n";
            }
        }
        else
        {
            //std::cin.get();
        }
    }

    lua_close(L);


    return 0;
}