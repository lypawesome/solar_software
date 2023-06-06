import QtQuick
import QtQuick.Window
import QtQuick.Controls

/*
    上方设置光追的仿真参数
    下方按钮，点击后运行光追的算法----算法部分还没完成

    ！！！要设置窗口大小不可改
    ！！！注意带单位

*/

Window {
    id: ray_tracing_window
    width: 400
    height: 300
    maximumHeight: ray_tracing_window.height        // 防止窗口大小发生改变
    maximumWidth: ray_tracing_window.width
    minimumHeight: ray_tracing_window.height
    minimumWidth:ray_tracing_window.width
    title: "ray tracing"
    x: Screen.width/2 - width/2         // 位置--位于屏幕中央
    y: Screen.height/2 - height/2
    
    modality: Qt.WindowModal            // 表示这个窗口没有关闭时，无法点击主窗口

    // Text{
        
    //     anchors.centerIn: parent
    //     text: "This is a window to set parameters about raytracing." 
        
    // }
    Rectangle{
        id: ray_tracing_parameter_rect

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 5
        anchors.horizontalCenter: parent.horizontalCenter
        

        height: 250
        width: 300

        border.width:1
        border.color: "gray"
        radius: 3

        Column{
            anchors.fill: parent
            spacing:5
            padding:10

            RayTracingWindowParaRect{       // 光线数目
                type: 0
                rayTracingParaNameText: "Number of rays"
                rayTracingParaTextField: rayTracingParameter.ray_cnt

                onFinishEdit:{
                    rayTracingParameter.ray_cnt = rayTracingParaTextField
                }
            }

            RayTracingWindowParaRect{       // 接收器像素个数
                type:1
                rayTracingParaNameText: "Receiver pixel length"
                rayTracingParaTextField: rayTracingParameter.pixel_length

                onFinishEdit:{
                    rayTracingParameter.pixel_length = rayTracingParaTextField
                }
            }

            RayTracingWindowParaRect{       // 微定日镜个数
                type:1
                rayTracingParaNameText: "Subheliostat length"
                rayTracingParaTextField: rayTracingParameter.subheliostat_length

                onFinishEdit:{
                    rayTracingParameter.subheliostat_length = rayTracingParaTextField
                }
            }

            RayTracingWindowParaRect{       // 场景的网格划分--x
                type:2
                rayTracingParaNameText: "Scene grid size"
                rayTracingParaIdentity: "x:"
                rayTracingParaTextField: rayTracingParameter.scene_grid_x

                onFinishEdit:{
                    rayTracingParameter.scene_grid_x = rayTracingParaTextField
                }
            }

            RayTracingWindowParaRect{       // 场景的网格划分--y
                type: 3
                rayTracingParaNameText: "Scene grid size"
                rayTracingParaIdentity: "y:"
                rayTracingParaTextField: rayTracingParameter.scene_grid_y

                onFinishEdit:{
                    rayTracingParameter.scene_grid_y = rayTracingParaTextField
                }
            }

            RayTracingWindowParaRect{       // 场景的网格划分--z
                type: 3
                rayTracingParaNameText: "Scene grid size"
                rayTracingParaIdentity: "z:"
                rayTracingParaTextField: rayTracingParameter.scene_grid_z

                onFinishEdit:{
                    rayTracingParameter.scene_grid_z = rayTracingParaTextField
                }
            }
        }
            
        Connections {       // 建立一个到NOTIFY接口的连接，这里，似乎没什么用，可以先留着
            target:rayTracingParameter
            onRayCntChanged: {    }
            onPixelLengthChanged:{  }
            onSubheliostatLengthChanged:{  }
            onSceneGridLengthChanged:{  }
        }

    }

    /*
        这里按下按钮，应该是执行光追过程，算法目前还没集成...
    */
    Button{
        anchors.top: ray_tracing_parameter_rect.bottom
        anchors.margins: 10
        anchors.horizontalCenter: parent.horizontalCenter
        
        text: "Run Ray Tracing"

        onClicked:{
            console.log("执行ray tracing！！！")
        }
    }

}