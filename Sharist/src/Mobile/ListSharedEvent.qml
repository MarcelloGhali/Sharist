import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item{
    id: mainWindow
    width: 320
    height: 400
    Component {
       id: eventDelegate
       Item{
           width: parent.width
           height: 40
           Text { text: '<b>Event name:</b> ' + name }
           MouseArea{
               anchors.fill: parent
               onClicked: {
                   list.currentIndex = index
                   if (navigator){
                       navigator.push({
                            item: Qt.resolvedUrl("DetailsSharedEvent.qml"),
                            properties:{
                                    eventModel: eventsModel.selectedIndex = index
                            }
                        })
                   }
               }
           }
       }
    }
    Column{
        spacing: 10
        anchors.fill: parent
        ListView{
            id: list
            //clip: true
            model: eventsModel
            width:parent.width
            height:4*40
            spacing: 10
            boundsBehavior: Flickable.StopAtBounds
            delegate: eventDelegate
            highlight: Rectangle{color:"lightsteelblue"; radius: 5}
            focus:true
        }
        Button{
            id: addNewSharedEvent
            width: parent.width
            text: "Add new event"
            onClicked: {
                if (navigator){
                    navigator.push({item:Qt.resolvedUrl("NewSharedEvent.qml")})
                }
            }
        }
    }
}

