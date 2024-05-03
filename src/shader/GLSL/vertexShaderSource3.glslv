#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;


//we won't add any tranformations to the object now
//uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{
    //gl_Position = transform * perspective * view * model * vec4(aPosition, 1.0f);

    gl_Position = perspective * view * model * vec4(aPosition, 1.0f);

    //gl_Position = transform * vec4(aPosition, 1.0f);
    //gl_Position = vec4(aPosition, 1.0f);


    vertexColor = aColor;

}


