#version 330 core

//out vec4 FragColor;
in vec3 vertexColor;
in vec2 textCoord;
//in float time;


//uniform vec3 vertexColor;
//uniform vec3 objectColor;
//uniform vec3 lightColor;


//uniform float time;

uniform sampler2D ourTexture;


void main()
{
    //FragColor = vec4(vertexColor, 1.0f);

    //FragColor = vec4(objectColor * lightColor, 1.0f);

    //vec3 changingColor = 0.5f * (sin(time)+1);

    //gl_FragColor = vec4(vertexColor, 1.0f);

    gl_FragColor = texture(ourTexture, textCoord);
}


