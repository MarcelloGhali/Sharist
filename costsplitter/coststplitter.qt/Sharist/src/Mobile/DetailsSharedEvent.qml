import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Sharist.Models 1.0

Item{
    width: 320
    height: 400
    Column{
        spacing: 10
        anchors.fill: parent
        Text{
            width: parent.width
            text: eventsModel.selectedSharedEvent.name
            horizontalAlignment: Text.AlignHCenter
            height: 40
        }
        ListView{
            id: expenses
            model: eventsModel.selectedSharedEvent.expenseList
            delegate: Text {
                text: model.display
                height: 40
                width: parent.width
            }
            height: 4*40
            width:parent.width
            highlight: Rectangle{color:"lightsteelblue"; radius: 5}
            focus:true
        }
        Text{
            width: parent.width
            text: eventsModel.selectedSharedEvent.result
            height: 80
        }
        Row{
            width: parent.width
            spacing: 10
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
                        eventsModel.selectedSharedEvent.expenseList.createTempExpense();
                        navigator.push({item:Qt.resolvedUrl("NewExpenseItem.qml")})
                }
            }
        }
    }
}
