import QtQuick 2.15
import QtQuick.Controls 2.15

import QtQuick.Controls 1.4 as Controls_1_4         //用于实现treeview
//import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.15

/*
！！！！！！需要更改
*/


Rectangle{
    id: paratreeview_root
    color:  "lightgray"
    //color: parameter.paraColor[parast.currentIndex]


    required property var treeViewName
    required property var treeModel

    //property var treeModel: mControl.getTreeModel()


    //添加自定义选中
    ItemSelectionModel{
        id:sel
        model:paratreeview_root.treeModel
        property bool currentHasSelection: false     //是否有选中的项---一开始是没有的点击之后才有
    }


    //TreeView视图部分
    Controls_1_4.TreeView{
        id: paratreeview
        anchors.fill: parent

        headerVisible: true
        backgroundVisible: false

        style: paratreeViewStyle
        model: paratreeview_root.treeModel
        selection: sel


        //两列数据
        Controls_1_4.TableViewColumn{
            width: 100
            title:"Parameter"
            role:'name'
        }
        Controls_1_4.TableViewColumn{
            width: parent.width-100
            title:"Value"
            role:'para'
        }




        /*
        定义TreeViewStyle：即model数据是如何呈现在视图里的
        */
        Component{
            id: paratreeViewStyle
            TreeViewStyle{
                padding.left:2
                padding.right:2
                indentation: 10     //节点间的缩进



                /*
                问题：在点击textedit后，无法进行selection的选择

                */
                //某一行、列中的一项
                itemDelegate:Rectangle{
                    id:paratreeview_item_delegate

                    color: styleData.selected ? "lightblue":(paratreeview_item_mousearea.containsMouse?"lightgreen":"transparent")

                    Component{
                        id:componentText
                        Text{
                            anchors.fill: parent
                            text: styleData.value
                            font.pointSize: 10
                        }
                    }
                    Component{
                        id:componentTextEdit
                        TextEdit{                       //需要改写一下事件：editfinished
                            id:textEdit
                            anchors.fill:parent
                            text: styleData.value
                            font.pointSize: 10
                            focus: true

                            //！！！！输入限制：：没有发挥作用
                            inputMethodHints: Qt.ImhFormattedNumbersOnly | Qt.ImhLowercaseOnly

                            onEditingFinished: {        //编辑完成后
                                console.log("editfinished:"+textEdit.text)
                                sunControl.updatePara(styleData.index, textEdit.text)
                            }
                        }
                    }
                    Component{
                        id:componentComboBox
                        //property var optionList: sunControl.getOptionList()
                        ComboBox{                       //!!!!!需要改设置一下 comboBox的model、事件和style
                            id: combobox
                            property var optionList: paraController[treeViewName].getOptionList(styleData.index)
                            model:optionList
                            currentIndex: {
                                //QString currentoption = sunControl.getPara(styleData.index)
                                return optionList.indexOf(paraController[treeViewName].getPara(styleData.index));
                            }

                            /*
                            contentItem: Text{
                                anchors.fill:parent
                                text: modelData
                                font.pointSize: 10
                            }
                            */
                            onActivated:{
                                console.log("click: "+currentText )
                                sunControl.makeChoice(styleData.index,currentText)
                            }

                            delegate: ItemDelegate {
                                     width: combobox.width
                                     contentItem: Text {
                                         text: modelData
                                         color: "#21be2b"
                                         font: combobox.font
                                         elide: Text.ElideRight
                                         verticalAlignment: Text.AlignVCenter
                                    }
                                    highlighted: combobox.highlightedIndex === index
                            }
                            indicator: Canvas {
                                    id: canvas
                                    x: combobox.width - width - combobox.rightPadding
                                    y: combobox.topPadding + (combobox.availableHeight - height) / 2
                                     width: 12
                                     height: 8
                                     contextType: "2d"

                                     Connections {
                                         target: combobox
                                         function onPressedChanged() { canvas.requestPaint(); }
                                     }

                                     onPaint: {
                                         context.reset();
                                         context.moveTo(0, 0);
                                         context.lineTo(width, 0);
                                         context.lineTo(width / 2, height);
                                         context.closePath();
                                         context.fillStyle = combobox.pressed ? "#17a81a" : "#21be2b";
                                         context.fill();
                                    }
                            }
                            contentItem: Text {
                                     leftPadding: 0
                                     rightPadding: combobox.indicator.width + combobox.spacing

                                     text: combobox.displayText
                                     font: combobox.font
                                     color: combobox.pressed ? "#17a81a" : "#21be2b"
                                     verticalAlignment: Text.AlignVCenter
                                     elide: Text.ElideRight
                            }
                            background: Rectangle {
                                     implicitWidth: 120
                                     implicitHeight: 40
                                     border.color: combobox.pressed ? "#17a81a" : "#21be2b"
                                     border.width: combobox.visualFocus ? 2 : 1
                                     radius: 2
                            }
                            popup: Popup {
                                     y: combobox.height - 1
                                     width: combobox.width
                                     implicitHeight: contentItem.implicitHeight
                                     padding: 1

                                     contentItem: ListView {
                                         clip: true
                                         implicitHeight: contentHeight
                                         model: combobox.popup.visible ? combobox.delegateModel : null
                                         currentIndex: combobox.highlightedIndex

                                         ScrollIndicator.vertical: ScrollIndicator { }
                                     }

                                     background: Rectangle {
                                         border.color: "#21be2b"
                                         radius: 2
                                     }
                            }


                        }
                    }

                    Loader{
                        id:item_loader
                        anchors.fill:parent
                        sourceComponent:{
                            if(styleData.column===0)
                                return componentText            //name那一列，不可编辑text
                            else if(paraController[treeViewName].iseditable(styleData.index))
                                return componentTextEdit        //可编辑text
                            else if(paraController[treeViewName].isoptional(styleData.index))
                                return componentComboBox        //组合按钮--用于选项
                            else return componentText           //不可编辑
                        }
                    }

                    MouseArea{
                        id:paratreeview_item_mousearea
                        anchors.fill:parent

                        propagateComposedEvents: true
                        hoverEnabled: true
                        acceptedButtons: Qt.LeftButton
                        drag.target: paratreeview_item_delegate

                        onClicked: {        //单击：选中当前节点
                            sel.setCurrentIndex(styleData.index,0x0010)
                            sel.currentHasSelection = true
                            mouse.accepted = false
                        }
                        onPressed: {
                            sel.setCurrentIndex(styleData.index,0x0010)
                            sel.currentHasSelection = true
                            mouse.accepted = false
                        }

                        onDoubleClicked: {      //双击：刷新子节点
                            paratreeview.collapse(styleData.index)
                            console.log("click" + styleData.value )
                            paratreeview.expand(styleData.index)
                        }
                    }
                }


                /*
                  某行数据是如何呈现的
                */
                rowDelegate: Rectangle {
                    id: paratreeview_row_delegate
                    color:"transparent"
                    height:15
                }



                /*
                节点展开、收起的图标
                */
                branchDelegate: Image{      //节点展开、收缩的图标
                    id: paratreeviewstyle_branch_delegate
                    source: {
                        return styleData.isExpanded ? "./tiny_icon/arrow_down.png" : "./tiny_icon/arrow_right.png"
                    }
                    width:10
                    height:10
                    MouseArea {
                        id:paratreeviewstyle_branch_mousearea
                        anchors.fill: parent
                        hoverEnabled: true
                        drag.target: paratreeviewstyle_branch_delegate

                        onClicked: {
                            if(styleData.isExpanded)
                            {
                                paratreeview.collapse(styleData.index)
                            }
                            else{
                                paratreeview.expand(styleData.index)
                            }

                        }
                    }
                }








            }
        }

    }

}
