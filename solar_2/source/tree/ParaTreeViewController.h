
#ifndef PARATREEVIEWCONTROLLER_H
#define PARATREEVIEWCONTROLLER_H

/*
 * 这里，因为下方参数设置的部分有好几个树状视图，因此与TopoTreeViewController不同
 *      用一个QList存若干个ParaTreeModel，并且存到TopoTreeNode或者TopoTreeModel一个指针，
 *      一旦Topo中新增加了节点，就在这里新增加一个ParaTreeModel
 *      或者，每个TopoNode都存一个对应的ParaModel
 *      只要能找到TopoNode和ParaModel即可
 */

#include "tree/ParaTreeModel.h"

namespace solar
{

    class ParaTreeViewController : public QObject
    {
            Q_OBJECT
        public:
            ParaTreeViewController(QObject* parent = nullptr);
            ~ParaTreeViewController();

            // 供cpp调用

            // 添加paratreemodel，自己新建一个指针
            void addParaTreeModel(TreeModelType model_type, const QSharedPointer<Para>& para);
            // 添加para
            void addParaTreeModel(const QSharedPointer<ParaTreeModel>& para_tree_model);
            // 移除paratreemodel
            void removeParaTreeModel(int para_tree_id);
            // 按照指针移除
            void removeParaTreeModel(const QSharedPointer<ParaTreeModel>& para_tree);
            // 看这个paratreemodel在tree_models中第几项
            auto getParaTreeModelId(const  QSharedPointer<ParaTreeModel>& para_tree_model) -> qsizetype;

        public slots: // 槽函数，被qml调用
            Q_INVOKABLE auto getTreeModel(int para_tree_id) -> QAbstractItemModel*;
            // 更新para，默认是第1列------!!!!不要忘记更新para中的内容
            Q_INVOKABLE void updateNodePara(int para_tree_id, const QModelIndex& index,
                                            const QVariant& value);
            // 测试是否可以被qml调用
            Q_INVOKABLE static void test();
            // 判断index这一节点是否可编辑
            Q_INVOKABLE auto isEditable(int para_tree_id, const QModelIndex& index) -> bool;
            // 判断index这一节点是否有选项
            Q_INVOKABLE auto isOptional(int para_tree_id, const QModelIndex& index) -> bool;
            // 获取index这一节点的所有选项的string列表
            Q_INVOKABLE auto getOptionList(int para_tree_id, const QModelIndex& index) -> QStringList;
            // 做出选择
            // ！！！！！！！updateNodePara已经实现了这一功能，可以删去
            Q_INVOKABLE void makeChoice(int para_tree_id, const QModelIndex& index, QString option);

            Q_INVOKABLE auto getPara(int para_tree_id,
                                        const QModelIndex& index) -> QString; // ！！！！这个可能会删掉
            // index是optional，返回其当前选中的选项在选项列表中的次序
            Q_INVOKABLE auto getCurrentOptionId(int para_tree_id, const QModelIndex& index) -> int;

        private:
            QList<QSharedPointer<ParaTreeModel>> tree_models;
    };

} // namespace solar

#endif // PARATREEVIEWCONTROLLER_H
