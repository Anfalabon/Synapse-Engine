#include "EntityLoader.hpp"



namespace Synapse
{

void EntityLoader::addEntity(std::vector<Entity*> &entities,
                               const char *entityName,
                               Vertex *verticies, GLuint totalVerticies,
                               GLuint *indicies, GLuint totalIndicies,
                               const std::string &vertexShaderSourcePath,
                               const std::string &fragmentShaderSourcePath,
                               std::unique_ptr<Camera> camera,
                               std::unique_ptr<Renderer> renderer)
{
    entities.push_back(new Entity(entityName,
                                  verticies, totalVerticies,
                                  indicies, totalIndicies,
                                  vertexShaderSourcePath,
                                  fragmentShaderSourcePath));


    std::size_t lastEntityIndex = entities.size()-1;
    entities[lastEntityIndex]->LoadShader();


    camera->AddShaderProgramID(entities[lastEntityIndex]->GetShader().ProgramID());

    renderer->InitVAO(entities[lastEntityIndex]->GetVertexObjects().GetVAO());
    renderer->InitIndicies(entities[lastEntityIndex]->TotalIndicies());

    entities[lastEntityIndex]->Translate(camera->GetTargetPos());

}


}

