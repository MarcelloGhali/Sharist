import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Sharist.Models 1.0

Item{
    id: mainWindow
//    width: 320
//    height: 400
    property SharedEventListView viewmodel : viewmodelEventsListView
    Component {
       id: eventDelegate
       Item{
           width: parent.width
           height: 40
           Text { text: '<b>Event name:</b> ' + name }
           MouseArea{
               anchors.fill: parent
               onClicked: {
                   viewmodel.NavigateToDetails(index);
               }
           }
       }
    }
    Column{
        spacing: 10
        anchors.fill: parent
        ListView{
            id: list
            clip: true
            model: viewmodel.eventsList
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
                viewmodel.NavigateToNew();
            }
        }
    }
}

