import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQml.Models 2.3

Item {
    id: dragDelegate
    
    MouseArea {
        id: dragArea
        
        property bool held: false
        property int delegateIndex: index
        
        anchors { left: parent.left; right: parent.right }
        height: content.height
        
        drag.target:  held ? content : undefined
        drag.axis: Drag.YAxis
        
        onPressed:  held = true
        onReleased: held = false
        
        onHeldChanged: {
            if (!held)
                sorterModel.moveItems(root.fromIndex, root.toIndex)
        }
        
        Rectangle {
            id: content
            
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            width: dragArea.width
            height: dragDelegate.height
            
            border.width: 1
            border.color: "lightsteelblue"
            
            color: dragArea.held ? "lightsteelblue" : "white"
            Behavior on color { ColorAnimation { duration: 100 } }
            
            radius: 2
            
            Drag.active: dragArea.held
            Drag.source: dragArea
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2
            
            states: State {
                when: dragArea.held
                
                ParentChange { target: content; parent: root }
                AnchorChanges {
                    target: content
                    anchors { horizontalCenter: undefined; verticalCenter: undefined }
                }
            }
            
            Column {
                id: column
                
                anchors {
                    margins: 2
                    verticalCenter: parent.verticalCenter
                }
                
                Row {
                    spacing: 10

                    Text {
                        anchors.leftMargin: 10
                        color: "red"
                        text: index + 1
                    }

                    Text {
                        text: fileName
                    }
                }
            }
        }
        
        DropArea {
            anchors { fill: parent; margins: 10 }
            
            onEntered: {
                root.fromIndex = drag.source.delegateIndex
                root.toIndex = dragArea.delegateIndex
            }
        }
    }
}
