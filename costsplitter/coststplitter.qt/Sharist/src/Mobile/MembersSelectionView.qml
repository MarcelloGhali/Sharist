import QtQuick 2.0
import QtQuick.Controls 1.3

Item {
    width: 320
    height: 400
    Column{
        spacing: 10
        anchors.fill: parent
        Text {
            id: text1
            text: qsTr("Members")
            horizontalAlignment: Text.AlignHCenter
            height: 40
            width: parent.width
        }
        ListView{
            model: eventsModel.selectedSharedEvent.memberList
            width: parent.width
            height: 4*40
            delegate: Text {
                text: model.display
                height: 40
                width: parent.width
            }
            highlight: Rectangle{color:"lightsteelblue"; radius: 5}
        }
        Row{
            width: parent.width
            height: 40
            spacing: 10

            Button {
                id: button1
                text: qsTr("Back")
                onClicked: {
                    if (navigator){
                        navigator.pop()
                    }
                }
            }

            Button {
                id: button2
                text: qsTr("Add")
            }

        }
    }
}

