import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
/*
右上角的topology视图
先是一行button，再是树状视图
*/
Rectangle{

    //anchors.fill: parent
    id: topology_settings

    /*
    ---------------------------------------------------------------------------------
    顶部的一行，包括左侧的若干个btn和右侧的文件输入
    */
    Rectangle{
        id: topologyMenu_rect
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 20
        color: "lightgray"



        /*
        -------------------------------------------------------
        左侧的三个btn
        */
        Component
        {
            id:topology_delegate

            Button{                         //！！！最好鼠标移到button上，就能出现一个hint框说明button的作用
                id:topologyMenu_item_btn
                height:18
                width:18
                
                anchors.verticalCenter: parent.verticalCenter
                
                anchors.margins: 2
                
                icon.source:imagesrc
                icon.color: topologyMenu_item_btn.hovered ? "blue":"green"
                padding:3               //注意坑点：icon的大小受限于padding的大小，因为padding是button内部边界宽度


                //！！！在background后添加Rectangle组件会出现警告
    //            background:Rectangle{
    //                implicitHeight: 20
    //                implicitWidth: 20
    //                color: topologyMenu_item_btn.hovered ? "lightgray":"transparent"
    //            }


                onClicked: {
                    console.log("click treeview menu: "+index+" "+name)
                    topo.updateTopoSelection(index)
                    //点击之后，在sel.currentIndex下添加一个孩子,要求孩子名与同级的均不相同，记得传入孩子类型
                    //console.log("add "+name)
                    //topo.selFun(index)

                    /*
                    if(topo.sel.currentHasSelection){
                        topoControl.appendChild(topo.sel.currentIndex,index)
                        topo.topoTreeview.expand(topo.sel.currentIndex)    //添加孩子节点后，要把父节点展开
                    }
                    else{
                        console.log("no selection")
                    }
                    */

                }
            }
        }
        //！！！问题：node需要保留吗？？？
        ListModel{
            id:topologyMenu_listmodel
            ListElement{ name:'Node';       imagesrc:'qrc:/image/settings_icon/node.png'}
            ListElement{ name:'Heliosat';      imagesrc:'qrc:/image/settings_icon/heliosat.png'}
            ListElement{ name:'Receiver';    imagesrc:'qrc:/image/settings_icon/receiver.png'}
            
        }

        ListView{
            id: topologyMenu_listview

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            //anchors.fill: parent
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 3
            width: 60

            orientation:ListView.Horizontal
            spacing:1
            model:topologyMenu_listmodel
            delegate:topology_delegate
        }


        //分割线
        Rectangle{
            id: topologyMenu_spliter
            anchors.left: topologyMenu_listview.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 1
            anchors.leftMargin: 3
            color: "gray"
        }

        /*
        ----------------------------------------------
        右侧的文件输入部分,输入镜场数据
        */
        Button{
            id: topologyMenu_file_set_btn
            anchors.left: topologyMenu_spliter.right
            anchors.leftMargin: 3
            anchors.verticalCenter: parent.verticalCenter
            
            width: 15
            height: 15

            onClicked:{
                topologyMenu_file_set_fds.open()
            }
        }
        Rectangle{
            id: topologyMenu_file_set_rect

            border.width:1
            border.color: "gray"
            anchors.left: topologyMenu_file_set_btn.right
            anchors.leftMargin: 3
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 3
            height: 16
            

            Label{
                id: topologyMenu_file_set_label
                anchors.fill: parent
                anchors.margins: 3
                
                text: "input scene file: .json"
                font.pointSize: 8
                verticalAlignment: Text.AlignVCenter

            }
        }
        
        FileDialog{
            id: topologyMenu_file_set_fds
            title: "选择镜场文件"
            currentFolder: shortcuts.desktop
            //selectExisting: true
            //selectFolder: false
            //selectMultiple: false
            nameFilters: ["json文件 (*.json)"]
            onAccepted:{
                world_file_set_label.text = selectedFile
                console.log("You chose: " + fds.fileUrl)
            }

        }

    }






/*
---------------------------------------------------------------
button与treeview之间的分割线
*/
    Rectangle{
        id: topology_spliter
        anchors.top: topologyMenu_rect.bottom
        anchors.left:parent.left
        anchors.right:parent.right
        height: 1
        color: "gray"
    }


/*
---------------------------------------------------------------
treeview
*/
    Rectangle{
        anchors.top: topology_spliter.bottom
        anchors.left:parent.left
        anchors.right:parent.right
        anchors.bottom:parent.bottom

        //topo部分的树状视图
        //!!!!!!!!!!!!!!!!!!!!!还没写好，先放着
        TopoTreeView{
            anchors.fill: parent
            id: topo
            treeModel: topoControl.getTreeModel()

            onUpdateTopoSelection: function(index){
                updateSelection(index)
            }
        }

    }

}
