
#ifndef PARATREEVIEWCONTROLLER_H
#define PARATREEVIEWCONTROLLER_H

/*
 * 这里，因为下方参数设置的部分有好几个树状视图，因此与TopoTreeViewController不同
 *      用一个QList存若干个ParaTreeModel，并且存到TopoTreeNode或者TopoTreeModel一个指针，
 *      一旦Topo中新增加了节点，就在这里新增加一个ParaTreeModel
 *      或者，每个TopoNode都存一个对应的ParaModel
 *      只要能找到TopoNode和ParaModel即可
*/

#include "ParaTreeModel.h"


namespace solar{

    class ParaTreeViewController : public QObject
    {
        Q_OBJECT
    public:
        ParaTreeViewController(QObject* parent = nullptr);
        ~ParaTreeViewController();

    public:
        //供cpp调用
        void addParaTreeModel(TreeModelType model_type, QSharedPointer<Para> para); //添加paratreemodel，自己新建一个指针
        void addParaTreeModel(QSharedPointer<ParaTreeModel> para_tree_model);       //添加para
        void removeParaTreeModel(int para_tree_id);   //移除paratreemodel
        void removeParaTreeModel(QSharedPointer<ParaTreeModel> para_tree);  //按照指针移除
        int getParaTreeModelId(QSharedPointer<ParaTreeModel> para_tree_model); //看这个paratreemodel在tree_models中第几项


    public slots:   //槽函数，被qml调用
        Q_INVOKABLE QAbstractItemModel* getTreeModel(int para_tree_id);
        Q_INVOKABLE void updateNodePara(int para_tree_id, const QModelIndex& index,
                                        const QVariant& value); // 更新para，默认是第1列------!!!!不要忘记更新para中的内容
        Q_INVOKABLE void test(); // 测试是否可以被qml调用

        Q_INVOKABLE bool isEditable(int para_tree_id, const QModelIndex& index); // 判断index这一节点是否可编辑
        Q_INVOKABLE bool isOptional(int para_tree_id, const QModelIndex& index); // 判断index这一节点是否有选项
        Q_INVOKABLE QStringList getOptionList(int para_tree_id, const QModelIndex& index); // 获取idnex这一节点的所有选项的string列表
        Q_INVOKABLE void makeChoice(int para_tree_id, const QModelIndex& index, QString option); // 做出选择 ！！！！！！！updateNodePara已经实现了这一功能，可以删去
        Q_INVOKABLE QString getPara(int para_tree_id, const QModelIndex& index);           // ！！！！这个可能会删掉

        Q_INVOKABLE int getCurrentOptionId(int para_tree_id, const QModelIndex&index); //index是optional，返回其当前选中的选项在选项列表中的次序

    private:
        QList<QSharedPointer<ParaTreeModel> > tree_models;
    };

} // namespace solar


#endif // PARATREEVIEWCONTROLLER_H
