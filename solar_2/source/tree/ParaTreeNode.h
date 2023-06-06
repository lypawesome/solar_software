
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

namespace solar
{

    enum ParaState
    {
        QUIET,    // 不可编辑，也不可选
        EDITABLE, // 可编辑
        OPTIONAL  // 可选，有若干个选项，每个选项都有对应的一系列孩子节点
    };

    class ParaTreeNode : public QEnableSharedFromThis<ParaTreeNode>
    {
        public:
            ParaTreeNode(const QList<QVariant>& data,
                         QSharedPointer<ParaTreeNode> parent = nullptr); // 数据，父节点
            ~ParaTreeNode();

            // 给该节点添加一个孩子
            void appendChild(const QSharedPointer<ParaTreeNode>& child);
            // 删除该节点的所有孩子
            void deleteAllChild();
            auto child(int row) -> QSharedPointer<ParaTreeNode>;
            // 孩子个数
            auto childCount() const -> qsizetype;
            // 该节点记录多少个属性
            auto columnCount() const -> qsizetype;
            // 该节点的第column个属性
            auto data(int column) const -> QVariant;
            // 是父节点的第几个孩子
            auto row() const -> qsizetype;
            // 返回父节点的指针
            auto parent() -> QSharedPointer<ParaTreeNode>;

            // 设置父节点,修改父节点的孩子列表
            void setParent(const QSharedPointer<ParaTreeNode>& parent);
            // 设置该节点的第column个属性
            void setData(const QVariant& data, int column);

            //------------------------------------------------------
            // 下面的这些方法，只是初步设置，很大概率会再改

            // 设置该节点的状态:不可编辑不可选、可编辑、可选择
            void setState(ParaState _state);
            // 获取该节点的状态
            auto getState() -> ParaState;

            // OPTIONAL专有的函数，在使用之前，要先判断是否为OPTIONAL

            // 初始化该节点的全部选项
            void initOptions(QList<QString> options);

            // 获得该节点的全部选项
            auto getOptions() -> QList<QString>;


            // 获得该节点的某个选项的孩子节点列表
            auto getOptionChilds(const QString& option) -> QList<QSharedPointer<ParaTreeNode>>;
            // 获得某个选项的孩子个数-------可以删去,因为getOptionChilds可以获得孩子节点列表，从而获得个数
            auto getOptionChildsCount(const QString& option) -> qsizetype;
            // 重置，把option对应的孩子节点列表设置为childs
            void resetOptionChilds(const QString& option,
                                   QList<QSharedPointer<ParaTreeNode>>& childs);
            // 在option对应的孩子节点的列表最后，加上child
            void addOptionChild(const QString& option, QSharedPointer<ParaTreeNode>& child);
            // 做出选择，要更改node_datas和child_nodes
            void makeChoice(const QString& option);
            // 返回现在选中的选项的序号
            auto getCurrentOptionId() -> qsizetype;


            //-------------------用于测试-----------------------
            // 输出当前选项及选中的孩子列表
            void printCurrentChild();
            // 输出所有option对应的孩子列表
            void printAllOptionChild();
            // 输出某个option对应的孩子列表
            void printOptionChild();
            // 输出信息，包括父节点,孩子节点
            void printInfo();


        private:
            QSharedPointer<ParaTreeNode> parent_node;
            // 所有孩子节点的指针
            QList<QSharedPointer<ParaTreeNode>> child_nodes;
            // 该节点的所有数据/属性
            QList<QVariant> node_datas;

            // 默认不可编辑也不可选
            ParaState state = QUIET;
            // 每个选项对应的孩子节点
            QHash<QString, QList<QSharedPointer<ParaTreeNode>>> option_childnodes;
    };

} // namespace solar

#endif // PARATREENODE_H
