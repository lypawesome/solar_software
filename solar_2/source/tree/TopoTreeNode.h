
#ifndef TOPOTREENODE_H
#define TOPOTREENODE_H

/*

界面右上方拓扑模型的部分，树状视图的节点
*/

#include <QList>
#include <QModelIndex>
#include <QObject>
#include <QStringList>
#include <QVariant>

#include "tree/ParaTreeModel.h"
#include "tree/ParaTreeViewController.h"

namespace solar
{

    class TopoTreeNode : public QEnableSharedFromThis<TopoTreeNode>
    {
        public:
            TopoTreeNode(const QList<QVariant>& data, const QSharedPointer<TopoTreeNode>& parent);

            ~TopoTreeNode();
            // 给该节点添加一个孩子
            void appendChild(const QSharedPointer<TopoTreeNode>& child);
            // 删去该节点的所有孩子
            void deleteAllChild();
            // 该节点的第row个孩子
            auto child(int row) -> QSharedPointer<TopoTreeNode>;
            // 孩子个数
            auto childCount() const -> qsizetype;
            // 该节点记录多少个属性
            auto columnCount() const -> qsizetype;
            // 该节点的第column个属性
            auto data(qsizetype column) const -> QVariant;
            // 是父节点的第几个孩子
            auto row() const -> qsizetype;
            // 返回父节点的指针
            auto parent() -> QSharedPointer<TopoTreeNode>;

            // 设置父节点
            void setParent(const QSharedPointer<TopoTreeNode>& in_parent_node);
            // 设置该节点的第column个属性
            void setNodeData(QVariant data, qsizetype column);

            // 该topo节点对应的ParaTreeModel在paracontroller中QList的下标
            auto getParaTreeId(const QSharedPointer<ParaTreeViewController>& para_tree_control) -> qsizetype;
            // 返回NODE、SHAPE、TRACKER、ARRAY
            auto getParaModelType() const -> int;
            // 返回所有子孙后代的个数--递归
            auto getOffspringCount() const -> qsizetype;

        private:
            QSharedPointer<TopoTreeNode> parent_node;        // 父节点的指针
            QList<QSharedPointer<TopoTreeNode>> child_nodes; // 所有孩子节点的指针
            QList<QVariant> node_datas;                      // 该节点的所有数据/属性

            QSharedPointer<ParaTreeModel> para_tree_model; // 每一个都对应一个树状视图
            // 可能要保存一个对应的para树状视图控制器
            // QSharedPointer<ParaTreeViewController> para_tree_control;
    };

} // namespace solar

#endif // TOPOTREENODE_H
