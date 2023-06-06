
#ifndef PARATREEVIEWCONTROLLER_H
#define PARATREEVIEWCONTROLLER_H

/*
 * 这里，因为下方参数设置的部分有好几个树状视图，因此与TopoTreeViewController不同
 *      用一个QList存若干个ParaTreeModel，并且存到TopoTreeNode或者TopoTreeModel一个指针，
 *      一旦Topo中新增加了节点，就在这里新增加一个ParaTreeModel
 *      或者，每个TopoNode都存一个对应的ParaModel
 *      只要能找到TopoNode和ParaModel即可
 * 
 * 
 * !!!!!!这部分要大改！！！！
 * 
 * 依然是按照ID来分别存world和topo对应的para tree model
 * world对应的para model的ID是0-5（总共6个）
 * topo对应的para model用QHash来存(QModelIndex,paramodel)对，同时用List存QModelIndex
 */

#include "tree/ParaTreeModel.h"
#include "tree/TopoTreeNode.h"

namespace solar
{

    
    class ParaTreeViewController : public QObject
    {
            Q_OBJECT

            
        public:
            ParaTreeViewController(QObject* parent = nullptr);
            ~ParaTreeViewController();

            // 供cpp调用

            
            // 添加paratreemodel
            void addParaTreeModel(TreeModelType model_type, const QSharedPointer<Para>& para);
            // 添加para
            void addParaTreeModel(const QSharedPointer<ParaTreeModel>& para_tree_model);
            // // 移除paratreemodel
            void removeParaTreeModel(int para_tree_id);
            // // 按照指针移除
            void removeParaTreeModel(const QSharedPointer<ParaTreeModel>& para_tree);
            // // 看这个paratreemodel在tree_models中第几项
            auto getParaTreeModelId(const  QSharedPointer<ParaTreeModel>& para_tree_model) -> qsizetype;


            // 定义宏
            Q_PROPERTY(int para_cnt READ getParaTreeModelCnt NOTIFY paraTreeCntChanged)

            signals:
            void paraTreeCntChanged();

        public slots: // 槽函数，被qml调用

            // 根据id返回treemodel，用于UI层调用
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


            
            // 返回总有多少个ParaTreeModel：world和topo对应的model加在一起
            Q_INVOKABLE auto getParaTreeModelCnt() ->int ;
            // // 返回有多少个tree_model_about_world
            // Q_INVOKABLE auto getParaTreeModelAboutWorldCnt() ->int ;
            // // 返回有多少个tree_model_about_topo
            // Q_INVOKABLE auto getParaTreeModelAboutTopoCnt() ->int ;
            // 返回label中的内容
            Q_INVOKABLE auto getLabelTxt(int para_tree_id) -> QString;
            // 根据index返回对应的ID
            Q_INVOKABLE auto getIDAccordingToIndex(QModelIndex index) -> int ;

            //-------------用于测试--------------------
            Q_INVOKABLE void printInfo(int para_tree_id, QModelIndex index);


        private:
            // 根据id返回paratreemodel的智能指针
            auto getParaTreeModelAccordingToId(int para_tree_id) ->QSharedPointer<ParaTreeModel>;

        private:
            QList<QSharedPointer<ParaTreeModel>> tree_models;


            // world和topo部分对应的treemodel分开存
            // QList<QSharedPointer<ParaTreeModel>> tree_models_about_world;

            // // !!!!!!!!!!!!!!!!!!!!用index做hash不可行
            // // !!!!!!!!!!!!!!!!!!!!跟之前一样，直接存成一个QList？？不知是否可行
            // // 或者直接简单粗暴地给一个QHash<int,para_tree_model>

            // QHash<QModelIndex,QSharedPointer<ParaTreeModel>> tree_models_about_topo;

            // // 保存在TopoTreeModel中设置的节点，每个QModelIndex在QList中都有一个下标,下标用于qml中设置stackview
            // QList<QModelIndex> topo_model_index_list;   
    };

} // namespace solar

#endif // PARATREEVIEWCONTROLLER_H
