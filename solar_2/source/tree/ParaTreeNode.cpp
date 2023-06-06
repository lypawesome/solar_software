
//#include <qtypes.h>
#include <utility>

#include "tree/ParaTreeNode.h"

namespace solar
{

    ParaTreeNode::ParaTreeNode(const QList<QVariant>& data, QSharedPointer<ParaTreeNode> parent)
        : parent_node(std::move(parent)), node_datas(data) // 数据，父节点
    {
    }

    ParaTreeNode::~ParaTreeNode() = default;

    void ParaTreeNode::appendChild(const QSharedPointer<ParaTreeNode>& child) // 给该节点添加一个孩子
    {
        child->setParent(sharedFromThis());
        child_nodes.append(child);
    }

    void ParaTreeNode::deleteAllChild() // 删除该节点的所有孩子
    {
        for (int index = 0; index < child_nodes.size(); index++)
        {
            child_nodes.value(index)->deleteAllChild();     //先递归地删去孩子
            //child_nodes.value(index).clear();               //会把地址也删去
        }
        child_nodes.clear();
    }

    auto ParaTreeNode::child(int row) -> QSharedPointer<ParaTreeNode>
    {
        if (row < 0 || row >= child_nodes.size()) // 如果row不合法，报错
        {
            throw "invalid row in Func: ParaTreeNode::child(row)";
        }
        return child_nodes.value(row);
    }

    auto ParaTreeNode::childCount() const -> qsizetype // 孩子个数
    {
        return child_nodes.size();
    }

    auto ParaTreeNode::columnCount() const -> qsizetype // 该节点记录多少个属性
    {
        return node_datas.size();
    }

    auto ParaTreeNode::data(int column) const -> QVariant // 该节点的第column个属性
    {
        if (column < 0 || column >= node_datas.size())
        {
            throw "invalid column in Func: TopoTreeNode::data(column)";
        }
        return node_datas.value(column);
    }

    auto ParaTreeNode::row() const -> qsizetype // 是父节点的第几个孩子
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
        return parent_node->child_nodes.indexOf(temp);
    }

    auto ParaTreeNode::parent() -> QSharedPointer<ParaTreeNode> // 返回父节点的指针
    {
        return parent_node;
    }

    void
    ParaTreeNode::setParent(const QSharedPointer<ParaTreeNode>& parent) // 设置父节点,修改父节点的孩子列表
    {
        parent_node = parent;
    }

    void ParaTreeNode::setData(const QVariant& data, int column) // 设置该节点的第column个属性
    {
        if (column < 0 || column >= node_datas.size())
        {
            throw "invalid column in Func: ParaTreeNode::setNodeData(data,column)";
        }

        //qDebug() << "ParaTreeNode中修改参数成功！";
        //qDebug() << "\t 原来参数为：" << node_datas[column].toString();

        node_datas[column] = data;



        //qDebug() << "\t 新的参数为：" << data.toString();
    }

    // 设置该节点的状态:不可编辑不可选、可编辑、可选择
    void ParaTreeNode::setState(ParaState _state) { state = _state; }

    // 获取该节点的状态
    auto ParaTreeNode::getState() -> ParaState { return state; }

    //==========================OPTIONAL专有函数=========================
    
    // 初始化该节点的全部选项
    void ParaTreeNode::initOptions(QList<QString> options)
    {
        int cnt = option_childnodes.capacity();
        if( cnt > 0) {
            qDebug()<<"WARNING::ParaTreeNode::initOPtions::option_childnodes is not null"
                    << "and it has "<<cnt<<" keys.";
            // option_childnodes.clear();
        }

        for(auto key : options)
            option_childnodes[key];
    }


    // 获得该节点的全部选项
    auto ParaTreeNode::getOptions() -> QList<QString> { return option_childnodes.keys(); }

    // 获得该节点的某个选项的孩子节点列表
    auto ParaTreeNode::getOptionChilds(const QString& option) -> QList<QSharedPointer<ParaTreeNode>>
    {
        return option_childnodes.value(option);
    }
    // 获得某个选项的孩子个数
    auto ParaTreeNode::getOptionChildsCount(const QString& option) -> qsizetype
    {
        return option_childnodes.value(option).size();
    }

    void ParaTreeNode::resetOptionChilds(
        const QString& option,
        QList<QSharedPointer<ParaTreeNode>>& childs) // 重置，把option对应的孩子节点列表设置为childs
    {
        option_childnodes[option]
            .clear(); // 清空该选项的孩子列表,这里直接用[],不能用value()，因为value()返回的不是引用类型
        for (auto& item : childs)
        {
            item->setParent(sharedFromThis());
        }
        option_childnodes[option] = childs;
    }
    // 在option对应的孩子节点的列表最后，加上child
    void ParaTreeNode::addOptionChild(const QString& option, QSharedPointer<ParaTreeNode>& child)
    {
        child->setParent(sharedFromThis());
        // 同理，要对qhash内存的值进行操作时，不能用value()要用[]
        option_childnodes[option].append(child);
    }
    // 做出选择，要更改node_datas和child_nodes
    void ParaTreeNode::makeChoice(const QString& option)
    {
        // 选项都是第2列----更改node_datas
        setData(option, 1);
        auto current_option_childnodes = option_childnodes.value(option);
        // 把孩子列表清空
        child_nodes.clear();
        // 把该选项的孩子添加到节点的孩子列表中
        for (auto& item : current_option_childnodes)
        {
            child_nodes.append(item);
        }
    }

    auto ParaTreeNode::getCurrentOptionId() -> qsizetype
    {
        QString current_option = data(1).toString();
        QList<QString> option_keys = option_childnodes.keys();
        qDebug() << current_option << "\n" << option_keys;
        return option_keys.indexOf(current_option);
    }

    // 输出当前选项及选中的孩子列表
    void ParaTreeNode::printCurrentChild()
    {
        qDebug() <<"\t"<<" has child: "<<childCount();
        for(auto child : child_nodes)
        {
            qDebug() <<"\t child node: "<<child->data(0).toString()<<", "<<child->data(1).toString();
        }
    }
    // 输出所有option对应的孩子列表
    void ParaTreeNode::printAllOptionChild()
    {
        int cnt = option_childnodes.size();
        qDebug() <<"\t has option cnt: "<<cnt;
        auto key_list = option_childnodes.keys();
        qDebug() <<"\t all options: "<<key_list;
        for(int i=0; i<cnt;i++)
        {
            auto child_list = option_childnodes.value(key_list.at(i));
            qDebug() <<"\t option: "<<key_list.at(i) <<" has child cnt: "<<child_list.size();
            for(auto child : child_list)
            {
                qDebug() <<"\t\t "<<child->data(0).toString() <<", "<<child->data(1).toString();
            }
        }
    }
    // 输出某个option对应的孩子列表
    void ParaTreeNode::printOptionChild()
    {

    }

    void ParaTreeNode::printInfo()
    {
        qDebug() <<"-----parent:"<<parent_node;
        if(parent_node)
            qDebug() <<"-------parent: "<<parent_node->data(0).toString()
                        <<", "<<parent_node->data(1).toString();
        qDebug() <<"-----para tree node: "<<data(0).toString()<<", "<<data(1).toString();
        printCurrentChild();
    }

} // namespace solar
