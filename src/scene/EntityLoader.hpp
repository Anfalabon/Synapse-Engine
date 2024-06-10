#pragma once

#include "Entities.hpp"
#include "entitiesAttributesData.hpp"
#include "../camera/Camera.hpp"
#include "../renderer/renderEntity.hpp"

#include <vector>
#include <memory>


namespace Synapse
{

struct EntityLoader  //haven't include 'EntityLoader' in Makefile
{
    void addEntity(std::vector<Entity*> &entities,
                   const char *entityName,
                   Vertex *verticies, GLuint totalVerticies,
                   GLuint *indicies, GLuint totalIndicies,
                   const std::string &vertexShaderSourcePath,
                   const std::string &fragmentShaderSourcePath,
                   std::unique_ptr<Camera> camera,
                   std::unique_ptr<Renderer> renderer);

    //void removeEntity(std::vectro<Entity*> &entities);
};


}







