import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Layouts
import CustomComponents 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1000
    height: 700
    title: "Touchstone Viewer"
    color: "#f5f5f5"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 15

        RowLayout {
            Layout.fillWidth: true
            spacing: 15

            Button {
                text: "Load Touchstone File"
                onClicked: fileDialog.open()
                Layout.preferredWidth: 200
            }

            Button {
                text: "Reload"
                onClicked: plot.update()
                Layout.preferredWidth: 100
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#e0e0e0"
            }

            Label { text: "Grid:" }
            ColorPicker {
                id: gridColorPicker
                onSelectedColorChanged: plot.gridColor = selectedColor
            }

            Label { text: "Line:" }
            ColorPicker {
                id: lineColorPicker
                selectedColor: plot.lineColor
                onSelectedColorChanged: plot.lineColor = selectedColor
            }

            Label { text: "X Ticks:" }
            SpinBox {
                editable: true
                from: 3; to: 20
                value: plot.numXTicks
                onValueChanged: plot.numXTicks = value
            }

            Label { text: "Y Ticks:" }
            SpinBox {
                editable: true
                from: 3; to: 20
                value: plot.numYTicks
                onValueChanged: plot.numYTicks = value
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            border.color: "#cccccc"
            border.width: 1
            radius: 4

            BusyIndicator {
                id: busyIndicator
                running: false
                anchors.centerIn: parent
                z: 1
            }

            PlotItem {
                id: plot
                anchors.fill: parent
                anchors.margins: 10
                points: dataModel.points
                gridColor: "#e0e0e0"
                axisColor: "#404040"
                textColor: "#606060"
                lineColor: "#1a73e8"
                numXTicks: 8
                numYTicks: 6
            }
        }

        FileDialog {
            id: fileDialog
            title: "Select Touchstone File"
            nameFilters: ["Touchstone files (*.s1p *.s2p *.snp)", "All files (*)"]
            onAccepted: {
                const filePath = selectedFile.toString().replace("file:///", "");
                dataModel.loadFile(filePath);
            }
        }
    }

    Dialog {
        id: errorDialog
        title: ""
        anchors.centerIn: parent
        modal: true
        standardButtons: Dialog.Ok

        property string errorTitle: ""
        property string errorMessage: ""

        width: Math.min(mainWindow.width * 0.8, 500)

        background: Rectangle {
            color: "white"
            border.color: "#cccccc"
            border.width: 1
            radius: 4
        }

        ColumnLayout {
            width: parent.width
            spacing: 10
            anchors.centerIn: parent

            Label {
                text: errorDialog.errorTitle
                font.bold: true
                font.pixelSize: 16
                Layout.alignment: Qt.AlignHCenter
                color: "#d32f2f"
            }

            Rectangle {
                height: 1
                color: "#e0e0e0"
                Layout.fillWidth: true
            }

            Label {
                text: errorDialog.errorMessage
                wrapMode: Text.Wrap
                Layout.fillWidth: true
                Layout.maximumWidth: errorDialog.width - 40
            }
        }
    }

    Connections {
        target: dataModel

        function onErrorOccurred(title, msg) {
            errorDialog.errorTitle = title;
            errorDialog.errorMessage = msg;
            errorDialog.open();
        }

        function onLoadingStarted() {
            busyIndicator.running = true;
        }

        function onLoadingFinished() {
            busyIndicator.running = false;
        }
    }

    component ColorPicker : Rectangle {
        id: colorPickerRoot
        property color selectedColor: "#e0e0e0"

        width: 30
        height: 30
        radius: 4
        border.color: "#cccccc"
        border.width: 1

        ColorDialog {
            id: colorDialog
            selectedColor: colorPickerRoot.selectedColor
            onAccepted: colorPickerRoot.selectedColor = selectedColor
        }

        MouseArea {
            anchors.fill: parent
            onClicked: colorDialog.open()
        }

        Rectangle {
            anchors.fill: parent
            anchors.margins: 2
            color: parent.selectedColor
            radius: 2
        }
    }
}
