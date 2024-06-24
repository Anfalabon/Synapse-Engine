#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;


uniform vec3 position;  //this should be 'translate' but for now let's keep it like this
//uniform vec3 translate;


uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{   
    //gl_Position = transform * perspective * view * model * vec4(aPosition, 1.0f);
    //gl_Position = transform * vec4(aPosition, 1.0f);
    //gl_Position = vec4(aPosition, 1.0f);



    mat4 localToCamera = perspective * view * model;
    gl_Position = localToCamera * vec4(aPosition + position, 1.0f);


    vertexColor = aColor;
}


