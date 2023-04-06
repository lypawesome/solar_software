#include "TreeNode.h"

namespace solar
{
    TreeNode::TreeNode(const QList<QVariant>& data,
                       TreeNode* parent) // 数据，父节点
    {
        parent_node = parent;
        node_data = data;

        para_tree_view_controller = nullptr;
    }
    TreeNode::~TreeNode()
    {
        delete para_tree_view_controller;
        // 没有在类中new，就不需要delete
    }

    void TreeNode::appendChild(TreeNode* child)
    {
        child->setParent(this);
        child_nodes.append(child);
    }

    void TreeNode::deletaAllChild()
    {
        for (int index = 0; index < child_nodes.size(); index++)
        {
            child_nodes.value(index)->deletaAllChild();
        }
        qDeleteAll(child_nodes);
        child_nodes.clear();
    }

    TreeNode* TreeNode::child(int row)
    {
        if (row < 0 || row >= child_nodes.size())
            return nullptr;
        return child_nodes.value(row);
    }
    int TreeNode::childCount() const // 孩子个数
    {
        return child_nodes.size();
    }
    int TreeNode::columnCount() const // 该节点记录多少个属性
    {
        return node_data.size();
    }
    QVariant TreeNode::data(int column) const // 该节点的第column个属性
    {
        if (column < 0 || column >= node_data.size())
            return QVariant();
        return node_data.value(column);
    }
    int TreeNode::row() const // 是父节点的第几个孩子
    {
        return parent_node == nullptr ? 0
                                      : parent_node->child_nodes.indexOf(
                                            const_cast<TreeNode*>(this));
    }
    TreeNode* TreeNode::parent() // 返回父节点的指针
    {
        return parent_node;
    }
    void TreeNode::setParent(TreeNode* parent) // 设置父节点,修改父节点的孩子列表
    {
        parent_node = parent;
    }
    bool TreeNode::setData(const QVariant& data,
                           int column) // 设置该节点的第column个属性
    {
        if (column < 0 || column >= node_data.size())
            return false;
        node_data[column] = data;
        return true;
    }
    void TreeNode::setEditable() { editable = true; }
    void TreeNode::setOptional() { optional = true; }
    bool TreeNode::getEditable() { return editable; }
    bool TreeNode::getOptional() { return optional; }
    QList<QString> TreeNode::getOptions() { return options; }
    void TreeNode::insertOption(QString option) { options.append(option); }
    QList<TreeNode*> TreeNode::getOptionChilds(QString option)
    {
        return option_child_nodes.value(option);
    }

    void TreeNode::makeChoice(
        const QString&
            option) // 做出选择，把mNodeData[1]的数据改了，同时把mChildNodes给改了
    {
        if (!optional)
            return;
        if (option == data(1))
            return;

        // deletaAllChild();
        setData(option, 1);
        child_nodes = option_child_nodes.value(option);
    }
    void TreeNode::resetOptionChilds(const QString& option,
                                     QList<TreeNode*> childs)
    {
        if (option_child_nodes.contains(
                option)) // 如果已经记录了这一选项，就删掉
        {
            option_child_nodes.remove(option);
        }
        option_child_nodes.insert(option, childs);
        for (
            auto& item :
            childs) // 孩子的父节点可以现在就设置，但是父亲中的孩子列表，要在选中这一选项后再设置
            item->setParent(this);
    }
    void TreeNode::addOptionChild(QString option, TreeNode* child)
    {
        option_child_nodes[option].append(child);
        child->setParent(this);
    }
} // namespace solar
