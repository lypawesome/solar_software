import QtQuick
import QtQuick.Controls


Rectangle{
    id: paraTreeview_rect


    required property var treeModel         //传入模型
    required property int paraTreeId

    ItemSelectionModel{     //添加自定义选中
        id:para_sel
        model: paraTreeview_rect.treeModel
        property bool currentHasSelection: false     //是否有选中的项---一开始是没有的点击之后才有
    }

    TreeView{
        id: paraTreeview
        anchors.fill: parent

        model: paraTreeview_rect.treeModel

        selectionModel: para_sel

        delegate: Item{
            id: para_item_root

            implicitWidth: 100
            implicitHeight:20

            readonly property real indent: 20
            readonly property real padding: 2

            required property TreeView treeView
            required property bool isTreeNode
            required property bool expanded
            required property int hasChildren
            required property int depth
            required property int column        //这里有疑问的是，究竟有哪些required属性可以用？

            visible: column===2 ? false:true     //！！！第三列是TYPE，设置为不可见即可




            //！！！！！！！！！！！！！！！！！！！！！！！！
            //注意这里，QUIET、EDITABLE、OPTIONAL是三种不同的形式，孩子节点也是不一样的，需要再找一下示例代码
            //可以写三个不同的component，在这里动态加载
            //！！！！！！！！！！！！！！！！！！！！！！！！
            //这里注意每个Item的位置,column=0的位置宽度，column=1的宽度
            Rectangle{
                id: paraTreeviewItem_rect
                height: parent.height
                width: column===0 ? parent.width: paraTreeview.width - parent.width

                property var indicatorsrc:["arrow_down.png", "arrow_right.png"]

                Image{
                    id: para_indicator
                    anchors.verticalCenter: parent.verticalCenter
                    visible: para_item_root.isTreeNode&& para_item_root.hasChildren && column===0
                    x: padding + (para_item_root.depth * para_item_root.indent)
                    width: 15
                    height: 15
                    source: "qrc:/image/indicator_icon/"
                            + (para_item_root.expanded ? paraTreeviewItem_rect.indicatorsrc[0]:paraTreeviewItem_rect.indicatorsrc[1])

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            treeView.toggleExpanded(row)
                        }
                    }
                }

//                Text{
//                    anchors.left: para_indicator.right
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom

//                    text: para_item_root.column==0 ? model.name : model.para
//                }


                //动态加载组件，如果是editable就写TextEdit，如果是optional就写一个组合框ComboBox
                Loader{
                    id: para_item_text_loader
                    anchors.left: para_indicator.right
                    width: parent.width
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    sourceComponent: column===0 ? component_no_operation :
                                    ( paraControl.isEditable(paraTreeId, para_item_root.treeView.index(row,column)) ? component_editable :
                                    ( paraControl.isOptional(paraTreeId, para_item_root.treeView.index(row,column)) ? component_optional : component_no_operation ) )

                    Component.onCompleted: {
                        console.log("这一Item的参数："+model.name + " - "+model.para
                                    + " row="+row + " column="+column)
                    }
                }

                //什么操作都没有，也没有特殊的函数
                Component
                {
                    id: component_no_operation

                    Rectangle{
                        anchors.fill: parent

                        Text{
                            anchors.fill: parent
                            text: para_item_root.column===0 ? model.name : model.para
                        }
                    }

                }

                //要可编辑，并且要在编辑完之后把参数传回CPP
                Component
                {
                    id: component_editable

                    Rectangle{
                        id: component_editable_rect
                        anchors.fill: parent

//                        border.color: "gray"
//                        border.width: 2

                        //！！！！！！！！！！！！！！！！！
                        //已完成：将数据传回cpp中并更改cpp中的参数
                        //待完善：每个TextField中可以输入参数类型没有设置。。。
                        //       还有，要对输入的参数进行修正吗？？？比如输入001,要不要去掉前缀0自动修正成1
                        TextField
                        {
                            id: text_field
                            anchors.fill: parent
                            anchors.rightMargin: 5      //！！！！这里没有起作用！！！！编辑框与外面的框没有间距
                            text: para_item_root.column===0 ? model.name : model.para

                            onEditingFinished: {
                                console.log("完成edit")
                                console.log("新的text是：" + text_field.text)
                                paraControl.updateNodePara(paraTreeId, para_item_root.treeView.index(row,column), text_field.text)
                            }

                            Component.onCompleted: {
                                console.log("TextField:")
                                console.log("width: " + text_field.width +
                                            " height: " + text_field.height +
                                            " text: " + text_field.text)
                            }
                        }




                    }


                }

                //要可选择，ComboBox复选框，要在做出选择之后把参数传到CPP
                //！！！！！！！！！！！！！！！！！！！！！！！！！！！
                //问题：comboBox与前面的TextField没有对齐....（可能是孩子节点会往后缩的原因，这里等全部写好之后再改）

                Component
                {
                    id: component_optional
                    Rectangle{
                        id: component_optional_rect
                        anchors.fill: parent

                        property var options:paraControl.getOptionList(paraTreeId, para_item_root.treeView.index(row,column))

//                        function getCurrentIndex(para)
//                        {
//                            console.log("options的类型" )
//                            var para_str = para.toString();
//                            var ret = -1;
//                            var num = options.length();
//                            for(var i=0 ; i<num; ++i)
//                            {
//                                if( para_str === para[i] )
//                                {
//                                    ret = i;
//                                    break;
//                                }
//                            }
//                            return ret
//                        }

                        //！！！！添加选择事件
                        ComboBox{
                            id: component_optional_combobox
                            anchors.fill: parent

                            model: options

                            currentIndex: paraControl.getCurrentOptionId(paraTreeId,para_item_root.treeView.index(row,column))

                            onActivated: {
                                //选中了一个option，要传给cpp，让cpp做出选择-----或许直接用setPara就可以
                                console.log("在ComboBox中选中了一个Item：" + component_optional_combobox.currentText)

                                //报错....
                                paraControl.updateNodePara(paraTreeId,para_item_root.treeView.index(row,column),
                                                           component_optional_combobox.currentText)

                            }

                        }

                        Component.onCompleted: {        //测试options输出是否正确
                            var ret = paraControl.getCurrentOptionId(paraTreeId,para_item_root.treeView.index(row,column))
                            console.log("options: " + options)
                            console.log("model.para:" + model.para)
                            console.log("ret: " + ret)

                        }
                    }


                }
            }
        }

    }

}


