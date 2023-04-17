
#ifndef PARATREEMODEL_H
#define PARATREEMODEL_H

/*
    右下角的树状视图
*/

#include <QAbstractItemModel>
#include <QObject>

#include "Para.h"
#include "ParaTreeNode.h"


namespace solar{

    enum TreeModelType
    {
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

    class ParaTreeModel : public QAbstractItemModel
    {
        Q_OBJECT
        enum nodeRoles
        {
            NAME = Qt::UserRole + 1,
            PARA
        };
    public:
        ParaTreeModel(TreeModelType _model_type, QObject* parent = nullptr, QSharedPointer<Para> _para=nullptr);
        ~ParaTreeModel();


        int columnCount(const QModelIndex& parent = QModelIndex()) const;
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        QHash<int, QByteArray> roleNames() const;
        QVariant data(const QModelIndex& index, int role) const;
        Qt::ItemFlags flags(const QModelIndex& index) const;
        QModelIndex index(int row, int column,
                          const QModelIndex& parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex& index) const;


        QSharedPointer<ParaTreeNode> getRootNode() const;

        //右下角的视图，只需要编辑、选择，不需要增加/删除节点
//        void appendChild(const QModelIndex& index, QList<QVariant> dataList,
//                         int count);
//        void appendChild(const QModelIndex& index,
//                         QList<QSharedPointer<ParaTreeNode>> childNodes,
//                         int count); // 添加一系列孩子
        void setNodePara( QModelIndex index, QVariant value);   // 设置index这一节点的属性数据为value
        QString getNodePara(const QModelIndex& index );         // 获取index这一节点的para数据,注意这里一直返回string

        bool isNodeEditable(const QModelIndex& index);
        bool isNodeOptional(const QModelIndex& index);
        QList<QString> getNodeOptionList( const QModelIndex& index);    // 获得这一节点的所有option
        void makeChoice(const QModelIndex& index, QString option);      // 做出选择

        //建立参数----这部分也可能会更改
    private:

        //建立节点，若parent_state为OPTIONAL，则新创立的节点放到parent节点的option_childnodes[parent_option]列表内，
        //若同时is_current_option_child为true，则把心窗里的节点放在option_childnodes下的同时，也放到child_nodes下
        //注意：parent_state是通过parent->getState()获得的
        QSharedPointer<ParaTreeNode> createNode(
                                            QSharedPointer<ParaTreeNode> parent,
                                            QVariant data1, QVariant data2,
                                            ParaState state=QUIET,
                                            bool is_current_option_child = false,
                                            QString parent_option = "");
        void buildSunTreeModel(QSharedPointer<Sun> sun);
        void buildLocationTreeModel(QSharedPointer<Location> location);

        void updatePara();      //更新para中的某个属性
        void updataSunPara();   //当model_type为SUN时，更新属性
    private:
        QSharedPointer<ParaTreeNode> root_node;   //树状视图中的根节点

        TreeModelType model_type;
        QSharedPointer<Para> para;
    };

}



#endif // PARATREEMODEL_H
