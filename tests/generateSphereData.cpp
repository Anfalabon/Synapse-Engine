#include <iostream>
#include <vector>
#include <cmath>

std::vector<float> generateSphereVertices(float radius, int latSegments, int longSegments)
{
    std::vector<float> vertices;

    for (int i = 0; i <= latSegments; ++i)
    {
        float theta = i * M_PI / latSegments;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int j = 0; j <= longSegments; ++j)
        {
            float phi = j * 2 * M_PI / longSegments;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;
            float u = 1.0 - (float(j) / longSegments);
            float v = 1.0 - (float(i) / latSegments);

            vertices.push_back(radius * x);
            vertices.push_back(radius * y);
            vertices.push_back(radius * z);
        }
    }

    return vertices;
}

std::vector<unsigned int> generateSphereIndices(int latSegments, int longSegments)
{
    std::vector<unsigned int> indices;

    for (int i = 0; i < latSegments; ++i)
    {
        for (int j = 0; j < longSegments; ++j)
        {
            int first = (i * (longSegments + 1)) + j;
            int second = first + longSegments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    return indices;
}

int main()
{
    float radius = 1.0f;
    int latSegments = 20;
    int longSegments = 20;

    std::vector<float> vertices = generateSphereVertices(radius, latSegments, longSegments);
    std::vector<unsigned int> indices = generateSphereIndices(latSegments, longSegments);

    std::cout << "Vertices" << '\n';

    for(std::size_t i=0; i<vertices.size(); ++i)
    {
        float r = rand() % 2;
        float g = rand() % 2;
        float b = rand() % 2;

        float txtCoord1 = (1 + rand()) % 2;
        float txtCoord2 = (1 + rand()) % 2;


        if(i%3 == 0) std::cout << " " << r << ", " << g << ", " << b << ", " << txtCoord1 << ", " << txtCoord2 << ",\n\n";


        std::cout << vertices[i] << ", ";
    }

    std::cout << "\n\n";
    std::cout << "Indices" << '\n';



//    for(std::size_t i=0; i<indices.size(); ++i)
//    {
//        if(i%3 == 0) std::cout << "\n\n";
//        std::cout << indices[i] << " ,";
//    }


    std::cout << "Total verticies: " << vertices.size() << '\n';
    std::cout << "Total indicies: " << indices.size() << '\n';


    // Use vertices and indices for rendering
    // Example: OpenGL code to create VBO and EBO goes here

    return 0;
}
