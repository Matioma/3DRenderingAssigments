#include "TerrainMaterial.h"
#include "glm.hpp"

#include "LightMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"

#include <mge/Lights/PointLight.h>
#include "mge/Lights/DirectionalLight.h"
#include "mge/Lights/SpotLight.h"

#include "mge/core/Camera.hpp"


ShaderProgram* TerrainMaterial::_shader = NULL;

TerrainMaterial::TerrainMaterial(glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor, float shininess) :_diffuseColor(pDiffuseColor), _specularColor(pSpecularColor), shininess(shininess)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void TerrainMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "terrain.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "terrain.fs");
        _shader->finalize();
    }
}

TerrainMaterial::~TerrainMaterial()
{
    //dtor
}

void TerrainMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void TerrainMaterial::setSpecularColor(glm::vec3 pSpecularColor)
{
    _specularColor = pSpecularColor;
}

void TerrainMaterial::setShininess(float pShininess)
{
    shininess = pShininess;
}

void TerrainMaterial::setHeightMap(Texture* pHeightMap) {
    heightMap = pHeightMap;
}

void TerrainMaterial::setSplatMap(Texture* pSplatMap)
{
    splatMap = pSplatMap;
}

void TerrainMaterial::setDiffuseTexture1(Texture* pDiffuseTexture)
{
    diffuseTexture1 = pDiffuseTexture;
}

void TerrainMaterial::setDiffuseTexture2(Texture* pDeffuseTexture)
{
    diffuseTexture2 = pDeffuseTexture;
}

void TerrainMaterial::setDiffuseTexture3(Texture* pDeffuseTexture)
{
    diffuseTexture3 = pDeffuseTexture;
}

void TerrainMaterial::setDiffuseTexture4(Texture* pDeffuseTexture)
{
    diffuseTexture4 = pDeffuseTexture;
}

void TerrainMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!heightMap) {
        std::cout << "HeightMap is missing" << std::endl;
        return;
    }  
    if (!diffuseTexture1) { 
        std::cout << "Diffuse Texture is missing" << std::endl; 
        return;
    }
    
    _shader->use();

    



    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightMap->getId());
    glUniform1i(_shader->getUniformLocation("heightMap"),0);
    glUniform1f(_shader->getUniformLocation("maxHeight"), 10);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, splatMap->getId());
    glUniform1i(_shader->getUniformLocation("splatMap"), 1);


    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, diffuseTexture1->getId());
    glUniform1i(_shader->getUniformLocation("diffuseTexture1"), 2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, diffuseTexture2->getId());
    glUniform1i(_shader->getUniformLocation("diffuseTexture2"), 3);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, diffuseTexture3->getId());
    glUniform1i(_shader->getUniformLocation("diffuseTexture3"), 4);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, diffuseTexture4->getId());
    glUniform1i(_shader->getUniformLocation("diffuseTexture4"), 5);



    int lightCount = pWorld->getLightCount();
    Light* light = pWorld->getLightAt(0);


    DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(light);

    if (dirLight) {
        glUniform1i(_shader->getUniformLocation("lightType"), 0);
        glm::vec3 direction = glm::normalize(dirLight->getTransform()[2]);
        glUniform3fv(_shader->getUniformLocation("lightDirection"), 1, glm::value_ptr(direction));

    }
    PointLight* pointLight = dynamic_cast<PointLight*>(light);
    if (pointLight) {
        glUniform1i(_shader->getUniformLocation("lightType"), 1);
    }

    SpotLight* spotLight = dynamic_cast<SpotLight*>(light);
    if (spotLight) {
        glUniform1i(_shader->getUniformLocation("lightType"), 2);
        glm::vec3 down = -glm::normalize(spotLight->getWorldTransform()[1]);
        // std::cout << down << std::endl;
        glUniform3fv(_shader->getUniformLocation("lightDirection"), 1, glm::value_ptr(down));

        glUniform1f(_shader->getUniformLocation("coneAngle"), 60);
        glUniform1f(_shader->getUniformLocation("coneFallOffAngle"), 20);
    }


    glm::vec3 lightPosition = light->getWorldTransform()[3];
    glUniform3fv(_shader->getUniformLocation("pointLightPos"), 1, glm::value_ptr(lightPosition));
    //Specular data
    glm::vec3 worldCameraPosition = pWorld->getMainCamera()->getWorldPosition();
    glUniform3f(_shader->getUniformLocation("cameraPosition"), worldCameraPosition.x, worldCameraPosition.y, worldCameraPosition.z);
    glUniform3f(_shader->getUniformLocation("specularColor"), _specularColor.x, _specularColor.y, _specularColor.z);
    glUniform1f(_shader->getUniformLocation("shininess"), shininess);


    glUniform3fv(_shader->getUniformLocation("ambientColor"), 1, glm::value_ptr(light->getColor()));
    //set the material color
    glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));





    //pass in all MVP matrices separately
    glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
    glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );

}
