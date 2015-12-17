import QtQuick 2.0
import QtQuick.Controls 1.2

Item{
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
                placeholderText: qsTr("Text Field")
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
            Repeater{
                //model:eventsModel.selectedSharedEvent
            }
            Button{
                text: "*"
                onClicked:{
                    if (navigator){
                        navigator.push({item:Qt.resolvedUrl("MembersSelectionView.qml"), properties:{isMultiselect:"false"}})
                    }
                }
            }
        }
        Row {
            id: row3
            width: parent.width
            height: 40*(paidList.count+1)
            spacing: 10
            Label {
                id: coveredLabel
                width: 43
                height: 40
                text: qsTr("Paid:")
            }
            Column{
                ListView{
                    id: paidList
                    width: 200
                    height: 40
                    model:eventsModel.selectedSharedEvent.expenseList.currentExpenseItem.paid
                    delegate: Text{
                        text: Name
                    }
                }
                Button{
                    text: "*"
                    onClicked:{
                        if (navigator){
                            navigator.push({item:Qt.resolvedUrl("MembersSelectionView.qml"), properties:{isMultiselect:"true"}})
                        }
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

                    }
                }
            }
        }
    }
}

