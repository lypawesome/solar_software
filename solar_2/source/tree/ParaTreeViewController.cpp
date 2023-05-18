
#include "tree/ParaTreeViewController.h"
#include <qtypes.h>

namespace solar
{

    ParaTreeViewController::ParaTreeViewController(QObject*) {}
    ParaTreeViewController::~ParaTreeViewController() = default;

    void ParaTreeViewController::addParaTreeModel(TreeModelType model_type,
                                                  const QSharedPointer<Para>& para)
    {
        QSharedPointer<ParaTreeModel> para_tree_model =
            QSharedPointer<ParaTreeModel>(new ParaTreeModel(model_type, para));
        tree_models.append(para_tree_model);
    }
    void ParaTreeViewController::addParaTreeModel(const QSharedPointer<ParaTreeModel>& para_tree_model)
    {
        tree_models.append(para_tree_model);
    }
    void ParaTreeViewController::removeParaTreeModel(int para_tree_id)
    {
        tree_models.removeAt(para_tree_id);
    }
    void ParaTreeViewController::removeParaTreeModel(const QSharedPointer<ParaTreeModel>& para_tree_model)
    {
        auto tree_model_cnt = tree_models.count();
        for (int i = 0; i < tree_model_cnt; ++i)
        {
            if (tree_models.at(i) == para_tree_model)
            {
                tree_models.removeAt(i);
                break;
            }
        }
    }

    auto ParaTreeViewController::getParaTreeModelId(const QSharedPointer<ParaTreeModel>& para_tree_model) -> qsizetype
    {
        qsizetype ret = -1;
        auto tree_model_cnt = tree_models.count();
        for (qsizetype i = 0; i < tree_model_cnt; ++i)
        {
            if (tree_models.at(i) == para_tree_model)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    auto ParaTreeViewController::getTreeModel(int para_tree_id) -> QAbstractItemModel*
    {
        qDebug() << "调用ParaTreeViewController::getTreeModel(int para_tree_id) ";
        qDebug() << " para_tree_id = " << para_tree_id;
        return tree_models[para_tree_id].get();
    }

    void ParaTreeViewController::updateNodePara(int para_tree_id, const QModelIndex& index,
                                                const QVariant& value)
    {
        tree_models.at(para_tree_id)->setNodePara(index, value);
    }

    void ParaTreeViewController::test() { qDebug() << "test ParaTreeViewController"; }

    auto ParaTreeViewController::isEditable(int para_tree_id, const QModelIndex& index) -> bool
    {
        return tree_models.at(para_tree_id)->isNodeEditable(index);
    }
    auto ParaTreeViewController::isOptional(int para_tree_id, const QModelIndex& index) -> bool
    {
        return tree_models.at(para_tree_id)->isNodeOptional(index);
    }

    auto ParaTreeViewController::getOptionList(int para_tree_id, const QModelIndex& index) -> QStringList
    {
        QList<QString> data_list = tree_models.at(para_tree_id)->getNodeOptionList(index);
        QStringList model_list;
        for (qsizetype i = 0; i < data_list.size(); i++)
        {
            model_list.append(data_list.value(i));
        }
        return model_list;
    }
    // 这里要再写一写
    void ParaTreeViewController::makeChoice(int para_tree_id, const QModelIndex& index,
                                            QString option)
    {
    }
    auto ParaTreeViewController::getPara(int para_tree_id, const QModelIndex& index) -> QString
    {
        return tree_models.at(para_tree_id)->getNodePara(index);
    }

    // 可以不用para_tree_id，哪个都有
    auto ParaTreeViewController::getCurrentOptionId(int para_tree_id, const QModelIndex& index) -> int
    {
        return tree_models.at(para_tree_id)->getCurrentOptionId(index);
    }

} // namespace solar
