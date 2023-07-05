import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt.labs.qmlmodels

import AnalyticFunctionEnums 1.0

Window {
    id: analytic_function_window
    width: 640
    height: 512
    title: "analytic function"
    x: Screen.width/2 - width/2
    y: Screen.height/2 - height/2
    
    modality: Qt.WindowModal
    onVisibleChanged:
    {
        if (visible)
        {
            if (analyticFunctionWindowAdapter.dataChangedFromExternal())
            {
                hflcal_based_tableview.updateAll()
                unizar_tableview.updateAll()
                icauchy_tableview.updateAll()
                huang_tableview.updateAll()
                huang_with_glass_tableview.updateAll()

                analyticFunctionWindowAdapter.dataSyncedWithUI()
            }
        }
    }
    
    Rectangle
    {
        id: rectangle
        width: 640
        height: 512
        Text
        {
            id: model_type_text
            anchors.top: parent.top
            anchors.topMargin: 20 + model_type_box.height / 4
            anchors.left: parent.left
            anchors.leftMargin: 20
            text: "Model Type: "
        }
        Text
        {
            id: num_gpu_threads_text
            anchors.top: parent.top
            anchors.topMargin: 20 + num_gpu_threads_textinput.height / 4
            anchors.left: model_type_box.right
            anchors.leftMargin: 40
            text: "GPU Threads: "
        }
        TextField
        {
            id: num_gpu_threads_textinput
            text: "512"
            color: "black"
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: num_gpu_threads_text.right
            anchors.leftMargin: 20
            // font.pixelSize: 25
            validator: IntValidator{bottom: 1}
            Component.onCompleted:
            {
                num_gpu_threads_textinput.text = analyticFunctionWindowAdapter.getCommonPara("num_gpu_threads_")
            }
            onTextChanged:
            {
                analyticFunctionWindowAdapter.setCommonPara("num_gpu_threads_", num_gpu_threads_textinput.text)
            }
        }

        ComboBox
        {
            id: model_type_box
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: model_type_text.right
            anchors.leftMargin: 20
            model:["Simplified", "Convolution"]
            width: 100
            // font.pixelSize: 25
            delegate: ItemDelegate
            {
                id: model_type_box_delegate
                contentItem: Text
                {
                    text: model_type_box.textRole
                        ? (Array.isArray(model_type_box.model)
                            ? modelData[model_type_box.textRole]
                            : model[model_type_box.textRole])
                        : modelData
                    // font.pixelSize:25
                    color: hovered? "green": "black"
                }
                hoverEnabled: model_type_box.hoverEnabled
            }
            Component.onCompleted: 
            {
                model_type_box.currentIndex = analyticFunctionWindowAdapter.getModelType()
            }

            onCurrentIndexChanged:
            {
                switch (currentIndex)
                {
                case AnalyticFunctionEnums.Simplified:
                {
                    detail_model_type_box.model = ["HFLCAL", "iHFLCAL", "bHFLCAL", "NEG"]
                    hflcal_based_tableview_boundry.visible = true
                    unizar_tableview_boundry.visible = false
                    huang_tableview_boundry.visible = false
                    huang_with_glass_tableview_boundry.visible = false
                    icauchy_tableview_boundry.visible = false

                    heliostat_with_glass_text.visible = false
                    heliostat_with_glass_checkbox.visible = false

                    analytic_function_window.width = hflcal_based_tableview_boundry.width

                    analyticFunctionWindowAdapter.setModelType(AnalyticFunctionEnums.Simplified)
                    analyticFunctionWindowAdapter.setSimplifiedModelType(AnalyticFunctionEnums.HFLCAL)
                    break
                }
                case AnalyticFunctionEnums.Convolution:
                {
                    detail_model_type_box.model = ["UNIZAR", "iCauchy", "Huang"]
                    hflcal_based_tableview_boundry.visible = false
                    unizar_tableview_boundry.visible = true
                    huang_tableview_boundry.visible = false
                    huang_with_glass_tableview_boundry.visible = false
                    icauchy_tableview_boundry.visible = false

                    heliostat_with_glass_text.visible = false
                    heliostat_with_glass_checkbox.visible = false

                    analytic_function_window.width = Math.max(unizar_tableview_boundry.width, 550)

                    analyticFunctionWindowAdapter.setModelType(AnalyticFunctionEnums.Convolution)
                    analyticFunctionWindowAdapter.setConvolutionModelType(AnalyticFunctionEnums.UNIZAR)
                    break
                }
                }
                detail_model_type_box.currentIndex = 0
                detail_model_type_text.text = model[currentIndex] + " Model Type: "
            }
        }
        Rectangle
        {
            id: splitter_1
            anchors.top: model_type_box.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            width: analytic_function_window.width
            height: 2
            color: "green"
        }
        Text
        {
            id: detail_model_type_text
            anchors.top: splitter_1.bottom
            anchors.topMargin: 20 + detail_model_type_box.height / 4
            anchors.left: parent.left
            anchors.leftMargin: 20
            text: "Simplified Model Type: "
        }

        ComboBox
        {
            id: detail_model_type_box
            anchors.left: detail_model_type_text.right
            anchors.leftMargin: 20
            anchors.top: splitter_1.bottom
            anchors.topMargin: 20
            // font.pixelSize: 25
            // width: 170
            model:["HFLCAL", "iHFLCAL", "bHFLCAL", "NEG"]
            Component.onCompleted: 
            {
                if (model_type_box.currentIndex == AnalyticFunctionEnums.Simplified)
                {
                    detail_model_type_box.currentIndex = analyticFunctionWindowAdapter.getSimplifiedModelType()
                }
                else
                {
                    detail_model_type_box.currentIndex = analyticFunctionWindowAdapter.getConvolutionModelType()
                }
            }
            delegate: ItemDelegate
            {
                id: detail_model_type_box_delegate
                contentItem: Text
                {
                    text: detail_model_type_box.textRole
                        ? (Array.isArray(detail_model_type_box.model)
                            ? modelData[detail_model_type_box.textRole]
                            : model[detail_model_type_box.textRole])
                        : modelData
                    // font.pixelSize:25
                    color: hovered? "green": "black"
                }
                hoverEnabled: detail_model_type_box.hoverEnabled
            }
            onCurrentIndexChanged:
            {
                if (model_type_box.currentIndex === AnalyticFunctionEnums.Simplified)
                {
                    analyticFunctionWindowAdapter.setSimplifiedModelType(currentIndex)
                }
                else
                {
                    analyticFunctionWindowAdapter.setConvolutionModelType(currentIndex)
                }
                if (model[currentIndex] === "UNIZAR")
                {
                    hflcal_based_tableview_boundry.visible = false
                    unizar_tableview_boundry.visible = true
                    huang_tableview_boundry.visible = false
                    huang_with_glass_tableview_boundry.visible = false
                    icauchy_tableview_boundry.visible = false

                    heliostat_with_glass_text.visible = false
                    heliostat_with_glass_checkbox.visible = false

                    analytic_function_window.width = Math.max(unizar_tableview_boundry.width, 550)
                }
                if (model[currentIndex] === "Huang")
                {
                    hflcal_based_tableview_boundry.visible = false
                    unizar_tableview_boundry.visible = false
                    icauchy_tableview_boundry.visible = false

                    if (heliostat_with_glass_checkbox.checked)
                    {
                        huang_tableview_boundry.visible = false
                        huang_with_glass_tableview_boundry.visible = true

                        analytic_function_window.width = huang_with_glass_tableview_boundry.width
                    }
                    else
                    {
                        huang_tableview_boundry.visible = true
                        huang_with_glass_tableview_boundry.visible = false

                        analytic_function_window.width = huang_tableview_boundry.width
                    }

                    heliostat_with_glass_text.visible = true
                    heliostat_with_glass_checkbox.visible = true
                }
                if (model[currentIndex] === "iCauchy")
                {
                    hflcal_based_tableview_boundry.visible = false
                    unizar_tableview_boundry.visible = false
                    huang_tableview_boundry.visible = false
                    huang_with_glass_tableview_boundry.visible = false
                    icauchy_tableview_boundry.visible = true

                    heliostat_with_glass_text.visible = false
                    heliostat_with_glass_checkbox.visible = false

                    analytic_function_window.width = Math.max(icauchy_tableview_boundry.width, 550)
                }
            }
        }
        Text
        {
            id: dni_text
            text: "DNI: "
            anchors.top: detail_model_type_box.bottom
            anchors.topMargin: 20 + dni_textinput.height / 4
            anchors.left: parent.left
            anchors.leftMargin: 20
        }
        TextField
        {
            id: dni_textinput
            text: "0"
            color: "black"
            anchors.top: detail_model_type_box.bottom
            anchors.topMargin: 20
            anchors.left: dni_text.right
            anchors.leftMargin: 20
            // font.pixelSize: 25
            validator: DoubleValidator{bottom: 0.0}
            Component.onCompleted:
            {
                dni_textinput.text = analyticFunctionWindowAdapter.getScenePara("DNI_")
            }
            onTextChanged:
            {
                analyticFunctionWindowAdapter.setScenePara("DNI_", dni_textinput.text)
            }
        }
        Text
        {
            id: csr_text
            text: "CSR: "
            anchors.top: detail_model_type_box.bottom
            anchors.topMargin: 20 + dni_textinput.height / 4
            anchors.left: dni_textinput.right
            anchors.leftMargin: 20
        }
        TextField
        {
            id: csr_textinput
            text: "0"
            color: "black"
            anchors.top: detail_model_type_box.bottom
            anchors.topMargin: 20
            anchors.left: csr_text.right
            anchors.leftMargin: 20
            // font.pixelSize: 25
            validator: DoubleValidator{bottom: 0.0}
            Component.onCompleted:
            {
                csr_textinput.text = analyticFunctionWindowAdapter.getScenePara("CSR_")
            }
            onTextChanged:
            {
                analyticFunctionWindowAdapter.setScenePara("CSR_", dni_textinput.text)
            }
        }
        Text
        {
            id: receiver_partition_text
            text: "Receiver Pixel Size (m): "
            anchors.top: csr_textinput.bottom
            anchors.topMargin: 20 + dni_textinput.height / 4
            anchors.left: parent.left
            anchors.leftMargin: 20
        }
        Text
        {
            id: receiver_partition_x_text
            text: "x: "
            anchors.top: csr_textinput.bottom
            anchors.topMargin: 20 + receiver_partition_x_textinput.height / 4
            anchors.left: receiver_partition_text.right
            anchors.leftMargin: 20
        }
        TextField
        {
            id: receiver_partition_x_textinput
            text: "1"
            color: "black"
            anchors.top: csr_textinput.bottom
            anchors.topMargin: 20
            anchors.left: receiver_partition_x_text.right
            anchors.leftMargin: 20
            // font.pixelSize: 25
            validator: DoubleValidator{bottom: 0.0}
            Component.onCompleted:
            {
                var vec2_text = analyticFunctionWindowAdapter.getSimulationPara("receiver_pixel_size_")
                var vec2_text_split = vec2_text.split(/,\s*/)
                receiver_partition_x_textinput.text = vec2_text_split[0]
            }
            onTextChanged:
            {
                analyticFunctionWindowAdapter.setSimulationPara("receiver_pixel_size_", receiver_partition_x_textinput.text + ", " + receiver_partition_y_textinput.text)
            }
        }
        Text
        {
            id: receiver_partition_y_text
            text: "y: "
            anchors.top: csr_textinput.bottom
            anchors.topMargin: 20 + receiver_partition_y_textinput.height / 4
            anchors.left: receiver_partition_x_textinput.right
            anchors.leftMargin: 20
        }
        TextField
        {
            id: receiver_partition_y_textinput
            text: "1"
            color: "black"
            anchors.top: csr_textinput.bottom
            anchors.topMargin: 20
            anchors.left: receiver_partition_y_text.right
            anchors.leftMargin: 20
            // font.pixelSize: 25
            validator: DoubleValidator{bottom: 0.0}
            Component.onCompleted:
            {
                var vec2_text = analyticFunctionWindowAdapter.getSimulationPara("receiver_pixel_size_")
                var vec2_text_split = vec2_text.split(/,\s*/)
                receiver_partition_y_textinput.text = vec2_text_split[1]
            }
            onTextChanged:
            {
                analyticFunctionWindowAdapter.setSimulationPara("receiver_pixel_size_", receiver_partition_x_textinput.text + ", " + receiver_partition_y_textinput.text)
            }
        }
        Text
        {
            id: projection_type_text
            text: "Projection Type: "
            anchors.top: receiver_partition_x_textinput.bottom
            anchors.topMargin: 20 + projection_type_box.height / 4
            anchors.left: parent.left
            anchors.leftMargin: 20
        }
        ComboBox
        {
            id: projection_type_box
            anchors.left: projection_type_text.right
            anchors.leftMargin: 20
            anchors.top: receiver_partition_x_textinput.bottom
            anchors.topMargin: 20
            // font.pixelSize: 25
            width: 100
            model: ["Parallel", "Gnomonic"]
            Component.onCompleted: 
            {
                projection_type_box.currentIndex = analyticFunctionWindowAdapter.getProjectionType()
            }
            onCurrentIndexChanged:
            {
                analyticFunctionWindowAdapter.setProjectionType(projection_type_box.currentIndex)
            }
            delegate: ItemDelegate
            {
                id: projection_type_box_delegate
                contentItem: Text
                {
                    text: projection_type_box.textRole
                        ? (Array.isArray(projection_type_box.model)
                            ? modelData[projection_type_box.textRole]
                            : model[projection_type_box.textRole])
                        : modelData
                    // font.pixelSize: 25
                    color: hovered? "green": "black"
                }
                hoverEnabled: projection_type_box.hoverEnabled
            }
        }
        Text
        {
            visible: false
            id: heliostat_with_glass_text
            text: "Heliostat with glass: "
            anchors.top: receiver_partition_x_textinput.bottom
            anchors.topMargin: 20 + projection_type_box.height / 4
            anchors.left: projection_type_box.right
            anchors.leftMargin: 20
        }
        CheckBox
        {
            visible: false
            id: heliostat_with_glass_checkbox
            anchors.top: receiver_partition_x_textinput.bottom
            anchors.topMargin: 20 + projection_type_box.height / 6
            anchors.left: heliostat_with_glass_text.right
            Component.onCompleted:
            {
                if (analyticFunctionWindowAdapter.getHeliostatType() === AnalyticFunctionEnums.WithGlass)
                {
                    heliostat_with_glass_checkbox.checked = true
                }
                else
                {
                    heliostat_with_glass_checkbox.checked = false
                }
            }
            onCheckedChanged:
            {
                if (detail_model_type_box.model[detail_model_type_box.currentIndex] === "Huang")
                {
                    if (checked)
                    {
                        huang_tableview_boundry.visible = false
                        huang_with_glass_tableview_boundry.visible = true

                        analytic_function_window.width = huang_with_glass_tableview_boundry.width

                        analyticFunctionWindowAdapter.setHeliostatType(AnalyticFunctionEnums.WithGlass)
                    }
                    else
                    {
                        huang_tableview_boundry.visible = true
                        huang_with_glass_tableview_boundry.visible = false

                        analytic_function_window.width = huang_tableview_boundry.width

                        analyticFunctionWindowAdapter.setHeliostatType(AnalyticFunctionEnums.WithoutGlass)
                    }
                }
            }
        }
        Text
        {
            id: tableview_text
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: projection_type_box.bottom
            font.pointSize: 12
            anchors.topMargin: 20
            text: "Heliostat Info: "
        }

        Rectangle
        {
            id: hflcal_based_tableview_boundry
            width: hflcal_based_tableview_header_repeater.count * 100 + hflcal_based_tableview_header_repeater.count - 1 + 40
            height: 512 / 2
            visible: false
            anchors.top: tableview_text.bottom
            onVisibleChanged:
            {
                if (visible)
                {
                    var rows_changed = analyticFunctionWindowAdapter.getRowsChanged(AnalyticFunctionEnums.HFLCALBasedTableView)
                    var i = 0;
                    for (i = 0; i < rows_changed.length; i++)
                    {
                        var current_row = rows_changed[i]
                        hflcal_based_tableview.updateRow(current_row)
                    }
                    analyticFunctionWindowAdapter.clearRowsChanged(AnalyticFunctionEnums.HFLCALBasedTableView)
                }
            }
            Row
            {
                id: hflcal_based_tableview_header
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 1

                Repeater
                {
                    id: hflcal_based_tableview_header_repeater
                    model: ["Heliostat ID", "Receiver ID", "Mirror Area", "Reflectivity", "σ Tracking", "σ Slope Error"]

                    Rectangle
                    {
                        id: hflcal_based_tableview_header_rect
                        width: 100
                        height: 25
                        border.width: 1
                        border.color: "#efefef"
                        color: "#efefef"
                        Text
                        {
                            text: modelData
                            font.bold: true
                            anchors.centerIn: parent
                        }
                    }
                }
            }

            TableView
            {
                id: hflcal_based_tableview
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                boundsMovement: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: TableModel.rowCount > 6
                    background: Rectangle
                    {
                        color:"#666666"
                    }
                    onActiveChanged:
                    {
                        active = true;
                    }
                    contentItem: Rectangle
                    {
                        implicitWidth  : 6
                        implicitHeight : 30
                        radius : 3
                        color  : "#848484"
                    }
                }
                model: TableModel
                {
                    TableModelColumn{display: "heliostat_id"}
                    TableModelColumn{display: "receiver_id"}
                    TableModelColumn{display: "mirror_area"}
                    TableModelColumn{display: "reflectivity"}
                    TableModelColumn{display: "sigma_tracking"}
                    TableModelColumn{display: "sigma_slope_error"}
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"
                    MouseArea
                    {
                        id: hflcal_based_tableview_mousearea
                        anchors.fill: parent
                        hoverEnabled: true
                        property bool needs_update: false
                        onExited:
                        {
                            if (needs_update)
                            {
                                hflcal_based_tableview.updateRow(row)
                                needs_update = false
                            }
                        }
                        TextEdit
                        {
                            text: display
                            readOnly: column <= 1 ? true : false
                            anchors.centerIn: parent
                            onTextChanged:
                            {
                                var current_heliostat_id = hflcal_based_tableview.model.rows[row].heliostat_id
                                switch (column)
                                {
                                    case 2: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "mirror_area_", text); break;
                                    case 3: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "reflectivity_", text); break;
                                    case 4: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "sigma_tracking_", text); break;
                                    case 5: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "sigma_slope_error_", text); break;
                                }
                                analyticFunctionWindowAdapter.addRowChanged(AnalyticFunctionEnums.HFLCALBasedTableView, row)
                                hflcal_based_tableview_mousearea.needs_update = true
                            }
                        }
                    }
                    
                }
                function updateRow(row)
                {
                    var current_heliostat_id = hflcal_based_tableview.model.rows[row].heliostat_id
                    model.setRow(row, {
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            reflectivity: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "reflectivity_"),
                            sigma_tracking: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_tracking_"),
                            sigma_slope_error: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_slope_error_"),
                        })
                }
                function updateAll()
                {
                    var heliostat_index_list = analyticFunctionWindowAdapter.getHeliostatIndices()
                    var heliostat_count = analyticFunctionWindowAdapter.getNumberOfHeliostats()
                    var i = 0;
                    for (i = 0; i < heliostat_index_list.length; i++)
                    {
                        var current_heliostat_id = heliostat_index_list[i]
                        model.appendRow({
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            reflectivity: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "reflectivity_"),
                            sigma_tracking: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_tracking_"),
                            sigma_slope_error: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_slope_error_"),
                        })
                    }
                }
                Component.onCompleted:
                {
                    hflcal_based_tableview.updateAll()
                }
            }
        }
        Rectangle
        {
            id: unizar_tableview_boundry
            width: unizar_tableview_header_repeater.count * 100 + unizar_tableview_header_repeater.count - 1 + 40
            height: 512 / 2
            visible: false
            anchors.top: tableview_text.bottom
            onVisibleChanged:
            {
                if (visible)
                {
                    var rows_changed = analyticFunctionWindowAdapter.getRowsChanged(AnalyticFunctionEnums.UNIZARTableView)
                    var i = 0;
                    for (i = 0; i < rows_changed.length; i++)
                    {
                        var current_row = rows_changed[i]
                        unizar_tableview.updateRow(current_row)
                    }
                    analyticFunctionWindowAdapter.clearRowsChanged(AnalyticFunctionEnums.UNIZARTableView)
                }
                
            }
            Row
            {
                id: unizar_tableview_header
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 1

                Repeater
                {
                    id: unizar_tableview_header_repeater
                    model: ["Heliostat ID", "Receiver ID", "Mirror Area", "Total Area"]

                    Rectangle
                    {
                        id: unizar_tableview_header_rect
                        width: 100
                        height: 25
                        border.width: 1
                        border.color: "#efefef"
                        color: "#efefef"
                        Text
                        {
                            text: modelData
                            font.bold: true
                            anchors.centerIn: parent
                        }
                    }
                }
            }

            TableView
            {
                id: unizar_tableview
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                boundsMovement: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: TableModel.rowCount > 6
                    background: Rectangle
                    {
                        color:"#666666"
                    }
                    onActiveChanged:
                    {
                        active = true;
                    }
                    contentItem: Rectangle
                    {
                        implicitWidth  : 6
                        implicitHeight : 30
                        radius : 3
                        color  : "#848484"
                    }
                }
                model: TableModel
                {
                    TableModelColumn{display: "heliostat_id"}
                    TableModelColumn{display: "receiver_id"}
                    TableModelColumn{display: "mirror_area"}
                    TableModelColumn{display: "total_area"}
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"
                    MouseArea
                    {
                        id: unizar_tableview_mousearea
                        anchors.fill: parent
                        hoverEnabled: true
                        property bool needs_update: false
                        onExited:
                        {
                            if (needs_update)
                            {
                                unizar_tableview.updateRow(row)
                                needs_update = false
                            }
                        }
                        TextEdit
                        {
                            text: display
                            readOnly: column <= 1 ? true : false
                            anchors.centerIn: parent
                            onTextChanged:
                            {
                                var current_heliostat_id = unizar_tableview.model.rows[row].heliostat_id
                                switch (column)
                                {
                                    case 2: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "mirror_area_", text); break;
                                    case 3: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "total_area_", text); break;
                                }
                                analyticFunctionWindowAdapter.addRowChanged(AnalyticFunctionEnums.UNIZARTableView, row)
                                unizar_tableview_mousearea.needs_update = true
                            }
                        }
                    }
                }
                function updateRow(row)
                {
                    var current_heliostat_id = unizar_tableview.model.rows[row].heliostat_id
                    model.setRow(row, {
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            total_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "total_area_"),
                        })
                }
                function updateAll()
                {
                    var heliostat_index_list = analyticFunctionWindowAdapter.getHeliostatIndices()
                    var heliostat_count = analyticFunctionWindowAdapter.getNumberOfHeliostats()
                    var i = 0;
                    for (i = 0; i < heliostat_index_list.length; i++)
                    {
                        var current_heliostat_id = heliostat_index_list[i]
                        model.appendRow({
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            total_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "total_area_"),
                        })
                    }
                }
                Component.onCompleted:
                {
                    unizar_tableview.updateAll()
                }
            }
        }
        Rectangle
        {
            id: huang_tableview_boundry
            width: huang_tableview_header_repeater.count * 100 + huang_tableview_header_repeater.count - 1 + 40
            height: 512 / 2
            visible: false
            anchors.top: tableview_text.bottom
            onVisibleChanged:
            {
                if (visible)
                {
                    var rows_changed = analyticFunctionWindowAdapter.getRowsChanged(AnalyticFunctionEnums.HuangTableView)
                    var i = 0;
                    for (i = 0; i < rows_changed.length; i++)
                    {
                        var current_row = rows_changed[i]
                        huang_tableview.updateRow(current_row)
                    }
                    analyticFunctionWindowAdapter.clearRowsChanged(AnalyticFunctionEnums.HuangTableView)
                }
            }
            Row
            {
                id: huang_tableview_header
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 1

                Repeater
                {
                    id: huang_tableview_header_repeater
                    model: ["Heliostat ID", "Receiver ID", "Mirror Area", "Reflectivity", "σ Tracking", "σ Slope Error"]

                    Rectangle
                    {
                        id: huang_tableview_header_rect
                        width: 100
                        height: 25
                        border.width: 1
                        border.color: "#efefef"
                        color: "#efefef"
                        Text
                        {
                            text: modelData
                            font.bold: true
                            anchors.centerIn: parent
                        }
                    }
                }
            }

            TableView
            {
                id: huang_tableview
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                boundsMovement: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: TableModel.rowCount > 6
                    background: Rectangle
                    {
                        color:"#666666"
                    }
                    onActiveChanged:
                    {
                        active = true;
                    }
                    contentItem: Rectangle
                    {
                        implicitWidth  : 6
                        implicitHeight : 30
                        radius : 3
                        color  : "#848484"
                    }
                }
                model: TableModel
                {
                    TableModelColumn{display: "heliostat_id"}
                    TableModelColumn{display: "receiver_id"}
                    TableModelColumn{display: "mirror_area"}
                    TableModelColumn{display: "reflectivity"}
                    TableModelColumn{display: "sigma_tracking"}
                    TableModelColumn{display: "sigma_slope_error"}
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"
                    MouseArea
                    {
                        id: huang_tableview_mousearea
                        anchors.fill: parent
                        hoverEnabled: true
                        property bool needs_update: false
                        onExited:
                        {
                            if (needs_update)
                            {
                                huang_tableview.updateRow(row)
                                needs_update = false
                            }
                        }
                        TextEdit
                        {
                            text: display
                            readOnly: column <= 1 ? true : false
                            anchors.centerIn: parent
                            onTextChanged:
                            {
                                var current_heliostat_id = huang_tableview.model.rows[row].heliostat_id
                                switch (column)
                                {
                                    case 2: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "mirror_area_", text); break;
                                    case 3: reflectivity: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "reflectivity_", text); break;
                                    case 4: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "sigma_tracking_", text); break;
                                    case 5: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "sigma_slope_error_", text); break;
                                }
                                analyticFunctionWindowAdapter.addRowChanged(AnalyticFunctionEnums.HuangTableView, row)
                                huang_tableview_mousearea.needs_update = true
                            }
                        }
                    }
                }
                function updateRow(row)
                {
                    var current_heliostat_id = huang_tableview.model.rows[row].heliostat_id
                    model.setRow(row, {
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            reflectivity: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "reflectivity_"),
                            sigma_tracking: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_tracking_"),
                            sigma_slope_error: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_slope_error_"),
                        })
                }
                function updateAll()
                {
                    var heliostat_index_list = analyticFunctionWindowAdapter.getHeliostatIndices()
                    var heliostat_count = analyticFunctionWindowAdapter.getNumberOfHeliostats()
                    var i = 0;
                    for (i = 0; i < heliostat_index_list.length; i++)
                    {
                        var current_heliostat_id = heliostat_index_list[i]
                        model.appendRow({
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            reflectivity: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "reflectivity_"),
                            sigma_tracking: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_tracking_"),
                            sigma_slope_error: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_slope_error_"),
                        })
                    }
                }
                Component.onCompleted:
                {
                    huang_tableview.updateAll()
                }
            }
        }
        Rectangle
        {
            id: huang_with_glass_tableview_boundry
            width: huang_with_glass_tableview_header_repeater.count * 130 + huang_with_glass_tableview_header_repeater.count - 1 + 40
            height: 512 / 2
            visible: false
            anchors.top: tableview_text.bottom
            onVisibleChanged:
            {
                if (visible)
                {
                    var rows_changed = analyticFunctionWindowAdapter.getRowsChanged(AnalyticFunctionEnums.HuangWithGlassTableView)
                    var i = 0;
                    for (i = 0; i < rows_changed.length; i++)
                    {
                        var current_row = rows_changed[i]
                        huang_with_glass_tableview.updateRow(current_row)
                    }
                    analyticFunctionWindowAdapter.clearRowsChanged(AnalyticFunctionEnums.HuangWithGlassTableView)
                }
            }
            Row
            {
                id: huang_with_glass_tableview_header
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 1

                Repeater
                {
                    id: huang_with_glass_tableview_header_repeater
                    model: ["Heliostat ID", "Receiver ID", "Mirror Area", "Reflectivity", "σ Tracking", "σ Surface Slope Error"
                        , "Refractivity", "σ Bottom Slope Error"]

                    Rectangle
                    {
                        id: huang_with_glass_tableview_header_rect
                        width: 130
                        height: 25
                        border.width: 1
                        border.color: "#efefef"
                        color: "#efefef"
                        Text
                        {
                            text: modelData
                            font.bold: true
                            anchors.centerIn: parent
                        }
                    }
                }
            }

            TableView
            {
                id: huang_with_glass_tableview
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                boundsMovement: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: TableModel.rowCount > 6
                    background: Rectangle
                    {
                        color:"#666666"
                    }
                    onActiveChanged:
                    {
                        active = true;
                    }
                    contentItem: Rectangle
                    {
                        implicitWidth  : 6
                        implicitHeight : 30
                        radius : 3
                        color  : "#848484"
                    }
                }
                model: TableModel
                {
                    TableModelColumn{display: "heliostat_id"}
                    TableModelColumn{display: "receiver_id"}
                    TableModelColumn{display: "mirror_area"}
                    TableModelColumn{display: "reflectivity"}
                    TableModelColumn{display: "sigma_tracking"}
                    TableModelColumn{display: "sigma_surface_slope_error"}
                    TableModelColumn{display: "refractivity"}
                    TableModelColumn{display: "sigma_bottom_slope_error"}
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 130
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"
                    MouseArea
                    {
                        id: huang_with_glass_tableview_mousearea
                        anchors.fill: parent
                        hoverEnabled: true
                        property bool needs_update: false
                        onExited:
                        {
                            if (needs_update)
                            {
                                hflcal_based_tableview.updateRow(row)
                                needs_update = false
                            }
                        }
                        TextEdit
                        {
                            text: display
                            readOnly: column <= 1 ? true : false
                            anchors.centerIn: parent
                            onTextChanged:
                            {
                                var current_heliostat_id = huang_with_glass_tableview.model.rows[row].heliostat_id
                                switch (column)
                                {
                                    case 2: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "mirror_area_", text); break;
                                    case 3: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "reflectivity_", text); break;
                                    case 4: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "sigma_tracking_", text); break;
                                    case 5: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "sigma_slope_error_", text); break;
                                    case 6: analyticFunctionWindowAdapter.setHeliostatWithGlassPara(current_heliostat_id, "refractivity_", text); break;
                                    case 7: analyticFunctionWindowAdapter.setHeliostatWithGlassPara(current_heliostat_id, "sigma_glass_down_slope_error_", text); break;
                                }
                                analyticFunctionWindowAdapter.addRowChanged(AnalyticFunctionEnums.HuangWithGlassTableView, row)
                                huang_with_glass_tableview_mousearea.needs_update = true
                            }
                        }
                    }
                }
                function updateRow(row)
                {
                    var current_heliostat_id = hflcal_based_tableview.model.rows[row].heliostat_id
                    model.setRow(row, {
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            reflectivity: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "reflectivity_"),
                            sigma_tracking: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_tracking_"),
                            sigma_surface_slope_error: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_slope_error_"),
                            refractivity: analyticFunctionWindowAdapter.getHeliostatWithGlassPara(current_heliostat_id, "refractivity_"),
                            sigma_bottom_slope_error: analyticFunctionWindowAdapter.getHeliostatWithGlassPara(current_heliostat_id, "sigma_glass_down_slope_error_"),
                        })
                }
                function updateAll()
                {
                    var heliostat_index_list = analyticFunctionWindowAdapter.getHeliostatIndices()
                    var heliostat_count = analyticFunctionWindowAdapter.getNumberOfHeliostats()
                    var i = 0;
                    for (i = 0; i < heliostat_index_list.length; i++)
                    {
                        var current_heliostat_id = heliostat_index_list[i]
                        model.appendRow({
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            reflectivity: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "reflectivity_"),
                            sigma_tracking: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_tracking_"),
                            sigma_surface_slope_error: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "sigma_slope_error_"),
                            refractivity: analyticFunctionWindowAdapter.getHeliostatWithGlassPara(current_heliostat_id, "refractivity_"),
                            sigma_bottom_slope_error: analyticFunctionWindowAdapter.getHeliostatWithGlassPara(current_heliostat_id, "sigma_glass_down_slope_error_"),
                        })
                    }
                }
                Component.onCompleted:
                {
                    huang_with_glass_tableview.updateAll()
                }
            }
        }
        Rectangle
        {
            id: icauchy_tableview_boundry
            width: icauchy_tableview_header_repeater.count * 100 + icauchy_tableview_header_repeater.count - 1 + 40
            height: 512 / 2
            visible: false
            anchors.top: tableview_text.bottom
            onVisibleChanged:
            {
                if (visible)
                {
                    var rows_changed = analyticFunctionWindowAdapter.getRowsChanged(AnalyticFunctionEnums.ICauchyTableView)
                    var i = 0;
                    for (i = 0; i < rows_changed.length; i++)
                    {
                        var current_row = rows_changed[i]
                        icauchy_tableview.updateRow(current_row)
                    }
                    analyticFunctionWindowAdapter.clearRowsChanged(AnalyticFunctionEnums.ICauchyTableView)
                }
            }
            Row
            {
                id: icauchy_tableview_header
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 1

                Repeater
                {
                    id: icauchy_tableview_header_repeater
                    model: ["Heliostat ID", "Receiver ID", "Mirror Area", "Reflectivity", "Diffusion Coeff"]

                    Rectangle
                    {
                        id: icauchy_tableview_header_rect
                        width: 100
                        height: 25
                        border.width: 1
                        border.color: "#efefef"
                        color: "#efefef"
                        Text
                        {
                            text: modelData
                            font.bold: true
                            anchors.centerIn: parent
                        }
                    }
                }
            }

            TableView
            {
                id: icauchy_tableview
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                boundsMovement: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: TableModel.rowCount > 6
                    background: Rectangle
                    {
                        color:"#666666"
                    }
                    onActiveChanged:
                    {
                        active = true;
                    }
                    contentItem: Rectangle
                    {
                        implicitWidth  : 6
                        implicitHeight : 30
                        radius : 3
                        color  : "#848484"
                    }
                }
                model: TableModel
                {
                    TableModelColumn{display: "heliostat_id"}
                    TableModelColumn{display: "receiver_id"}
                    TableModelColumn{display: "mirror_area"}
                    TableModelColumn{display: "reflectivity"}
                    TableModelColumn{display: "diffusion_coeff"}
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"
                    MouseArea
                    {
                        id: icauchy_tableview_mousearea
                        anchors.fill: parent
                        hoverEnabled: true
                        property bool needs_update: false
                        onExited:
                        {
                            if (needs_update)
                            {
                                hflcal_based_tableview.updateRow(row)
                                needs_update = false
                            }
                        }
                        TextEdit
                        {
                            text: display
                            readOnly: column <= 1 ? true : false
                            anchors.centerIn: parent
                            onTextChanged:
                            {
                                var current_heliostat_id = icauchy_tableview.model.rows[row].heliostat_id
                                switch (column)
                                {
                                    case 2: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "mirror_area_", text); break;
                                    case 3: analyticFunctionWindowAdapter.setHeliostatPara(current_heliostat_id, "reflectivity_", text); break;
                                    case 4: analyticFunctionWindowAdapter.setModelPara(current_heliostat_id, 
                                AnalyticFunctionEnums.Convolution, AnalyticFunctionEnums.ICauchy, "diffusion_coeff_", text); break;
                                }
                                analyticFunctionWindowAdapter.addRowChanged(AnalyticFunctionEnums.ICauchyTableView, row)
                                icauchy_tableview_mousearea.needs_update = true
                            }
                        }
                    }
                }
                function updateRow(row)
                {
                    var current_heliostat_id = icauchy_tableview.model.rows[row].heliostat_id
                    model.setRow(row, {
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            reflectivity: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "reflectivity_"),
                            diffusion_coeff: analyticFunctionWindowAdapter.getModelPara(current_heliostat_id, 
                            AnalyticFunctionEnums.Convolution, AnalyticFunctionEnums.ICauchy, "diffusion_coeff_"),
                        })
                }
                function updateAll()
                {
                    var heliostat_index_list = analyticFunctionWindowAdapter.getHeliostatIndices()
                    var heliostat_count = analyticFunctionWindowAdapter.getNumberOfHeliostats()
                    var i = 0;
                    for (i = 0; i < heliostat_index_list.length; i++)
                    {
                        var current_heliostat_id = heliostat_index_list[i]
                        model.appendRow({
                            checkable: true,
                            heliostat_id: current_heliostat_id,
                            receiver_id: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "receiver_id_"),
                            mirror_area: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "mirror_area_"),
                            reflectivity: analyticFunctionWindowAdapter.getHeliostatPara(current_heliostat_id, "reflectivity_"),
                            diffusion_coeff: analyticFunctionWindowAdapter.getModelPara(current_heliostat_id, AnalyticFunctionEnums.Convolution, AnalyticFunctionEnums.ICauchy, "diffusion_coeff_"),
                        })
                    }
                }
                Component.onCompleted:
                {
                    icauchy_tableview.updateAll()
                }
            }
        }
    }
}