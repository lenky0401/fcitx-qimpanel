import QtQuick 1.1

Rectangle {
    id: mainWindow
    objectName: "mainWindowQml"
    visible : mainModel.showTips || mainModel.showPreedit || mainModel.showLookupTable
    border.color: "#0080FF"
    border.width: mainSkin.inputBackImg ? 0 : 1
    color: "transparent"

    BorderImage {
        id: inputBackImg
        visible : mainModel.showPreedit || mainModel.showLookupTable
        anchors.fill: parent
        anchors.left:parent.left
        border {
            left: mainSkin.marginLeft;
            top: mainSkin.marginTop;
            right: mainSkin.marginRight;
            bottom: mainSkin.marginBottom;
        }
        horizontalTileMode: mainSkin.horizontalTileMode
        verticalTileMode: mainSkin.verticalTileMode
        source: mainSkin.inputBackImg
    }

//custom0
 Image {
    id:custom0
    source: mainSkin.customImg0
    visible : mainModel.isHorizontal && (mainModel.showPreedit || mainModel.showLookupTable)
    width: sourceSize.width; height: sourceSize.height
    fillMode: Image.PreserveAspectFit
    anchors.left: inputBackImg.left
    }

//custom1
  Image {
    id:custom1
    source: mainSkin.customImg1
    visible : mainModel.isHorizontal && (mainModel.showPreedit || mainModel.showLookupTable)
    width: sourceSize.width; height: sourceSize.height
    fillMode: Image.PreserveAspectFit
    anchors.right: parent.right
    }
   
    BorderImage {
        visible : mainModel.showTips && !mainModel.showPreedit && !mainModel.showLookupTable
        anchors.fill: parent
        border {
            left: 10;
            top: 10;
            right: 10;
            bottom: 10;
        }
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch
        source: mainSkin.tipsImg
    }
    
    Text {
        x: 5
        y: 3
        id: "tipsString"
        visible : mainModel.showTips
        text: mainModel.tipsString
        font.pointSize : mainSkin.fontSize
        color: mainSkin.inputColor
    }
        
    Text {
        id: "inputString"
        visible : mainModel.showPreedit
        text: mainModel.inputString
        font.pointSize : mainSkin.fontSize
        color: mainSkin.inputColor
    }

    Row {    
        id: "horizontal"
        visible : mainModel.showLookupTable && mainModel.isHorizontal
        Repeater {
            model: mainModel.candidateWords
            Text {
                id: "candidateWord"
                text: "<font style='color:" + mainSkin.indexColor + "'>" + cddLabel + "</font>" + 
                         "<font style='color:" + ((index == mainModel.highLight) ? mainSkin.firstCandColor : 
                            mainSkin.otherColor) + "'>" + cddText + "</font>" + "  "
                font.pointSize : mainSkin.candFontSize != 0 ? mainSkin.candFontSize : mainSkin.fontSize
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
        id: "vertical"
        visible : mainModel.showLookupTable && !mainModel.isHorizontal
        
        Repeater {
            model: mainModel.candidateWords
            Text {
                id: "candidateWord"
                text: "<font style='color:" + mainSkin.indexColor + "'>" + cddLabel + "</font>" + 
                         "<font style='color:" + ((index == mainModel.highLight) ? mainSkin.firstCandColor : 
                            mainSkin.otherColor) + "'>" + cddText + "</font>" + "  "
                font.pointSize : mainSkin.candFontSize != 0 ? mainSkin.candFontSize : mainSkin.fontSize
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                            mainCtrl.selectCandidate(index)
                    }
                }
            }
        }
    }

    function clearAllAnchors(obj) {
        obj.anchors.left = undefined;
        obj.anchors.leftMargin = 0;
        obj.anchors.top = undefined;
        obj.anchors.topMargin = 0;
        obj.anchors.right = undefined;
        obj.anchors.rightMargin = 0;
        obj.anchors.bottom = undefined;
        obj.anchors.bottomMargin = 0;
    }
    
    function setObjAbsolutePosition(bindObj, x, y) {
        if (x > 0) {
            bindObj.anchors.left = mainWindow.left;
            bindObj.anchors.leftMargin = x;
        } else if (x < 0) {
            bindObj.anchors.right = mainWindow.right;
            bindObj.anchors.rightMargin = -x;
        }
        
        if (y > 0) {
            bindObj.anchors.top = mainWindow.top;
            bindObj.anchors.topMargin = y;
        } else if (y < 0) {
            bindObj.anchors.bottom = mainWindow.bottom;
            bindObj.anchors.bottomMargin = -y;
        }
    }
    
    Component.onCompleted: {
    
        if (mainSkin.inputStringPosX == 0)
            mainSkin.inputStringPosX = mainSkin.marginLeft;
            
        if (mainSkin.inputStringPosY == 0)
            mainSkin.inputStringPosY = mainSkin.marginTop;
        clearAllAnchors(inputString);
        setObjAbsolutePosition(inputString, mainSkin.inputStringPosX, mainSkin.inputStringPosY);

        if (mainSkin.outputCandPosX == 0)
            mainSkin.outputCandPosX = mainSkin.marginLeft;
            
        if (mainSkin.outputCandPosY == 0)
            mainSkin.outputCandPosY = inputString.height + mainSkin.marginTop;
        clearAllAnchors(horizontal);
        setObjAbsolutePosition(horizontal, mainSkin.outputCandPosX, mainSkin.outputCandPosY);
        clearAllAnchors(vertical);
        setObjAbsolutePosition(vertical, mainSkin.outputCandPosX, mainSkin.outputCandPosY);
    }
    
    function max(x, y) { return x > y ? x : y; }
    
    Connections {
        target: mainModel
        
        onMainWindowSizeChanged: {
            var tmp;
            var width, width1;
            var height, height1;
            
            if (mainModel.showTips && !mainModel.showPreedit && !mainModel.showLookupTable) {
                mainWindow.width = tipsString.width + 10;
                mainWindow.height = tipsString.height + 10;
                
                return;
            }

            width = mainSkin.marginLeft;
            width1 = 0;
            height = mainSkin.marginTop;
            height1 = 0;

            if (mainModel.showTips) {
                tmp = tipsString.x + tipsString.width;
                width = max(width, tmp);

                tmp = tipsString.y + tipsString.height;
                height = max(height, tmp);
            }            
                
            if (mainModel.showPreedit) {
                if (mainSkin.inputStringPosX > 0) {
                    tmp = inputString.x + inputString.width;
                    width = max(width, tmp);
                } else {
                    width1 = max(width1, -mainSkin.inputStringPosX);
                }
                
                if (mainSkin.inputStringPosY > 0) {
                    tmp = inputString.y + inputString.height;
                    height = max(height, tmp);
                } else {
                    height1 = max(height1, -mainSkin.inputStringPosY);
                }
            }
                
            if (mainModel.showLookupTable) {
                if (mainSkin.outputCandPosX > 0) {
                    if (mainModel.isHorizontal)
                        tmp = horizontal.x + horizontal.width;
                    else
                        tmp = vertical.x + vertical.width;
                    width = max(width, tmp);
                } else {
                    width1 = max(width1, -mainSkin.outputCandPosX);
                }
                
                if (mainSkin.outputCandPosY > 0) {
                    if (mainModel.isHorizontal)
                        tmp = horizontal.y + horizontal.height;
                    else
                        tmp = vertical.y + vertical.height;
                    height = max(height, tmp);
                } else {
                    height1 = max(height1, -mainSkin.outputCandPosY);
                }
            }
           
            mainWindow.width = width + width1 + mainSkin.marginRight + mainSkin.adjustWidth;
            mainWindow.height = height + height1 + mainSkin.marginBottom + mainSkin.adjustHeight;
        }
    }

    MouseArea {
        anchors.fill: parent
        property variant previousPosition
        onPressed: {
            previousPosition = Qt.point(mouseX, mouseY)
        }
        onPositionChanged: {
            if (pressedButtons == Qt.LeftButton) {
                var dx = mouseX - previousPosition.x
                var dy = mouseY - previousPosition.y
                mainWidget.pos = Qt.point(mainWidget.pos.x + dx,
                                        mainWidget.pos.y + dy)
            }
        }
    }
}
