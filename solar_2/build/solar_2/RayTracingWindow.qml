import QtQuick
import QtQuick.Window

Window {
    width: 600
    height: 300
    title: "ray tracing"
    x: Screen.width/2 - width/2
    y: Screen.height/2 - height/2
    
    modality: Qt.WindowModal

    Text{
        
        anchors.centerIn: parent
        text: "This is a window to set parameters about raytracing."
        
    }
}