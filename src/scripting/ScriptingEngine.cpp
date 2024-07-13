#include "ScriptingEngine.hpp"

#include <iostream>

namespace Synapse
{

void ScriptingEngine::Init()
{
    L = luaL_newstate();
}


template<typename T> void ScriptingEngine::AddData(T data)
{
    lua_pushstring(L, "");
}



template<typename T> void ScriptingEngine::SetData(T data)
{
    lua_setglobal(L, "str");
    luaL_openlibs(L);
}





void ScriptingEngine::UpdateSceneObject(Synapse::Scene *scene)
{
    if(m_fileWatcher.WasFileModified(m_scriptingFilePath))
    {
        //luaL_openlibs(L);
        this->AddData<float>(scene->GetRenderableObject(0)->m_position.x);
        if(luaL_dofile(L, m_scriptingFilePath.c_str()))
        {
            std::cout << "Error: " << lua_tostring(L, -1) << "\n";
        }
    }
}





void ScriptingEngine::ShutDown()
{
    lua_close(L);
}







}