//Rectangle{
//    id: paraTreeview_root
//    color:  "lightgray"
//    //color: parameter.paraColor[parast.currentIndex]


//    required property var treeViewName
//    required property var treeModel

//    //property var treeModel: mControl.getTreeModel()


//    //添加自定义选中
//    ItemSelectionModel{
//        id:sel
//        model:paraTreeview_root.treeModel
//        property bool currentHasSelection: false     //是否有选中的项---一开始是没有的点击之后才有
//    }


//    //TreeView视图部分
//    Controls_1_4.TreeView{
//        id: paratreeview
//        anchors.fill: parent

//        headerVisible: true
//        backgroundVisible: false

//        style: paratreeViewStyle
//        model: paratreeview_root.treeModel
//        selection: sel


//        //两列数据
//        Controls_1_4.TableViewColumn{
//            width: 100
//            title:"Parameter"
//            role:'name'
//        }
//        Controls_1_4.TableViewColumn{
//            width: parent.width-100
//            title:"Value"
//            role:'para'
//        }




//        /*
//        定义TreeViewStyle：即model数据是如何呈现在视图里的
//        */
//        Component{
//            id: paratreeViewStyle
//            TreeViewStyle{
//                padding.left:2
//                padding.right:2
//                indentation: 10     //节点间的缩进



//                /*
//                问题：在点击textedit后，无法进行selection的选择

//                */
//                //某一行、列中的一项
//                itemDelegate:Rectangle{
//                    id:paratreeview_item_delegate

//                    color: styleData.selected ? "lightblue":(paratreeview_item_mousearea.containsMouse?"lightgreen":"transparent")

//                    Component{
//                        id:componentText
//                        Text{
//                            anchors.fill: parent
//                            text: styleData.value
//                            font.pointSize: 10
//                        }
//                    }
//                    Component{
//                        id:componentTextEdit
//                        TextEdit{                       //需要改写一下事件：editfinished
//                            id:textEdit
//                            anchors.fill:parent
//                            text: styleData.value
//                            font.pointSize: 10
//                            focus: true

//                            //！！！！输入限制：：没有发挥作用
//                            inputMethodHints: Qt.ImhFormattedNumbersOnly | Qt.ImhLowercaseOnly

//                            onEditingFinished: {        //编辑完成后
//                                console.log("editfinished:"+textEdit.text)
//                                sunControl.updatePara(styleData.index, textEdit.text)
//                            }
//                        }
//                    }
//                    Component{
//                        id:componentComboBox
//                        //property var optionList: sunControl.getOptionList()
//                        ComboBox{                       //!!!!!需要改设置一下 comboBox的model、事件和style
//                            id: combobox
//                            property var optionList: paraController[treeViewName].getOptionList(styleData.index)
//                            model:optionList
//                            currentIndex: {
//                                //QString currentoption = sunControl.getPara(styleData.index)
//                                return optionList.indexOf(paraController[treeViewName].getPara(styleData.index));
//                            }

//                            /*
//                            contentItem: Text{
//                                anchors.fill:parent
//                                text: modelData
//                                font.pointSize: 10
//                            }
//                            */
//                            onActivated:{
//                                console.log("click: "+currentText )
//                                sunControl.makeChoice(styleData.index,currentText)
//                            }

