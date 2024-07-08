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

#include "../scene/Entities.hpp"
#include "../scene/Scene.hpp"



namespace Synapse
{


class ScriptingEngine
{
public:
    ScriptingEngine() = default;
    ~ScriptingEngine() = default;

    void Init();
    void AddData();
    void SetData();
    void AddFunctions();
    void SetFunctions();
    static void Run();
    void CheckErrors();
    void UpdateSceneObject(Scene *scene);
    bool Changed();
    void ShutDown();

private:
    lua_State *L;
    const char *scriptingFilePath;
};


}

