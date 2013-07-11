import QtQuick 1.1

Rectangle {
    width: 400
    height: 300
    id: main
    objectName: "mainWindowQml"
    
    Column {
        spacing: 2

        Text {
            id: "inputString"
            text: mainModel.inputString
            font.family: "Helvetica"
            font.pointSize: 12
            color: "red"
        }
        Row {
            spacing: 0
            
            Repeater {
                id: repeater
                model: mainModel.candidateWords

                Text {
                    id: "candidateWord"
                    text: cddLabel + " " + cddText + "  "
                    font.family: "Helvetica"
                    font.pointSize: 12
                    color: "red"
                }
            }
        }
    }
}
