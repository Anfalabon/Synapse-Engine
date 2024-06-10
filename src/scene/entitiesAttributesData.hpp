#pragma once

#include <glad/glad.hpp>
#include <vertexObjects.hpp>



namespace Synapse
{

//each of the scene data will go in seperate header files(or maybe text or hex files which will be later retrived by fstream)
//and will include each of the header files in one single file called 'entitiesAttributesData.hpp' which is the current file

//these are currently available objects in this Game Engine
//will work further on this and add more objects(models using Mesh class)



namespace entitiesData
{



namespace cubeData
{


    inline GLuint cubeTotalVerticies = 8;
    inline GLuint cubeTotalIndicies = 36;

    inline Vertex *cubeVerticiesData = new Vertex[cubeTotalVerticies]{
            //an scene with all unique vertex attributes(shape: cube)
            {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
            {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 1.0f}},
            {{0.5f,  -0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}},
            {{0.5f,  -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
            {{-0.5f, 0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
            {{-0.5f, 0.5f,  -0.5f}, {1.0f, 1.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
    };

    inline GLuint *cubeIndiciesData = new GLuint[cubeTotalIndicies]{
            //twelf triangles to create a cube(as cube has 6 surfaces and each surface is a rectanle itselft which again is made of 2 triangles)
            0, 1, 2,        //first triangle
            1, 2, 3,        //second triangle
            0, 1, 4,        //third triangle
            1, 4, 5,        //fourth triangle
            4, 5, 6,        //fifth triangle
            5, 6, 7,        //sixth triangle
            2, 3, 6,        //seventh triangle
            3, 6, 7,        //eight triangle
            0, 2, 4,        //ninth triangle
            2, 4, 6,        //tenth triangle
            1, 3, 5,        //eleventh triangle
            3, 7, 5,        //twelfth triangle
    };

}




namespace groundData
{


    inline GLuint groundTotalVerticies = 4;
    inline GLuint groundTotalIndicies = 12;

    inline Vertex *groundVerticiesData = new Vertex[groundTotalVerticies]{
            {{960.0f,  -0.5f, 540.0f},  {1.0f, 0.0f, 0.0f}},
            {{-960.0f, -0.5f, 540.0f},  {0.0f, 1.0f, 0.0f}},
            {{960.0f,  -0.5f, -540.0f}, {0.0f, 0.0f, 1.0f}},
            {{-960.0f, -0.5f, -540.0f}, {0.5f, 0.5f, 0.5f}},
    };

    inline GLuint *groundIndiciesData = new GLuint[groundTotalIndicies]{
            0, 1, 2,
            1, 2, 3,
    };

}


namespace anotherCubeData
{


    inline GLuint anotherCubeTotalVerticies = 8;
    inline GLuint anotherCubeTotalIndicies = 36;

    inline Vertex *anotherCubeVerticiesData = new Vertex[anotherCubeTotalVerticies]{
            {{3.0f, 0.5f,  1.0f},  {1.0f, 0.0f, 0.0f}},
            {{3.0f, 0.5f,  -1.0f}, {0.0f, 1.0f, 0.0f}},
            {{2.0f, -0.5f, 1.0f},  {0.0f, 0.0f, 1.0f}},
            {{2.0f, -0.5f, -1.0f}, {0.5f, 1.0f, 0.0f}},
            {{3.0f, -0.5f, 1.0f},  {0.0f, 1.0f, 0.0f}},
            {{3.0f, -0.5f, -1.0f}, {0.5f, 0.0f, 1.0f}},
            {{2.0f, 0.5f,  1.0f},  {0.0f, 0.5f, 0.0f}},
            {{2.0f, 0.5f,  -1.0f}, {0.5f, 0.0f, 0.5f}},
    };

    inline GLuint *anotherCubeIndiciesData = new GLuint[anotherCubeTotalIndicies]{
            0, 1, 2,        //first triangle
            1, 2, 3,        //second triangle
            0, 1, 4,        //third triangle
            1, 4, 5,        //fourth triangle
            4, 5, 6,        //fifth triangle
            5, 6, 7,        //sixth triangle
            2, 3, 6,        //seventh triangle
            3, 6, 7,        //eight triangle
            0, 2, 4,        //ninth triangle
            2, 4, 6,        //tenth triangle
            1, 3, 5,        //eleventh triangle
            3, 7, 5,        //twelfth triangle
    };

}

}


}
