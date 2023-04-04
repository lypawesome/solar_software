import QtQuick 2.15
import QtQuick.Controls 2.15

import QtQuick.Controls 1.4 as Controls_1_4         //用于实现treeview
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.15

Rectangle{
    id:topo_treeview_root
    anchors.fill: parent

    required property var treeModel
    signal updateTopoSelection(int index)
    //property alias selFun: updateSelection()
    //property alias sel: sel
    //property var treeModel: mControl.getTreeModel()         //cpp把模型传到这一参数中

    function updateSelection(index)
    {
        if(sel.currentHasSelection){
           mControl.appendChild(sel.currentIndex,index)
           topo_treeview.expand(sel.currentIndex)    //添加孩子节点后，要把父节点展开
        }
        else{
            console.log("no selection")
        }
    }

    ItemSelectionModel{     //添加自定义选中
        id:sel
        model:topo_treeview_root.treeModel
        property bool currentHasSelection: false     //是否有选中的项---一开始是没有的点击之后才有


    }
/*
    signal updateTopoSelection(int index)
    onUpdateTopoSelection:{
        if(sel.currentHasSelection){
            mControl.appendChild(sel.currentIndex,index)
            topo_treeview.expand(sel.currentIndex)    //添加孩子节点后，要把父节点展开
        }
        else{
            console.log("no selection")
        }
    }
*/
    Controls_1_4.TreeView{
        id: topo_treeview
        anchors.fill:parent

        headerVisible: false;
        backgroundVisible: false

        style: topo_treeview_style            //还没写
        model:topo_treeview_root.treeModel
        selection: sel


        Controls_1_4.TableViewColumn{
            width: topo_treeview.width
            title:"Name"
            role:'name'
        }



        itemDelegate:Rectangle{
            id:topo_treeview_item_rect

            color: styleData.selected ? "lightgreen" : (topo_treeview_item_mousearea.containsMouse?"lightgray":"transparent")

            Image{
                id:topo_treeview_item_img
                anchors.verticalCenter: parent.verticalCenter
                anchors.left:parent.left
                anchors.leftMargin:5
                source:"./settings_icon/" + mControl.getImageName(styleData.index)
                width:10
                height:10
            }

            //这里或许应该改为EditText
            Text{
                id:topo_treeview_item_text
                anchors.verticalCenter: parent.verticalCenter
                anchors.left:topo_treeview_item_img.right
                anchors.leftMargin: 5
                text: styleData.value
                font.pointSize: 10
                elide:styleData.elideMode
            }
            Drag.active:topo_treeview_item_mousearea.drag.active
            Drag.dragType: Drag.Automatic;      //选择自动开始拖动
            Drag.supportedActions: Qt.CopyAction;   //选择复制数据到DropArea
            Drag.onDragFinished: {              //拖拽结束

            }

            MouseArea{
                id:topo_treeview_item_mousearea
                anchors.fill:parent

                hoverEnabled: true
                acceptedButtons: Qt.LeftButton
                drag.target: topo_treeview_item_text

                onClicked: {        //单击：选中当前节点
                    sel.setCurrentIndex(styleData.index,0x0010)
                    sel.currentHasSelection = true
                    //emit: sel.selectionChanged()
                    console.log("click treeview: "+topo_treeview_item_text.text)
                }
                onDoubleClicked: {      //双击：刷新子节点
                    scene_settings_treeview.collapse(styleData.index)
                    //mControl.updateNode(styleData.index)
                    scene_settings_treeview.expand(styleData.index)
                }
            }

        }

        Component{
            id: topo_treeview_style
            TreeViewStyle{
                padding.left:2
                padding.right:2
                indentation: 10     //节点间的缩进

                rowDelegate: Rectangle {    //这里要改!!!!
                    //color:styleData.selected ? "blue":"red"
                    height:15
                }
                branchDelegate: Image{      //节点展开、收缩的图标
                    id: topo_treeview_style_branch_icon
                    source: {
                        return styleData.isExpanded ? "./tiny_icon/arrow_down.png" : "./tiny_icon/arrow_right.png"

                    }
                    width:10
                    height:10
                    MouseArea {
                        id:topo_treeview_style_branch_mousearea
                        anchors.fill: parent
                        hoverEnabled: true
                        drag.target: topo_treeview_style_branch_icon

                        //property bool isExpand: true        //这一部分的点击逻辑是否可以更改？？？
                        onClicked: {
                            /*
                            if(isExpand){
                                emit: scene_settings_treeview.expand(styleData.index)
                                isExpand = false
                            }
                            else{
                                emit: scene_settings_treeview.collapse(styleData.index)
                                isExpand = true
                            }
                            */
                            if(styleData.isExpanded)
                            {
                                topo_treeview.collapse(styleData.index)
                            }
                            else{
                                topo_treeview.expand(styleData.index)
                            }

                        }
                    }
                }
            }
        }






    }

}
