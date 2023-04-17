
#include "Scene.h"

namespace solar{


Scene::Scene()
{
    topo_tree_control = QSharedPointer<TopoTreeViewController>(new TopoTreeViewController);

    sun = QSharedPointer<Sun>(new Sun);
    sun_para_tree_control = QSharedPointer<ParaTreeViewController>(new ParaTreeViewController(SUN,sun));
    location = QSharedPointer<Location>(new Location);
    location_para_tree_control = QSharedPointer<ParaTreeViewController>(new ParaTreeViewController(LOCATION,location));
}


}

