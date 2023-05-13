
#include "tree/ParaTreeViewController.h"

namespace solar{

ParaTreeViewController::ParaTreeViewController(QObject* parent )
{}
ParaTreeViewController::~ParaTreeViewController()
{
}

void ParaTreeViewController::addParaTreeModel(TreeModelType model_type, QSharedPointer<Para> para)
{
    QSharedPointer<ParaTreeModel> para_tree_model =
        QSharedPointer<ParaTreeModel>(new ParaTreeModel(model_type,para));
    tree_models.append(para_tree_model);
}
void ParaTreeViewController::addParaTreeModel(QSharedPointer<ParaTreeModel> para_tree_model)
{
    tree_models.append(para_tree_model);
}
void ParaTreeViewController::removeParaTreeModel(int para_tree_id)
{
    tree_models.removeAt(para_tree_id);
}
void ParaTreeViewController::removeParaTreeModel(QSharedPointer<ParaTreeModel> para_tree_model)
{
    int tree_model_cnt = tree_models.count();
    for(int i = 0 ; i < tree_model_cnt ; ++ i)
    {
        if(tree_models.at(i) == para_tree_model)
        {
            tree_models.removeAt(i);
            break;
        }
    }
}

int ParaTreeViewController::getParaTreeModelId(QSharedPointer<ParaTreeModel> para_tree_model)
{
    int ret = -1;
    int tree_model_cnt = tree_models.count();
    for(int i=0 ; i < tree_model_cnt ; ++i)
    {
        if(tree_models.at(i)==para_tree_model){
            ret = i;
            break;
        }
    }
    return ret;
}

QAbstractItemModel* ParaTreeViewController::getTreeModel(int para_tree_id)
{
    qDebug()<<"调用ParaTreeViewController::getTreeModel(int para_tree_id) ";
    qDebug()<<" para_tree_id = "<<para_tree_id;
    return tree_models[para_tree_id].get();
}

void ParaTreeViewController::updateNodePara(int para_tree_id, const QModelIndex& index, const QVariant& value)
{
    tree_models.at(para_tree_id)->setNodePara(index,value);
}

void ParaTreeViewController::test()
{
    qDebug()<<"test ParaTreeViewController";
}

bool ParaTreeViewController::isEditable(int para_tree_id, const QModelIndex& index)
{
    return tree_models.at(para_tree_id)->isNodeEditable(index);
}
bool ParaTreeViewController::isOptional(int para_tree_id, const QModelIndex& index)
{
    return tree_models.at(para_tree_id)->isNodeOptional(index);
}

QStringList ParaTreeViewController::getOptionList(int para_tree_id, const QModelIndex& index)
{
    QList<QString> data_list = tree_models.at(para_tree_id)->getNodeOptionList(index);
    QStringList model_list;
    for (int i = 0; i < data_list.size(); i++)
    {
        model_list.append(data_list.value(i));
    }
    return model_list;
}
//这里要再写一写
void ParaTreeViewController::makeChoice(int para_tree_id, const QModelIndex& index, QString option)
{

}
QString ParaTreeViewController::getPara(int para_tree_id, const QModelIndex& index)
{
    return tree_models.at(para_tree_id)->getNodePara(index);
}


//可以不用para_tree_id，哪个都有
int ParaTreeViewController::getCurrentOptionId(int para_tree_id, const QModelIndex&index)
{
    return tree_models.at(para_tree_id)->getCurrentOptionId(index);
}


} // namespace solar

