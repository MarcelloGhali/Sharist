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
    Row{
        width: parent.width
        Button{
            id: backBtn
            text: "Back"
            onClicked: {
                if (navigator){
                    navigator.pop()
                }
            }
        }
        Button{
            id: addNewSharedEvent
            text: "Save"
            onClicked: {
                eventsModel.addSharedEvent(eventName.text)
                if (navigator){
                    navigator.pop()
                }
            }
        }
    }
}

