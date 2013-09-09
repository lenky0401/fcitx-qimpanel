//横排布局
import QtQuick 1.1

Rectangle {
    width: layout.width + 10 + mainSkin.marginLeft + mainSkin.marginRight
    height: layout.height + 5 + mainSkin.marginTop + mainSkin.marginBottom
    id: mainWindow
    objectName: "mainWindowQml"
    visible : mainModel.showTips || mainModel.showPreedit || mainModel.showLookupTable

    border.color: "#0080FF"
    border.width: mainSkin.inputBackImg ? 0 : 1

    BorderImage {
        anchors.fill: parent
        border { 
            left: mainSkin.marginLeft; 
            top: mainSkin.marginTop; 
            right: mainSkin.marginRight; 
            bottom: mainSkin.marginBottom; 
        }
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch
        source: mainSkin.inputBackImg
    }

    Row {
        id: layout
        x: 5 + mainSkin.marginLeft
        y: 2 + mainSkin.marginTop
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
                font.pointSize : mainSkin.fontSize 
                color: mainSkin.inputColor
            }
            
            Row {
                spacing: 0
                id: "horizontal"
                visible : mainModel.showLookupTable && mainModel.isHorizontal
                
                Repeater {
                    model: mainModel.candidateWords
    
                    Text {
                        id: "candidateWord"
                        text: "<font style='color:" + mainSkin.indexColor + "'>" + cddLabel + "</font>" + 
                                 "<font style='color:" + ((index == mainModel.highLight) ? mainSkin.firstCandColor : 
                                    mainSkin.otherColor) + "'>" + cddText + "</font>" + "  "
                        font.pointSize : mainSkin.fontSize
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
                        text: "<font style='color:" + mainSkin.indexColor + "'>" + cddLabel + "</font>" + 
                                 "<font style='color:" + ((index == mainModel.highLight) ? mainSkin.firstCandColor : 
                                    mainSkin.otherColor) + "'>" + cddText + "</font>" + "  "
                        font.pointSize : mainSkin.fontSize
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
            spacing: mainSkin.backArrowImg ? 5 : 0
            Text {
                id: "prev_page"
                Image {
                    source: mainSkin.backArrowImg
                    opacity: mainModel.hasPrev ? 1 : 0.5
                }
                text: mainSkin.backArrowImg ? " " : "<"
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
                Image {
                    source: mainSkin.forwardArrowImg
                    opacity: mainModel.hasNext ? 1 : 0.5
                }
                text: mainSkin.forwardArrowImg ? " " : ">"
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
