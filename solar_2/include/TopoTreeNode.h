
#ifndef TOPOTREENODE_H
#define TOPOTREENODE_H

/*

界面右上方拓扑模型的部分，树状视图的节点
*/


#include <QObject>
#include <QList>
#include <QVariant>
#include <QStringList>
#include <QModelIndex>

namespace solar{

class TopoTreeNode : public QEnableSharedFromThis<TopoTreeNode>
    {
    public:
        TopoTreeNode(const QList<QVariant> &data, QSharedPointer<TopoTreeNode> parent);

        ~TopoTreeNode();

        void appendChild(QSharedPointer<TopoTreeNode> child);      //给该节点添加一个孩子
        void deleteAllChild();                  //删去该节点的所有孩子

        QSharedPointer<TopoTreeNode> child(int row);           //该节点的第row个孩子
        int childCount() const;             //孩子个数
        int columnCount() const;            //该节点记录多少个属性
        QVariant data(int column) const;    //该节点的第column个属性
        int row() const;                    //是父节点的第几个孩子
        QSharedPointer<TopoTreeNode> parent();                 //返回父节点的指针

        void setParent(QSharedPointer<TopoTreeNode> parent);   //设置父节点
        void setNodeData(QVariant data, int column);    //设置该节点的第column个属性

    private:
        QSharedPointer<TopoTreeNode> parent_node;              //父节点的指针
        QList<QSharedPointer<TopoTreeNode>> child_nodes;       //所有孩子节点的指针
        QList<QVariant> node_datas;          //该节点的所有数据/属性

        //可能要保存一个对应的para树状视图控制器
        //QSharedPointer<ParaTreeViewController> para_tree_control;
};

}

#endif // TOPOTREENODE_H
