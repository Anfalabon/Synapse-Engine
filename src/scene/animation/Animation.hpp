#pragma once

#include "scene/Scene.hpp"
#include "physics/PhysicsEngine.hpp"
#include "scripting/ScriptingEngine.hpp"

namespace Synapse
{


class Animation
{
public:

    Animation()
    : m_physics(new Synapse::Physics()),
      m_scripter(new Synapse::ScriptingEngine()){};

    ~Animation()
    {
        delete m_physics;
        delete m_scripter;
    }

    virtual void ApplyAnimation(Synapse::Scene *scene, const float deltaTime) = 0;

    //void ApplyBouncingAnimation(Synapse::Scene *scene);

    static __ALWAYS__INLINE__ void UpdateAnimations(const std::vector<Synapse::Animation*> &animators, Synapse::Scene *scene, const float deltaTime)
    {
        for(auto animator : animators) [[likely]]
        {
            animator->ApplyAnimation(scene, deltaTime);
        }
    }

protected:

    Synapse::Physics         *m_physics;
    Synapse::ScriptingEngine *m_scripter;   //m_scriptingEngine->UpdateScene(m_scene);  //this will be inside Animation class

};


}














//m_animator->ApplyAnimation(m_scene, m_deltaTime);
//if(glfwGetKey(m_window->WindowAddress(), GLFW_KEY_ENTER) != GLFW_PRESS)
//{
//    for(auto animator : m_animator) [[likely]]
//    {
//        animator->ApplyAnimation(m_scene, m_deltaTime);
//    }
//}
