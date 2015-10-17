import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    width: 100
    height: 62
    property var model
    Text{
        text: model.name
    }

    Button{
        id: addNewSharedEvent
        text: "Back"
        onClicked: {
            if (navigator){
                navigator.pop()
            }
        }
    }
}

