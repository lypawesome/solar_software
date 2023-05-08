
#ifndef TOPOTREEMODEL_H
#define TOPOTREEMODEL_H




#include <QAbstractItemModel>
#include <QObject>

#include "TopoTreeNode.h"

namespace solar{

class TopoTreeModel : public QAbstractItemModel
{
    Q_OBJECT

    enum nodeRoles {
        NAME = Qt::UserRole + 1,
        TYPE
    };

public:
    TopoTreeModel(QObject *parent = nullptr);
    ~TopoTreeModel();

    void appendChild(const QModelIndex& index, QList<QVariant> dataList, int count);
    void setNodeName(QString appendName, QModelIndex index);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;



    QString getType(const QModelIndex& index);          //获取该项对应的类型的图片名
    int getTotalNodeCnt();      //返回总共的节点数--遍历一下树

private:
    QSharedPointer<TopoTreeNode> root_node;
};


}//namespace solar

#endif // TOPOTREEMODEL_H
