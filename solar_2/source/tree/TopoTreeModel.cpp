
#include "tree/TopoTreeModel.h"

namespace solar
{

    TopoTreeModel::TopoTreeModel(QObject* parent) : QAbstractItemModel(parent)
    {
        this->role_names_ = QHash<int, QByteArray>(QAbstractItemModel::roleNames());
        this->role_names_[NAME] = "name";
        this->role_names_[TYPE] = "type";

        QList<QVariant> list;
        list.append("RootNode");
        list.append("0");
        // 注意：这里，如果采用std::shared_ptr会报错
        // 这里程序崩溃----已解决，如果TopoTreeNode使用多个构造函数来区分传入的是普通指针还是智能指针，而这里传入的是NULL，那么系统就不知道要使用哪个构造函数
        // 解决方法：TopoTreeNode只使用一个构造函数
        root_node =
            QSharedPointer<TopoTreeNode>(new TopoTreeNode(list, nullptr)); // 这个节点在视图中不显示

        // 建立一个可见的树状视图的根节点
        QList<QVariant> first_list;
        first_list.append("root_node");
        first_list.append("0");
        auto first_node = QSharedPointer<TopoTreeNode>(new TopoTreeNode(first_list, root_node));
        root_node->appendChild(first_node);
    }
    TopoTreeModel::~TopoTreeModel() = default;

    void TopoTreeModel::appendChild(const QModelIndex& index, const QList<QVariant>& data_list,
                                    int count)
    {
        // 这里的智能指针，会被child_node的parent指向，所以不会自动delete
        auto click_node =
            QSharedPointer<TopoTreeNode>(static_cast<TopoTreeNode*>(index.internalPointer()));

        if ((click_node->childCount() != 0) && count == 0)
        { // 刷新时先删除所有子节点
            beginRemoveRows(index, 0, click_node->childCount() - 1);
            click_node->deleteAllChild();
            endRemoveRows();
        }

        // 这里使用智能指针
        auto child_node = QSharedPointer<TopoTreeNode>(new TopoTreeNode(data_list, click_node));
        beginInsertRows(index, click_node->childCount(), click_node->childCount());
        click_node->appendChild(child_node);
        endInsertRows();
    }

    void TopoTreeModel::setNodeName(const QString& append_name, QModelIndex index)
    {
        // 这里用普通指针，不能用智能指针
        auto* p_tree_node = static_cast<TopoTreeNode*>(index.internalPointer());
        p_tree_node->setNodeData(append_name, 0);

        emit dataChanged(index, index); // 更新树节点数据
    }

    auto TopoTreeModel::columnCount(const QModelIndex& parent) const -> int { return 2; }
    auto TopoTreeModel::rowCount(const QModelIndex& parent) const -> int
    {
        int ret = 0;
        if (parent.column() > 0)
        {
            return 0;
        }

        if (!parent.isValid())
        {
            ret = root_node->childCount();
        }
        else
        {
            // 这里使用普通指针
            auto* parent_node = static_cast<TopoTreeNode*>(parent.internalPointer());
            ret = parent_node->childCount();
        }

        return ret;
    }
    auto TopoTreeModel::roleNames() const -> QHash<int, QByteArray> { return this->role_names_; }
    auto TopoTreeModel::data(const QModelIndex& index, int role) const -> QVariant
    {
        if (!index.isValid())
        {
            return {};
        }

        switch (role)
        {
        case NAME:
        {
            return static_cast<TopoTreeNode*>(index.internalPointer())->data(0);
        }
        case TYPE:
        {
            return static_cast<TopoTreeNode*>(index.internalPointer())->data(1);
        }
        }
        return {};
    }
    auto TopoTreeModel::flags(const QModelIndex& index) const -> Qt::ItemFlags
    {
        if (!index.isValid())
        {
            return Qt::NoItemFlags;
        }

        return Qt::ItemIsEnabled | Qt::ItemIsEditable; // 不可选，但是可以编辑
    }

    auto TopoTreeModel::index(int row, int column, const QModelIndex& parent) const -> QModelIndex
    {
        if (!hasIndex(row, column, parent))
        {
            return {};
        }

        TopoTreeNode* parent_node = nullptr;
        if (!parent.isValid())
        {
            parent_node = root_node.get();
        }
        else
        {
            parent_node = static_cast<TopoTreeNode*>(parent.internalPointer());
        }

        TopoTreeNode* child_node = (parent_node->child(row)).get();
        if (child_node != nullptr)
        {
            return createIndex(row, column, child_node);
        }
        return {};
    }

    auto TopoTreeModel::parent(const QModelIndex& index) const -> QModelIndex
    {
        if (!index.isValid())
        {
            return {};
        }

        auto* child_node = static_cast<TopoTreeNode*>(index.internalPointer());
        auto parent_node = child_node->parent();

        if (parent_node == root_node)
        {
            return {};
        }
        // !!!!!注意一下，这里的row()是否能返回正确的值
        return createIndex(parent_node->row(), 0, parent_node.get());
    }

    // !!!!获取图片路径名，这里可以直接写到qml文件中，没必要在treemodel中专门写类
    auto TopoTreeModel::getType(const QModelIndex& index) const
        -> QString // 获取该项对应的类型的图片名
    {
        //    if( !index.isValid() ) return "";

        //    TreeNode *currentNode = static_cast<TreeNode*>(index.internalPointer());
        //    QVariant type = currentNode->data(1);

        //    int typeStr = type.toInt();

        //    QString imageName="";
        //    switch(typeStr)
        //    {
        //    case 0: imageName = "node.png"; break;
        //    case 1: imageName = "shape.png"; break;
        //    case 2: imageName = "tracker.png"; break;
        //    case 3: imageName = "array.png"; break;
        //    }

        //    return imageName;
        return "";
    }

    auto TopoTreeModel::getTotalNodeCnt() const -> qsizetype
    {
        return root_node->getOffspringCount();
    }

} // namespace solar
