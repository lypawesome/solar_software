#include "TopoTreeViewController.h"


TopoTreeViewController::TopoTreeViewController(QObject *parent)
    : QObject(parent)
{
    tree_model = new TreeModel(0);  //0表示类型是Topo，即是右上方的树状结构
}

TopoTreeViewController::~TopoTreeViewController()
{
    delete tree_model;
}

QAbstractItemModel *TopoTreeViewController::getTreeModel()
{
    return tree_model;
}

void TopoTreeViewController::updateNodeData(const QModelIndex& index, int column, const QVariant& value )
{
    tree_model->setNodeColumn(index,column,value);
}


QString TopoTreeViewController::getImageName(const QModelIndex& index)
{
    return tree_model->getIconName(index);
}

void TopoTreeViewController::appendChild(const QModelIndex& index,int type)
{
    QList<QVariant> list;
    QString name;
    switch(type)
    {
    case 0: name = "node"; break;
    case 1: name = "shape"; break;
    case 2: name = "tracker"; break;
    case 3: name = "array"; break;
    }
    list.append(name);
    list.append(type);

    tree_model->appendChild(index,list,1);
}
