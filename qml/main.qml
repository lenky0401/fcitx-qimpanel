//横排布局
import QtQuick 1.1

Rectangle {
    width: layout.width + mainSkin.marginLeft + mainSkin.marginRight
    height: layout.height + mainSkin.marginTop + mainSkin.marginBottom - (mainSkin.outputPos - mainSkin.inputPos)
    id: mainWindow
    objectName: "mainWindowQml"
    visible : mainModel.showTips || mainModel.showPreedit || mainModel.showLookupTable

    border.color: "#0080FF"
    border.width: mainSkin.inputBackImg ? 0 : 1
    color: "transparent"

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
        x: mainSkin.marginLeft
        y: mainSkin.marginTop
        spacing: 0
        Column {
            spacing: 0
            
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
                font.pixelSize : mainSkin.fontSize
                color: mainSkin.inputColor
            }
            
            Column {
                id: "horizontal"
                spacing: 0
                visible : mainModel.showLookupTable && mainModel.isHorizontal
                Text {
                    id: "horizontalSeparator"
                    text: " "
                    height: mainSkin.outputPos - mainSkin.inputPos > 0 ? mainSkin.outputPos - mainSkin.inputPos : 0
                }
                Row {
                    spacing: 5
                    Repeater {
                        model: mainModel.candidateWords
        
                        Text {
                            id: "candidateWord"
                            text: "<font style='color:" + mainSkin.indexColor + "'>" + cddLabel + "</font>" + 
                                     "<font style='color:" + ((index == mainModel.highLight) ? mainSkin.firstCandColor : 
                                        mainSkin.otherColor) + "'>" + cddText + "</font>" + "  "
                            font.pixelSize : mainSkin.fontSize
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
            Column {
                id: "vertical"
                spacing: 0
                visible : mainModel.showLookupTable && !mainModel.isHorizontal
                Text {
                    id: "verticalSeparator"
                    text: " "
                    height: mainSkin.outputPos - mainSkin.inputPos > 0 ? mainSkin.outputPos - mainSkin.inputPos : 0
                }
                Column {
                    spacing: 5
                    
                    Repeater {
                        model: mainModel.candidateWords
        
                        Text {
                            id: "candidateWord"
                            text: "<font style='color:" + mainSkin.indexColor + "'>" + cddLabel + "</font>" + 
                                     "<font style='color:" + ((index == mainModel.highLight) ? mainSkin.firstCandColor : 
                                        mainSkin.otherColor) + "'>" + cddText + "</font>" + "  "
                            font.pixelSize : mainSkin.fontSize
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
        }
        Row {
            visible : mainModel.hasPrev | mainModel.hasNext
            spacing: 5
            Image {
                id: "prev_page"
                source: mainSkin.backArrowImg
                opacity: mainModel.hasPrev ? 1 : 0.5
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (mainModel.hasPrev)
                            mainCtrl.getPrevPage()
                    }
                }
            }
            Image {
                id: "next_page"
                source: mainSkin.forwardArrowImg
                opacity: mainModel.hasNext ? 1 : 0.5
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