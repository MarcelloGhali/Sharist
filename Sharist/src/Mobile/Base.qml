import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.0

Item{
    height: 480
    width: 320
    StackView{
        id: navigator
        anchors.fill: parent
        initialItem: Qt.resolvedUrl("ListSharedEvent.qml")
    }
}
