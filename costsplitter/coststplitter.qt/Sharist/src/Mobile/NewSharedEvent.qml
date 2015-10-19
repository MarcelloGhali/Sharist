import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Column{
    id:form
    width: parent.width
    spacing: 10
    Label{
        text: "Name:"
    }
    TextInput{
        id: eventName
        height: 40
        width: parent.width
        cursorVisible: true
    }
    Button{
        id: addNewSharedEvent
        width: parent.width
        text: "Save"
        onClicked: {
            eventsModel.addSharedEvent(eventName.text)
            if (navigator){
                navigator.pop()
            }
        }
    }
}

