import QtQuick
import QtQuick.Controls

/*
    定义一个表示方框类型的property
    然后根据情况加载component
    分为以下几种情况：
            0、ray_cnt--无单位
            1、receiver pixel length、subheliostat length，要加单位
            2、grid length的x值，占一行，有单位
            3、grid length的y和z值，没有ray_tracing_text里的text，有单位
*/

Rectangle{

    required property int type

    property alias rayTracingParaNameText : ray_tracing_text.text
    property alias rayTracingParaTextField : ray_tracing_textfield.text
    property alias rayTracingParaIdentity : ray_tracing_identity.text
    property alias rayTracingParaUnit: ray_tracing_unit.text
    signal finishEdit()


    property int strFontSize : 10
    property int numFontSize: 8

    height:20
    //width: parent.width
    anchors.left: parent.left
    anchors.right:parent.right
    
    anchors.leftMargin:5
    anchors.rightMargin: 5
    // border.color:"blue"

    Text{
        id: ray_tracing_text
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        width: 130
        font.pointSize: strFontSize

        Component.onCompleted:{
            if(type === 3)
            {
                ray_tracing_text.text = ""
            }
        }
    }
    Text{
        id: ray_tracing_identity
        anchors.left:ray_tracing_text.right
        width:10
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: strFontSize

        Component.onCompleted:{
            if(type < 2)
                ray_tracing_identity.text = ""
        }
    }
    TextField{
        id: ray_tracing_textfield
        anchors.left: ray_tracing_identity.right
        anchors.leftMargin:10
        anchors.verticalCenter: parent.verticalCenter
        height: 18
        width: 100

        font.pointSize: numFontSize
        onEditingFinished: {
            console.log("完成edit")
            finishEdit();type==0? "" : paraUnit
        }
    }
    Text{
        id: ray_tracing_unit
        anchors.left: ray_tracing_textfield.right
        anchors.leftMargin:3
        text: "m"

        Component.onCompleted:{
            if (type===0)
                ray_tracing_unit.text = ""
        }
    }
    

    /*
    Rectangle{
        id: ray_tracing_textfield_rect
        anchors.left: ray_tracing_text.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        height: 20
        
        // border.width: 2
        // border.color: "red"
        radius:3
        color: "lightgray"

        TextField{
            id: ray_tracing_textfield
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            height: 16
            anchors.margins: 5
            width: 100
                                    
            // background: Rectangle{
            //     border.width:0
            //     color: "transparent"
            // }
                    
            // text: rayTracingParameter.ray_cnt

            font.pointSize: fontSize
            onEditingFinished: {
                console.log("完成edit")
                //rayTracingParameter.ray_cnt = ray_tracing_textfield.text    // 这里如何改
                finishEdit();
            }
        }
        Text{
            anchors.left: ray_tracing_textfield.right
            text: "m"

        }
    }
    */
    /*
    Loader{
        id: ray_tracing_textfield_loader
        anchors.left: ray_tracing_text.right
        width: 100
        sourceComponent: type==0 ? ray_tracing_textfield_component_0 
                                 : ray_tracing_textfield_component_1
    }

    
    
    Component{
        id: ray_tracing_textfield_component_0

        Rectangle{
            
        }

    }
    Component{
        id: ray_tracing_textfield_component_1

        Rectangle{
            Text{
                id: ray_tracing_textfield_iden
                text: "x:"
                width:10
            }
            TextField{
                id: ray_tracing_textfield
                anchors.left: ray_tracing_textfield_iden.right
                anchors.verticalCenter: parent.verticalCenter
                height: 18
                width: 90

                font.pointSize: numFontSize
                onEditingFinished: {
                    console.log("完成edit")
                    finishEdit();
                }
            }
        }

    }

    */
    

    
    
                
}
