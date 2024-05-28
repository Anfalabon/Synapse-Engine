#pragma once


GLuint totalVerticies = 21;
GLuint totalIndicies = 78;

Vertex *verticiesData = new Vertex[totalVerticies]{
        //an entity with all unique vertex attributes(shape: cube)
        {{0.5f, 0.5f, 0.5f},    {1.0f, 1.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f},   {1.0f, 1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f},   {1.0f, 1.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f, 1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f},   {1.0f, 1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f},  {1.0f, 1.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},

        {{0.0f, 10.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},    //this is a point at the top of the cube

        //these vertex attributes are for the ground
        {{960.0f, -10.0f, 540.0f}, {1.0f, 0.0f, 0.0f}},
        {{-960.0f, -10.0f, 540.0f}, {0.0f, 1.0f, 0.0f}},
        {{960.0f, -10.0f, -540.0f}, {0.0f, 0.0f, 1.0f}},
        {{-960.0f, -10.0f, -540.0f}, {1.0f, 0.0f, 1.0f}},


        //another entity with all unique vertex attributes(shape: random IDK)
        {{3.0f, 0.5f, 1.0f},    {1.0f, 0.0f, 0.0f}},
        {{3.0f, 0.5f, -1.0f},   {0.0f, 1.0f, 0.0f}},
        {{2.0f, -0.5f, 1.0f},   {0.0f, 0.0f, 1.0f}},
        {{2.0f, -0.5f, -1.0f},  {0.5f, 1.0f, 0.0f}},
        {{3.0f, -0.5f, 1.0f},   {0.0f, 1.0f, 0.0f}},
        {{3.0f, -0.5f, -1.0f},  {0.5f, 0.0f, 1.0f}},
        {{2.0f, 0.5f, 1.0f},    {0.0f, 0.5f, 0.0f}},
        {{2.0f, 0.5f, -1.0f},   {0.5f, 0.0f, 0.5f}},
};

GLuint *indiciesData = new GLuint[totalIndicies]{

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

        //this is for the point above the triangle
//             0, 1, 8,        //thirteenth triangle
//             0, 4, 8,        //fourteenth triangle
//             1, 5, 8,        //fifteenth triangle
//             4, 5, 8,        //sixteenth triangle

        //this is for the ground
        9,  10, 11,      //seventeenth triangle
        10, 11, 12,      //eighteenth triangle


        //this is for another but same cube which is located at different position
        13, 14, 15,        // triangle
        14, 15, 16,        // triangle
        13, 14, 17,        // triangle
        14, 17, 18,        // triangle
        17, 18, 19,        // triangle
        18, 19, 20,        // triangle
        15, 16, 19,        // triangle
        16, 19, 20,        // triangle
        13, 15, 17,        // triangle
        15, 17, 19,        // triangle
        14, 16, 18,        // triangle
        16, 20, 18         // triangle
};




//Vertex m_verticiesArr[21] = {
//
//        //an entity with all unique vertex attributes(shape: cube)
//        {{0.5f, 0.5f, 0.5f},    {1.0f, 1.0f, 1.0f}},
//        {{0.5f, 0.5f, -0.5f},   {1.0f, 1.0f, 1.0f}},
//        {{0.5f, -0.5f, 0.5f},   {1.0f, 1.0f, 1.0f}},
//        {{0.5f, -0.5f, -0.5f},  {1.0f, 1.0f, 1.0f}},
//        {{-0.5f, 0.5f, 0.5f},   {1.0f, 1.0f, 1.0f}},
//        {{-0.5f, 0.5f, -0.5f},  {1.0f, 1.0f, 1.0f}},
//        {{-0.5f, -0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}},
//        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
//
//        {{0.0f, 10.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},    //this is a point at the top of the cube
//
//        //these vertex attributes are for the ground
//        {{960.0f, -10.0f, 540.0f}, {1.0f, 0.0f, 0.0f}},
//        {{-960.0f, -10.0f, 540.0f}, {0.0f, 1.0f, 0.0f}},
//        {{960.0f, -10.0f, -540.0f}, {0.0f, 0.0f, 1.0f}},
//        {{-960.0f, -10.0f, -540.0f}, {1.0f, 0.0f, 1.0f}},
//
//
//        //another entity with all unique vertex attributes(shape: random IDK)
//        {{3.0f, 0.5f, 1.0f},    {1.0f, 0.0f, 0.0f}},
//        {{3.0f, 0.5f, -1.0f},   {0.0f, 1.0f, 0.0f}},
//        {{2.0f, -0.5f, 1.0f},   {0.0f, 0.0f, 1.0f}},
//        {{2.0f, -0.5f, -1.0f},  {0.5f, 1.0f, 0.0f}},
//
//        {{3.0f, -0.5f, 1.0f},   {0.0f, 1.0f, 0.0f}},
//        {{3.0f, -0.5f, -1.0f},  {0.5f, 0.0f, 1.0f}},
//        {{2.0f, 0.5f, 1.0f},    {0.0f, 0.5f, 0.0f}},
//        {{2.0f, 0.5f, -1.0f},   {0.5f, 0.0f, 0.5f}},
//};
//
//
////GLuint *m_indicies = new GLuint[78]{}
//GLuint m_indiciesArr[78] = {
//
//        //twelf triangles to create a cube(as cube has 6 surfaces and each surface is a rectanle itselft which again is made of 2 triangles)
//        0, 1, 2,        //first triangle
//        1, 2, 3,        //second triangle
//        0, 1, 4,        //third triangle
//        1, 4, 5,        //fourth triangle
//        4, 5, 6,        //fifth triangle
//        5, 6, 7,        //sixth triangle
//        2, 3, 6,        //seventh triangle
//        3, 6, 7,        //eight triangle
//        0, 2, 4,        //ninth triangle
//        2, 4, 6,        //tenth triangle
//        1, 3, 5,        //eleventh triangle
//        3, 7, 5,        //twelfth triangle
//
//        //this is for the point above the triangle
////             0, 1, 8,        //thirteenth triangle
////             0, 4, 8,        //fourteenth triangle
////             1, 5, 8,        //fifteenth triangle
////             4, 5, 8,        //sixteenth triangle
//
//        //this is for the ground
//        9,  10, 11,      //seventeenth triangle
//        10, 11, 12,      //eighteenth triangle
//
//
//        //this is for another but same cube which is located at different position
//        13, 14, 15,        // triangle
//        14, 15, 16,        // triangle
//        13, 14, 17,        // triangle
//        14, 17, 18,        // triangle
//        17, 18, 19,        // triangle
//        18, 19, 20,        // triangle
//        15, 16, 19,        // triangle
//        16, 19, 20,        // triangle
//        13, 15, 17,        // triangle
//        15, 17, 19,        // triangle
//        14, 16, 18,        // triangle
//        16, 20, 18         // triangle
//};






