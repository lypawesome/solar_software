#include "TreeModel.h"

namespace solar
{
    TreeModel::TreeModel(int _model_type, QObject* parent)
        : model_type(_model_type), QAbstractItemModel(parent)
    {
        /*
        QList<QVariant> list;
        list.append("RootNode");
        list.append("0");
        root_node = new TreeNode(list, NULL);       //这个节点在视图中不显示
    */
        root_node = createNode("RootNode", 0, nullptr);

        if (model_type == TOPO)
        {
            /*
            QList<QVariant> nodelist;
            nodelist.append("first_node");
            nodelist.append("0");
            auto firstnode = new TreeNode(nodelist,root_node);
            root_node->appendChild(firstnode);
            */
            TreeNode* firstchild = createNode("rootnode", 0, root_node);
        }

        /*
            switch(model_type)
            {
            case TOPO:      break;
            case LOCATION:  break;
            case SUN:       break;
            case AIR:       break;
            case TERRAIN:   break;
            case CAMERA:    break;
            case CLOUD:     break;
            }
            */
    }
    TreeModel::~TreeModel()
    {
        root_node->deletaAllChild();
        delete root_node;
    }

    TreeNode* TreeModel::createNode(QVariant data1, QVariant data2,
                                    TreeNode* parent, bool editable,
                                    bool optional, bool isOptionChild,
                                    QString option)
    {
        QList<QVariant> list;
        list.append(data1);
        list.append(data2);
        TreeNode* childNode = new TreeNode(list, parent);
        if (editable)
            childNode->setEditable();
        if (optional)
            childNode->setOptional();
        if (parent && !isOptionChild)
            parent->appendChild(childNode);
        if (parent && isOptionChild)
            parent->addOptionChild(option, childNode);
        return childNode;
    }

    TreeNode* TreeModel::getRootNode() const { return root_node; }

