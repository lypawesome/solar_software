import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import QtQuick.Controls 1.4 as Controls_1_4         //用于实现treeview
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.15                            //用于实现itemselectionmodel

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "solarsoft"



    /*
      顶部菜单栏
        框架基本完成
        ！！！待补充：写成正式软件，设置menu样式，添加点击事件
        ！！！进一步完善：缺少封装，把menu写成组件的形式，在component.onCompleted里面动态加载
      */
    menuBar: MenuBar{
        id:menuBar

        //contentHeight: 20
        Menu {
            title: "File"
            Action{ text:"Open"}
            Action{ text:"New"}
            MenuSeparator { }
            Action{ text:"close"}

            implicitWidth: 100


            delegate:MenuItem{
                id:menuItem_1
                implicitWidth: 100
                implicitHeight: 20

                contentItem:Text{
                    text:menuItem_1.text
                    font:menuItem_1.font
                    color:menuItem_1.highlighted? "white":"green"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    elide:Text.ElideRight
                }

                background:Rectangle{
                    color:menuItem_1.highlighted ? "green": "white"

                }

            }
            //！！！这里，menuItem的边框被盖住了,先设置为透明
            background:Rectangle{
                border.width:1
                border.color:"transparent"
            }

        }
        Menu {
            title: "Edit"
            Action{ text:"Open"}
            Action{ text:"New"}
            MenuSeparator { }
            Action{ text:"close"}

            implicitWidth: 100


            delegate:MenuItem{
                id:menuItem_2
                implicitWidth: 100
                implicitHeight: 20

                contentItem:Text{
                    text:menuItem_2.text
                    font:menuItem_2.font
                    color:menuItem_2.highlighted? "white":"green"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    elide:Text.ElideRight
                }

                background:Rectangle{
                    color:menuItem_2.highlighted ? "green": "white"

                }

            }
            //！！！这里，menuItem的边框被盖住了,先设置为透明
            background:Rectangle{
                border.width:1
                border.color:"transparent"
            }

        }
        Menu {
            title: "Run"
            Action{ text:"Open"}
            Action{ text:"New"}
            MenuSeparator { }
            Action{ text:"close"}

            implicitWidth: 100


            delegate:MenuItem{
                id:menuItem_3
                implicitWidth: 100
                implicitHeight: 20

                contentItem:Text{
                    text:menuItem_3.text
                    font:menuItem_3.font
                    color:menuItem_3.highlighted? "white":"green"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignHCenter
                    elide:Text.ElideRight
                }

                background:Rectangle{
                    color:menuItem_3.highlighted ? "green": "white"

                }

            }
            //！！！这里，menuItem的边框被盖住了,先设置为透明
            background:Rectangle{
                border.width:1
                border.color:"transparent"
            }


        }

        delegate:MenuBarItem{
            id:menuBarItem
            height:23
            anchors.top: parent.top
            contentItem:Text{
                text:menuBarItem.text
                font:menuBarItem.font
                opacity:enabled?1.0:0.3
                color:menuBarItem.highlighted? "white":"green"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignHCenter
                elide:Text.ElideRight
            }

            background: Rectangle{
                //implicitHeight: 20
                implicitWidth: 40
                opacity:enabled?1:0.3
                color:menuBarItem.highlighted ? "green":"white"
            }

        }

        background: Rectangle{
            implicitHeight: 20
            implicitWidth: 40
            color:"white"
            Rectangle{              //绿色分割线
                color:"green"
                width:parent.width
                height:1
                anchors.bottom: parent.bottom
            }
        }

        Component.onCompleted: {
            console.log('contentheight:',contentHeight)
        }

    }
    /*
    头部工具栏
        框架基本完成
        ！！！待补充：图标要按照正式软件来找点击事件，及其弹出的菜单和窗口
        ！！！待完善：封装，可以把ToolButton写成一个Repeater
    */
    header:ToolBar{

        height:23

        Row{
            anchors.fill:parent

            ToolButton{
                height:parent.height
                width:30
                icon.source: "./icon/start.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolButton{
                height:parent.height
                width:30
                icon.source:"./icon/system.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolButton{
                height:parent.height
                width:30
                icon.source: "./icon/parameter.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolSeparator{      //图标的垂直分界线
                orientation: Qt.Vertical
                padding:10
                topPadding: 2
                bottomPadding: 2
                height:20

            }
            ToolButton{
                height:parent.height
                width:30

                icon.source: "./icon/edit.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolButton{
                height:parent.height
                width:30
                icon.source: "./icon/task.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolButton{
                height:parent.height
                width:30
                icon.source: "./icon/result.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
        }

        Rectangle{      //分割线
            height:1
            width:parent.width
            anchors.bottom: parent.bottom
            color:"#36ab60"
        }

        background:Rectangle{
            color:"white"
        }

    }
    /*
    页脚
        展示一些信息
    */
    footer:ToolBar{
        height:10

        Rectangle{      //分界线
            height:1
            width:parent.width
            anchors.top: parent.top
            color:"gray"
        }

        Text{
            text:"This is a footer"
            font.pointSize: 8
            color:"gray"
            anchors.left: parent.left
        }
        background: Rectangle{
            color:"lightgray"
        }
    }

    /*
    正文内容
    先用splitview把页面分为两半，左边是3D模型可视化窗口，右边是树状节点和参数设置

    */
    SplitView{
        anchors.fill: parent
        orientation: Qt.Horizontal

        //左边图形可视化界面
        Rectangle {
            SplitView.maximumWidth: parent.width - 100
            SplitView.minimumWidth: 100
            SplitView.preferredWidth: 400
            color: "lightblue"
            Label {
                text: "View 1"
                anchors.centerIn: parent
            }

        }

        //右边：建立模型+参数设置
        Rectangle {
            id: centerItem
            SplitView.minimumWidth: 50
            SplitView.fillWidth: true
            //color: "lightgray"

            SplitView{
                anchors.fill:parent
                orientation:Qt.Vertical

                //模型建立模块
                Rectangle{
                    SplitView.maximumHeight: parent.height-20
                    SplitView.minimumHeight: 20
                    SplitView.preferredHeight: parent.height / 2

                    //菜单模块:两个按钮----world、scene
                    //用row结构，repeater + component + button写成，无法实现选中按钮后该按钮变黑其他按钮变灰的效果
                    //可以试着用menu来重写一下，或者试着把组件写到其他文件里，把main文件简化
                    Row{
                        id:toolbar
                        height:20
                        anchors.top: parent.top
                        anchors.left:parent.left
                        anchors.right:parent.right

                        Component{

                            id:rightuppermenubtn_delegate

                            Button{
                                id:rightUpperMenu_btn
                                height:parent.height
                                width:30
                                Text{
                                    text:modelData
                                    anchors.centerIn: parent
                                    font.family: "微软雅黑"
                                    font.pointSize: 6
                                    color:rightUpperMenu_btn.pressed ? "black":"gray"
                                }
                                background: Rectangle{
                                    color:rightUpperMenu_btn.hovered?"lightgray":"white"
                                }
                                onClicked: {
                                    st.currentIndex = index
                                }

                            }

                        }
                        Repeater{
                            model:['world','scene']

                            delegate:rightuppermenubtn_delegate
                        }

                        //color:"pink"
                    }

                    //分割线
                    Rectangle{
                        id:spliter
                        anchors.top:toolbar.bottom
                        anchors.left:parent.left
                        anchors.right:parent.right
                        height:1
                        color:"black"
                    }

                    //模型建立界面
                    // stacklayout中包括两个界面，分别是world和scene的相关设置
                    StackLayout{
                        id: st
                        anchors.top:spliter.bottom
                        anchors.bottom:parent.bottom
                        anchors.left:parent.left
                        anchors.right:parent.right

                        currentIndex: 0







                        //world的相关设置
                        //用一个listview设置比较好，每行的内容用一个组件写好
                        Rectangle{
                            id:world_settings

                            //问题：：：如何做这样的效果：点击一行后，该行的背景变为蓝色，其他行的背景变为透明
                            //-----或许可以做一个list，把每行放进去，然后每点击一次，就把index对应的行变为蓝色，其他行变为透明
                            Component{
                                id:world_delegate

                                Rectangle{
                                    id: rightuplistview_item_rect
                                    width:parent.width
                                    height:15

                                    //color:mouse_area.down? "blue":"transparent"

                                    Image{
                                        id:rightup_item_delegate_img
                                        anchors.left:parent.left
                                        anchors.leftMargin: 10
                                        anchors.verticalCenter: parent.verticalCenter
                                        height:10
                                        width:10

                                        source:imagesrc
                                    }
                                    Text{
                                        text:name
                                        anchors.left:rightup_item_delegate_img.right
                                        anchors.leftMargin: 5
                                        anchors.verticalCenter: parent.verticalCenter
                                        font.family:"微软雅黑"
                                        font.pointSize: 6
                                    }
                                    MouseArea{
                                        id:mouse_area
                                        anchors.fill:parent
                                        hoverEnabled: true
                                        onClicked:{
                                            //parent.color = "red"
                                            parast.currentIndex = index
                                            console.log("click: " + name)
                                        }
                                        onEntered: {
                                            parent.color = "lightgray"
                                        }
                                        onExited: {
                                            parent.color = "transparent"
                                        }

                                    }
                                }
                            }
                            ListModel{
                                id:world_listmodel
                                ListElement{ name:'Location';   imagesrc:'./settings_icon/location.png'}
                                ListElement{ name:'Sun';        imagesrc:'./settings_icon/sun.png'}
                                ListElement{ name:'Air';        imagesrc:'./settings_icon/air.png'}
                                ListElement{ name:'Terrain';    imagesrc:'./settings_icon/terrain.png'}
                                ListElement{ name:'Camera';     imagesrc:'./settings_icon/camera.png'}
                                ListElement{ name:'Cloud';      imagesrc:'./settings_icon/cloud.png'}        //云----先留着
                            }

                            ListView{
                                id:world_listview
                                anchors.fill:parent
                                anchors.margins: 10

                                spacing:1
                                model:world_listmodel
                                delegate:world_delegate
                            }


                        }



                        //scene的相关设置
                        //先写一行menu，再写treeview，并且可以动态添加treeview中的组件
                        Rectangle{
                            id:scene_settings



                            //scene的menu按钮，共4个：node、shape、tracker、array
                            //!!!!!用listview实现横向视图,但是没有做好背景色随着鼠标事件的变化
                            //！！！有时间的话，尝试用menubar重写
                            Component{
                                id:scene_menu_delegate
                                Button{                         //！！！最好鼠标移到button上，就能出现一个hint框说明button的作用
                                    id:scene_menu_delegate_btn
                                    height:20
                                    width:20
                                    icon.source:imagesrc
                                    icon.color:scene_menu_delegate_btn.down ? "lightgreen":"green"
                                    padding:3               //注意坑点：icon的大小受限于padding的大小，因为padding是button内部边界宽度

                                    //！！！！！！点击之后treeview并不会增加新的节点！！！！！
                                    //！！！！！！！！！！！！！排查原因！！！
                                    onClicked: {
                                        console.log("click treeview menu: "+index+" "+name)
                                        topo.updateTopoSelection(index)
                                        //点击之后，在sel.currentIndex下添加一个孩子,要求孩子名与同级的均不相同，记得传入孩子类型
                                        //console.log("add "+name)
                                        //topo.selFun(index)
                                        /*
                                        if(topo.sel.currentHasSelection){
                                            mControl.appendChild(topo.sel.currentIndex,index)
                                            topo.topo_treeview.expand(topo.sel.currentIndex)    //添加孩子节点后，要把父节点展开
                                        }
                                        else{
                                            console.log("no selection")
                                        }
                                        */
                                    }
                                }
                            }
                            ListModel{
                                id:scene_menu_listmodel
                                ListElement{ name:'Node';       imagesrc:'./settings_icon/node.png'}
                                ListElement{ name:'Shape';      imagesrc:'./settings_icon/shape.png'}
                                ListElement{ name:'Tracker';    imagesrc:'./settings_icon/tracker.png'}
                                ListElement{ name:'Array';      imagesrc:'./settings_icon/array.png'}
                            }
                            ListView{
                                id:scene_menu_listview

                                anchors.top:parent.top
                                anchors.left:parent.left
                                anchors.right:parent.right
                                height:20

                                orientation:ListView.Horizontal
                                spacing:1
                                model:scene_menu_listmodel
                                delegate:scene_menu_delegate

                            }


                            //分割线
                            Rectangle{
                                id:scene_settings_spliter
                                anchors.top:scene_menu_listview.bottom
                                anchors.left:parent.left
                                anchors.right:parent.right
                                height: 1
                                color:"gray"
                            }


                            //建立模型的treeview
                            //这里的listmodel的name，不能就这么建立，model里应该包括建立的每个节点的名称，且每一级都不能有重名
                            //！！！！！！可能要自定义组件！！！！先看教程
                            //给treeview加上selection
                            //!!!！！！！!问题：展开正常，但是点击收回时，程序崩溃
                            Rectangle{
                                anchors.top:scene_settings_spliter.bottom
                                anchors.left:parent.left
                                anchors.right:parent.right
                                anchors.bottom:parent.bottom

                                //topo部分的树状视图
                                TopoTreeView{
                                    id: topo
                                    treeModel: mControl.getTreeModel()

                                    onUpdateTopoSelection: {

                                        updateSelection(index)
                                    }

                                }
                            }






                        }

                    }

                }


                //右下方，参数设置模块，根据右上方的点击事件更改这里的页面
                Rectangle{
                    id:parameter
                    SplitView.fillHeight: true
                    color:"lightgreen"


                    property var paraName:['location','sun','air','terrain','camera','node','shape','array','tracker']

                    Label{
                        id:parameterLabel
                        anchors.top:parent.top
                        anchors.left:parent.left
                        anchors.right:parent.right
                        height:15

                        text:parameter.paraName[parast.currentIndex]
                        background:Rectangle{
                            color:'white'
                        }
                    }

                    StackLayout{
                        id:parast
                        currentIndex:0              //默认为0

                        anchors.top:parameterLabel.bottom
                        anchors.left:parent.left
                        anchors.right:parent.right
                        anchors.bottom:parent.bottom

                        ParaTreeView{
                            treeViewName:0
                            treeModel:  sunParaControl.getTreeModel()
                        }


/*
                        //location的参数设置
                        Rectangle{
                            color:"red"

                        }
                        //sun的参数设置
                        Rectangle{
                            color:"green"

                        }
                        //air的参数设置
                        Rectangle{
                            color:"blue"
                        }
                        //terrain的参数设置
                        Rectangle{
                            color:"gray"
                        }
                        //camera的参数设置
                        Rectangle{
                            color:"plum"
                        }
*/


                    }

                }

            }
        }

    }









}
