#include "Application.hpp"
#include "../debug/Timer.hpp"

//direction vector is also defined as cameraFront
//extern glm::vec3 directionVector;



//if you are getting 'multiple definition' linker error then first check the linking of all obj files in 'Makefile'.
//then add or fix anything if needed.
//lastly delete all the previous obj files and generate new obj files using make


namespace Synapse
{

int8_t Main()   //will place 'main.cpp' in the 'Engine' directory instead of 'Engine/src/core'
{
    Timer timer;
    timer.Start();

    //Engine *engine = new Engine();
    Engine &engine = Engine::getInstance();
    if(engine.Init())
    {
        engine.Run();
    }
    //delete engine;

    timer.ShutDown();
    timer.PrintResult("Ran for: ");

    return 0;
}


}



//will add the entity point for other platforms

int main(){return static_cast<int>(Synapse::Main());}

















































// #ifdef MAIN_INIT


// void updateFrame(Camera &camera,
//                  GLuint &VAO,
//                  Shader &entityShaders)
// {
//     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//     glEnable(GL_DEPTH_TEST);
//     glDisable(GL_CULL_FACE);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     entityShaders.useProgram();
   
//     //    GLuint objectLocation = glGetUniformLocation(shaderProgramID, "objectColor");
//     //    glUniform3f(objectLocation, 1.0f, 0.5f, 0.31f);

//     //    GLuint lightLocation = glGetUniformLocation(shaderProgramID, "lightColor");
//     //    glUniform3f(lightLocation, 1.0f, 1.0f, 1.0f);

//     // float timeSinceInit = glfwGetTime();
//     // float changingColor = 0.5f * (glm::sin(timeSinceInit) + 1.0f);
//     // GLuint vertexColorLocation = glGetUniformLocation(entityShaders.ProgramID(), "vertexColor");
//     // glUniform3f(vertexColorLocation, changingColor, changingColor - 0.5, changingColor + 0.5);


//     //view = glm::lookAt(cameraPos, targetPos, upVecPos);
//     //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));


//     //camera.lookAtTarget();
//     camera.lookAtTarget(CoordinateTransformation::view);
    

//     CoordinateTransformation::model = glm::rotate(CoordinateTransformation::model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//     CoordinateTransformation::perspective = glm::perspective(glm::radians(camera.zoomValue()), 1920.0f/1080.0f, 0.1f, 100.0f);

    

//     //transform coordinate to coordinate

//     CoordinateTransformation::modelLocation(entityShaders.ProgramID());
//     //CoordinateTransformation::viewLocation(entityShaders.ProgramID());    
//     camera.viewLocation(entityShaders.ProgramID());
//     CoordinateTransformation::perspectiveLocation(entityShaders.ProgramID());


//     // GLuint transformationLocation = glGetUniformLocation(shaderProgramID, "transform");
//     // glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, glm::value_ptr(transformation));

//     //bind the vertex attribute array and draw the premitive
//     glBindVertexArray(VAO);
//     //glDrawArrays(GL_TRIANGLES, 0, 36);
//     glDrawElements(GL_TRIANGLES, Entity::totalIndicies, GL_UNSIGNED_INT, 0);

// }






// int core()
// {
//     //initialize the glfw functions and other glfw features
//     if (!glfwInit())
//     {
//         std::cerr << "Falied to initialize glfw!" << '\n';
//         return -1;
//     }

//     GLfloat WIDTH = 1920.0f;
//     GLfloat HEIGHT = 1080.0f;


//     Window window(WIDTH, HEIGHT,"Simulation Engine");

//     //simulate a camera
//     Camera camera;
//     Camera::setupMouse(window.windowAddress());

//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//        std::cout << "Failed to load GLAD" << std::endl;
//        return -1;
//     }   

//     glViewport(0, 0, WIDTH, HEIGHT);


//     //initialize, compile, link and remove the vertex and fragment shaders
//     //will make it 'entityShader' from 'entityShaders'
//     Shader entityShaders("../GLSL/vertexShaderSource1.glslv", "../GLSL/fragmentShaderSource1.glslf");
//     entityShaders.setup();
//     entityShaders.link();
//     entityShaders.remove();
//     //GLuint entityShaderProgramID = entityShaders.ProgramID();



