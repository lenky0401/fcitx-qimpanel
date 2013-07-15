import QtQuick 1.1

Rectangle {
    width: layout.width
    height: layout.height
    id: mainWindow
    objectName: "mainWindowQml"
    
    Row {
        id: layout
        spacing: 36
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
                        text: cddLabel + " " + cddText + " "
                        font.family: "Helvetica"
                        font.pointSize: 12
                        color: "#0080FF"
                    }
                }
            }
        }
        Row {
            visible : mainModel.hasPrev | mainModel.hasNext
            Text {
                id: "prev_page"
                text: "<"
                font.family: "Helvetica"
                font.pointSize: 12
                color: mainModel.hasPrev ? "#005AB5" : "#ACD6FF"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (mainModel.hasPrev)
                            mainCtrl.getPrevPage()
                    }
                }
            }
            Text {
                id: "next_page"
                text: ">"
                font.family: "Helvetica"
                font.pointSize: 12
                color: mainModel.hasNext ? "#005AB5" : "#ACD6FF"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (mainModel.hasNext)
                            mainCtrl.getNextPage()
                    }
                }
            }
        }
    }
}