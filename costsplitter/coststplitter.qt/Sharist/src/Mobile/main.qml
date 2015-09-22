import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ColumnLayout{
    ListView{
        width: 480;
        height: 240;
        model: eventsModel
        delegate: Text{text: "Event: "+ name}
    }
    Button{
        id: addNewSharedEvent
        text: "Add new event"
        onClicked: {}
    }
}
