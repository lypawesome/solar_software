
#include "tree/TopoTreeNode.h"
#include <qtypes.h>

namespace solar
{

    TopoTreeNode::TopoTreeNode(const QList<QVariant>& data,
                               const QSharedPointer<TopoTreeNode>& parent)
        : parent_node(parent), node_datas(data)
    {

        // 处理对应的ParaTreeModel
        //    QSharedDataPointer<Para> para;
        //    int para_model_type = getParaModelType();
        //    switch (para_model_type) {
        //    case NODE:
        //        //para = QSharedPointer<Node>()
        //        break;
        //    case SHAPE:
        //        break;
        //    case TRACKER:
        //        break;
        //    case ARRAY:
        //        break;
        //    default:
        //        break;
        //    }
        // para_tree_model = QSharedDataPointer<ParaTreeModel>(new
        // ParaTreeModel(getParaModelType(),para));
    }

    TopoTreeNode::~TopoTreeNode() = default;

    // 给该节点添加一个孩子
    void TopoTreeNode::appendChild(const QSharedPointer<TopoTreeNode>& child)
    {
        child->setParent(sharedFromThis());
        child_nodes.append(child);
    }
    // 删去该节点的所有孩子
    void TopoTreeNode::deleteAllChild()
    {
        for (int index = 0; index < child_nodes.size(); index++)
        {
            child_nodes.value(index)->deleteAllChild();
            child_nodes.value(index).clear();
        }
        child_nodes.clear();
    }
    // 该节点的第row个孩子
    auto TopoTreeNode::child(int row) -> QSharedPointer<TopoTreeNode>
    {
        if (row < 0 || row >= child_nodes.size()) // 如果row不合法，报错
        {
            throw "invalid row in Func: TopoTreeNode::child(row)";
        }
        return child_nodes.value(row);
    }
    // 孩子个数
    auto TopoTreeNode::childCount() const -> qsizetype { return child_nodes.size(); }
    // 该节点记录多少个属性
    auto TopoTreeNode::columnCount() const -> qsizetype { return node_datas.size(); }
    // 该节点的第column个属性
    auto TopoTreeNode::data(qsizetype column) const -> QVariant
    {
        if (column < 0 || column >= node_datas.size())
        {
            throw "invalid column in Func: TopoTreeNode::data(column)";
        }
        return node_datas.value(column);
    }
    auto TopoTreeNode::row() const -> qsizetype // 是父节点的第几个孩子
    {
        if (parent_node == nullptr) // 父节点为空，表示无父节点
        {
            return 0;
        }
        auto temp = sharedFromThis();
        if (temp == nullptr)
        {
            throw "can't find this pointer in Func:TopoTreeNode::row() ";
        }
        return parent_node->child_nodes.indexOf(temp); // ！！！注意这里是否有bug
    }
    auto TopoTreeNode::parent() -> QSharedPointer<TopoTreeNode> // 返回父节点的指针
    {
        return parent_node;
    }
    void TopoTreeNode::setParent(const QSharedPointer<TopoTreeNode>& in_parent_node) // 设置父节点
    {
        this->parent_node = in_parent_node;
    }
    void TopoTreeNode::setNodeData(QVariant data, qsizetype column) // 设置该节点的第column个属性
    {
        if (column < 0 || column >= node_datas.size())
        {
            throw "invalid column in Func: TopoTreeNode::setNodeData(data,column)";
        }
        node_datas[column] = data;
    }

    auto TopoTreeNode::getParaTreeId(const QSharedPointer<ParaTreeViewController>& para_tree_control) -> qsizetype
    {
        return para_tree_control->getParaTreeModelId(para_tree_model);
    }
    auto TopoTreeNode::getParaModelType() const -> int // 返回的是TreeModelType的枚举
    {
        QVariant type = data(1);
        return type.toInt() - 0 + NODE;
    }
    // 所有子孙后代的个数，不包括自身
    auto TopoTreeNode::getOffspringCount() const -> qsizetype
    {
        auto cnt = childCount();
        for (auto&& child : std::as_const(child_nodes))
        {
            cnt += child->getOffspringCount();
        }
        return cnt;
    }

} // namespace solar
