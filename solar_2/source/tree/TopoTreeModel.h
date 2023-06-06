
#ifndef TOPOTREEMODEL_H
#define TOPOTREEMODEL_H

#include <QAbstractItemModel>
#include <QObject>

#include "tree/TopoTreeNode.h"

namespace solar
{

    class TopoTreeModel : public QAbstractItemModel
    {
            Q_OBJECT

            enum nodeRoles
            {
                NAME = Qt::UserRole + 1,
                TYPE
            };

        public:
            explicit TopoTreeModel(QObject* parent = nullptr);
            ~TopoTreeModel();

            void appendChild(const QModelIndex& index, const QList<QVariant>& data_list, int count,QSharedPointer<ParaTreeModel> &para_tree_model);
            bool appendChild(const QModelIndex& index, int type, int count, QSharedPointer<ParaTreeModel> &para_tree_model);
            void setNodeName(const QString& append_name, QModelIndex index);

            [[nodiscard]] auto columnCount(const QModelIndex& parent = QModelIndex()) const -> int override;
            [[nodiscard]] auto rowCount(const QModelIndex& parent = QModelIndex()) const -> int override;
            [[nodiscard]] auto roleNames() const -> QHash<int, QByteArray> override;
            [[nodiscard]] auto data(const QModelIndex& index, int role) const -> QVariant override;
            [[nodiscard]] auto flags(const QModelIndex& index) const -> Qt::ItemFlags override;
            [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
            [[nodiscard]] auto parent(const QModelIndex& index) const -> QModelIndex override;

            // 获取该项对应的类型的图片名
            [[nodiscard]] auto getType(const QModelIndex& index) const -> QString;
            // 返回总共的节点数--遍历一下树
            [[nodiscard]] auto getTotalNodeCnt() const -> qsizetype;

            //获得根节点的para_tree_model
            auto getParaTreeModelAboutFirstNode() ->QSharedPointer<ParaTreeModel> ;

        private:

            // appendChild中调用，返回与父节点下的兄弟节点都不同的name
            QString getUniqueName(TopoTreeNode* parent_node,int type);   

            // 在appendChild中调用，在添加新的孩子节点时，生成ParaTreeModel
            void createParaTreeModel(int type, QSharedPointer<ParaTreeModel> &para_tree_model);    


        private:
            QSharedPointer<TopoTreeNode> root_node;
            QHash<int, QByteArray> role_names_;         // 即roleNames

    };

} // namespace solar

#endif // TOPOTREEMODEL_H