//                            delegate: ItemDelegate {
//                                     width: combobox.width
//                                     contentItem: Text {
//                                         text: modelData
//                                         color: "#21be2b"
//                                         font: combobox.font
//                                         elide: Text.ElideRight
//                                         verticalAlignment: Text.AlignVCenter
//                                    }
//                                    highlighted: combobox.highlightedIndex === index
//                            }
//                            indicator: Canvas {
//                                    id: canvas
//                                    x: combobox.width - width - combobox.rightPadding
//                                    y: combobox.topPadding + (combobox.availableHeight - height) / 2
//                                     width: 12
//                                     height: 8
//                                     contextType: "2d"

//                                     Connections {
//                                         target: combobox
//                                         function onPressedChanged() { canvas.requestPaint(); }
//                                     }

//                                     onPaint: {
//                                         context.reset();
//                                         context.moveTo(0, 0);
//                                         context.lineTo(width, 0);
//                                         context.lineTo(width / 2, height);
//                                         context.closePath();
//                                         context.fillStyle = combobox.pressed ? "#17a81a" : "#21be2b";
//                                         context.fill();
//                                    }
//                            }
//                            contentItem: Text {
//                                     leftPadding: 0
//                                     rightPadding: combobox.indicator.width + combobox.spacing

//                                     text: combobox.displayText
//                                     font: combobox.font
//                                     color: combobox.pressed ? "#17a81a" : "#21be2b"
//                                     verticalAlignment: Text.AlignVCenter
//                                     elide: Text.ElideRight
//                            }
//                            background: Rectangle {
//                                     implicitWidth: 120
//                                     implicitHeight: 40
//                                     border.color: combobox.pressed ? "#17a81a" : "#21be2b"
//                                     border.width: combobox.visualFocus ? 2 : 1
//                                     radius: 2
//                            }
//                            popup: Popup {
//                                     y: combobox.height - 1
//                                     width: combobox.width
//                                     implicitHeight: contentItem.implicitHeight
//                                     padding: 1

//                                     contentItem: ListView {
//                                         clip: true
//                                         implicitHeight: contentHeight
//                                         model: combobox.popup.visible ? combobox.delegateModel : null
//                                         currentIndex: combobox.highlightedIndex

//                                         ScrollIndicator.vertical: ScrollIndicator { }
//                                     }

//                                     background: Rectangle {
//                                         border.color: "#21be2b"
//                                         radius: 2
//                                     }
//                            }


//                        }
//                    }

//                    Loader{
//                        id:item_loader
//                        anchors.fill:parent
//                        sourceComponent:{
//                            if(styleData.column===0)
//                                return componentText            //name那一列，不可编辑text
//                            else if(paraController[treeViewName].iseditable(styleData.index))
//                                return componentTextEdit        //可编辑text
//                            else if(paraController[treeViewName].isoptional(styleData.index))
//                                return componentComboBox        //组合按钮--用于选项
//                            else return componentText           //不可编辑
//                        }
//                    }

//                    MouseArea{
//                        id:paratreeview_item_mousearea
//                        anchors.fill:parent

//                        propagateComposedEvents: true
//                        hoverEnabled: true
//                        acceptedButtons: Qt.LeftButton
//                        drag.target: paratreeview_item_delegate

//                        onClicked: {        //单击：选中当前节点
//                            sel.setCurrentIndex(styleData.index,0x0010)
//                            sel.currentHasSelection = true
//                            mouse.accepted = false
//                        }
//                        onPressed: {
//                            sel.setCurrentIndex(styleData.index,0x0010)
//                            sel.currentHasSelection = true
//                            mouse.accepted = false
//                        }

//                        onDoubleClicked: {      //双击：刷新子节点
//                            paratreeview.collapse(styleData.index)
//                            console.log("click" + styleData.value )
//                            paratreeview.expand(styleData.index)
//                        }
//                    }
//                }


//                /*
//                  某行数据是如何呈现的
//                */
//                rowDelegate: Rectangle {
//                    id: paratreeview_row_delegate
//                    color:"transparent"
//                    height:15
//                }



//                /*
//                节点展开、收起的图标
//                */
//                branchDelegate: Image{      //节点展开、收缩的图标
//                    id: paratreeviewstyle_branch_delegate
//                    source: {
//                        return styleData.isExpanded ? "./tiny_icon/arrow_down.png" : "./tiny_icon/arrow_right.png"
//                    }
//                    width:10
//                    height:10
//                    MouseArea {
//                        id:paratreeviewstyle_branch_mousearea
//                        anchors.fill: parent
//                        hoverEnabled: true
//                        drag.target: paratreeviewstyle_branch_delegate

//                        onClicked: {
//                            if(styleData.isExpanded)
//                            {
//                                paratreeview.collapse(styleData.index)
//                            }
//                            else{
//                                paratreeview.expand(styleData.index)
//                            }

//                        }
//                    }
//                }








//            }
//        }

//    }

//}
