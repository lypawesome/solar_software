import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
/*
界面右上角world部分的设置
主要用ListView+ListModel+component来写
！！！待补充：onClick响应事件
！！！待完善：需要添加一个selection
*/

Rectangle{
    //required property var col

    //不需要fill parent，因为会自动填充，而且Layout类的组件中不能使用anchors
    //anchors.fill: parent
    //color:col
    id:world_settings


    //用文件来设置world中的各个参数
    //!!!!!!!!!!!!!!!!!!!!!!!!!
    //！！！！还需要进一步完善和测试
    Rectangle{
        id: world_file_set
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        
        height: 20
        color: "lightgray"

        //button，点击后弹出文件选择界面
        Button{
            id: world_file_set_btn
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            
            width: 15
            height: 15

            onClicked:{
                world_file_set_fds.open()
            }
        }
        //显示文件名，也可以写成TextField，用来输入文件
        Rectangle{
            border.width:1
            border.color: "gray"
            anchors.left: world_file_set_btn.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 18

            Label{
                id: world_file_set_label
                anchors.fill: parent
                anchors.margins: 3
                
                text: "input world file: .json"
                font.pointSize: 8
                verticalAlignment: Text.AlignVCenter

            }
        }
        
        FileDialog{
            id: world_file_set_fds
            title: "选择world文件"
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


    Component{
        id: world_delegate

        Rectangle{
            id: worldSettingsListview_item_rect
            width:parent.width
            height:20
            color: worldSettingsListview_item_mousearea.containsMouse ? (world_listview.isCurrentItem?"blue":"lightgray") : "transparent"


            Image{
                id: worldSettingsListView_item_img
                anchors.left:parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                height:15
                width:15

                source:imagesrc
            }
            Text{
                text:name
                anchors.left:worldSettingsListView_item_img.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                font.family:"微软雅黑"
                font.pointSize: 8
            }
            MouseArea{
                id:worldSettingsListview_item_mousearea
                anchors.fill:parent

                hoverEnabled: true
                onClicked:{

                    lower_st.currentIndex = index
                    //!!!!!!!!!!!!!!!!!!!!!!!!!等下方treeview写好再改!!!!!!!!!!!!!!!!!!!!!!!!!!
                    //parent.color = "red"
                    //parast.currentIndex = index
                    //console.log("click: " + name)
                }
            }
        }
    }
    ListModel{
        id:world_listmodel
        ListElement{ name:'Location';   imagesrc:'qrc:/image/settings_icon/location.png'}
        ListElement{ name:'Sun';        imagesrc:'qrc:/image/settings_icon/sun.png'}
        ListElement{ name:'Air';        imagesrc:'qrc:/image/settings_icon/air.png'}
        ListElement{ name:'Terrain';    imagesrc:'qrc:/image/settings_icon/terrain.png'}
        ListElement{ name:'Camera';     imagesrc:'qrc:/image/settings_icon/camera.png'}
        ListElement{ name:'Cloud';      imagesrc:'qrc:/image/settings_icon/cloud.png'}        //云----先留着
    }

    ListView{
        id:world_listview
        //anchors.fill:parent
        anchors.top: world_file_set.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        spacing:1
        model:world_listmodel
        delegate:world_delegate

//        highlight: Rectangle{
//            color:"blue"
//        }
//        highlightFollowsCurrentItem: true
//        focus:true
    }

}
