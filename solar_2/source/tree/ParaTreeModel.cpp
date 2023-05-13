
#include "tree/ParaTreeModel.h"

namespace solar{

    ParaTreeModel::ParaTreeModel(TreeModelType _model_type,  QSharedPointer<Para> _para, QObject* parent)
            :QAbstractItemModel(parent)
    {
        para = _para;
        model_type = _model_type;
        root_node = createNode(nullptr, "root", "" );     //建立根节点,这个节点在视图中不显示,因此其他参数部分采用默认值

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
    ！！！！！！！！！！！！！！！！！！！！！！！！
    问题：：：在这里设置参数的初始值然后传到para里 or 直接在Para的子类中初始化参数值这里只获取 ？
            目前是，在Para子类中初始化，这里获取参数值
*/

    //state是当前节点的state
    QSharedPointer<ParaTreeNode> ParaTreeModel::createNode(
        QSharedPointer<ParaTreeNode> parent,
        QVariant data1, QVariant data2, QVariant data3,
        ParaState state,
        bool is_current_option_child,
        QString parent_option )
    {
        QList<QVariant> list;
        list.append(data1);
        list.append(data2);
        list.append(data3);
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
            {
                parent->appendChild(child_node);
                if(parent->data(1).toString()!=parent_option)
                    parent->setData(parent_option,1);
            }
        }
        else{
            parent->appendChild(child_node);
        }

        return child_node;

    }

    void ParaTreeModel::buildSunTreeModel(QSharedPointer<Sun> sun)
    {
        //position
        auto position_node = createNode(root_node,"position","");   //这个节点不可更改，只是用来放子节点的父节点

        //position-azimuth
        QVariant azimuth = sun->getPara(kAzimuth);
        createNode(position_node,"azimuth",azimuth, kAzimuth, EDITABLE);

        //position-elevation
        QVariant elevation = sun->getPara(kElevation);
        createNode(position_node,"elevation",elevation,kElevation, EDITABLE);

        //position-irradiance
        QVariant irradiance = sun->getPara(kIrradiance);
        createNode(position_node,"irradiance",irradiance,kIrradiance, EDITABLE);

        //position-trackable
        QVariant trackable = sun->getPara(kTrackable);
        createNode(position_node,"trackable",trackable,kTrackable, EDITABLE);

        //sunshape
        auto sunshape_node = createNode(root_node,"sunshape","",kSunShape,OPTIONAL);

        int current_sunshape_type = sun->getPara(kSunShape).toInt();

        //！！！这里添加option_child时，一定要格外留意是否选中当前的选项

        //sunshape-csr
        if(current_sunshape_type == kSunShapeBuie)
        {
            QVariant csr = sun->getPara(kCSR);
            createNode(sunshape_node,"csr",csr,kCSR,EDITABLE,true,"Buie");
        }
        else{
            QVariant csr = 0.02;
            createNode(sunshape_node,"csr",csr,kCSR,EDITABLE,false,"Buie");
        }

        //sunshape-theta_max
        if(current_sunshape_type == kSunShapePillbox)
        {
            QVariant theta_max = sun->getPara(kThetaMax);
            createNode(sunshape_node,"theta_max",theta_max,kThetaMax,EDITABLE,true,"Pillbox");
        }
        else{
            QVariant theta_max = 0.00465;
            createNode(sunshape_node,"theta_max",theta_max,kThetaMax,EDITABLE,false,"Pillbox");
        }

        //sunshape-gaussian
        if(current_sunshape_type == kSunShapeGaussian)
        {
            QVariant sigma = sun->getPara(kSigma);
            createNode(sunshape_node,"sigma",sigma,kSigma,EDITABLE,true,"Gaussian");
        }
        else{
            QVariant sigma = 0.00251;
            createNode(sunshape_node,"sigma",sigma,kSigma,EDITABLE,false,"Gaussian");
        }

    }


