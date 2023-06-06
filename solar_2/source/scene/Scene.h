
#ifndef SCENE_H
#define SCENE_H


#include "tree/ParaTreeViewController.h"
#include "tree/TopoTreeViewController.h"
#include "utils/Para.h"
#include "scene/Location.h"
#include "scene/Sun.h"
#include "scene/Air.h"
#include "scene/Camera.h"
#include "scene/Terrain.h"
#include "scene/Cloud.h"
#include "scene/Node.h"
#include "scene/Heliostat.h"
#include "scene/Receiver.h"
#include "scene/Ordinary.h"



namespace solar
{

    class Scene
    {
        public:
            Scene();

        public:
            QSharedPointer<TopoTreeViewController> topo_tree_control_;
            QSharedPointer<ParaTreeViewController>
                para_tree_control_; // 里面包含了若干个ParaTreeModel
            // QList<QSharedPointer<ParaTreeViewController>> world_para_tree_controllist;

        private:
            QSharedPointer<Location> location_;
            QSharedPointer<Sun> sun_;
            QSharedPointer<Air> air_;
            QSharedPointer<Terrain> terrain_;
            QSharedPointer<Camera> camera_;
            
            QSharedPointer<Cloud> cloud_;
           

    };

} // namespace solar

#endif // SCENE_H
