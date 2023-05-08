
#include "TopoTreeNode.h"

namespace solar
{

TopoTreeNode::TopoTreeNode(const QList<QVariant> &data,
                           QSharedPointer<TopoTreeNode> parent)
{
    parent_node = parent;
    node_datas = data;

    //处理对应的ParaTreeModel
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
    //para_tree_model = QSharedDataPointer<ParaTreeModel>(new ParaTreeModel(getParaModelType(),para));
}


TopoTreeNode::~TopoTreeNode()
{
}

void TopoTreeNode::appendChild(QSharedPointer<TopoTreeNode> child)      //给该节点添加一个孩子
{

    child->setParent( sharedFromThis() );
    child_nodes.append(child);
}
void TopoTreeNode::deleteAllChild()                  //删去该节点的所有孩子
{
    for (int index = 0; index < child_nodes.size(); index++)
    {
        child_nodes.value(index)->deleteAllChild();
        child_nodes.value(index).clear();
    }
    child_nodes.clear();
}

QSharedPointer<TopoTreeNode> TopoTreeNode::child(int row)           //该节点的第row个孩子
{
    if (row < 0 || row >= child_nodes.size())   //如果row不合法，报错
    {
        throw "invalid row in Func: TopoTreeNode::child(row)";
    }
    return child_nodes.value(row);
}

int TopoTreeNode::childCount() const       //孩子个数
{
    return child_nodes.size();
}
int TopoTreeNode::columnCount() const            //该节点记录多少个属性
{
    return node_datas.size();
}
QVariant TopoTreeNode::data(int column) const    //该节点的第column个属性
{
    if (column < 0 || column >= node_datas.size())
    {
        throw "invalid column in Func: TopoTreeNode::data(column)";
    }
    return node_datas.value(column);
}
int TopoTreeNode::row() const                    //是父节点的第几个孩子
{
    if(parent_node == nullptr)  //父节点为空，表示无父节点
    {
        return 0;
    }
    auto temp = sharedFromThis();
    if(temp==nullptr)
    {
        throw "can't find this pointer in Func:TopoTreeNode::row() ";
    }
    return parent_node->child_nodes.indexOf(temp);  //！！！注意这里是否有bug

}
QSharedPointer<TopoTreeNode> TopoTreeNode::parent()                 //返回父节点的指针
{
    return parent_node;
}
void TopoTreeNode::setParent(QSharedPointer<TopoTreeNode> parent)   //设置父节点
{
    parent_node = parent;
}
void TopoTreeNode::setNodeData(QVariant data, int column)    //设置该节点的第column个属性
{
    if (column < 0 || column >= node_datas.size())
    {
        throw "invalid column in Func: TopoTreeNode::setNodeData(data,column)";
    }
    node_datas[column] = data;
}


int TopoTreeNode::getParaTreeId(const QSharedPointer<ParaTreeViewController>& para_tree_control)
{
    return para_tree_control->getParaTreeModelId(para_tree_model);
}
int TopoTreeNode::getParaModelType()    //返回的是TreeModelType的枚举
{
    QVariant type = data(1);
    return type.toInt()-0 + NODE;
}
//所有子孙后代的个数，不包括自身
int TopoTreeNode::getOffspringCount()
{
    int cnt = childCount();
    for(auto child : child_nodes)
    {
        cnt+=child->getOffspringCount();
    }
    return cnt;
}

}//namespace solar
