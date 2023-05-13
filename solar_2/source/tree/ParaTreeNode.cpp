
#include "tree/ParaTreeNode.h"

namespace solar
{

    ParaTreeNode::ParaTreeNode(const QList<QVariant>& data,
             QSharedPointer<ParaTreeNode> parent) // 数据，父节点
    {
        parent_node = parent;
        node_datas = data;
    }

    ParaTreeNode::~ParaTreeNode()
    {
    }

    void ParaTreeNode::appendChild(QSharedPointer<ParaTreeNode> child) // 给该节点添加一个孩子
    {
        child->setParent(sharedFromThis());
        child_nodes.append(child);
    }

    void ParaTreeNode::deletaAllChild()             // 删除该节点的所有孩子
    {
        for (int index = 0; index < child_nodes.size(); index++)
        {
            child_nodes.value(index)->deletaAllChild();         //孩子节点用的是智能指针，只要不主动删除，是不会释放空间的
           // child_nodes.value(index).clear();               //会把地址也删去
        }
        child_nodes.clear();
    }

    QSharedPointer<ParaTreeNode> ParaTreeNode::child(int row)
    {
        if (row < 0 || row >= child_nodes.size())   //如果row不合法，报错
        {
            throw "invalid row in Func: ParaTreeNode::child(row)";
        }
        return child_nodes.value(row);
    }

    int ParaTreeNode::childCount() const          // 孩子个数
    {
        return child_nodes.size();
    }

    int ParaTreeNode::columnCount() const         // 该节点记录多少个属性
    {
        return node_datas.size();
    }

    QVariant ParaTreeNode::data(int column) const // 该节点的第column个属性
    {
        if (column < 0 || column >= node_datas.size())
        {
            throw "invalid column in Func: TopoTreeNode::data(column)";
        }
        return node_datas.value(column);
    }

    int ParaTreeNode::row() const                 // 是父节点的第几个孩子
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
        return parent_node->child_nodes.indexOf(temp);
    }

    QSharedPointer<ParaTreeNode> ParaTreeNode::parent()              // 返回父节点的指针
    {
        return parent_node;
    }

    void ParaTreeNode::setParent(QSharedPointer<ParaTreeNode> parent) // 设置父节点,修改父节点的孩子列表
    {
        parent_node = parent;
    }

    void ParaTreeNode::setData(const QVariant& data, int column) // 设置该节点的第column个属性
    {
        if (column < 0 || column >= node_datas.size())
        {
            throw "invalid column in Func: ParaTreeNode::setNodeData(data,column)";
        }

        qDebug()<<"ParaTreeNode中修改参数成功！";
        qDebug()<<"\t 原来参数为：" << node_datas[column].toString();

        node_datas[column] = data;

        qDebug() <<"\t 新的参数为："<<data.toString();
    }

    void ParaTreeNode::setState(ParaState _state)        //设置该节点的状态:不可编辑不可选、可编辑、可选择
    {
        state= _state;
    }
    ParaState ParaTreeNode::getState()                   //获取该节点的状态
    {
        return state;
    }

    //==========================OPTIONAL专有函数=========================
    QList<QString> ParaTreeNode::getOptions()            //获得该节点的全部选项
    {
        return option_childnodes.keys();
    }

    QList<QSharedPointer<ParaTreeNode>> ParaTreeNode::getOptionChilds(QString option)    //获得该节点的某个选项的孩子节点列表
    {
        return option_childnodes.value(option);
    }
    int ParaTreeNode::getOptionChildsCount(QString option)   //获得某个选项的孩子个数
    {
        return option_childnodes.value(option).size();
    }


    void ParaTreeNode::resetOptionChilds(const QString& option,
                           QList<QSharedPointer<ParaTreeNode>> childs) // 重置，把option对应的孩子节点列表设置为childs
    {
        option_childnodes[option].clear();    //清空该选项的孩子列表,这里直接用[],不能用value()，因为value()返回的不是引用类型
        for(auto &item:childs)
        {
            item->setParent(sharedFromThis());
        }
        option_childnodes[option] = childs;
    }

    void ParaTreeNode::addOptionChild( QString option,
                        QSharedPointer<ParaTreeNode> child) // 在option对应的孩子节点的列表最后，加上child
    {
        child->setParent(sharedFromThis());
        option_childnodes[option].append(child);    //同理，要对qhash内存的值进行操作时，不能用value()要用[]
    }

    void ParaTreeNode::makeChoice(const QString& option) // 做出选择，要更改node_datas和child_nodes
    {
        setData(option,1);  //选项都是第2列----更改node_datas
        auto current_option_childnodes = option_childnodes.value(option);
        child_nodes.clear();    //把孩子列表清空
        for(auto &item:current_option_childnodes)    //把该选项的孩子添加到节点的孩子列表中
        {
            child_nodes.append(item);
        }
    }

    int ParaTreeNode::getCurrentOptionId()
    {
        QString current_option = data(1).toString();
        QList<QString> option_keys = option_childnodes.keys();
        qDebug() <<current_option<<"\n"<<option_keys;
        return option_keys.indexOf(current_option);
    }

} // namespace solar

