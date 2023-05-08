
#ifndef TOPOTREEVIEWCONTROLLER_H
#define TOPOTREEVIEWCONTROLLER_H

/*
用于右上角，Topo模型部分的树状视图的控制器
！！！注意这里的成员函数还需要改
*/


#include <QObject>
#include "TopoTreeModel.h"

namespace solar{

class TopoTreeViewController : public QObject
{
    Q_OBJECT

public:
    TopoTreeViewController(QObject *parent = nullptr);
    ~TopoTreeViewController();

public slots://被qml调用
    Q_INVOKABLE QAbstractItemModel *getTreeModel();
    Q_INVOKABLE void updateNodeName(const QModelIndex& index, QVariant new_name);      //更新节点名字
    Q_INVOKABLE void updateNode(const QModelIndex& index);  // !!!!!!!!!!!更新节点，可能要删去
    Q_INVOKABLE QString getImageName(const QModelIndex& index);         //找到该项对应的类型,返回该类型对应的图片名
    Q_INVOKABLE void appendChild(const QModelIndex& index,int type);    //在index下添加孩子节点，孩子节点的类型是type
    Q_INVOKABLE int getTotalNodeCnt();         //返回总共的节点数

private:
    QSharedPointer<TopoTreeModel> tree_model;     //这里要写成智能指针吗？？？
};

}//namespace solar

#endif // TOPOTREEVIEWCONTROLLER_H
