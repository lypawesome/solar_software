
#ifndef PARATREEVIEWCONTROLLER_H
#define PARATREEVIEWCONTROLLER_H


#include "ParaTreeModel.h"


namespace solar{

    class ParaTreeViewController : public QObject
    {
    public:
        ParaTreeViewController(TreeModelType model_type,
                               QSharedPointer<Para> para,
                               QObject* parent = nullptr);
        ~ParaTreeViewController();

    public:
        Q_INVOKABLE QAbstractItemModel* getTreeModel();
        Q_INVOKABLE void updateNodePara(const QModelIndex& index,
                                        const QVariant& value); // 更新para，默认是第1列------!!!!不要忘记更新para中的内容
        Q_INVOKABLE void test(); // 测试是否可以被qml调用

        Q_INVOKABLE bool isEditable(const QModelIndex& index); // 判断index这一节点是否可编辑
        Q_INVOKABLE bool isOptional(const QModelIndex& index); // 判断index这一节点是否有选项
        Q_INVOKABLE QStringList getOptionList(const QModelIndex& index); // 获取idnex这一节点的所有选项的string列表
        Q_INVOKABLE void makeChoice(const QModelIndex& index, QString option); // 做出选择
        Q_INVOKABLE QString getPara(const QModelIndex& index);           // ！！！！这个可能会删掉


    private:
        QSharedPointer<ParaTreeModel> tree_model;
    };

} // namespace solar


#endif // PARATREEVIEWCONTROLLER_H
