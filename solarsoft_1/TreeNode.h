#ifndef TREENODE_H
#define TREENODE_H

/*
树状视图的节点，
存储：
父节点、本节点的数据列表，子节点列表，-------topo
是否可选，是否可编辑，每个选项，每个选项对应的子节点列表


*/

#include <QObject>
#include <QList>
#include <QVariant>
#include <QStringList>
#include <QModelIndex>
#include <QDebug>

class ParaTreeViewController;

class TreeNode
{
public:
    TreeNode(const QList<QVariant> &data, TreeNode *parent = nullptr);  //数据，父节点
    ~TreeNode();

    void appendChild(TreeNode* child);      //给该节点添加一个孩子
    void deletaAllChild();                      //删除该节点的所有孩子

    TreeNode* child(int row);
    int childCount() const;             //孩子个数
    int columnCount() const;            //该节点记录多少个属性
    QVariant data(int column) const;    //该节点的第column个属性
    int row() const;                    //是父节点的第几个孩子
    TreeNode* parent();                 //返回父节点的指针

    void setParent(TreeNode* parent);   //设置父节点,修改父节点的孩子列表
    bool setData(const QVariant& data, int column);    //设置该节点的第column个属性

    void setEditable();
    void setOptional();
    bool getEditable();
    bool getOptional();
    QList<QString> getOptions();
    void insertOption(QString option);      //在options中添加
    QList<TreeNode*> getOptionChilds(QString option);

    void makeChoice(const QString& option );    //做出选择，把mNodeData[1]的数据改了，同时把mChildNodes给改了
    void resetOptionChilds(const QString& option, QList<TreeNode*>childs);     //重置，把option对应的孩子节点列表设置为childs
    void addOptionChild( QString option, TreeNode* child);             //在option对应的孩子节点的列表最后，加上child

private:
    TreeNode* parent_node;          //父节点指针
    QList<TreeNode*> child_nodes;   //孩子节点列表
    QList<QVariant> node_data;      //节点的数据

    //para设置部分特有的成员变量
    bool editable = false;      //是否可编辑
    bool optional = false;      //是否可编辑
    QList<QString> options;     //选项------特殊情况：只有options，但是每种option没有对应的孩子节点，只是单纯的做选择
    QHash<QString, QList<TreeNode*>> option_child_nodes;    //每个选项的孩子列表

    bool is_para;
    bool is_topo;
    ParaTreeViewController* para_tree_view_controller;      //当is_topo为真时，存相应的右下方的树状模型
};

#endif // TREENODE_H
