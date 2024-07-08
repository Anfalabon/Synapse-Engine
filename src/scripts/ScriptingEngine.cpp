#include "ScriptingEngine.hpp"

#include <iostream>

namespace Synapse
{

void ScriptingEngine::Init()
{
    L = luaL_newstate();
}



void ScriptingEngine::AddData()
{

}



void ScriptingEngine::SetData()
{

}



void ScriptingEngine::AddFunctions()
{

}



void ScriptingEngine::SetFunctions()
{

}


void ScriptingEngine::Run()
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

}


void ScriptingEngine::CheckErrors()
{
    if(luaL_dofile(L, scriptingFilePath))
    {
        std::cout << "Error: " << lua_tostring(L, -1) << "\n";
    }
}



void ScriptingEngine::UpdateSceneObject(Scene *scene)
{

}



bool ScriptingEngine::Changed()
{
    return false;
}


void ScriptingEngine::ShutDown()
{
    lua_close(L);
}







}