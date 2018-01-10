import QtQuick 2.7
import QtQuick.Controls 1.4
//import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Сортировщик")

    Item {
        id: root
        anchors.fill: parent

        property int fromIndex: 0
        property int toIndex: 0

        Column {
            anchors.fill: parent
            spacing: 20

            ScrollView {
                width: parent.width
                height: 430

                ListView {
                    id: view

                    anchors.fill: parent
                    model: sorterModel
                    spacing: 4
                    clip: true
                    delegate: DragDelegate {
                        width: parent.width
                        height: 30
                    }
                }
            }

            Row {
                spacing: 10

                TextField {
                    readOnly: true
                    width: 360
                }

                Button {
                    text: qsTr("Открыть папку")
                    onClicked: fileDialog.open()
                }

                Button {
                    text: qsTr("Сохранить изменения")
                }
            }

        }

        FileDialog {
            id: fileDialog

            selectFolder: true
            folder: shortcuts.home
            onAccepted: sorterModel.refreshModel(fileUrl)
        }
    }
}
