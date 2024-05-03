#version 330 core

out vec4 FragColor;

in vec3 vertexColor;

//uniform vec3 vertexColor;

//uniform vec3 objectColor;
//uniform vec3 lightColor;


void main()
{
    FragColor = vec4(vertexColor, 1.0f);

    //FragColor = vec4(objectColor * lightColor, 1.0f);
}


