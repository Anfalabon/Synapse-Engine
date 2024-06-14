#version 330 core


layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;
//out float time;



uniform mat4 transform = mat4(1.0f);
uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{   
    //gl_Position = transform * perspective * view * model * vec4(aPosition, 1.0f);
    //gl_Position = transform * vec4(aPosition, 1.0f);
    //gl_Position = vec4(aPosition, 1.0f);


    gl_Position = transform * perspective * view * model * vec4(aPosition, 1.0f);

    vertexColor = aColor;
}


