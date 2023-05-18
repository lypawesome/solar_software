
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

            void appendChild(const QModelIndex& index, const QList<QVariant>& data_list, int count);
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

        private:
            QSharedPointer<TopoTreeNode> root_node;
            QHash<int, QByteArray> role_names_;
    };

} // namespace solar

#endif // TOPOTREEMODEL_H
