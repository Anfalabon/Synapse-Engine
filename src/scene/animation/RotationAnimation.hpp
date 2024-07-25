#pragma once

#include "scene/animation/Animation.hpp"

namespace Synapse
{


class RotationAnimation : public Animation
{
public:

    RotationAnimation() = default;
    ~RotationAnimation() = default;

    void ApplyAnimation(Synapse::Scene *scene, const float deltaTime) override;
    void ApplyBallProjectileRotation(Synapse::Scene *scene, const float deltaTime);
    void ApplyDoorOpenAnimation(Synapse::Scene *scene, const float deltaTime);

private:

    float m_theta = 0.0f;

};


}