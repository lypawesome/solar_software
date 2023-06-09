import QtQuick

/*
界面右上角world部分的设置
主要用ListView+ListModel+component来写
！！！待补充：onClick响应事件
！！！待完善：ListModel的imagesrc字段，需要改为相对路径
*/

Rectangle{
    required property var col

    //不需要fill parent，因为会自动填充，而且Layout类的组件中不能使用anchors
    //anchors.fill: parent
    //color:col
    id:world_settings

    Component{
        id: world_delegate

        Rectangle{
            id: worldSettingsListview_item_rect
            width:parent.width
            height:20
            color: worldSettingsListview_item_mousearea.containsMouse? "lightgray":"transparent"
            //color:mouse_area.down? "blue":"transparent"

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
        ListElement{ name:'Location';   imagesrc:'file:///D:/E/0_MyCode/QT_qml/qt6_5/solar_1/settings_icon/location.png'}
        ListElement{ name:'Sun';        imagesrc:'file:///D:/E/0_MyCode/QT_qml/qt6_5/solar_1/settings_icon/sun.png'}
        ListElement{ name:'Air';        imagesrc:'file:///D:/E/0_MyCode/QT_qml/qt6_5/solar_1/settings_icon/air.png'}
        ListElement{ name:'Terrain';    imagesrc:'file:///D:/E/0_MyCode/QT_qml/qt6_5/solar_1/settings_icon/terrain.png'}
        ListElement{ name:'Camera';     imagesrc:'file:///D:/E/0_MyCode/QT_qml/qt6_5/solar_1/settings_icon/camera.png'}
        ListElement{ name:'Cloud';      imagesrc:'file:///D:/E/0_MyCode/QT_qml/qt6_5/solar_1/settings_icon/cloud.png'}        //云----先留着
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
