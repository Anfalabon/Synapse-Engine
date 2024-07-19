#pragma once

#include "scene/animation/Animation.hpp"


namespace Synapse
{



class BouncingAnimation : public Animation
{
public:

    BouncingAnimation() = default;
    ~BouncingAnimation() = default;

    void ApplyAnimation(Synapse::Scene *scene, const float deltaTime) override;

    void ApplyBouncingAnimation(Synapse::Scene *scene, const float deltaTime);

private:

};



}
