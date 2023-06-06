
#ifndef TOPOTREEVIEWCONTROLLER_H
#define TOPOTREEVIEWCONTROLLER_H

/*
用于右上角，Topo模型部分的树状视图的控制器
！！！注意这里的成员函数还需要改
*/

#include "TopoTreeModel.h"
#include <QObject>

namespace solar
{

    class TopoTreeViewController : public QObject
    {
            Q_OBJECT

        public:
            TopoTreeViewController(QObject* parent = nullptr);
            ~TopoTreeViewController();

        public slots: // 被qml调用
            Q_INVOKABLE auto getTreeModel() -> QAbstractItemModel*;
            // 更新节点名字
            Q_INVOKABLE void updateNodeName(const QModelIndex& index, const QVariant& new_name);
            // !!!!!!!!!!!更新节点，可能要删去
            Q_INVOKABLE void updateNode(const QModelIndex& index);
            // 找到该项对应的类型,返回该类型对应的图片名
            Q_INVOKABLE auto getImageName(const QModelIndex& index) -> QString;
            // 在index下添加孩子节点，孩子节点的类型是type
            Q_INVOKABLE void appendChild(const QModelIndex& index, int type);
            // 返回总共的节点数
            Q_INVOKABLE auto getTotalNodeCnt() -> qsizetype;
        
        public:
            // 保存指向paratreeviewcontroller的指针，同时加上root_node的para_tree_model
            // !!!!注意，要加的不是root_node的para_tree_model，root_node在ui中不可见，要加的是first_node的para_tree
            void setParaTreeController(const QSharedPointer<ParaTreeViewController> para_tree_control);
            // auto getParaTreeModelAboutRootNode() -> QSharedPointer<ParaTreeModel>;

        private:
            QSharedPointer<TopoTreeModel> tree_model; 

            // 存一个指向右下方树状视图的指针，当增删topo节点时，也增加para中对应的model
            QSharedPointer<ParaTreeViewController> para_tree_control;   
    };

} // namespace solar

#endif // TOPOTREEVIEWCONTROLLER_H
