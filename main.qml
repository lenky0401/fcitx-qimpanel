import QtQuick 1.1

Rectangle {
    width: 400
    height: 300
    id: main
    objectName: "mainWindowQml"
    
    function update_input_string(string, attributes_list) {
        inputString.text = string
    }

    Column {
        Text {
            id: "inputString"
            text: "Hello-Hinata!"
            font.family: "Helvetica"
            font.pointSize: 24
            color: "red"
        }
    }
}
