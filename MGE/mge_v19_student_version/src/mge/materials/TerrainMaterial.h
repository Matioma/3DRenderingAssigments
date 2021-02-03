#pragma once

#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"

#include "mge/core/World.hpp"

class ShaderProgram;
class World;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class TerrainMaterial : public AbstractMaterial
{
public:
    TerrainMaterial(glm::vec3 pColor = glm::vec3(1, 0, 0), glm::vec3 pSpecularColor = glm::vec3(1, 1, 1), float shininess = 1.0);
    virtual ~TerrainMaterial();

    virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

    //in rgb values
    void setDiffuseColor(glm::vec3 pDiffuseColor);
    void setSpecularColor(glm::vec3 pSpecularColor);
    void setShininess(float pShininess);


    void setHeightMap(Texture* pHeightMap);
    void setSplatMap(Texture* pSplatMap);
    void setDiffuseTexture1(Texture* pDeffuseTexture);
    void setDiffuseTexture2(Texture* pDeffuseTexture);
    void setDiffuseTexture3(Texture* pDeffuseTexture);
    void setDiffuseTexture4(Texture* pDeffuseTexture);
private:
    //all the static properties are shared between instances of ColorMaterial
    //note that they are all PRIVATE, we do not expose this static info to the outside world
    static ShaderProgram* _shader;
    static void _lazyInitializeShader();

    //this one is unique per instance of color material
    glm::vec3 _diffuseColor;
    glm::vec3 _specularColor;
    float shininess;

    Texture* heightMap;
    Texture* splatMap;
    Texture* diffuseTexture1;
    Texture* diffuseTexture2;
    Texture* diffuseTexture3;
    Texture* diffuseTexture4;
};

#endif // TERRAINMATERIAL_HPP
