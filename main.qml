import QtQuick 1.1

Rectangle {
    width: 400
    height: 300
    id: main
    objectName: "mainWindowQml"
    
    Column {
        Text {
            id: "inputString"
            text: model.inputString
            font.family: "Helvetica"
            font.pointSize: 12
            color: "red"
        }
    }
}
