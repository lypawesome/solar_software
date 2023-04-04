#ifndef TOPOTREEVIEWCONTROLLER_H
#define TOPOTREEVIEWCONTROLLER_H

/*
 *控制右上方的topo的树状模型
 *只有一个树状模型，需要添加子孩子，更改孩子节点的属性数据，获取节点前面的icon的名字
*/

#include"TreeModel.h"

class TopoTreeViewController: public QObject
{

    Q_OBJECT

public:
    TopoTreeViewController(QObject *parent = nullptr);
    ~TopoTreeViewController();

public slots://被qml调用
    Q_INVOKABLE QAbstractItemModel *getTreeModel();                 //返回对应的model
    Q_INVOKABLE void updateNodeData(const QModelIndex& index, int column, const QVariant& value );      //更新节点第column列的数据为value
    //Q_INVOKABLE void updateNode(const QModelIndex& index);          //更新节点的数据（包括名字）

    //只有TOPO才有的函数
    Q_INVOKABLE QString getImageName(const QModelIndex& index);         //找到该项对应的类型,返回该类型对应的图片名
    Q_INVOKABLE void appendChild(const QModelIndex& index,int type);    //在index下添加孩子节点，孩子节点的类型是type,type放到para属性上，并且与前面的icon有关

private:
    TreeModel* tree_model;
};

#endif // TOPOTREEVIEWCONTROLLER_H
