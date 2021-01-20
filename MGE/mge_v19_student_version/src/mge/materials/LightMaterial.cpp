#include "LightMaterial.hpp"

#include "glm.hpp"

#include "LightMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"

#include <mge/Lights/PointLight.h>
#include "mge/Lights/DirectionalLight.h"


ShaderProgram* LightMaterial::_shader = NULL;

LightMaterial::LightMaterial(glm::vec3 pDiffuseColor) :_diffuseColor(pDiffuseColor)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void LightMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "light.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "light.fs");
        _shader->finalize();
    }
}

LightMaterial::~LightMaterial()
{
    //dtor
}

void LightMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void LightMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    _shader->use();


    int lightCount = pWorld->getLightCount();
    Light* light= pWorld->getLightAt(0);
   
    DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(light);
    
    if (dirLight) {
        glm::vec3 direction =glm::normalize(dirLight->getTransform()[2]);
        glUniform3fv(_shader->getUniformLocation("lightDirection"), 1,glm::value_ptr(direction));
        
    }

    PointLight* pointLight = dynamic_cast<PointLight*>(light);
    if (pointLight) {
        glm::vec3 lightPosition = pointLight->getWorldTransform()[3];
        glUniform3fv(_shader->getUniformLocation("pointLightPos"), 1, glm::value_ptr(lightPosition));
    }


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
