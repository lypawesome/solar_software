#ifndef TREEVIEWCONTROLLER_H
#define TREEVIEWCONTROLLER_H


#include<QObject>
#include"TreeModel.h"

class TreeViewController : public QObject
{
    Q_OBJECT
public:
    TreeViewController(QObject *parent=nullptr);
    ~TreeViewController();

public:
    Q_INVOKABLE QAbstractItemModel* getTreeModel();
    Q_INVOKABLE void updatePara(const QModelIndex& index, QVariant value);  //更新para，存到sun里面
    Q_INVOKABLE void test();                                    //测试是否可以被qml调用

    Q_INVOKABLE bool iseditable(const QModelIndex& index);      //判断index这一节点是否可编辑
    Q_INVOKABLE bool isoptional(const QModelIndex& index);      //判断index这一节点是否有选项
    Q_INVOKABLE QStringList getOptionList(const QModelIndex& index); //获取idnex这一节点的所有选项的string列表
    Q_INVOKABLE void makeChoice(const QModelIndex& index, QString option);      //做出选择
    Q_INVOKABLE QString getPara(const QModelIndex& index);      //获取当前参数
private:
    TreeModel* treemodel;
};

#endif // TREEVIEWCONTROLLER_H
