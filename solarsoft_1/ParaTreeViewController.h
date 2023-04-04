#ifndef PARATREEVIEWCONTROLLER_H
#define PARATREEVIEWCONTROLLER_H

/*
 * 控制右下方部分的参数设置的树状结构
 * 包括location、sun、air、camera、terrain、cloud以及node、shape、tracker、array等
 * 不用添加子节点，只需要进行编辑（更改孩子节点的属性）、进行选择（更改节点的孩子节点列表）
*/
#include"TreeModel.h"

class ParaTreeViewController : public QObject
{
public:
    ParaTreeViewController(int model_type, Para* object,QObject *parent = nullptr);     //这里要用一下Para
    ~ParaTreeViewController();

public:
    Q_INVOKABLE QAbstractItemModel* getTreeModel();
    Q_INVOKABLE void updateNodeData(const QModelIndex& index, int column, const QVariant& value );     //更新para，存到sun里面
    Q_INVOKABLE void test();   //测试是否可以被qml调用

    Q_INVOKABLE bool iseditable(const QModelIndex& index);      //判断index这一节点是否可编辑
    Q_INVOKABLE bool isoptional(const QModelIndex& index);      //判断index这一节点是否有选项
    Q_INVOKABLE QStringList getOptionList(const QModelIndex& index); //获取idnex这一节点的所有选项的string列表
    Q_INVOKABLE void makeChoice(const QModelIndex& index, QString option);      //做出选择
    Q_INVOKABLE QString getPara(const QModelIndex& index);      //获取当前参数

private:
    TreeModel* tree_model;

};

#endif // PARATREEVIEWCONTROLLER_H
