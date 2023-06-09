import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt.labs.qmlmodels

Window {
    id: analytic_function_window
    width: 640
    height: 512
    title: "analytic function"
    x: Screen.width/2 - width/2
    y: Screen.height/2 - height/2
    
    modality: Qt.WindowModal
    
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

            onCurrentIndexChanged:
            {
                switch (currentIndex)
                {
                case 0:
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
                    break
                }
                case 1:
                {
                    detail_model_type_box.model = ["UNIZAR", "iCauchy", "Huang"]
                    hflcal_based_tableview_boundry.visible = false
                    unizar_tableview_boundry.visible = true
                    huang_tableview_boundry.visible = false
                    huang_with_glass_tableview_boundry.visible = false
                    icauchy_tableview_boundry.visible = false

                    heliostat_with_glass_text.visible = false
                    heliostat_with_glass_checkbox.visible = false

                    analytic_function_window.width = unizar_tableview_boundry.width
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
                if (model[currentIndex] === "UNIZAR")
                {
                    hflcal_based_tableview_boundry.visible = false
                    unizar_tableview_boundry.visible = true
                    huang_tableview_boundry.visible = false
                    huang_with_glass_tableview_boundry.visible = false
                    icauchy_tableview_boundry.visible = false

                    heliostat_with_glass_text.visible = false
                    heliostat_with_glass_checkbox.visible = false

                    analytic_function_window.width = unizar_tableview_boundry.width
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

                    analytic_function_window.width = icauchy_tableview_boundry.width
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
            onCheckedChanged:
            {
                if (detail_model_type_box.model[detail_model_type_box.currentIndex] === "Huang")
                {
                    if (checked)
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
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: tableModel.rowCount > 6
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

                    rows: [
                        {
                            heliostat_id: "0",
                            receiver_id: "0",
                            mirror_area: "100",
                            reflectivity: "0.88",
                            sigma_tracking: "0.0",
                            sigma_slope_error: "0.0",
                        },
                        {
                            heliostat_id: "1"
                        },
                        {
                            heliostat_id: "2"
                        }
                    ]
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"

                    TextEdit
                    {
                        text: display
                        readOnly: false
                        anchors.centerIn: parent
                    }
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
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: tableModel.rowCount > 6
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

                    rows: [
                        {
                            heliostat_id: "0",
                            receiver_id: "0",
                            mirror_area: "100",
                            total_area: "100",
                        },
                        {
                            heliostat_id: "1"
                        },
                        {
                            heliostat_id: "2"
                        }
                    ]
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"

                    TextEdit
                    {
                        text: display
                        readOnly: false
                        anchors.centerIn: parent
                    }
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
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: tableModel.rowCount > 6
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

                    rows: [
                        {
                            heliostat_id: "0",
                            receiver_id: "1",
                            mirror_area: "100",
                            reflectivity: "0.88",
                            sigma_tracking: "0.0",
                            sigma_slope_error: "0.0"
                        },
                        {
                            heliostat_id: "1"
                        },
                        {
                            heliostat_id: "2"
                        }
                    ]
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"

                    TextEdit
                    {
                        text: display
                        readOnly: false
                        anchors.centerIn: parent
                    }
                }
            }
        }
        Rectangle
        {
            id: huang_with_glass_tableview_boundry
            width: huang_with_glass_tableview_header_repeater.count * 125 + huang_with_glass_tableview_header_repeater.count - 1 + 40
            height: 512 / 2
            visible: false
            anchors.top: tableview_text.bottom
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
                    model: ["Heliostat ID", "Receiver ID", "Mirror Area", "Reflectivity", "σ Tracking", "σ Slope Error"
                        , "Refractivity", "σ Glass Refract 1st", "σ Glass Reflect", "σ Glass Refract 2nd"]

                    Rectangle
                    {
                        id: huang_with_glass_tableview_header_rect
                        width: 125
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
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: tableModel.rowCount > 6
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
                    TableModelColumn{display: "refractivity"}
                    TableModelColumn{display: "sigma_glass_refract_1"}
                    TableModelColumn{display: "sigma_glass_reflect"}
                    TableModelColumn{display: "sigma_glass_refract_2"}

                    rows: [
                        {
                            heliostat_id: "0",
                            receiver_id: "1",
                            mirror_area: "100",
                            reflectivity: "0.88",
                            sigma_tracking: "0.0",
                            sigma_slope_error: "0.0",
                            refractivity: "0.7",
                            sigma_glass_refract_1: "0.4, 0.4",
                            sigma_glass_reflect: "0.2",
                            sigma_glass_refract_2: "0.5, 0.5"
                        },
                        {
                            heliostat_id: "1"
                        },
                        {
                            heliostat_id: "2"
                        }
                    ]
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 125
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"

                    TextEdit
                    {
                        text: display
                        readOnly: false
                        anchors.centerIn: parent
                    }
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
                    model: ["Heliostat ID", "Receiver ID", "Diffusion Coeff"]

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
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 46
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar
                {
                    anchors.right:parent.right
                    anchors.rightMargin: 0
                    visible: tableModel.rowCount > 6
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
                    TableModelColumn{display: "diffusion_coeff"}

                    rows: [
                        {
                            heliostat_id: "0",
                            receiver_id: "1",
                            diffusion_coeff: "0.2"
                        },
                        {
                            heliostat_id: "1"
                        },
                        {
                            heliostat_id: "2"
                        }
                    ]
                }
                delegate: Rectangle
                {
                    color: "#efefef"
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: 1
                    border.color: "#efefef"

                    TextEdit
                    {
                        text: display
                        readOnly: false
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
}