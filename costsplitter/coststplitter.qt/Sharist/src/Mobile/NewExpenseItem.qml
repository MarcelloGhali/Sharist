import QtQuick 2.0
import QtQuick.Controls 1.2

Column{
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

