#include "TreeViewController.h"

namespace solar
{
    TreeViewController::TreeViewController(QObject* parent) : QObject(parent)
    {
        treemodel = new TreeModel();
        Sun* sun = new Sun();
        m_TreeModel->buildSunTreeModel(sun);
    }

    TreeViewController::~TreeViewController() { delete m_TreeModel; }

    QAbstractItemModel* ParaTreeViewController::getTreeModel()
    {
        return m_TreeModel;
    }

    void
    ParaTreeViewController::updatePara(const QModelIndex& index,
                                       QVariant value) // 更新para，存到sun里面
    {
        qDebug() << "click paratreeviewcontroller: "
                 << m_TreeModel->getNodeColumn(index, 0) << ": "
                 << value.toString();
        m_TreeModel->setNodeColumn(index, value.toString(), 1); // para是第1列
    }
    void ParaTreeViewController::test() // 测试是否可以被qml调用
    {
        qDebug() << "ParaTreeViewController is used";
    }
    bool ParaTreeViewController::iseditable(
        const QModelIndex& index) // 判断index这一节点是否可编辑
    {
        return m_TreeModel->isNodeEditable(index);
    }
    bool ParaTreeViewController::isoptional(
        const QModelIndex& index) // 判断index这一节点是否有选项
    {
        return m_TreeModel->isNodeOptional(index);
    }

    QStringList ParaTreeViewController::getOptionList(
        const QModelIndex& index) // 获取idnex这一节点的所有选项的string列表
    {
        QList<QString> dataList = m_TreeModel->getNodeOptionList(index);
        QStringList modelList;
        for (int i = 0; i < dataList.size(); i++)
            modelList.append(dataList.value(i));
        return modelList;
    }
    void ParaTreeViewController::makeChoice(const QModelIndex& index,
                                            QString option)
    {
        m_TreeModel->makeChoice(index, option);
    }
    QString ParaTreeViewController::getPara(const QModelIndex& index)
    {
        return m_TreeModel->getNodeColumn(index, 1);
    }

} // namespace solar
