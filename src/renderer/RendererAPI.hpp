#pragma once

#include "core/Macros.hpp"

namespace Synapse
{


class RendererAPI
{
public:

    //Rigth now this Engine only supports "OpenGL" for rendering
    RendererAPI()
    : m_rendererAPI("OpenGL"){}
    ~RendererAPI() = default;

    void SetRendererAPI(const std::string &rendererAPI);
    [[nodiscard]] __ALWAYS__INLINE__ const char *GetRendererAPI() const {return m_rendererAPI;}

private:

    const char *m_rendererAPI;

};


}