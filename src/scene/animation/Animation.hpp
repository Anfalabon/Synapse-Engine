#pragma once

#include "scene/Scene.hpp"
#include "physics/PhysicsEngine.hpp"

namespace Synapse
{


class Animation
{
public:

    Animation() : m_physics(new Synapse::Physics()){};
    ~Animation() = default;

    virtual void ApplyAnimation(Synapse::Scene *scene, const float deltaTime) = 0;

    //void ApplyBouncingAnimation(Synapse::Scene *scene);

protected:

    Synapse::Physics *m_physics;

};


}