    int TreeModel::columnCount(const QModelIndex& parent) const
    {
        return 2;

        if (parent.isValid())
        {
            return static_cast<TreeNode*>(parent.internalPointer())
                ->columnCount();
        }
        else
        {
            return root_node->columnCount();
        }
    }
    int TreeModel::rowCount(const QModelIndex& parent) const
    {
        TreeNode* parentNode;
        if (parent.column() > 0)
        {
            return 0;
        }

        if (!parent.isValid())
        {
            parentNode = root_node;
        }
        else
        {
            parentNode = static_cast<TreeNode*>(parent.internalPointer());
        }

        return parentNode->childCount();
    }
    QHash<int, QByteArray> TreeModel::roleNames() const
    {
        QHash<int, QByteArray> names(QAbstractItemModel::roleNames());
        names[NAME] = "name";
        names[PARA] = "para";
        return names;
    }
    QVariant TreeModel::data(const QModelIndex& index, int role) const
    {
        if (!index.isValid())
        {
            return QVariant();
        }

        switch (role)
        {
        case NAME:
        {
            return static_cast<TreeNode*>(index.internalPointer())->data(0);
        }
        case PARA:
        {
            return static_cast<TreeNode*>(index.internalPointer())->data(1);
        }
        }
        return QVariant();
    }
    Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
    {
        if (!index.isValid())
        {
            return Qt::NoItemFlags;
        }

        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    QModelIndex TreeModel::index(int row, int column,
                                 const QModelIndex& parent) const
    {
        if (!hasIndex(row, column, parent))
        {
            return QModelIndex();
        }

        TreeNode* parentNode;
        if (!parent.isValid())
        {
            parentNode = root_node;
        }
        else
        {
            parentNode = static_cast<TreeNode*>(parent.internalPointer());
        }

        TreeNode* childNode = parentNode->child(row);
        if (childNode)
        {
            return createIndex(row, column, childNode);
        }
        else
        {
            return QModelIndex();
        }
    }
    QModelIndex TreeModel::parent(const QModelIndex& index) const
    {
        if (!index.isValid())
        {
            return QModelIndex();
        }

        TreeNode* childNode = static_cast<TreeNode*>(index.internalPointer());
        TreeNode* parentNode = childNode->parent();

        if (parentNode == root_node)
        {
            return QModelIndex();
        }

        return createIndex(parentNode->row(), 0, parentNode);
    }

    void TreeModel::appendChild(const QModelIndex& index,
                                QList<QVariant> dataList, int count)
    {
        TreeNode* clickNode = static_cast<TreeNode*>(index.internalPointer());

        if (clickNode->childCount() && count == 0)
        { // 刷新时先删除所有子节点

            beginRemoveRows(index, 0, clickNode->childCount() - 1);
            clickNode->deletaAllChild();
            endRemoveRows();
        }

        TreeNode* pNode = new TreeNode(dataList, clickNode);
        beginInsertRows(index, clickNode->childCount(),
                        clickNode->childCount());
        clickNode->appendChild(pNode);
        endInsertRows();
    }
    void TreeModel::appendChild(const QModelIndex& index,
                                QList<TreeNode*> childNodes, int count)
    {
        TreeNode* clickNode = static_cast<TreeNode*>(index.internalPointer());
        if (clickNode->childCount() && count == 0)
        { // 刷新时先删除所有子节点

            beginRemoveRows(index, 0, clickNode->childCount() - 1);
            clickNode->deletaAllChild();
            endRemoveRows();
        }

        for (int i = 0; i < childNodes.size(); i++)
        {
            beginInsertRows(index, clickNode->childCount(),
                            clickNode->childCount());
            clickNode->appendChild(childNodes[i]);
            endInsertRows();
        }
    }
    bool TreeModel::isNodeEditable(const QModelIndex& index)
    {
        if (!index.isValid())
            return false;
        TreeNode* currentNode = static_cast<TreeNode*>(index.internalPointer());
        return currentNode->getEditable();
    }
    bool TreeModel::isNodeOptional(const QModelIndex& index)
    {
        if (!index.isValid())
            return false;
        TreeNode* currentNode = static_cast<TreeNode*>(index.internalPointer());
        return currentNode->getOptional();
    }
    // ！！！！！！！！！！！！！！！这里函数需要修改
    void TreeModel::setNodeColumn(QModelIndex index, int column, QVariant value)
    {
        if (!index.isValid())
            return;
        TreeNode* pTreeNode = static_cast<TreeNode*>(index.internalPointer());
        pTreeNode->setData(value, column);

        emit dataChanged(index, index);

        // 由于name不可编辑，所以只能更新参数，而参数一般都是textedit、comboBox，因此不需要提醒qml树已更新
        // QString name = pTreeNode->data(0).toString();  //得到这一节点的name
        //!!!!!!!!!!!!!!!!!!!!!!!!!!遗留问题!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // 在node更新后，需要把更新后的数据存到Para指定的对象中，这一部分比较复杂,因为对象可能是不同类型的，且这一节点的name不一样
    }
    QString
    TreeModel::getNodeColumn(const QModelIndex& index,
                             int column) // 获取index这一节点第column列的数据
    {
        if (!index.isValid())
            return "";

        TreeNode* currentNode = static_cast<TreeNode*>(index.internalPointer());
        QVariant retdata = currentNode->data(column);

        return retdata.toString();
    }

    QList<QString> TreeModel::getNodeOptionList(const QModelIndex& index)
    {
        if (!index.isValid())
            return QList<QString>();

        TreeNode* currentNode = static_cast<TreeNode*>(index.internalPointer());
        return currentNode->getOptions();
    }

    // ！！！！！！！！！！！！这个函数需要修改
    void TreeModel::makeChoice(const QModelIndex& index, QString option)
    {
        qDebug() << "makechoice: " << option;
        if (!index.isValid())
        {
            qDebug() << "invalid QModelIndex";
            return;
        }
        TreeNode* currentNode = static_cast<TreeNode*>(index.internalPointer());
        if (!currentNode->getOptional())
        {
            qDebug() << "iThis node is unoptional";
            return;
        }
        // currentNode->makeChoice(option);
        // ParaTreeNode* lastchild =
        // currentNode->child(currentNode->childCount()-1);
        // emit dataChanged(index,);
        // currentNode->setData(option,1);
        // emit dataChanged(index,index);
        // QList<TreeNode*> childs = currentNode->getOptionChilds(option);
        // appendChild(index,childs,0);
    }

    /*
     * ====================================================================
     */
    QString TreeModel::getIconName(const QModelIndex& index)
    {
        if (!index.isValid())
            return "";
        if (model_type)
            return "";

        TreeNode* currentNode = static_cast<TreeNode*>(index.internalPointer());

        QVariant type = currentNode->data(1);

        int typeStr = type.toInt();

        QString imageName = "";
        switch (typeStr)
        {
        case 0:
            imageName = "node.png";
            break;
        case 1:
            imageName = "shape.png";
            break;
        case 2:
            imageName = "tracker.png";
            break;
        case 3:
            imageName = "array.png";
            break;
        }

        return imageName;
    }

    /*
    ========================建立模型部分======================================
    有bug，需要注意
    */
    void TreeModel::buildSunTreeModel(Sun* sun) // 建立一个sun的参数设置treeview
    {
        // data_ptr = sun;
        object = sun;

        /*
        建立模型部分注意坑点：：：建立孩子节点时就已经指明了父节点，不要忘记给父节点添加孩子节点
        */

        // position
        TreeNode* positionNode = createNode("position", "", root_node);
        createNode("azimuth", sun->getPara("azimuth"), positionNode, true,
                   false);
        createNode("elevation", sun->getPara("elevation"), positionNode, true,
                   false);
        createNode("irradiance", sun->getPara("irradiance"), positionNode, true,
                   false);
        TreeNode* trackable =
            createNode("trackable", sun->getPara("trackable"), positionNode,
                       false, true); // 这里应该改为可选的
        trackable->insertOption("true");
        trackable->insertOption("false");

        // shape
        TreeNode* shapeNode =
            createNode("shape", "Pillbox", root_node, false, true);
        createNode("thetaMax", "1", shapeNode, true, false, true,
                   "Pillbox"); // 这里如何设置list的第二个
        createNode("csr", "2", shapeNode, true, false, true, "Buie");
        createNode("sigma", "3", shapeNode, true, false, true, "Gaussion");
        shapeNode->makeChoice("Buie");
    }
} // namespace solar
