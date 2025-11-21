
#include <glad/glad.h> //must include glad before glfw bc glad has the required openGL headers needed for other libs
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include "Engine.h"


int main() {
    Engine engine(1200, 800, "NEW ENGINE");
    engine.Init();
    engine.Run();
    
    

    return 0;

}
