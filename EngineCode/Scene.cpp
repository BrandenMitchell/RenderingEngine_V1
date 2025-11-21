#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iomanip> 
#include "Light.h"



Scene::Scene() {

}


Scene::~Scene() {

}


std::vector<unsigned int> CreateIndexedData(std::vector<Vertex>& vertices) {

    struct usedVertex {
        Vertex vertex;
        unsigned int index;
    };

    std::vector<unsigned int> indices;
    std::vector<usedVertex> dupes;
    std::vector<Vertex> updatedVertices;

    for (Vertex vertex : vertices) {

        bool dupeFound = false;

        for (usedVertex dupe : dupes) {
            if (vertex == dupe.vertex) {
                indices.emplace_back(dupe.index);
                dupeFound = true;
                break;
            }
        }

        if (!dupeFound) {
            usedVertex val = { vertex, (unsigned int)dupes.size() };
            dupes.emplace_back(val);
            indices.emplace_back(updatedVertices.size());
            updatedVertices.emplace_back(val.vertex);
        }
    }
    vertices = updatedVertices;
    return indices;
}


void Scene::CreateScene(unsigned int screenWidth, unsigned int screenHeight) {
    SCR_WIDTH = screenWidth;
    SCR_HEIGHT = screenHeight;
    m_globalShader.ShaderFileSetup("vertSimple.vert", "floorFragShader.frag");



    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    std::vector<Texture> textures;

    TextureClass testTexture(0, "CoolWoodContainer.png");
    testTexture.Bind();

    Texture testTextureContainer;
    testTextureContainer.id = testTexture.GetTextureID();
    testTextureContainer.index = testTexture.GetTextureIndex();
    testTextureContainer.type = "";

    TextureClass specularTexture(1, "WoodBoxSpecular.png");
    specularTexture.Bind();
    Texture specular;
    specular.id = specularTexture.GetTextureID();
    specular.index = specularTexture.GetTextureIndex();
    specular.type = "";

    TextureClass thirdTexture(2, "awesomeface.png");
    thirdTexture.Bind();
    Texture third;
    third.id = thirdTexture.GetTextureID();
    third.index = thirdTexture.GetTextureIndex();
    third.type = "";

    TextureClass normalWoodContainer(0, "WoodContainerImg.jpg");
    normalWoodContainer.Bind();
    Texture woodContainer;
    woodContainer.id = normalWoodContainer.GetTextureID();
    woodContainer.index = normalWoodContainer.GetTextureIndex();
    woodContainer.type = "";


    textures.emplace_back(testTextureContainer);
    textures.emplace_back(specular);
    textures.emplace_back(third);


    std::vector<Vertex> vertexVector;
    constexpr int floatsPerVertex = 8;

    int vertexCount = (sizeof(vertices) / sizeof(float)) / floatsPerVertex;


    for (int i = 0; i < vertexCount; i++) {
        int base = i * floatsPerVertex;

        Vertex vert;
        vert.Position = glm::vec3(vertices[base + 0], vertices[base + 1], vertices[base + 2]);
        vert.Normal = glm::vec3(vertices[base + 3], vertices[base + 4], vertices[5]);
        vert.TextCoords = glm::vec2(vertices[base + 6], vertices[base + 7]);

        vertexVector.push_back(vert);
    }
    std::vector<unsigned int> indices = CreateIndexedData(vertexVector);


    std::unique_ptr<Mesh> firstMesh = std::make_unique<Mesh>(vertexVector, indices, textures, "vertSimple.vert", "fragShaderMesh.frag");
    firstMesh->SetPosition(glm::vec3(1.2f, 1.0f, 2.0f));

    ////set uniforms
    firstMesh->addUniform((std::string)"texture1", ONEINT, (unsigned int)0);
    firstMesh->addUniform((std::string)"texture2", ONEINT, (unsigned int)1);
    firstMesh->addUniform((std::string)"texture3", ONEINT, (unsigned int)2);
    firstMesh->addUniform((std::string)"projection", MATFOUR, glm::value_ptr(projection));
    firstMesh->addUniform((std::string)"view", MATFOUR, glm::value_ptr(view));
    currentMeshModel = firstMesh->GetModelMatrix();
    firstMesh->addUniform("model", MATFOUR, glm::value_ptr(currentMeshModel));
    /*glm::vec3 tempPos = firstMesh->GetPosition();
    std::cout << "Cube position: " << tempPos.x << " , " << tempPos.y << " , " << tempPos.z << "\n";*/

    meshObjs.emplace_back(std::move(firstMesh));

    float lightingVertices[] = {
        -0.5f, -0.5f, -0.5f, // 0
         0.5f, -0.5f, -0.5f, // 1
         0.5f,  0.5f, -0.5f, // 2
        -0.5f,  0.5f, -0.5f, // 3
        -0.5f, -0.5f,  0.5f, // 4
         0.5f, -0.5f,  0.5f, // 5
         0.5f,  0.5f,  0.5f, // 6
        -0.5f,  0.5f,  0.5f  // 7
    };
    std::vector<unsigned int> lightingIndices = {
        // back face
        0, 1, 2,
        2, 3, 0,
        // front face
        4, 5, 6,
        6, 7, 4,
        // left face
        4, 0, 3,
        3, 7, 4,
        // right face
        1, 5, 6,
        6, 2, 1,
        // bottom face
        4, 5, 1,
        1, 0, 4,
        // top face
        3, 2, 6,
        6, 7, 3
    };

    std::vector<Vertex> lightingVerts;
    int floatsPerVert = 3;

    vertexCount = (sizeof(lightingVertices) / sizeof(float)) / floatsPerVert;


    for (int i = 0; i < vertexCount; i++) {
        int base = i * floatsPerVert;

        Vertex vert;
        vert.Position = glm::vec3(lightingVertices[base + 0], lightingVertices[base + 1], lightingVertices[base + 2]);
        vert.Normal = glm::vec3(1.0f);
        vert.TextCoords = glm::vec3(1.0f);
        lightingVerts.push_back(vert);
    }

    std::vector<unsigned int> newIndices = CreateIndexedData(lightingVerts);
    //textures.clear();
    //textures.emplace_back(specular);
    //textures.emplace_back(woodContainer);

    glm::vec3 lightColor = glm::vec3(0.4, 0.2f, 0.8f);
    glm::vec3 lightColorDir = glm::vec3(0.01, 0.01f, 0.01f);
    glm::vec3 diffuseColor = lightColorDir * glm::vec3(0.5f);
    glm::vec3 ambient = diffuseColor * glm::vec3(0.2f);
    glm::vec3 specularCol = glm::vec3(1.0f);

    std::unique_ptr<PointLight> ptLight1 = std::make_unique<PointLight>(1.0f, 0.22f, 0.20f);
    ptLight1->AddShader("lightSourceVert.vert", "lightSourceFrag.frag");
    //ptLight1->SetAmbient(ambient);
    //ptLight1->SetDiffuse(diffuseColor);
    //ptLight1->SetDirection(lightColorDir);
    //ptLight1->SetSpecular(specularCol);
    ptLight1->PopulateBuffers(lightingVerts, newIndices);
    ptLight1->SetPosition(glm::vec3(2.5f, 4.0f, -1.5f));
    ptLight1->addUniform((std::string)"projection", MATFOUR, glm::value_ptr(projection));
    ptLight1->addUniform((std::string)"view", MATFOUR, glm::value_ptr(view));
    currentMeshModel = ptLight1->GetModelMatrix();
    ptLight1->addUniform("model", MATFOUR, glm::value_ptr(currentMeshModel));
    //textures.emplace_back(woodContainer);

    //ptLight1->addUniform((std::string)"texture1", ONEINT, (unsigned int)0);
    //ptLight1->addUniform((std::string)"texture2", ONEINT, (unsigned int)1);
    //ptLight1->addUniform((std::string)"pointLights[0].position", THREEFLOAT, ptLight1->GetPosition());
    //ptLight1->addUniform((std::string)"pointLights[0].ambient", THREEFLOAT, ambient);
    //ptLight1->addUniform((std::string)"pointLights[0].diffuse", THREEFLOAT, diffuseColor);
    //ptLight1->addUniform((std::string)"pointLights[0].specular", THREEFLOAT, specularCol);
    //ptLight1->addUniform((std::string)"pointLights[0].constant", ONEFLOAT, 1.0f);
    //ptLight1->addUniform((std::string)"pointLights[0].linear", ONEFLOAT, 0.22f);
    //ptLight1->addUniform((std::string)"pointLights[0].quadratic", ONEFLOAT, 0.20f);
    //ptLight1->addUniform((std::string)"pointLights[0].color", THREEFLOAT, lightColor);

    //tempPos = ptLight1->GetPosition();
    //std::cout << "Light position: " << tempPos.x << " , "<<tempPos.y <<" , " << tempPos.z<< "\n";
    //meshObjs.emplace_back(std::move(ptLight1));
    


}

