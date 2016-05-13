import QtQuick 2.0
import QtQuick.Controls 1.2
import Sharist.Models 1.0

Item{
    id:newExpenseItem
    width: 320
    height: 400
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
                id: textField1
                text: eventsModel.selectedSharedEvent.expenseList.currentExpenseItem.cost
            }
        }
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
            Column{
                Button{
                    text: "*"
                    onClicked:{
                        if (navigator){
                            navigator.push({item:Qt.resolvedUrl("MembersSelectionView.qml"), properties:{isMultiselect:false}})
                        }
                    }
                }
                Text{
                    text: eventsModel.selectedSharedEvent.expenseList.currentExpenseItem.owner.name
                }
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
            Column{
                Button{
                    text: "*"
                    onClicked:{
                        if (navigator){
                            navigator.push({item:Qt.resolvedUrl("MembersSelectionView.qml"), properties:{isMultiselect:"true"}})
                        }
                    }
                }
                ListView{
                    id: paidList
                    height: 40
                    width: 200
                    model:eventsModel.selectedSharedEvent.expenseList.currentExpenseItem.paid
                    delegate: Text{
                        text: Name
                    }
                }
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
                    if (navigator){
                        navigator.pop()
                    }
                }
            }
            Button{
                id: saveBtn
                text: "Save"
                onClicked: {
                    if (navigator){
                        //check cost value
                        var costVal = textField1.text;
                        if (costVal!="" && costVal>0){
                            eventsModel.selectedSharedEvent.expenseList.currentExpenseItem.cost = costVal;
                            eventsModel.selectedSharedEvent.AddExpenseItem(eventsModel.selectedSharedEvent.expenseList.currentExpenseItem);
                            eventsModel.selectedSharedEvent.memberList.deselect();
                            navigator.pop()
                        }
                    }
                }
            }
        }
    }
}