    void ParaTreeModel::buildLocationTreeModel(QSharedPointer<Location> location)
    {
        //site_name
        QVariant site = location->getPara(kSiteName);
        createNode(root_node,"site_name", site,kSiteName, EDITABLE);

        //longitude
        QVariant longitude = location->getPara(kLongitude);
        createNode(root_node,"longitude", longitude, kLongitude, EDITABLE);

        //latitude
        QVariant latitude = location->getPara(kLatitude);
        createNode(root_node,"latitude", latitude, kLatitude, EDITABLE);

    }

    /*
------------------------------------------------------------------------------
*/

//！！！这里返回3列，但是界面部分只显示2列，把最后一列设置为不可见
int ParaTreeModel::columnCount(const QModelIndex& parent ) const    //返回列数
{
        return 3;
}
int ParaTreeModel::rowCount(const QModelIndex& parent ) const       //返回孩子节点的个数
{
        int ret=0;
                                        //QModelIndex代表的是一个Item，不是一个Row
        if (parent.column() > 0)        //这里是因为所有的孩子节点都是放在column=0上面的，当column>0时，默认是没有节点的
        {
            qDebug()<<"1111 "<<parent.column();
            return 0;
        }

        if (!parent.isValid())
        {
            qDebug()<<"2222";
            ret = root_node->childCount();
        }
        else
        {
            qDebug()<<"3333";
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
        names[TYPE_ID] = "type_id";        //参数类型
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
        case TYPE_ID:
        {
            return static_cast<ParaTreeNode*>(index.internalPointer())->data(2);
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

    //进行编辑
    if(click_node->getState() == EDITABLE)  //若该节点是可编辑的，只更改这一个节点的para，并发送信号
    {
        click_node->setData(value, 1);
        int para_property_type = click_node->data(2).toInt();
        para->setPara(para_property_type,value);
        qDebug()<<"\t para的参数是否更改？新的参数为:"<<para->getPara(para_property_type);
        //para->setPara(para_name.toStdString(),value);   // !!!!这里有问题
        emit dataChanged(index, index);
    }

    //进行选择
    // !!!!注意进行makechoice时，要看value是否在选项内
    if(click_node->getState()== OPTIONAL)   //该节点是可选择的，需要做出选择，并发送信号！！！！！发送信号的地方好像有bug
    {
        qDebug()<<"click OPTIONAL 选中的选项为："<<value.toString();
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

    //！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
    // 还是这里有问题，先删除所有的孩子节点，再把选中的选项中的孩子节点放上来
    // 删除该节点现有的孩子节点
    //！！！！！！这里，似乎是，孩子节点与父节点的row的定义不太一样
    if(click_node->childCount())
    {
        qDebug()<<"click_node->childCount(): "<<click_node->childCount();
        int parent_row = index.row();
        int first_row = parent_row + 1;
        int last_row = parent_row + 1 + click_node->childCount() -1;
        qDebug() << "parent_row: "<<parent_row;
        qDebug() <<"first_row: "<<first_row<<" last_row: "<<last_row<<" "<<rowCount(index);
        beginRemoveRows(index, first_row, last_row);
        click_node->deletaAllChild();
        endRemoveRows();

//        click_node->deletaAllChild();
//        bool ret = removeRows(index.row(),click_node->childCount(),index);  //要重写这个函数才能用
//        qDebug()<<ret;
    }

    //把选项的孩子列表添加到节点的孩子列表中
//    auto current_option_childnodes = click_node->getOptionChilds(option);
//    int count = current_option_childnodes.size();
//    beginInsertRows(index,click_node->childCount(), click_node->childCount() + count-1);
//    for(int i=0;i<count;i++)
//    {
//        click_node->appendChild(current_option_childnodes[i]);
//    }
//    endInsertRows();

}


int ParaTreeModel::getCurrentOptionId(const QModelIndex& index)
{
    if (!index.isValid())
        return -1;
    ParaTreeNode* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
    return click_node->getCurrentOptionId();
}

}

