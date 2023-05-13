
#ifndef SCENE_H
#define SCENE_H


#include "tree/TopoTreeViewController.h"
#include "tree/ParaTreeViewController.h"
#include "utils/Para.h"
#include "scene/Location.h"
#include "scene/Sun.h"
namespace solar{


class Scene
{
public:
    Scene();


public:
    QSharedPointer<TopoTreeViewController> topo_tree_control;
    QSharedPointer<ParaTreeViewController> para_tree_control;   //里面包含了若干个ParaTreeModel
    //QList<QSharedPointer<ParaTreeViewController>> world_para_tree_controllist;

private:
    QSharedPointer<Location> location;
    QSharedPointer<Sun> sun;


};


}

#endif // SCENE_H
