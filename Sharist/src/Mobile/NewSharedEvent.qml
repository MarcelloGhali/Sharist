import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Sharist.Models 1.0

Item{
    id:form
    width: 320
    height: 400
    Column{
        anchors.fill: parent
        Label{
            width: parent.width
            text: "Name:"
        }
        TextInput{
            id: eventName
            height: 40
            width: parent.width
            cursorVisible: true
        }
        Binding{target: viewmodel; property: "name"; value:eventName.text}
        Row{
            width: parent.width
            spacing: 10
            Button{
                id: backBtn
                text: "Back"
                onClicked: {
//                    if (navigator){
//                        navigator.pop()
//                    }
                }
            }
            Button{
                id: addNewSharedEvent
                text: "Save"
                onClicked: {
                    viewmodel.Save();
//                    if (navigator){
//                        navigator.pop()
//                    }
                }
            }
        }
    }
}

