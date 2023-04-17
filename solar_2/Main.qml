
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import "./"


ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "solar_1"
/*
=========================================================================
头部菜单栏：File、Edit、Run----------每个button都有一个下拉菜单
！！！待补充：下拉菜单没有写，每个菜单的点击事件没有写
！！！待完善：这里menu可以写成一个qml组件
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
==========================================================================
头部工具栏：几个icon图标------------每个icon图标也可以做对应的下拉菜单（如果需要的话）
！！！待补充：点击事件没有写
！！！待完善：ToolButton可以写成一个qml组件或者component、repeater
*/
    header:ToolBar{

        height:23

        Row{
            anchors.fill:parent

            ToolButton{
                height:parent.height
                width:30
                icon.source: "qrc:/image/menu_icon/start.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolButton{
                height:parent.height
                width:30
                icon.source:"qrc:/image/menu_icon/system.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolButton{
                height:parent.height
                width:30
                icon.source: "qrc:/image/menu_icon/parameter.png"
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

                icon.source: "qrc:/image/menu_icon/edit.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolButton{
                height:parent.height
                width:30
                icon.source: "qrc:/image/menu_icon/task.png"
                icon.color:"#36ab60"
                icon.height:22
                background:Rectangle{
                    color:parent.down ? "lightgray":"white"
                }
            }
            ToolButton{
                height:parent.height
                width:30
                icon.source: "qrc:/image/menu_icon/result.png"
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
==========================================================================
页脚：Text展示一些信息
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
==========================================================================
正文内容：SplitView把界面分为左右两部分，左边：3D可视化窗口，右边:树状视图和参数设置
*/
    SplitView{
        anchors.fill: parent
        orientation: Qt.Horizontal

        /*
        -------------------------------------------------------------------
        正文左边：3D可视化窗口
        ！！！待补充：需要与OpenGL结合
        */
        Rectangle {
            id:leftItem
            implicitWidth: parent.width*3/5
            SplitView.maximumWidth: parent.width        //注意：同一个rectangle里，不要同时设置maximum和minimum
            color: "lightblue"
            Label {
                text: "View 1"
                anchors.centerIn: parent
            }

        }

        /*
        -------------------------------------------------------------------
        正文右边：树状视图+参数设置
        */
        Rectangle{
            id:rightItem
            SplitView.minimumWidth: 10
            SplitView.fillWidth: true;
            //color:"lightgray"


            SplitView{
                anchors.fill: parent
                orientation: Qt.Vertical

                /*
                  ---------------------------------------------
                  上部：树状视图部分，建立模型，包括顶部的一行菜单和stackview
                */
                Rectangle{
                    implicitHeight: parent.height/2
                    SplitView.maximumHeight: parent.height
                    //color: "red"


                    //----------------------------------------------
                    //顶部的一行菜单：两个按钮：world、scene
                    Row{
                        id: menuRow
                        height:20
                        anchors.top: parent.top
                        anchors.left:parent.left
                        anchors.right:parent.right
                        //color:"pink"

                        Component{

                            id: rightUpperMenuBtn_delegate

                            Button{
                                id:rightUpperMenu_btn
                                height:parent.height
                                width:60
                                Text{
                                    text:modelData
                                    anchors.centerIn: parent
                                    font.family: "微软雅黑"
                                    font.pointSize: 8
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
                            model:['world','topology']
                            delegate: rightUpperMenuBtn_delegate
                        }

                    }


                    //----------------------------------------------
                    //菜单与stackview的分割线
                    Rectangle{
                        id: spliter
                        anchors.top: menuRow.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 1
                        color: "black"
                    }


                    //---------------------------------------------
                    //StackLayout
                    StackLayout{
                        id: st
                        anchors.top:spliter.bottom
                        anchors.bottom:parent.bottom
                        anchors.left:parent.left
                        anchors.right:parent.right

                        currentIndex: 0



                        MyRect_World{
                            col:"blue"
                        }

                        MyRect_Topology{

                        }

                    }

                }


                /*
                 ---------------------------------------------
                 下部：参数设置部分，是一个stackview，stackview内的每个界面都是一个treeview
                */
                Rectangle{
                    SplitView.minimumHeight: 20
                    SplitView.fillHeight: true
                    color: "skyblue"

                }
            }

        }


    }

}
