import QtQuick
import QtQuick.Controls

/*
！！！！这里要全部更改
不用style，改用delegate

*/

Rectangle{
    id:topoTreeview_rect
    anchors.fill: parent

    required property var treeModel
    signal updateTopoSelection(int index)
    //property alias selFun: updateSelection()
    //property alias sel: sel
    //property var treeModel: mControl.getTreeModel()         //cpp把模型传到这一参数中

    function updateSelection(index)
    {
        if(topo_sel.currentHasSelection){
           topoControl.appendChild(topo_sel.currentIndex,index)
            //！！！这里这句代码，不起作用
           topoTreeview.expandToIndex(topo_sel.currentIndex)    //添加孩子节点后，要把父节点展开
        }
        else{
            console.log("no selection")
        }
    }

    ItemSelectionModel{     //添加自定义选中
        id:topo_sel
        model:topoTreeview_rect.treeModel
        property bool currentHasSelection: false     //是否有选中的项---一开始是没有的点击之后才有


    }

//    signal updateTopoSelection(int index)
//    onUpdateTopoSelection:{
//        if(sel.currentHasSelection){
//            topoControl.appendChild(sel.currentIndex,index)
//            topo_treeview.expand(sel.currentIndex)    //添加孩子节点后，要把父节点展开
//        }
//        else{
//            console.log("no selection")
//        }
//    }

    TreeView{
        id: topoTreeview
        anchors.fill: parent

        //headerVisible: false;
        //backgroundVisible: false

        //style: topo_treeview_style            //还没写
        model:topoTreeview_rect.treeModel



        selectionModel: topo_sel
        //delegate: treeview_item_delegate

//        delegate: TreeViewDelegate{
//            id: treeview_item_delegate
//            //model:topoTreeview.model


//            required property TreeView treeView
//            required property bool isTreeNode
//            required property bool expanded
//            required property int hasChildren
//            required property int depth
//            required property bool editing

//            indicator:Item{
//                x: leftMargin + (depth*indentation)
//            }

//            contentItem: Rectangle{
//                height:20
//                width:parent.width
//                color:"red"
//                Text{
//                    //text: model.name
//                }
//            }
//            background:Rectangle{
//                anchors.fill: parent
//                color: "blue"
//            }
//        }




        delegate: Item{
            id: root

            implicitWidth: parent.width>0 ? parent.width: 200
            implicitHeight:30

            readonly property real indent: 20
            readonly property real padding: 2

            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded
            required property int hasChildren
            required property int depth
            required property int column        //这里有疑问的是，究竟有哪些required属性可以用？

            visible: column===0? true:false     //！！！因为定义了两个参数，所以为两列，把第二列设为不可见即可

            //鼠标点击
            //这部分在mousearea里放了，不需要再写
//            TapHandler{
//                onTapped: treeView.toggleExpanded(row)
//                //sel.SelectCurrent
//            }

            Rectangle{
                id: topoTreeviewItem_rect
                anchors.fill:parent
                anchors.leftMargin: 5
                color: topo_sel.currentIndex===topoTreeview.index(row,column)?"skyblue" :
                                           (topoTreeviewItem_mousearea.containsMouse?"lightgray":"transparent")

                property var indicatorsrc:["arrow_down.png", "arrow_right.png"]
                Image{
                    id: indicator
                    anchors.verticalCenter: parent.verticalCenter
                    visible: root.isTreeNode&& root.hasChildren
                    x:padding + (root.depth * root.indent)
                    width: 15
                    height: 15
                    source: "qrc:/image/indicator_icon/"
                            + (root.expanded ? topoTreeviewItem_rect.indicatorsrc[0]:topoTreeviewItem_rect.indicatorsrc[1])

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            treeView.toggleExpanded(row)
                        }
                    }
                }

                Rectangle{
                    id: topoTreeviewItem_rightrect
                    anchors.left: indicator.right
                    anchors.right:parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    color: "transparent"

                    property var imgsrc:["node.png","shape.png","tracker.png","array.png"]
                    Image{
                        id: img
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        width:20
                        height:20
                        source: "qrc:/image/settings_icon/" + topoTreeviewItem_rightrect.imgsrc[model.type]
                    }

                    Text{
                        id:label
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: img.right
                        anchors.right: parent.right
                        anchors.leftMargin: 5
                        //width:root.width - root.padding - x
                        clip: true
                        text: model.name
                    }

                    MouseArea{
                        id: topoTreeviewItem_mousearea
                        anchors.fill: parent
                        hoverEnabled:true

                        onClicked: {
                            topo_sel.setCurrentIndex(topoTreeview.index(row,column),0x0010)
                            topo_sel.currentHasSelection= true

                            console.log(row+" "+column+" "+label.text)
                        }
                    }

                }


            }

        }


        Component.onCompleted: {
            console.log(topoTreeview.columns+"  "+topoTreeview.rows)
        }


