#pragma once

#include <QAbstractItemModel>
#include <QObject>

#include "Para.h"
#include "TreeNode.h"


namespace solar
{
    enum TreeModelType
    {
        TOPO, // 拓扑结构---即右上方scene部分
        LOCATION,
        SUN,
        AIR,
        TERRAIN,
        CAMERA,
        CLOUD, // 右下角，worldPara设置部分
        NODE,
        SHAPE,
        TRACKER,
        ARRAY // 右下角，scenePara设置部分
    };

    class TreeModel : public QAbstractItemModel
    {
            Q_OBJECT

            enum nodeRoles
            {
                NAME = Qt::UserRole + 1,
                PARA
            };

        public:
            // TreeModel(QObject *parent = nullptr);
            TreeModel(int _model_type, QObject* parent = nullptr);
            ~TreeModel();

            TreeNode* createNode(QVariant data1, QVariant data2,
                                 TreeNode* parent, bool editable = false,
                                 bool optional = false,
                                 bool isOptionChild = false,
                                 QString option = ""); // 建立一个新节点

            TreeNode* getRootNode() const;

            int columnCount(const QModelIndex& parent = QModelIndex()) const;
            int rowCount(const QModelIndex& parent = QModelIndex()) const;
            QHash<int, QByteArray> roleNames() const;
            QVariant data(const QModelIndex& index, int role) const;
            Qt::ItemFlags flags(const QModelIndex& index) const;
            QModelIndex index(int row, int column,
                              const QModelIndex& parent = QModelIndex()) const;
            QModelIndex parent(const QModelIndex& index) const;

            void appendChild(const QModelIndex& index, QList<QVariant> dataList,
                             int count);
            void appendChild(const QModelIndex& index,
                             QList<TreeNode*> childNodes,
                             int count); // 添加一系列孩子
            void setNodeColumn(
                QModelIndex index, int column,
                QVariant value); // 设置index这一节点的第column个属性数据为value
            QString
            getNodeColumn(const QModelIndex& index,
                          int column); // 获取index这一节点第column列的数据

            // 右下角PARA特有的
            bool isNodeEditable(const QModelIndex& index);
            bool isNodeOptional(const QModelIndex& index);
            QList<QString> getNodeOptionList(
                const QModelIndex& index); // 获得这一节点的所有option
            void makeChoice(const QModelIndex& index,
                            QString option); // 做出选择

            // 右上角TOPO特有的，在函数开头要检查是否是TOPO类
            QString getIconName(const QModelIndex& index);

            // 这些函数是为了建立参数设置部分的模型，topo部分不需要
            void buildSunTreeModel(Sun* sun); // 建立一个sun的参数设置treeview
            void buildLocationTreeModel(); // Location
            void buildAirTreeModel();      // Air
            void buildTerrainTreeModel();  // Terrain
            void buildCameraTreeModel();   // Camera
            void buildCloudTreeModel();    // Cloud
            void buildNodeTreeModel();     // Node
            void buildShapeTreeModel();    // Shape
            void buildTrackerTreeModel();  // Tracker

        private:
            TreeNode* root_node;

            int model_type; // 设置模型的类型：用前面定义的枚举来写
            Para* object; // 当model_type不为TOPO时，这里可以赋值
    };

} // namespace solar
