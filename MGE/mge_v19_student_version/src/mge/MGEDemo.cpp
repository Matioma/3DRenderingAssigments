#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/LightMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/FollowBehaviour.h"
#include "mge/behaviours/OrbitBehaviour.h"
#include "mge/behaviours/SinMovementBehaviour.h"


#include "mge/Lights/PointLight.h"
#include "mge/Lights/DirectionalLight.h"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame (),_hud(0)
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    Assigment3();
    //Assigment2();

}

void MGEDemo::Assigment3()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

    Mesh* coneSmooth = Mesh::load(config::MGE_MODEL_PATH + "cone_smooth.obj");
    Mesh* teaPotMesh = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth.obj");
    Mesh* cilinderMesh = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth.obj");



    //MATERIALS

    //create some materials to display the cube, the plane and the light
   AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
    AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
    AbstractMaterial* brickMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));
    AbstractMaterial* landNaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));




     AbstractMaterial* red = new ColorMaterial(glm::vec3(1, 0, 0));
    AbstractMaterial* blue = new ColorMaterial(glm::vec3(0, 0, 1));

    AbstractMaterial* whiteMaterial = new LightMaterial(glm::vec3(0.5, 1.0, 0.7));

    //SCENE SETUP

    //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 15, 15));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    //camera->setBehaviour(new FollowBehavior(*camera));


    _world->add(camera);
    _world->setMainCamera(camera);


    //add the floor
    GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(whiteMaterial);
    _world->add(plane);



    GameObject* cube = new GameObject("cube", glm::vec3(0, 1, 0));
    cube->scale(glm::vec3(5, 5, 5));
    cube->setMesh(teaPotMesh);
    cube->setMaterial(whiteMaterial);
    cube->setBehaviour(new RotatingBehaviour(glm::vec3(1,0,1)));
    //_world->add(cube);


    //camera->setBehaviour(new OrbitBehaviour(*cube,glm::vec3(0,25,25)));
    //add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
    //It's here as a place holder to get you started.
    //Note how the texture material is able to detect the number of lights in the scene
    //even though it doesn't implement any lighting yet!

    Light* light = new PointLight("light", glm::vec3(0,0,0));
    light->rotate(90, glm::vec3(1, 0, 0));
    light->setColor(glm::vec4(1, 0.0f, 0.0f,1.0f));
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    //light->setBehaviour(new OrbitBehaviour(*cube, glm::vec3(0,0,10), false));
    light->setBehaviour(new SinMovementBehaviour(1, glm::vec3(0,-1,0)));

    //light->setBehaviour(new RotatingBehaviour(glm::vec3(1,0,0)));
    _world->add(light);
}

void MGEDemo::Assigment2()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

    Mesh* coneSmooth = Mesh::load(config::MGE_MODEL_PATH + "cone_smooth.obj");
    Mesh* teaPotMesh = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth.obj");
    Mesh* cilinderMesh = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth.obj");



    //MATERIALS

    //create some materials to display the cube, the plane and the light
    AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
    AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
    AbstractMaterial* brickMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));
    AbstractMaterial* landNaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));




    AbstractMaterial* red = new ColorMaterial(glm::vec3(1, 0, 0));
    AbstractMaterial* blue = new ColorMaterial(glm::vec3(0, 0, 1));

    //SCENE SETUP

    //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 20, 7));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    //camera->setBehaviour(new FollowBehavior(*camera));


    _world->add(camera);
    _world->setMainCamera(camera);



    // https://free3d.com/3d-model/trees-9-53338.html mesh source
    Mesh* treeMesh = Mesh::load(config::MGE_MODEL_PATH + "Tree.obj");
    AbstractMaterial* treeTexture = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Bark___0.jpg"));


    GameObject* tree = new GameObject("tree", glm::vec3(0, 0, 0));
    tree->setMesh(treeMesh);
    tree->setMaterial(treeTexture);
    _world->add(tree);


    //add the floor
    GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(runicStoneMaterial);
    _world->add(plane);

    //add a spinning sphere
    /*  GameObject* sphere = new GameObject ("sphere", glm::vec3(0,0,0));
    sphere->scale(glm::vec3(2.5,2.5,2.5));
    sphere->setMesh (sphereMeshS);
    sphere->setMaterial(runicStoneMaterial);
    sphere->setBehaviour (new RotatingBehaviour());
    _world->add(sphere);*/



    GameObject* coolStuff = new GameObject("coolStuff", glm::vec3(0, 0, 0));
    coolStuff->setBehaviour(new KeysBehaviour());
    //camera->setBehaviour(new FollowBehaviour(*coolStuff, glm::vec3(0, 10, 10)));
    camera->setBehaviour(new OrbitBehaviour(*coolStuff, glm::vec3(0, 10, 10)));


    _world->add(coolStuff);

    //camera->setBehaviour(new FollowBehavior(*coolStuff));



    GameObject* cone = new GameObject("cone", glm::vec3(-0.5, 0, 0));
    cone->rotate(0, glm::vec3(1, 0, 0));
    cone->scale(glm::vec3(1, 1, 1));
    cone->setMesh(coneSmooth);
    cone->setMaterial(brickMaterial);
    coolStuff->add(cone);

    GameObject* cone1 = new GameObject("cone", glm::vec3(0.5, 0, 0));
    cone1->rotate(0, glm::vec3(1, 0, 0));
    cone1->scale(glm::vec3(1, 1, 1));
    cone1->setMesh(coneSmooth);
    cone1->setMaterial(brickMaterial);
    coolStuff->add(cone1);

    GameObject* teaPot = new GameObject("teapot", glm::vec3(0, 0, 0));
    teaPot->scale(glm::vec3(0.3, 0.3, 0.3));
    teaPot->setMesh(teaPotMesh);
    teaPot->setMaterial(landNaterial);
    coolStuff->add(teaPot);

    GameObject* cilinder1 = new GameObject("Cilinder", glm::vec3(0, 1, 2));
    cilinder1->setMesh(cilinderMesh);
    cilinder1->setMaterial(red);
    teaPot->add(cilinder1);


    GameObject* cilinder2 = new GameObject("Cilinder", glm::vec3(0, 1, -2));
    cilinder2->setMesh(cilinderMesh);
    cilinder2->setMaterial(blue);
    teaPot->add(cilinder2);

    //teaPot->setMesh();


    //_world->add(cone);

    //add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
    //It's here as a place holder to get you started.
    //Note how the texture material is able to detect the number of lights in the scene
    //even though it doesn't implement any lighting yet!

    /*  Light* light = new Light("light", glm::vec3(0,4,0));
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    light->setBehaviour(new KeysBehaviour(25));
    _world->add(light);*/
}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
