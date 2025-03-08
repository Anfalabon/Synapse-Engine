#pragma once

#include <vector>


inline float r = 1.0f;
inline float h = 6.0f;

inline std::vector<float> cylinderVerticiesData = {
        r, h/2, 0, 1.0f, 0.0f, 0.0f, 0, 0,
        r/2, h/2, 0.86f * r, 0.0f, 1.0f, 1.0f, 0, 0,
        -r/2, h/2, 0.86f * r, 1.0f, 0.0f, 1.0f, 0, 0,
        -r, h/2, 0, 0.0f, 1.0f, 0.0f, 0, 0,
        -r/2, h/2, -0.86f * r, 0.0f, 1.0f, 1.0f, 0, 0,
        r/2, h/2, -0.86f * r, 1.0f, 0.0f, 0.0f, 0, 0,
        // Bottom hexagon
        r, -h/2, 0, 0.0f, 1.0f, 0.0f, 0, 0,
        r/2, -h/2, 0.86f * r, 0.0f, 0.0f, 1.0f, 0, 0,
        -r/2, -h/2, 0.86f * r, 1.0f, 0.0f, 1.0f, 0, 0,
        -r, -h/2, 0, 1.0f, 0.0f, 0.0f, 0, 0,
        -r/2, -h/2, -0.86f * r, 0.0f, 0.0f, 1.0f, 0, 0,
        r/2, -h/2, -0.86f * r, 0.0f, 0.0f, 1.0f, 0, 0,
        // Center vertices
        0, h/2, 0, 0.0f, 1.0f, 0.0f, 0, 0,
        0, -h/2, 0.0f, 0.0f, 1.0f, 0, 0
};


inline std::vector<unsigned int> cylinderIndiciesData = {
        // Top face
        12, 0, 1,
        12, 1, 2,
        12, 2, 3,
        12, 3, 4,
        12, 4, 5,
        12, 5, 0,
        // Bottom face
        13, 6, 7,
        13, 7, 8,
        13, 8, 9,
        13, 9, 10,
        13, 10, 11,
        13, 11, 6,
        // Side faces
        0, 1, 7,
        0, 7, 6,
        1, 2, 8,
        1, 8, 7,
        2, 3, 9,
        2, 9, 8,
        3, 4, 10,
        3, 10, 9,
        4, 5, 11,
        4, 11, 10,
        5, 0, 6,
        5, 6, 11
};
