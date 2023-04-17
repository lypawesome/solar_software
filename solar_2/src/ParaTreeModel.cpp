
#include "ParaTreeModel.h"

namespace solar{

    ParaTreeModel::ParaTreeModel(TreeModelType _model_type, QObject* parent, QSharedPointer<Para> _para)
            :QAbstractItemModel(parent)
    {
        para = _para;
        model_type = _model_type;
        root_node = createNode(nullptr, "root", "" );     //建立根节点,这个节点在视图中不显示

        switch(model_type)
        {

        case LOCATION:
        {
            buildLocationTreeModel(para.dynamicCast<Location>());
            break;
        }
        case SUN:
        {
            buildSunTreeModel(para.dynamicCast<Sun>());
            break;
        }
        case AIR:
        {
            break;
        }
        case TERRAIN:
        {
            break;
        }
        case CAMERA:
        {
            break;
        }
        case CLOUD:
        {
            break;
        }
        case NODE:
        {
            break;
        }
        case SHAPE:
        {
            break;
        }
        case TRACKER:
        {
            break;
        }
        case ARRAY:
        {
            break;
        }

        }
    }
    ParaTreeModel::~ParaTreeModel()
    {

    }

    /*
    ---------------------------------------------------------------------------
    建立模型相关的函数
*/

    //state是当前节点的state
    QSharedPointer<ParaTreeNode> ParaTreeModel::createNode(
        QSharedPointer<ParaTreeNode> parent,
        QVariant data1, QVariant data2,
        ParaState state,
        bool is_current_option_child,
        QString parent_option )
    {
        QList<QVariant> list;
        list.append(data1);
        list.append(data2);
        QSharedPointer<ParaTreeNode> child_node =
            QSharedPointer<ParaTreeNode>(new ParaTreeNode(list,parent));

        child_node->setState(state);

        if(parent == nullptr)
            return child_node;

        ParaState parent_state = parent->getState();
        if(parent_state == OPTIONAL)
        {
            parent->addOptionChild(parent_option, child_node);
            if(is_current_option_child)
                parent->appendChild(child_node);
        }
        else{
            parent->appendChild(child_node);
        }

        return child_node;

    }

    void ParaTreeModel::buildSunTreeModel(QSharedPointer<Sun> sun)
    {
        //position
        auto position_node = createNode(root_node,"position","",QUIET);

        //position-azimuth
        QVariant azimuth = sun->getPara("azimuth");
        createNode(position_node,"azimuth",azimuth, EDITABLE);

        //position-elevation
        QVariant elevation = sun->getPara("elevation");
        createNode(position_node,"elevation",elevation, EDITABLE);

        //position-irradiance
        QVariant irradiance = sun->getPara("irradiance");
        createNode(position_node,"irradiance",irradiance, EDITABLE);

        //position-trackable
        QVariant trackable = sun->getPara("trackable");
        createNode(position_node,"trackable",trackable, EDITABLE);

        //sunshape
        auto sunshape_node = createNode(root_node,"sunshape","",OPTIONAL);

        //sunshape-csr
        QVariant csr = sun->getPara("csr");
        createNode(sunshape_node,"csr",csr,EDITABLE,true,"Buie");

        //sunshape-theta_max
        QVariant theta_max = sun->getPara("theta_max");
        createNode(sunshape_node,"theta_max",theta_max,EDITABLE,false,"Pillbox");

        //sunshape-gaussian
        QVariant sigma = sun->getPara("sigma");
        createNode(sunshape_node,"sigma",sigma,EDITABLE,false,"Gaussian");


    }
    void ParaTreeModel::buildLocationTreeModel(QSharedPointer<Location> location)
    {
        //site_name
        QVariant site = location->getPara("site_name");
        createNode(root_node,"site_name", site, EDITABLE);

        //longitude
        QVariant longitude = location->getPara("longitude");
        createNode(root_node,"longitude", longitude, EDITABLE);

        //latitude
        QVariant latitude = location->getPara("latitude");
        createNode(root_node,"latitude", latitude, EDITABLE);

    }

    /*
------------------------------------------------------------------------------
*/


int ParaTreeModel::columnCount(const QModelIndex& parent ) const    //返回列数
{
        return 2;
}
int ParaTreeModel::rowCount(const QModelIndex& parent ) const
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
            auto parentNode = static_cast<ParaTreeNode*>(parent.internalPointer());
            ret = parentNode->childCount();
        }

        return ret;
}
QHash<int, QByteArray> ParaTreeModel::roleNames() const
{
        QHash<int, QByteArray> names(QAbstractItemModel::roleNames());
        names[NAME] = "name";
        names[PARA] = "para";
        return names;
}
QVariant ParaTreeModel::data(const QModelIndex& index, int role) const
{
        if (!index.isValid())
        {
            return QVariant();
        }

        switch (role)
        {
        case NAME:
        {
            return static_cast<ParaTreeNode*>(index.internalPointer())->data(0);
        }
        case PARA:
        {
            return static_cast<ParaTreeNode*>(index.internalPointer())->data(1);
        }
        }
        return QVariant();
}
Qt::ItemFlags ParaTreeModel::flags(const QModelIndex& index) const
{
        if (!index.isValid())
        {
            return Qt::NoItemFlags;
        }

        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}
