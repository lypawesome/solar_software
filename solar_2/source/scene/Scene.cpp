
#include "scene/Scene.h"

namespace solar{


Scene::Scene()
{
    para_tree_control_ = QSharedPointer<ParaTreeViewController>(new ParaTreeViewController);
    topo_tree_control_ = QSharedPointer<TopoTreeViewController>(new TopoTreeViewController);

    sun_ = QSharedPointer<Sun>(new Sun);
    location_ = QSharedPointer<Location>(new Location);
    air_ = QSharedPointer<Air>(new Air);
    camera_ = QSharedPointer<Camera>(new Camera);
    terrain_ = QSharedPointer<Terrain>(new Terrain);
    cloud_ = QSharedPointer<Cloud>(new Cloud);

    para_tree_control_->addParaTreeModel(LOCATION,location_);
    para_tree_control_->addParaTreeModel(SUN,sun_);
    para_tree_control_->addParaTreeModel(AIR,air_);
    para_tree_control_->addParaTreeModel(TERRAIN,terrain_);
    para_tree_control_->addParaTreeModel(CAMERA,camera_);
    para_tree_control_->addParaTreeModel(CLOUD,cloud_);

    topo_tree_control_->setParaTreeController(para_tree_control_);
    


}


}

