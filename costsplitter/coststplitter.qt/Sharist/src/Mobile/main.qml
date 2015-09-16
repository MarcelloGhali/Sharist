import QtQuick 2.4

ListView{
    width: 240;
    height: 480;

    model: eventsModel
    delegate: Text{text: "Event: "+ name}
}
