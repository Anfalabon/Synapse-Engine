#pragma once


#include <vector>



inline std::vector<float> groundVerticiesData = {
        10.0f,  0.0f, 10.0f, 1.0f/1.3f, 1.0f/1.3f, 1.0f/1.3f, 1, 1,
        -10.0f, 0.0f, 10.0f, 1.0f/1.3f, 1.0f/1.3f, 1.0f/1.3f, 1, 0,
        10.0f,  0.0f, -10.0f, 1.0f/1.3f, 1.0f/1.3f, 1.0f/1.3f, 0, 0,
        -10.0f, 0.0f, -10.0f, 1.0f/1.3f, 1.0f/1.3f, 1.0f/1.3f, 0, 1
};



inline std::vector<unsigned int> groundIndiciesData = {
        0, 1, 2,
        1, 2, 3,
};
