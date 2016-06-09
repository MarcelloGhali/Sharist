import QtQuick 2.0
import QtQuick.Controls 1.3
import Sharist.Models 1.0

Item {
    width: 320
    height: 400
    property bool isMultiselect
    property SelectableListViewModel context
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
                       var i;
                       //deselecting all previous
                       for(i = 0; i<context.rowCount(); i++){
                            context.setData(context.index(i,0), false, 0x0101);
                       }

                       Selected = true;
                   }
                   else{
                        Selected=!Selected;
                   }
               }
           }
       }
    }

    ListView{
        model: context
        width: parent.width
        height: 4*40
        delegate: memberDelegate
    }
}

