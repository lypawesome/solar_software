
#include "tree/TopoTreeModel.h"

namespace solar
{

TopoTreeModel::TopoTreeModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    QList<QVariant> list;
    list.append("RootNode");
    list.append("0");
    //注意：这里，如果采用std::shared_ptr会报错
    //这里程序崩溃----已解决，如果TopoTreeNode使用多个构造函数来区分传入的是普通指针还是智能指针，而这里传入的是NULL，那么系统就不知道要使用哪个构造函数
    //解决方法：TopoTreeNode只使用一个构造函数
    root_node = QSharedPointer<TopoTreeNode>(new TopoTreeNode (list, NULL));       //这个节点在视图中不显示

    //建立一个可见的树状视图的根节点
    QList<QVariant> first_list;
    first_list.append("root_node");
    first_list.append("0");
    auto first_node = QSharedPointer<TopoTreeNode>(new TopoTreeNode(first_list,root_node));
    root_node->appendChild(first_node);
}
TopoTreeModel::~TopoTreeModel()
{
}

void TopoTreeModel::appendChild(const QModelIndex& index, QList<QVariant> dataList, int count)
{
    //这里的智能指针，会被child_node的parent指向，所以不会自动delete
    auto click_node = QSharedPointer<TopoTreeNode>(static_cast<TopoTreeNode*>(index.internalPointer()));

    if (click_node->childCount() && count == 0) {	//刷新时先删除所有子节点
        beginRemoveRows(index, 0, click_node->childCount() - 1);
        click_node->deleteAllChild();
        endRemoveRows();
    }

    //这里使用智能指针
    auto child_node = QSharedPointer<TopoTreeNode>(new TopoTreeNode(dataList, click_node));
    beginInsertRows(index, click_node->childCount(), click_node->childCount());
    click_node->appendChild(child_node);
    endInsertRows();
}

void TopoTreeModel::setNodeName(QString appendName, QModelIndex index)
{
    //这里用普通指针，不能用智能指针
    TopoTreeNode *pTreeNode = static_cast<TopoTreeNode*>(index.internalPointer());
    pTreeNode->setNodeData(appendName, 0);

    emit dataChanged(index, index);	//更新树节点数据
}

int TopoTreeModel::columnCount(const QModelIndex &parent ) const
{
    return 2;
}
int TopoTreeModel::rowCount(const QModelIndex &parent ) const
{
    int ret=0;
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
        //这里使用普通指针
        auto parentNode = static_cast<TopoTreeNode*>(parent.internalPointer());
        ret = parentNode->childCount();
    }

    return ret;
}
QHash<int, QByteArray> TopoTreeModel::roleNames() const
{
    QHash<int, QByteArray> names(QAbstractItemModel::roleNames());
    names[NAME] = "name";
    names[TYPE] = "type";

    return names;
}
QVariant TopoTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
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
    return QVariant();
}
Qt::ItemFlags TopoTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsEditable;      //不可选，但是可以编辑
}

QModelIndex TopoTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TopoTreeNode *parentNode;
    if (!parent.isValid())
    {
        parentNode = root_node.get();
    }
    else
    {
        parentNode = static_cast<TopoTreeNode*>(parent.internalPointer());
    }

    TopoTreeNode *childNode = (parentNode->child(row)).get();
    if (childNode)
    {
        return createIndex(row, column, childNode);
    }
    else
    {
        return QModelIndex();
    }
    return QModelIndex();
}

QModelIndex TopoTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TopoTreeNode *childNode = static_cast<TopoTreeNode*>(index.internalPointer());
    auto parentNode = childNode->parent();

    if (parentNode == root_node)
    {
        return QModelIndex();
    }
    // !!!!!注意一下，这里的row()是否能返回正确的值
    return createIndex(parentNode->row(), 0, parentNode.get());

}


// !!!!获取图片路径名，这里可以直接写到qml文件中，没必要在treemodel中专门写类
QString TopoTreeModel::getType(const QModelIndex& index)          //获取该项对应的类型的图片名
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

int TopoTreeModel::getTotalNodeCnt()
{
    return root_node->getOffspringCount();
}


}

