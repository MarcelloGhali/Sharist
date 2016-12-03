import QtQuick 2.0
import QtQuick.Controls 1.2
import Sharist.Models 1.0

Item{
    id:newExpenseItem
//    width: 320
//    height: 400
    property ExpenseNewView viewmodel: viewmodelExpenseNewView
    Column {
        id: column1
        spacing: 10
        anchors.fill: parent
        Row {
            id: row1
            width: parent.width
            height: 40
            spacing: 10
            Label {
                id: amountLabel
                width: 43
                height: 40
                text: qsTr("Amount:")
            }
            TextField {
                id: totalTxt
            }
            Binding{target: viewmodel; property: "total"; value:totalTxt.text}
        }
        //TODO: update a paid list, if owner has changed
        //TODO: add a flag, if you just lended a money to a person
        Row {
            id: row2
            width: parent.width
            height: 40
            spacing: 10
            Label {
                id: ownerLabel
                width: 43
                height: 40
                text: qsTr("Owner:")
            }
            SelectableListView{
                isMultiselect: false
                context: viewmodel.ownerModel
            }
        }
        Row {
            id: row3
            width: parent.width
            height: 80
            spacing: 10
            Label {
                id: coveredLabel
                width: 43
                height: 40
                text: qsTr("Paid:")
            }
            SelectableListView{
                isMultiselect: true
                context: viewmodel.paidModel
            }
        }
        Row {
            id: row4
            width: parent.width
            height: 40
            spacing: 10
            Button{
                id: backBtn
                text: "Back"
                onClicked: {
                    viewmodel.NavigateBack();
                }
            }
            Button{
                id: saveBtn
                text: "Save"
                onClicked: {
                    viewmodel.Save()
                }
            }
        }
    }
}

