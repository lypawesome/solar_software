import QtQuick
import QtQuick.Controls

/*
！！！！这里要全部更改
不用style，改用delegate

*/

Rectangle{
    id: topoTreeview_rect
    
    anchors.fill: parent
    
    // border.width: 2
    // border.color: "blue"

    required property var treeModel
    signal updateTopoSelection(int index)
    //property alias selFun: updateSelection()
    //property alias sel: sel
    //property var treeModel: mControl.getTreeModel()         //cpp把模型传到这一参数中

    function updateSelection(index)
    {
        console.log("------TopoTreeView-updateSelection")
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
        anchors.fill: topoTreeview_rect
        // anchors.top: topoTreeview_rect.top
        // anchors.bottom: topoTreeview_rect.bottom

        //headerVisible: false;
        //backgroundVisible: false

        //style: topo_treeview_style            //还没写
        model:topoTreeview_rect.treeModel
        // pointerNavigationEnabled: true
        // selectionBehavior: TableView.SelectRows
        boundsBehavior: Flickable.DragOverBounds        //flickable默认是软边界，这句代码取消轻弹功能，只允许滑动

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

        // onFlickStarted:{
        //     console.log("----------flicking-------------")
        //     console.log("flick_originX: "+topoTreeview.originX + 
        //             onFlickStarted:{
        //     console.log("----------flicking-------------")
        //     console.log("flick_originX: "+topoTreeview.originX + 
        //                 " flick_originY: "+topoTreeview.originY)
        //     console.log("treeview_width: "+topoTreeview.width + 
        //                 " treeview_height: "+topoTreeview.height)
        //     console.log("parent_width: "+topoTreeview_rect.width + 
        //                 " parent_height: "+topoTreeview_rect.height)
        //                 console.log("treeview.parent=" + topoTreeview.parent.id)
        // }    " flick_originY: "+topoTreeview.originY)
        //     console.log("treeview_width: "+topoTreeview.width + 
        //                 " treeview_height: "+topoTreeview.height)
        //     console.log("parent_width: "+topoTreeview_rect.width + 
        //                 " parent_height: "+topoTreeview_rect.height)
        //                 console.log("treeview.parent=" + topoTreeview.parent.id)
        // }

        



        delegate: Item{
            id: topo_item_root

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


            Rectangle{
                id: topoTreeviewItem_rect
                anchors.fill:parent
                anchors.leftMargin: 5
                anchors.rightMargin: 5          //！！！无作用
                color: topo_sel.currentIndex===topoTreeview.index(row,column)?"skyblue" :
                                           (topoTreeviewItem_mousearea.containsMouse
                                           || topoTreeviewItem_textfield_mousearea.containsMouse
                                           ?"lightgray":"transparent")

                property var indicatorsrc:["arrow_down.png", "arrow_right.png"]
                Image{
                    id: indicator
                    anchors.verticalCenter: parent.verticalCenter
                    visible: topo_item_root.isTreeNode&& topo_item_root.hasChildren
                    x:padding + (topo_item_root.depth * topo_item_root.indent)
                    width: 15
                    height: 15
                    source: "qrc:/image/indicator_icon/"
                            + (topo_item_root.expanded ? topoTreeviewItem_rect.indicatorsrc[0]:topoTreeviewItem_rect.indicatorsrc[1])

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

                    MouseArea{
                        id: topoTreeviewItem_mousearea
                        anchors.fill: parent
                        hoverEnabled:true

                        //propagateComposedEvents: true       //让TextField中的MouseArea也能接收到信号

                        onClicked: (mouse)=>{
                            topo_sel.setCurrentIndex(topoTreeview.index(row,column),0x0010)
                            topo_sel.currentHasSelection= true

                            console.log(row+" "+column+" "+topo_textfield.text)

                            // 更改右下方的para树状视图
                            lower_st.currentIndex = paraControl.getIDAccordingToIndex(topo_sel.currentIndex)
                        }
                    }

                    property var imgsrc:["node.png","heliostat.png","receiver.png","brace.png"]
                    Image{
                        id: img
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        width:20
                        height:20
                        source: "qrc:/image/settings_icon/" + topoTreeviewItem_rightrect.imgsrc[model.type]
                    }

                    TextField{
                        id:topo_textfield
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: img.right
                        anchors.right: parent.right
                        anchors.leftMargin: 5
                        //width:root.width - root.padding - x
                        clip: true
                        text: model.name
                        activeFocusOnPress: true

                        background: Rectangle{      //删去TextField本身自带的边框和背景色
                            border.width:0
                            color: topo_textfield.activeFocus ? "white" : "transparent"
                        }

                        
                        /*
                            ！！！暂时先这样写。目前没找到更好的办法
                            将focus手动置为false，会导致再次调用onEditingFinished
                        */
                        onEditingFinished: {                //输入框失焦本身就会触发EditingFinished信号，没必要在这里再设置一个focus=false
                            console.log("edit finished")
                            topo_textfield.focus = false
                            topoControl.updateNodeName(topoTreeview.index(row,column),topo_textfield.text)
                        }
                        
                        

                        MouseArea{
                            id: topoTreeviewItem_textfield_mousearea
                            anchors.fill: parent
                            propagateComposedEvents: true
                            hoverEnabled: true

                            onDoubleClicked: {
                                console.log("double click textfield")
                                topo_textfield.forceActiveFocus(Qt.MouseFocusReason) //所以，这句代码是在哪里找到的，文档里没找到
                            
                            }
                            onClicked: {
                                mouse.accepted = false
                            }

                            
                        }

                        
                    }

                    

                }


            }

        }


        //！！！！还没写完
        //！！！！键盘输入好像有些问题，键盘输入容易被其他组件劫持，有时间换成鼠标
        Keys.onPressed: (event)=> {
            console.log("press delete");
            // 如果已经选中了一行，并且选中的不是根节点
            if( event.key === Qt.Key_Delete
                && topo_sel.currentHasSelection 
                && topo_sel.currentIndex!==topoTreeview.index(0,0))
            {
                console.log("即将删除节点");
                //写删除的逻辑
                event.accepted = true;
            }
        }

        Component.onCompleted: {
            console.log(topoTreeview.columns+"  "+topoTreeview.rows)
        }








    }
    

}