//        itemDelegate:Rectangle{
//            id:topo_treeview_item_rect

//            color: styleData.selected ? "lightgreen" : (topo_treeview_item_mousearea.containsMouse?"lightgray":"transparent")

//            Image{
//                id:topo_treeview_item_img
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.left:parent.left
//                anchors.leftMargin:5
//                source:"./settings_icon/" + mControl.getImageName(styleData.index)
//                width:10
//                height:10
//            }

//            //这里或许应该改为EditText
//            Text{
//                id:topo_treeview_item_text
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.left:topo_treeview_item_img.right
//                anchors.leftMargin: 5
//                text: styleData.value
//                font.pointSize: 10
//                elide:styleData.elideMode
//            }
//            Drag.active:topo_treeview_item_mousearea.drag.active
//            Drag.dragType: Drag.Automatic;      //选择自动开始拖动
//            Drag.supportedActions: Qt.CopyAction;   //选择复制数据到DropArea
//            Drag.onDragFinished: {              //拖拽结束

//            }

//            MouseArea{
//                id:topo_treeview_item_mousearea
//                anchors.fill:parent

//                hoverEnabled: true
//                acceptedButtons: Qt.LeftButton
//                drag.target: topo_treeview_item_text

//                onClicked: {        //单击：选中当前节点
//                    sel.setCurrentIndex(styleData.index,0x0010)
//                    sel.currentHasSelection = true
//                    //emit: sel.selectionChanged()
//                    console.log("click treeview: "+topo_treeview_item_text.text)
//                }
//                onDoubleClicked: {      //双击：刷新子节点
//                    scene_settings_treeview.collapse(styleData.index)
//                    //mControl.updateNode(styleData.index)
//                    scene_settings_treeview.expand(styleData.index)
//                }
//            }

//        }

//        Component{
//            id: topo_treeview_style
//            TreeViewStyle{
//                padding.left:2
//                padding.right:2
//                indentation: 10     //节点间的缩进

//                rowDelegate: Rectangle {    //这里要改!!!!
//                    //color:styleData.selected ? "blue":"red"
//                    height:15
//                }
//                branchDelegate: Image{      //节点展开、收缩的图标
//                    id: topo_treeview_style_branch_icon
//                    source: {
//                        return styleData.isExpanded ? "./tiny_icon/arrow_down.png" : "./tiny_icon/arrow_right.png"

//                    }
//                    width:10
//                    height:10
//                    MouseArea {
//                        id:topo_treeview_style_branch_mousearea
//                        anchors.fill: parent
//                        hoverEnabled: true
//                        drag.target: topo_treeview_style_branch_icon

//                        //property bool isExpand: true        //这一部分的点击逻辑是否可以更改？？？
//                        onClicked: {
//                            /*
//                            if(isExpand){
//                                emit: scene_settings_treeview.expand(styleData.index)
//                                isExpand = false
//                            }
//                            else{
//                                emit: scene_settings_treeview.collapse(styleData.index)
//                                isExpand = true
//                            }
//                            */
//                            if(styleData.isExpanded)
//                            {
//                                topo_treeview.collapse(styleData.index)
//                            }
//                            else{
//                                topo_treeview.expand(styleData.index)
//                            }

//                        }
//                    }
//                }
//            }
//        }







    }

}
