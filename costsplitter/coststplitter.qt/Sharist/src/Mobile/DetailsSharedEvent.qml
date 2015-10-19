import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Sharist.Models 1.0

Column{
    Text{
        text: eventsModel.selectedSharedEvent.name
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

