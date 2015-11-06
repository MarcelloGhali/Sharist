import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Sharist.Models 1.0

Rectangle{
    Column{
        spacing: 10
        anchors.fill: parent
        Text{
            text: eventsModel.selectedSharedEvent.name
            height: 40
        }
        ListView{
            id: expenses
            model: eventsModel.selectedSharedEvent.expenseList
            delegate: Text {
                text: model.display
                height: 40
            }
            height: 40
            width:parent.width
            clip: true
            highlight: Rectangle{color:"lightsteelblue"}
            focus:true

        }
        Row{
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
                id: addExpenseBtn
                text: "Add expense"
                onClicked: {
                    if (navigator)
                        navigator.push({item:Qt.resolvedUrl("NewExpenseItem.qml")})
                }
            }
        }
    }
}
