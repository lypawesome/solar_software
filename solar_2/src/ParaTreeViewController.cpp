
#include "ParaTreeViewController.h"

namespace solar{

ParaTreeViewController::ParaTreeViewController(TreeModelType model_type,
                       QSharedPointer<Para> para, QObject* parent )
{
    tree_model = QSharedPointer<ParaTreeModel>(new ParaTreeModel(model_type,parent,para));
}
ParaTreeViewController::~ParaTreeViewController()
{
}

QAbstractItemModel* ParaTreeViewController::getTreeModel()
{
    return tree_model.get();
}
void ParaTreeViewController::updateNodePara(const QModelIndex& index,
                                const QVariant& value) // 更新para，默认是第1列
{
    tree_model->setNodePara(index,value);   //如果节点是OPTIONAL,则要处理makechoice的代码
}
void ParaTreeViewController::test() // 测试是否可以被qml调用
{
    qDebug()<<"test ParaTreeViewController";
}
bool ParaTreeViewController::isEditable(const QModelIndex& index) // 判断index这一节点是否可编辑
{
    return tree_model->isNodeEditable(index);
}
bool ParaTreeViewController::isOptional(const QModelIndex& index) // 判断index这一节点是否有选项
{
    return tree_model->isNodeOptional(index);
}
QStringList ParaTreeViewController::getOptionList(const QModelIndex& index) // 获取idnex这一节点的所有选项的string列表
{
    QList<QString> data_list = tree_model->getNodeOptionList(index);
    QStringList model_list;
    for (int i = 0; i < data_list.size(); i++)
    {
        model_list.append(data_list.value(i));
    }
    return model_list;
}
void ParaTreeViewController::makeChoice(const QModelIndex& index, QString option) // 做出选择
{

}
QString ParaTreeViewController::getPara(const QModelIndex& index)           // ！！！！这个可能会删掉
{
    return tree_model->getNodePara(index);
}


} // namespace solar

