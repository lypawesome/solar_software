
#include "TopoTreeViewController.h"

namespace solar
{

TopoTreeViewController::TopoTreeViewController(QObject *parent)
    : QObject(parent)
{
    tree_model = QSharedPointer<TopoTreeModel>( new TopoTreeModel);
}

TopoTreeViewController::~TopoTreeViewController()
{
}

QAbstractItemModel *TopoTreeViewController::getTreeModel()
{
    return tree_model.get();
}

void TopoTreeViewController::updateNodeName(const QModelIndex& index, QVariant new_name)
{
    tree_model->setNodeName(new_name.toString(), index);
}

void TopoTreeViewController::updateNode(const QModelIndex& index)   // !!!可能要删去
{
    QList<QVariant> list_sc;
    list_sc.append(QString::fromLocal8Bit("sichuan"));
    tree_model->appendChild(index, list_sc, 0);

    QList<QVariant> list_bj;
    list_bj.append(QString::fromLocal8Bit("beijing"));
    tree_model->appendChild(index, list_bj, 1);
}

QString TopoTreeViewController::getImageName(const QModelIndex& index)      //可能要删去
{
    return tree_model->getType(index); //type标记图片名称
}


/*
注意这里，不是所有的添加孩子节点的操作都可以进行
！！！只能在node节点下添加其他的节点，在shape、tracker、array下不能添加节点
！！！注意名字的添加，同一个父亲节点下，不能重名，需要添加后缀
*/
void TopoTreeViewController::appendChild(const QModelIndex& index,int type)
{
    QList<QVariant> list;
    QString name;
    switch(type)
    {
    case 0: name = "node";      break;
    case 1: name = "shape";     break;
    case 2: name = "tracker";   break;
    case 3: name = "array";     break;
    }
    list.append(name);
    list.append(type);

    tree_model->appendChild(index,list,1);
}


} //namespace soalr
