#include "Scene.h"

Scene::Scene()
{
    location = new Location();
    sun = new Sun();
    air = new Air();
    camera = new Camera;
    terrain = new Terrain();
    cloud = new Cloud();
    topoTreeViewController = new TopoTreeViewController();
    topo_root_node = static_cast<TreeModel*>(topoTreeViewController->getTreeModel())->getRootNode()  ;   //这里注意类型转换

    //给para添加世界中的参数
    ParaTreeViewController* sunParaTree = new ParaTreeViewController(SUN,sun);
    paraTreeViewController.append(sunParaTree);
//    ParaTreeViewController sunParaTree(SUN,sun);
//    paraTreeViewController.insert("Sun",sunParaTree);
//    ParaTreeViewController locationParaTree(LOCATION, location);
//    paraTreeViewController.insert("Location",locationParaTree);
//    ParaTreeViewController airParaTree(AIR,air);
//    paraTreeViewController.insert("Air",airParaTree);
//    ParaTreeViewController cameraParaTree(CAMERA,camera);
//    paraTreeViewController.insert("Camera",cameraParaTree);
//    ParaTreeViewController terrainParaTree(TERRAIN, terrain);
//    paraTreeViewController.insert("Terrain",terrainParaTree);
//    ParaTreeViewController cloudParaTree(CLOUD,cloud);
//    paraTreeViewController.insert("Cloud",cloudParaTree);

    //遍历topo_root_node的每个子节点，给每个子节点都设置一个ParaTreeViewController
    //这里先不写

}

Scene::~Scene()
{
    delete location;
    delete sun;
    delete air;
    delete camera;
    delete terrain;
    delete cloud;
}


