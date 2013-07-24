import QtQuick 1.1

Rectangle {
    width: layout.width + 10
    height: layout.height + 5
    id: mainWindow
    objectName: "mainWindowQml"
    border.color: "#0080FF"
    border.width: 2
    
    Row {
        id: layout
        x: 5
        spacing: 36
        Column {
            spacing: 2
    
            Text {
                id: "inputString"
                text: mainModel.inputString
                font.family: "Helvetica"
                font.pointSize: 12
                color: "#FF0080"
            }
            Row {
                spacing: 0
                
                Repeater {
                    id: repeater
                    model: mainModel.candidateWords
    
                    Text {
                        id: "candidateWord"
                        text: cddLabel + cddText
                        font.family: "宋体"
                        font.pointSize: 12
                        color: (index == 0) ? "#FF0080" : "#0080FF"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                    mainCtrl.selectCandidate(index)
                            }
                        }
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