std::vector<Vertex> Scene::MakeVertexVector(float vertices[],int floatsPerVertex) {
    std::vector<Vertex> vertexVector;
    int vertexCount = (sizeof(vertices) / sizeof(float)) / floatsPerVertex;
    for (int i = 0; i < vertexCount; i++) {
        int base = i * floatsPerVertex;

        Vertex vert;
        vert.Position = glm::vec3(vertices[base + 0], vertices[base + 1], vertices[base + 2]);
        vert.Normal = glm::vec3(vertices[base + 3], vertices[base + 4], vertices[5]);
        vert.TextCoords = glm::vec2(vertices[base + 6], vertices[base + 7]);

        vertexVector.push_back(vert);
    }
    
    return vertexVector;
}

void Scene::DrawScene(Renderer& renderer) {
	std::cout << "Enghine called draw scene" << "\n\n";
    m_globalShader.Bind();
    m_globalShader.setUniformMatrix4("projection", projection);
    m_globalShader.setUniformMatrix4("view", view);
    glm::mat4 model = glm::mat4(1.0f);

    m_globalShader.setUniformMatrix4("model",model);

	for (int i = 0; i < meshObjs.size(); i++) {
        if (meshObjs[i]->hasShader) {
            meshObjs[i]->m_MeshShaderID.Bind();
            if (i == 1) {
                currentMeshModel = meshObjs[i]->GetModelMatrix();
                meshObjs[i]->addUniform("model", MATFOUR, glm::value_ptr(currentMeshModel));
            }
            meshObjs[i]->SetUniforms();
        }
        meshObjs[i]->UpdateModelMatrix(meshObjs[i]->GetPosition());
        meshObjs[i]->Draw(renderer);
	}
	
}


void Scene::UpdateScene(Renderer& renderer, glm::vec3 pos) {
   for (int i = 0; i < meshObjs.size(); i++) {
        meshObjs[i]->UpdateModelMatrix(meshObjs[i]->GetPosition());
   }
}

void Scene::UpdateMatrices() {
    projection = glm::perspective(glm::radians(m_Camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = m_Camera.GetViewMatrix();
}

void Scene::ProcessKeyboardMovement(Camera_Movement direction, float deltaTime) {
    m_Camera.ProcessKeyboardInput(direction, deltaTime);
}

void Scene::ProcessMouseMovement(float xoffset, float yoffset) {
    m_Camera.ProcessMouseMovement(xoffset, yoffset);
}

void Scene::ProcessMouseScroll(float yoffset) {
    m_Camera.processMouseScroll(yoffset);
}

