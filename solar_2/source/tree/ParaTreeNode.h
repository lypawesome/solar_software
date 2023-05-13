
#ifndef PARATREENODE_H
#define PARATREENODE_H

/*
    右下角参数设置部分的树状视图的节点


*/

#include <QDebug>
#include <QList>
#include <QModelIndex>
#include <QObject>
#include <QStringList>
#include <QVariant>

namespace solar{

    enum ParaState{
        QUIET,      //不可编辑，也不可选
        EDITABLE,   //可编辑
        OPTIONAL    //可选，有若干个选项，每个选项都有对应的一系列孩子节点
    };


    class ParaTreeNode : public QEnableSharedFromThis<ParaTreeNode>
    {
    public:
        ParaTreeNode(const QList<QVariant>& data,
                     QSharedPointer<ParaTreeNode> parent = nullptr); // 数据，父节点
        ~ParaTreeNode();

        void appendChild(QSharedPointer<ParaTreeNode> child); // 给该节点添加一个孩子
        void deletaAllChild();             // 删除该节点的所有孩子

        QSharedPointer<ParaTreeNode> child(int row);
        int childCount() const;          // 孩子个数
        int columnCount() const;         // 该节点记录多少个属性
        QVariant data(int column) const; // 该节点的第column个属性
        int row() const;                 // 是父节点的第几个孩子
        QSharedPointer<ParaTreeNode> parent();              // 返回父节点的指针

        void setParent(QSharedPointer<ParaTreeNode> parent); // 设置父节点,修改父节点的孩子列表
        void setData(const QVariant& data, int column); // 设置该节点的第column个属性

        //------------------------------------------------------
        // 下面的这些方法，只是初步设置，很大概率会再改
        void setState(ParaState _state);        //设置该节点的状态:不可编辑不可选、可编辑、可选择
        ParaState getState();                   //获取该节点的状态

        // OPTIONAL专有的函数，在使用之前，要先判断是否为OPTIONAL
        QList<QString> getOptions();                //获得该节点的全部选项
        QList<QSharedPointer<ParaTreeNode>> getOptionChilds(QString option);    //获得该节点的某个选项的孩子节点列表
        int getOptionChildsCount(QString option);   //获得某个选项的孩子个数-------可以删去,因为getOptionChilds可以获得孩子节点列表，从而获得个数
        void resetOptionChilds(const QString& option,
                               QList<QSharedPointer<ParaTreeNode>> childs); // 重置，把option对应的孩子节点列表设置为childs
        void addOptionChild( QString option,
                            QSharedPointer<ParaTreeNode> child); // 在option对应的孩子节点的列表最后，加上child
        void makeChoice(const QString& option);         // 做出选择，要更改node_datas和child_nodes

        int getCurrentOptionId();       //返回现在选中的选项的序号

    private:
        QSharedPointer<ParaTreeNode> parent_node;
        QList<QSharedPointer<ParaTreeNode>> child_nodes;       //所有孩子节点的指针
        QList<QVariant> node_datas;          //该节点的所有数据/属性

        ParaState state = QUIET;        //默认不可编辑也不可选
        QHash<QString, QList<QSharedPointer<ParaTreeNode> > > option_childnodes;//每个选项对应的孩子节点
    };

}

#endif // PARATREENODE_H
