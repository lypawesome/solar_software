
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

#include "scene/Air.h"
#include "scene/Terrain.h"
#include "scene/Camera.h"
#include "scene/Cloud.h"
#include "scene/Node.h"
#include "scene/Heliostat.h"
#include "scene/Receiver.h"
#include "scene/Ordinary.h"

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
        HELIOSTAT,
        RECEIVER,
        ORDINARY// 右下角，scenePara设置部分
    };

    class ParaTreeModel : public QAbstractItemModel
    {
            Q_OBJECT

            enum nodeRoles
            {
                NAME = Qt::UserRole + 1,
                PARA,
                
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

            // 需要实现的虚函数
            bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
            bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

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

            // 设置/获得paratreemodel的label属性
            void setLabelTxt(QString label_txt);
            QString getLabelTxt();  

            //----------------用于测试-----------------------
            void printIndexInfo(QModelIndex index);
            

            // 建立参数----这部分也可能会更改
        private:
            // 建立的新节点：data1：name，data2：para
            // 建立节点，若parent_state为OPTIONAL，则新创立的节点放到parent节点的option_childnodes[parent_option]列表内，
            // 若同时is_current_option_child为true，则把心窗里的节点放在option_childnodes下的同时，也放到child_nodes下
            // 注意：parent_state是通过parent->getState()获得的
            // ！！！！既然不用枚举，那么data3也就没必要放了！！！！！
            // ！！！！更改8
            auto createNode(const QSharedPointer<ParaTreeNode>& parent, const QVariant& data1,
                            const QVariant& data2, 
                            ParaState state = QUIET, bool is_current_option_child = false,
                            const QString& parent_option = "") -> QSharedPointer<ParaTreeNode>;
            // // 初始化节点的
            // void initNodeOptions(QList<QString> options);
            void buildSunTreeModel(const QSharedPointer<Sun>& sun);
            void buildLocationTreeModel(const QSharedPointer<Location>& location);
            void buildAirTreeModel(QSharedPointer<Air> air);
            void buildTerrainTreeModel(QSharedPointer<Terrain> terrain);
            void buildCameraTreeModel(QSharedPointer<Camera> camera);
            void buildCloudTreeModel(QSharedPointer<Cloud> cloud);
            void buildNodeTreeModel(QSharedPointer<Node> node);
            void buildHeliostatTreeModel(QSharedPointer<Heliostat> heliostat);
            void buildReceiverTreeModel(QSharedPointer<Receiver> receiver);
            void buildOrdinaryTreeModel(QSharedPointer<Ordinary> ordinary);

            // 更新para中的某个属性
            void updatePara(QModelIndex index, QVariant value);
            void updataSunPara(QModelIndex index, QVariant value);
            void updataLocationPara(QModelIndex index, QVariant value);
            void updataAirPara(QModelIndex index, QVariant value);
            void updataCameraPara(QModelIndex index, QVariant value);
            void updataTerrainPara(QModelIndex index, QVariant value);
            void updataCloudPara(QModelIndex index, QVariant value);
            void updataNodePara(QModelIndex index, QVariant value);
            void updataHeliostatPara(QModelIndex index, QVariant value);
            void updataReceiverPara(QModelIndex index, QVariant value);
            void updataOrdinaryPara(QModelIndex index, QVariant value);


            QSharedPointer<ParaTreeNode> root_node; // 树状视图中的根节点

            TreeModelType model_type;
            QSharedPointer<Para> para;

            QString label_txt;      //存储右下方树状结构的名字，即label的内容
            QHash<int, QByteArray> role_names_;     // 即roleNames
            

            // ！！！！！！！！！！先这样写着
            std::unordered_set<std::string> sun_position_keys = {"azimuth", "elevation", "irradiance", "trackable"};
    };

} // namespace solar

#endif // PARATREEMODEL_H
