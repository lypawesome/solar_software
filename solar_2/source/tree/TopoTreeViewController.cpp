
#include "tree/TopoTreeViewController.h"
//#include <qtypes.h>

namespace solar
{

    TopoTreeViewController::TopoTreeViewController(QObject* parent) : QObject(parent)
    {
        tree_model = QSharedPointer<TopoTreeModel>(new TopoTreeModel);
    }

    TopoTreeViewController::~TopoTreeViewController() = default;

    auto TopoTreeViewController::getTreeModel() -> QAbstractItemModel* { return tree_model.get(); }

    void TopoTreeViewController::updateNodeName(const QModelIndex& index, const QVariant& new_name)
    {
        tree_model->setNodeName(new_name.toString(), index);
    }

    // !!!可能要删去
    void TopoTreeViewController::updateNode(const QModelIndex& index) 
    {
        // QList<QVariant> list_sc;
        // list_sc.append(QString::fromLocal8Bit("sichuan"));
        // tree_model->appendChild(index, list_sc, 0);

        // QList<QVariant> list_bj;
        // list_bj.append(QString::fromLocal8Bit("beijing"));
        // tree_model->appendChild(index, list_bj, 1);
    }

    //！！！已经在qml中写了图片名，这个函数可以删去
    auto TopoTreeViewController::getImageName(const QModelIndex& index) -> QString // 可能要删去
    {
        return tree_model->getType(index); // type标记图片名称
    }

    /*
    注意这里，不是所有的添加孩子节点的操作都可以进行
    ！！！只能在node节点下添加其他的节点，在shape、tracker、array下不能添加节点
    ！！！注意名字的添加，同一个父亲节点下，不能重名，需要添加后缀
    */
    void TopoTreeViewController::appendChild(const QModelIndex& index, int type)
    {
        qDebug()<<"--1";
        QSharedPointer<ParaTreeModel> para_tree_model;
        bool ret = tree_model->appendChild(index, type, 1,para_tree_model);
        qDebug()<<"--2";

        if(ret)
        {
            qDebug()<<"--3";
            para_tree_control->addParaTreeModel(para_tree_model);
            qDebug()<<"--4";
        }
        emit para_tree_control->paraTreeCntChanged();       //信号
    }

    auto TopoTreeViewController::getTotalNodeCnt() -> qsizetype { return tree_model->getTotalNodeCnt(); }

    // 存一个指针
    void TopoTreeViewController::setParaTreeController(const QSharedPointer<ParaTreeViewController> para_tree_control)
    {
        this->para_tree_control = para_tree_control;
        auto para_tree_model = tree_model->getParaTreeModelAboutFirstNode();
        this->para_tree_control->addParaTreeModel(para_tree_model);
        // qDebug() <<"================root_node_para_tree = "<<para_tree_model.get();
        // qDebug() <<"==================para tree cnt = "<< this->para_tree_control->getParaTreeModelCnt();
        // qDebug() <<"==================para tree[6] = "<< this->para_tree_control->getTreeModel(6);
    
    }

    // auto TopoTreeViewController::getParaTreeModelAboutRootNode() -> QSharedPointer<ParaTreeModel>
    // {
    //     return tree_model->getParaTreeModelAboutRootNode();
    // }

} // namespace solar
