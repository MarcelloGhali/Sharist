import QtQuick 2.0
import QtQuick.Controls 1.3
import Sharist.Models 1.0

Item {
    width: 320
    height: 400
    property bool isMultiselect
    Component {
       id: memberDelegate
       Item{
           width: parent.width
           height: 40
           Rectangle{
               id: memberCntr
               width: parent.width
               height: parent.height
               radius: 5
               color: { Selected ? "lightsteelblue" : "white" }
               Text {
                   text: Name
               }
           }
           MouseArea{
               anchors.fill: parent
               onClicked: {
                   if (!isMultiselect){
                      eventsModel.selectedSharedEvent.memberList.deselect(index);
                   }

                   Selected=!Selected;
               }
           }
       }
    }

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
            delegate:memberDelegate
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
                        if (isMultiselect)
                            eventsModel.selectedSharedEvent.expenseList.currentExpenseItem.paid = eventsModel.selectedSharedEvent.memberList;
                        else
                            eventsModel.selectedSharedEvent.expenseList.currentExpenseItem.owner = eventsModel.selectedSharedEvent.memberList.firstSelected;
                        navigator.pop()
                    }
                }
            }
        }
    }
}

