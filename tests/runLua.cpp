#include <lua.hpp>
#include <lualib.h>

#include <iostream>


int main()
{

    lua_State* L = luaL_newstate();
    lua_pushstring(L, "Anfal");
    lua_setglobal(L, "str");
    luaL_openlibs(L);
    if(luaL_dofile(L, "hello.lua"))
    {
        std::cout << "Error: " << lua_tostring(L, -1) << "\n";
    }
    lua_close(L);


    return 0;
}