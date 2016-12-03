import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Sharist.Models 1.0

Item{
//    width: 320
//    height: 400
    property SharedEventDetailsView viewmodel : viewmodelDetailsEventView
    Column{
        spacing: 10
        anchors.fill: parent
        Text{
            width: parent.width
            text: viewmodel.eventModel.name
            horizontalAlignment: Text.AlignHCenter
            height: 40
        }
        ListView{
            id: expenses
            model: viewmodel.eventModel.expenseList
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
            text: viewmodel.eventModel.result
            height: 80
        }
        Row{
            width: parent.width
            spacing: 10
            Button{
                id: backBtn
                text: "Back"
                onClicked: {
                    viewmodel.NavigateBack();
                }
            }
            Button{
                id: addExpenseBtn
                text: "Add expense"
                onClicked: {
                    viewmodel.AddExpense();
                }
            }
            Button{
                id: addMemberBtn
                text: "Add member"
                onClicked: {
                    viewmodel.AddMember();
                }
            }
        }
    }
}