QModelIndex ParaTreeModel::index(int row, int column, const QModelIndex& parent ) const
{
        if (!hasIndex(row, column, parent))
        {
            return QModelIndex();
        }

        ParaTreeNode *parentNode;
        if (!parent.isValid())
        {
            parentNode = root_node.get();
        }
        else
        {
            parentNode = static_cast<ParaTreeNode*>(parent.internalPointer());
        }

        ParaTreeNode *childNode = (parentNode->child(row)).get();
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
QModelIndex ParaTreeModel::parent(const QModelIndex& index) const
{
        if (!index.isValid())
        {
            return QModelIndex();
        }

        ParaTreeNode *childNode = static_cast<ParaTreeNode*>(index.internalPointer());
        auto parentNode = childNode->parent();

        if (parentNode == root_node)
        {
            return QModelIndex();
        }
        // !!!!!注意一下，这里的row()是否能返回正确的值
        return createIndex(parentNode->row(), 0, parentNode.get());
}

// ！！！！！！！！注意：不要忘记更新para中的内容！！！！！
// ！！！！！！！问题：：para中记录的属性如何更新？？？如果是editable，直接setPara即可，如果是optional，如何做？？？
void ParaTreeModel::setNodePara( QModelIndex index, QVariant value)   // 设置index这一节点的属性数据为value
{
    if (!index.isValid())
        return;
    ParaTreeNode* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
    //QString para_name = click_node->data(0).toString();
    if(click_node->getState() == EDITABLE)  //若该节点是可编辑的，只更改这一个节点的para，并发送信号
    {
        click_node->setData(value, 1);
        //para->setPara(para_name.toStdString(),value);   // !!!!这里有问题
        emit dataChanged(index, index);
    }
    // !!!!注意进行makechoice时，要看value是否在选项内
    if(click_node->getState()== OPTIONAL)   //该节点是可选择的，需要做出选择，并发送信号！！！！！发送信号的地方好像有bug
    {
        makeChoice(index, value.toString());    //在该函数中进行选择和发送信号
        //para->setPara(para_name.toStdString(), value);
    }

}
QString ParaTreeModel::getNodePara(const QModelIndex& index )         // 获取index这一节点的para数据
{
    if (!index.isValid())
        return "";
    ParaTreeNode* current_node = static_cast<ParaTreeNode*>(index.internalPointer());
    QVariant para_data = current_node->data(1);
    return para_data.toString();
}

bool ParaTreeModel::isNodeEditable(const QModelIndex& index)
{
    if (!index.isValid())
        return false;
    ParaTreeNode* current_node = static_cast<ParaTreeNode*>(index.internalPointer());
    ParaState para_state = current_node->getState();
    return para_state == EDITABLE;
}
bool ParaTreeModel::isNodeOptional(const QModelIndex& index)
{
    if (!index.isValid())
        return false;
    ParaTreeNode* currentNode = static_cast<ParaTreeNode*>(index.internalPointer());
    ParaState para_state = currentNode->getState();
    return para_state == OPTIONAL;
}

QList<QString> ParaTreeModel::getNodeOptionList( const QModelIndex& index)    // 获得这一节点的所有option
{
    if (!index.isValid())
        return QList<QString>();
    ParaTreeNode* current_node = static_cast<ParaTreeNode*>(index.internalPointer());
    return current_node->getOptions();
}
void ParaTreeModel::makeChoice(const QModelIndex& index, QString option)      // 做出选择
{
    if (!index.isValid())
        return;
    ParaTreeNode* click_node = static_cast<ParaTreeNode*>(index.internalPointer());

    //首先，改变该节点的选项
    click_node->setData(option,1);
    emit dataChanged(index,index);

    // 删除该节点现有的孩子节点
    if(click_node->childCount())
    {
        beginRemoveRows(index, 0, click_node->childCount() - 1);
        click_node->deletaAllChild();
        endRemoveRows();
    }

    //把选项的孩子列表添加到节点的孩子列表中
    auto current_option_childnodes = click_node->getOptionChilds(option);
    int count = current_option_childnodes.size();
    beginInsertRows(index,click_node->childCount(), click_node->childCount() + count-1);
    for(int i=0;i<count;i++)
    {
        click_node->appendChild(current_option_childnodes[i]);
    }
    endInsertRows();

}

}

