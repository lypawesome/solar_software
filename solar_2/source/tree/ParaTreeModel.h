
#ifndef PARATREEMODEL_H
#define PARATREEMODEL_H

/*
    右下角的树状视图
    每个node存三个属性：name名字，para参数，type_id参数类型的枚举值
*/

#include <QAbstractItemModel>
#include <QObject>

#include <unordered_set>

#include "scene/Location.h"
#include "scene/Sun.h"
#include "tree/ParaTreeNode.h"
#include "utils/Para.h"
#include "utils/Utils.h"

namespace solar
{

    enum TreeModelType
    {
        LOCATION,
        SUN,
        AIR,
        TERRAIN,
        CAMERA,
        CLOUD, // 右下角，worldPara设置部分
        NODE,
        SHAPE,
        TRACKER,
        ARRAY // 右下角，scenePara设置部分
    };

    class ParaTreeModel : public QAbstractItemModel
    {
            Q_OBJECT
            enum nodeRoles
            {
                NAME = Qt::UserRole + 1,
                PARA,
                TYPE_ID // 表示每个参数的类型
            };

        public:
            ParaTreeModel(TreeModelType _model_type, QSharedPointer<Para> _para = nullptr,
                          QObject* parent = nullptr);
            ~ParaTreeModel() override;

            [[nodiscard]] auto columnCount(const QModelIndex& parent = QModelIndex()) const
                -> int override;
            [[nodiscard]] auto rowCount(const QModelIndex& parent = QModelIndex()) const
                -> int override;
            [[nodiscard]] auto roleNames() const -> QHash<int, QByteArray> override;
            [[nodiscard]] auto data(const QModelIndex& index, int role) const -> QVariant override;
            [[nodiscard]] auto flags(const QModelIndex& index) const -> Qt::ItemFlags override;
            [[nodiscard]] auto index(int row, int column,
                                     const QModelIndex& parent = QModelIndex()) const
                -> QModelIndex override;
            [[nodiscard]] auto parent(const QModelIndex& index) const -> QModelIndex override;

            [[nodiscard]] auto getRootNode() const -> QSharedPointer<ParaTreeNode>;

            // 右下角的视图，只需要编辑、选择，不需要增加/删除节点
            //        void appendChild(const QModelIndex& index, QList<QVariant> dataList,
            //                         int count);
            //        void appendChild(const QModelIndex& index,
            //                         QList<QSharedPointer<ParaTreeNode>> childNodes,
            //                         int count); // 添加一系列孩子
            // 设置index这一节点的属性数据为value
            void setNodePara(QModelIndex index, QVariant value);
            // 获取index这一节点的para数据,注意这里一直返回string
            static auto getNodePara(const QModelIndex& index) -> QString;

            static auto isNodeEditable(const QModelIndex& index) -> bool;
            static auto isNodeOptional(const QModelIndex& index) -> bool;
            // 获得这一节点的所有option
            static auto getNodeOptionList(const QModelIndex& index) -> QList<QString>;
            // 做出选择
            void makeChoice(const QModelIndex& index, const QString& option);

            // 返回对应的节点中，当前选中的选项在选项列表中的下标
            static auto getCurrentOptionId(const QModelIndex& index) -> int;

            // 建立参数----这部分也可能会更改
        private:
            // 建立的新节点：data1：name，data2：para，data3：type_id
            // 建立节点，若parent_state为OPTIONAL，则新创立的节点放到parent节点的option_childnodes[parent_option]列表内，
            // 若同时is_current_option_child为true，则把心窗里的节点放在option_childnodes下的同时，也放到child_nodes下
            // 注意：parent_state是通过parent->getState()获得的
            auto createNode(const QSharedPointer<ParaTreeNode>& parent, const QVariant& data1,
                            const QVariant& data2, const QVariant& data3 = kNothing,
                            ParaState state = QUIET, bool is_current_option_child = false,
                            const QString& parent_option = "") -> QSharedPointer<ParaTreeNode>;
            void buildSunTreeModel(const QSharedPointer<Sun>& sun);
            void buildLocationTreeModel(const QSharedPointer<Location>& location);
            // 更新para中的某个属性
            void updatePara();
            // 当model_type为SUN时，更新属性
            void updataSunPara();

            QSharedPointer<ParaTreeNode> root_node; // 树状视图中的根节点

            TreeModelType model_type;
            QSharedPointer<Para> para;

            QHash<int, QByteArray> role_names_;
            std::unordered_set<std::string> sun_position_keys = {"azimuth", "elevation", "irradiance", "trackable"};
    };

} // namespace solar

#endif // PARATREEMODEL_H
