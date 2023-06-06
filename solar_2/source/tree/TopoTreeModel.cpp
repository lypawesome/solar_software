
#include "tree/TopoTreeModel.h"
#include <utils/ParaUtils.h>
#include "scene/Heliostat.h"
#include "scene/Receiver.h"


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
        
        root_node =
            QSharedPointer<TopoTreeNode>(new TopoTreeNode(list, nullptr)); // 这个节点在视图中不显示

        

        // 建立一个可见的树状视图的根节点
        QList<QVariant> first_list;
        first_list.append("scene");
        first_list.append("0");
        auto first_node = QSharedPointer<TopoTreeNode>(new TopoTreeNode(first_list, root_node));
        
        // root_node只有一个孩子
        root_node->appendChild(first_node);

        // first_node是初始时就出现在UI界面上的，需要添加对应的para tree model
        QSharedPointer<ParaTreeModel> para_tree_model;
        createParaTreeModel(0,para_tree_model);
        first_node->setParaTreeModel(para_tree_model);
        para_tree_model->setLabelTxt("scene");
        

    }
    TopoTreeModel::~TopoTreeModel() = default;

    auto TopoTreeModel::getParaTreeModelAboutFirstNode() ->QSharedPointer<ParaTreeModel> 
    {
        //eturn root_node->getParaTreeModel();
        return root_node->child(0)->getParaTreeModel();
    }

    void TopoTreeModel::appendChild(const QModelIndex& index, const QList<QVariant>& data_list,
                                    int count,QSharedPointer<ParaTreeModel> &para_tree_model)
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
        child_node->setParaTreeModel(para_tree_model);
        beginInsertRows(index, click_node->childCount(), click_node->childCount());
        click_node->appendChild(child_node);
        endInsertRows();
    }

    bool TopoTreeModel::appendChild(const QModelIndex& index, int type, int count,QSharedPointer<ParaTreeModel> &para_tree_model)
    {
    
        // !!!!注意 index转化成指向TreeNode的指针时，不可以转化为智能指针，只能转化为普通指针
        // !!!!猜测原因：转化为智能指针时，当函数结束，智能指针会自动释放内存空间，导致index无法再正常访问
        // 这里，如果使用智能指针，则无法直接使用appendChild(index,list,count)函数——原因未知
        //auto click_node = QSharedPointer<TopoTreeNode>(static_cast<TopoTreeNode*>(index.internalPointer()));
        auto* click_node = static_cast<TopoTreeNode*>(index.internalPointer());
        // 限制添加
        // 只能在node节点下添加孩子,如果不是node节点，则不添加
        int click_node_type = click_node->data(1).toInt();
        //qDebug()<<"click_node_type:"<<click_node_type;
        if( click_node_type != 0){          // ！！！！运行到这句代码后会出现段错误，自动闪退
            qDebug()<<"WARNING::parent_node is not 0 type";
            return false;
        }

        // 获取与兄弟节点均不相同的name
        QString name = getUniqueName(click_node,type);
        QList<QVariant> list;
        list.append(name);
        list.append(type);
        qDebug()<<"===3  "<< name <<", "<<type;

        createParaTreeModel(type, para_tree_model);    //生成para_tree_model
        qDebug()<<"===4";
        para_tree_model->setLabelTxt(name);

        appendChild(index,list,count,para_tree_model); 

        return true;

        //添加孩子对应的形参：para_tree_model
        

        // if (click_node->childCount() && count == 0) {	//count为0的话刷新，刷新时先删除所有子节点
        //     beginRemoveRows(index, 0, click_node->childCount() - 1);
        //     click_node->deleteAllChild();
        //     endRemoveRows();
        // }

        // //这里使用智能指针
        // auto child_node = QSharedPointer<TopoTreeNode>(new TopoTreeNode(list, click_node));
        // beginInsertRows(index, click_node->childCount(), click_node->childCount());
        // click_node->appendChild(child_node);
        // endInsertRows();
 
    }

    // 返回不与parent_node下的子节点重名的name
    QString TopoTreeModel::getUniqueName(TopoTreeNode* parent_node,int type)
    {
        QString name;
        switch(type)
        {
        case 0: name = "node";      break;
        case 1: name = "heliostat";     break;
        case 2: name = "receiver";   break;
        case 3: name = "ordinary";     break;
        }

        int sibling_cnt = parent_node->childCount();
        if( !sibling_cnt ) 
            return name ;

        int name_appendix = 0;
        QString temp_name = name;    
        bool is_unique = false;

        do{
            int i;
            for( i=0; i<sibling_cnt ; ++i)
            {
                auto sibling_node = parent_node->child(i);
                QString sibling_name = sibling_node->data(0).toString();
                if(temp_name == sibling_name)
                {
                    break;
                }
            }
            if(i < sibling_cnt){
                temp_name = name + "_" + QString::number(name_appendix);
                name_appendix ++ ;
            }
            else{
                is_unique = true;
            }
        }while( ! is_unique );

        return temp_name;
    }

    // 用形参返回建立的para_tree_model
    void TopoTreeModel::createParaTreeModel(int type, QSharedPointer<ParaTreeModel> &para_tree_model)
    {
        TreeModelType model_type ;
        QSharedPointer<Para> para;
        switch(type)
        {
            case 0:     
                model_type = NODE; 
                para = QSharedPointer<Node>(new Node);
                break;
            case 1:     
                // qDebug() <<"****1";
                model_type = HELIOSTAT; 
                para = QSharedPointer<Heliostat>(new Heliostat);
                para->setPara(toMemberName("id"),Heliostat::heliostat_cnt_);
                ++ Heliostat::heliostat_cnt_ ;
                // qDebug() <<"****2";
                break;
            case 2:     
                model_type = RECEIVER;  
                para = QSharedPointer<Receiver>(new Receiver);
                para->setPara(toMemberName("id"), Receiver::receiver_cnt_);
                ++ Receiver::receiver_cnt_ ;
                break;
            case 3:     
                model_type = ORDINARY;  
                para = QSharedPointer<Ordinary>(new Ordinary);
                break;
        }
        qDebug() <<"****3";
        para_tree_model = QSharedPointer<ParaTreeModel>(new ParaTreeModel(model_type,para));
        qDebug() <<"****4";
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
