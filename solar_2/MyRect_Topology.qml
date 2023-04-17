import QtQuick
import QtQuick.Controls

/*
右上角的topology视图
先是一行button，再是树状视图
*/
Rectangle{

    //anchors.fill: parent
    id: topology_settings

    /*
    ---------------------------------------------------------------------------------
    顶部的一行button，用ListView+ListModel+Component完成
    */
    Rectangle{
        id: topologyMenu_rect
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 25


        Component
        {
            id:topology_delegate

            Button{                         //！！！最好鼠标移到button上，就能出现一个hint框说明button的作用
                id:topologyMenu_item_btn
                height:20
                width:20
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
        ListModel{
            id:topologyMenu_listmodel
            ListElement{ name:'Node';       imagesrc:'qrc:/image/settings_icon/node.png'}
            ListElement{ name:'Shape';      imagesrc:'qrc:/image/settings_icon/shape.png'}
            ListElement{ name:'Tracker';    imagesrc:'qrc:/image/settings_icon/tracker.png'}
            ListElement{ name:'Array';      imagesrc:'qrc:/image/settings_icon/array.png'}
        }

        ListView{
            id: topologyMenu_listview

            anchors.fill:parent
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 5

            orientation:ListView.Horizontal
            spacing:1
            model:topologyMenu_listmodel
            delegate:topology_delegate
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
            id: topo
            treeModel: topoControl.getTreeModel()

            onUpdateTopoSelection: function(index){
                updateSelection(index)
            }
        }

    }

}
