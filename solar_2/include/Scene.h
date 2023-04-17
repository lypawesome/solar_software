
#ifndef SCENE_H
#define SCENE_H


#include "TopoTreeViewController.h"
#include "ParaTreeViewController.h"
#include "Para.h"

namespace solar{


class Scene
{
public:
    Scene();


public:
    QSharedPointer<TopoTreeViewController> topo_tree_control;
    QList<QSharedPointer<ParaTreeViewController>> world_para_tree_controllist;

    QSharedPointer<ParaTreeViewController> sun_para_tree_control;
    QSharedPointer<ParaTreeViewController> location_para_tree_control;
private:
    QSharedPointer<Location> location;
    QSharedPointer<Sun> sun;


};


}

#endif // SCENE_H
