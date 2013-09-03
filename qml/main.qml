//横排布局
import QtQuick 1.1

Rectangle {
    width: layout.width + 10 
    height: layout.height + 5
    id: mainWindow
    objectName: "mainWindowQml"
    visible : mainModel.showTips || mainModel.showPreedit || mainModel.showLookupTable

    border.color: "#0080FF"
    border.width: 1
    
    Row {
        id: layout
        x: 5
        y: 2
        spacing: 36
        Column {
            spacing: 2
            
            Text {
                id: "tipsString"
                visible : mainModel.showTips
                text: mainModel.tipsString
                color: "#FF0080"
            }
            
            Text {
                id: "inputString"
                visible : mainModel.showPreedit
                text: mainModel.inputString
                color: "#FF0080"
            }
            
            Row {
                spacing: 0
                id: "horizontal"
                visible : mainModel.showLookupTable && mainModel.isHorizontal
                
                Repeater {
                    model: mainModel.candidateWords
    
                    Text {
                        id: "candidateWord"
                        text: cddLabel + cddText + "  "
                        color: (index == mainModel.highLight) ? "#FF0080" : "#0080FF"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                    mainCtrl.selectCandidate(index)
                            }
                        }
                    }
                }
            }
            Column {
                spacing: 2
                id: "vertical"
                visible : mainModel.showLookupTable && !mainModel.isHorizontal
                
                Repeater {
                    model: mainModel.candidateWords
    
                    Text {
                        id: "candidateWord"
                        text: cddLabel + cddText + "  "
                        color: (index == mainModel.highLight) ? "#FF0080" : "#0080FF"
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
