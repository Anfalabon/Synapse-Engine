#pragma once

//#ifdef __cplusplus

//extern "C"{
//    #include <lua.h>
//    #include <lualib.h>
//};

//#endif


#include <lua.hpp>
#include <lualib.h>

//#include <Synapse/src/scene/Entities.hpp>

#include "scene/Entities.hpp"
#include "scene/Scene.hpp"
#include "core/Filesystem.hpp"



namespace Synapse
{


class ScriptingEngine
{
public:
    ScriptingEngine() = default;
    ~ScriptingEngine() = default;

    void Init();
    template<typename T> void AddData(T data);
    template<typename T> void SetData(T data);

    void UpdateSceneObject(Synapse::Scene *scene);
    void ShutDown();


private:
    lua_State *L;
    std::string m_scriptingFilePath;
    Synapse::Filesystem m_fileWatcher;
};


}