//     GLuint VBO;
//     glGenBuffers(1, &VBO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(Entity::verticies), Entity::verticies, GL_STATIC_DRAW);
//     //glBufferData(GL_ARRAY_BUFFER, sizeof(Entity::verticies), Entity::verticies, GL_STATIC_DRAW);

//     //we strictly have to gen, bind, set offset and enable the vertex array object(VAO) right after vertex buffer object(VBO)
//     GLuint VAO;
//     glGenVertexArrays(1, &VAO);
//     glBindVertexArray(VAO);

//     //for the position vertex attribute (layout (location = 0))
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
//     glEnableVertexAttribArray(0);
//     //for the color vertex attribute (layout (location = 0))
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//     glEnableVertexAttribArray(1);
    
//     GLuint EBO;
//     glGenBuffers(1, &EBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Entity::indicies), Entity::indicies, GL_STATIC_DRAW);

//     //to render two cubes at diffrent position, in glBufferData() instead of going for whole sizeof(Entity::indicies) at once we need to do it twice

//     //glm::mat4 transformation = glm::mat4(1.0f);

//     //for now we won't rotate the model at every frame even at all
//     CoordinateTransformation::model = glm::rotate(CoordinateTransformation::model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//     //CoordinateTransformation::perspective = glm::perspective(glm::radians(45.0f), 1920.0f/1080.0f, 0.1f, 100.0f);


// #define MULTITHREADING_SYSTEM_AUDIO
// #define SFML_AUDIO_BUFFER_NOT
// #ifdef SFML_AUDIO_BUFFER
//     //system("xdg-open ~/Downloads/body-fall-47877.mp3");
//     //std::thread playMusic(system, "xdg-open ~/Downloads/body-fall-47877.mp3");
//     sf::Music music;
//     sf::SoundBuffer buffer;
//     if(!music.openFromFile("~/Downloads/body-fall-47877.wav"))
//     if(!buffer.loadFromFile("../../../../../Downloads/body-fall-47877.wav"))
//     {
//         std::cerr << "Couldn't open the audio file!" << '\n';
//     }
//     music.play();

//     sf::Sound sound;
//     sound.setBuffer(buffer);
//     sound.play();        
// #endif

// #define INSPECTION_MODE 0
// #define GAME_MODE 1

//     //using namespace renderingInfo;
//     //core Engine loop
//     while(window.running())
//     {
//         window.getKeyboardInput();
//         camera.getKeyboardInput(window.windowAddress());
        
//         camera.applyPhysics(GAME_MODE);

//         updateFrame(camera, VAO, entityShaders);
//         renderingInfo::framesPerSecond();

//         window.swapBuffers();
//         window.pollEvents();        
//     }


//     //unbind the vertex buffer object, element buffer object and vertex array object
//     glBindVertexArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//     //delete the vertex arrays, vertex buffers and element buffers
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);   

//     //delete the shader program
//     entityShaders.removeProgram();
    

//     window.terminate();
//     return 0;
// }





// #endif  //MAIN_INIT




















        //float timeSinceInit = glfwGetTime();
                
        
        //float inc = 1.0f;
        //float rangeValueXYZ = 0.5f * (glm::sin(inc * timeSinceInit) + 1.0f) - 0.5f;
        //float rangeValueDegree = 360.0f - 360.0f * 0.5f * (glm::sin(inc * timeSinceInit)+1.0f); // // 0.0f <= rangeValue >= 360.f

        //std::cout << rangeValueXYZ << '\n';
        //std::cout << rangeValueDegree << "°" << '\n';

        // std::cout << colorValue << '\n';
        // int vertexColorLocation = glGetUniformLocation(shaderProgramID, "vertexColor");
        // glUniform4f(vertexColorLocation, 0.0f, colorValue, 0.0f, 1.0f);


        //glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
        //glm::mat4 transformation = glm::mat4(1.0f);

        // float changeX = 0.0f + transform.translate.x;
        // float changeY = 0.0f + transform.translate.y;
        // float changeZ = 0.0f + transform.translate.z;

        //transformation = glm::translate(transformation, glm::vec3(changeX, changeY, changeZ));
        //transformation = glm::rotate(transformation, glm::radians(rangeValueDegree), glm::vec3(0.0f, 0.0f, 1.0f));















////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



































