#pragma once

/*
    存场景中的所有数据
注意：QObject的子类不可复制，使用指针可以避免这个问题
*/

#include "Para.h"
#include "ParaTreeViewController.h"
#include "TopoTreeViewController.h"

namespace solar
{
    class Scene : public QObject
    {
            Q_OBJECT

        public:
            Scene();
            ~Scene();

        public:
            // Q_INVOKABLE  getTopoTreeViewController() const;

        public:
            Location* location;
            Sun* sun;
            Air* air;
            Camera* camera;
            Terrain* terrain;
            Cloud* cloud;

            TreeNode* topo_root_node;

            QList<ParaTreeViewController*>
                paraTreeViewController; // 每个节点都需要一个treeview
            TopoTreeViewController* topoTreeViewController;
    };
} // namespace solar
