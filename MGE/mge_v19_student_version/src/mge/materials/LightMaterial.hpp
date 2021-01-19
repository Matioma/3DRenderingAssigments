#pragma once
#ifndef LIGHTMATERIAL_HPP
#define LIGHTMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"


#include "mge/core/World.hpp"

class ShaderProgram;
class World;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class LightMaterial : public AbstractMaterial
{
public:
    LightMaterial(glm::vec3 pColor = glm::vec3(1, 0, 0));
    virtual ~LightMaterial();

    virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

    //in rgb values
    void setDiffuseColor(glm::vec3 pDiffuseColor);

private:
    //all the static properties are shared between instances of ColorMaterial
    //note that they are all PRIVATE, we do not expose this static info to the outside world
    static ShaderProgram* _shader;
    static void _lazyInitializeShader();

    //this one is unique per instance of color material
    glm::vec3 _diffuseColor;
};

#endif // LIGHTMATERIAL_HPP
