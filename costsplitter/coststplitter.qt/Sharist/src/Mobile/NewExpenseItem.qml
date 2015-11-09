import QtQuick 2.0
import QtQuick.Controls 1.2

Item{
    width: 320
    height: 400
    Button{
        id: back
        text: "Back"
        onClicked: {
            if (navigator){
                navigator.pop()
            }
        }
    }
}

