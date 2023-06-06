
#include "tree/ParaTreeViewController.h"
//#include <qtypes.h>

namespace solar
{

    ParaTreeViewController::ParaTreeViewController(QObject*) {}
    ParaTreeViewController::~ParaTreeViewController() = default;

    // void ParaTreeViewController::addParaTreeModelAboutWorld(TreeModelType model_type,
    //                                               const QSharedPointer<Para>& para)
    // {
    //     QSharedPointer<ParaTreeModel> para_tree_model =
    //         QSharedPointer<ParaTreeModel>(new ParaTreeModel(model_type, para));
        
    //     tree_models_about_world.append(para_tree_model);
    // }

    // void ParaTreeViewController::addParaTreeModelAboutTopo(QModelIndex index, 
    //                         const QSharedPointer<ParaTreeModel> para_tree_model)
    // {
    //     topo_model_index_list.append(index);
    //     tree_models_about_topo.insert(index,para_tree_model);
    // }
    void ParaTreeViewController::addParaTreeModel(TreeModelType model_type, const QSharedPointer<Para>& para)
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
        int id = getParaTreeModelId(para_tree_model);
        tree_models.removeAt(id);
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
        //qDebug() << "调用ParaTreeViewController::getTreeModel(int para_tree_id) ";
        //qDebug() << " para_tree_id = " << para_tree_id;

        auto para_tree_model = getParaTreeModelAccordingToId(para_tree_id);

        return para_tree_model.get();
    }

    void ParaTreeViewController::updateNodePara(int para_tree_id, const QModelIndex& index,
                                                const QVariant& value)
    {
        qDebug() <<"paracontroller---updatenodepara";
        getParaTreeModelAccordingToId(para_tree_id)->setNodePara(index, value);
    }

    void ParaTreeViewController::test() { qDebug() << "test ParaTreeViewController"; }

    auto ParaTreeViewController::isEditable(int para_tree_id, const QModelIndex& index) -> bool
    {
        return getParaTreeModelAccordingToId(para_tree_id)->isNodeEditable(index);
    }
    auto ParaTreeViewController::isOptional(int para_tree_id, const QModelIndex& index) -> bool
    {
        return getParaTreeModelAccordingToId(para_tree_id)->isNodeOptional(index);
    }

    auto ParaTreeViewController::getOptionList(int para_tree_id, const QModelIndex& index) -> QStringList
    {
        QList<QString> data_list = getParaTreeModelAccordingToId(para_tree_id)->getNodeOptionList(index);
        QStringList model_list;
        for (qsizetype i = 0; i < data_list.size(); i++)
        {
            model_list.append(data_list.value(i));
        }
        return model_list;
    }

    // !!!!!!!这里要再写一写
    void ParaTreeViewController::makeChoice(int para_tree_id, const QModelIndex& index,
                                            QString option)
    {
    }
    auto ParaTreeViewController::getPara(int para_tree_id, const QModelIndex& index) -> QString
    {
        return getParaTreeModelAccordingToId(para_tree_id)->getNodePara(index);
    }

    // 可以不用para_tree_id，哪个都有
    auto ParaTreeViewController::getCurrentOptionId(int para_tree_id, const QModelIndex& index) -> int
    {
        return getParaTreeModelAccordingToId(para_tree_id)->getCurrentOptionId(index);
    }


    auto ParaTreeViewController::getParaTreeModelCnt() ->int 
    {
        return tree_models.size();
    }
    // auto ParaTreeViewController::getParaTreeModelAboutWorldCnt() ->int
    // {
    //     return tree_models_about_world.size();
    // }
    // auto ParaTreeViewController::getParaTreeModelAboutTopoCnt() ->int
    // {
    //     return tree_models_about_topo.size();
    // }

    auto ParaTreeViewController::getLabelTxt(int para_tree_id) -> QString
    {
        qDebug() <<"HINT::ParaTreeViewController::getLabelTxt::para_tree_id = "<<para_tree_id;
        auto para_tree_model = getParaTreeModelAccordingToId(para_tree_id);
        return para_tree_model->getLabelTxt() ;
    }

    auto ParaTreeViewController::getParaTreeModelAccordingToId(int para_tree_id) ->QSharedPointer<ParaTreeModel>
    {
        int para_tree_model_cnt = tree_models.size();
        if(para_tree_id<0 || para_tree_id>=para_tree_model_cnt)
        {
            qDebug() << "ERROR::ParaTreeViewController::getParaTreeModelAccordingToId()::para_tree_id out of range";
            return nullptr;
        }
        return tree_models[para_tree_id];
    }

// ！！！！！注意：topomodel的根节点也需要对应的para tree model----这里一定是topo对应的paratreemodel，不是world对应的
    auto ParaTreeViewController::getIDAccordingToIndex(QModelIndex index) -> int
    {
        auto topo_tree_node = static_cast<TopoTreeNode*>(index.internalPointer());
        auto para_tree_model = topo_tree_node->getParaTreeModel();
        
        //qDebug()<<"para_tree_model_cnt = "<<getParaTreeModelCnt();
        //qDebug() <<"para tree model[6] = "<<getTreeModel(6);
        //qDebug() <<"topo_tree_node: "<<topo_tree_node->data(0).toString() <<" "<<topo_tree_node->data(1).toString();
        int para_tree_model_cnt = tree_models.size();
        for(int i=0;i<para_tree_model_cnt; ++i)
        {
            //qDebug()<<"pointer: "<<topo_tree_node->getParaTreeModel().get()<<" "<<tree_models.at(i).get();
            //qDebug()<<"pointer: "<<para_tree_model->getLabelTxt()<<" "<<tree_models[i]->getLabelTxt();

            if(para_tree_model.get() == tree_models.at(i).get())
            {
                //qDebug()<<"pointer: "<<para_tree_model.get()<<" "<<tree_models.at(i).get();
                return i;
            }

        }
        qDebug()<<"ERROR::ParaTreeViewController::getIDAccordingToIndex()<<do not have this index";
        return -1;
        //return 6;
    }


    void ParaTreeViewController::printInfo(int para_tree_id, QModelIndex index)
    {
        auto para_tree_model = getParaTreeModelAccordingToId(para_tree_id);
        para_tree_model->printIndexInfo(index);
    }

} // namespace solar
                  