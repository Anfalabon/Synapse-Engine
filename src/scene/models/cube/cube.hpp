#pragma once

#include <vector>



inline std::vector<float> cubeVerticiesData = {
        //an scene with all unique vertex attributes(shape: cube)
        //vertex positions      //colors
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0, 0,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1, 0,
        0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 1, 1,
        0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1, 1,
        -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0, 1,
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 0, 0,
        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0, 0,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1, 0
};


inline std::vector<unsigned int> cubeIndiciesData = {
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
