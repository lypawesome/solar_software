
#include "scene/Scene.h"

namespace solar{


Scene::Scene()
{
    topo_tree_control = QSharedPointer<TopoTreeViewController>(new TopoTreeViewController);
    para_tree_control = QSharedPointer<ParaTreeViewController>(new ParaTreeViewController);

    sun = QSharedPointer<Sun>(new Sun);
    location = QSharedPointer<Location>(new Location);

    para_tree_control->addParaTreeModel(LOCATION,location);
    para_tree_control->addParaTreeModel(SUN,sun);

    //给TopoTreeViewController加一个函数，让所有Topo节点对应的ParaTreeModel全部加到ParaTreeViewController中
    // topo_tree_control -> setParaTreeModels(para_tree_control)

}


}

