#include "ParaTreeViewController.h"

ParaTreeViewController::ParaTreeViewController(int model_type, Para* object,QObject *parent )
    :QObject(parent)
{
    tree_model = new TreeModel(model_type);
    tree_model->buildSunTreeModel(static_cast<Sun*>(object));
}
ParaTreeViewController::~ParaTreeViewController()
{
    delete tree_model;
}

QAbstractItemModel* ParaTreeViewController::getTreeModel()
{
    return tree_model;
}
void ParaTreeViewController::updateNodeData(const QModelIndex& index, int column, const QVariant& value )
{
    tree_model->setNodeColumn(index,column,value);
}

void ParaTreeViewController::test()        //测试是否可以被qml调用
{
    qDebug()<<"ParaTreeViewController is used";
}

bool ParaTreeViewController::iseditable(const QModelIndex& index)      //判断index这一节点是否可编辑
{
    return tree_model->isNodeEditable(index);
}
bool ParaTreeViewController::isoptional(const QModelIndex& index)       //判断index这一节点是否有选项
{
    return tree_model->isNodeOptional(index);
}

QStringList ParaTreeViewController::getOptionList(const QModelIndex& index) //获取idnex这一节点的所有选项的string列表
{
    QList<QString> dataList =  tree_model->getNodeOptionList(index);
    QStringList modelList;
    for(int i=0;i<dataList.size();i++)
        modelList.append(dataList.value(i));
    return modelList;
}
void ParaTreeViewController::makeChoice(const QModelIndex& index, QString option)
{
    tree_model->makeChoice(index,option);
}
QString ParaTreeViewController::getPara(const QModelIndex& index)
{
    return tree_model->getNodeColumn(index,1);
}
