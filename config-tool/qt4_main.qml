import QtQuick 1.1

Rectangle {
    id: mainWindow

    objectName: "mainWindowQml"
    visible : true
    border.color: "#0080FF"
    border.width: mainSkin.inputBackImg ? 0 : 1
    color: "transparent"
    BorderImage {
        id:borderInputBackImage
        visible : true
        anchors.fill: mainWindow
        border {
            left: mainSkin.marginLeft;
            top: mainSkin.marginTop;
            right: mainSkin.marginRight;
            bottom: mainSkin.marginBottom;
        }
        source: mainSkin.inputBackImg

    }
    
    Text {
        id: inputString
        visible : true
        text: "ni hao"
        font.pointSize :mainSkin.fontSize//mainSkin.candFontSize != 0 ? mainSkin.candFontSize : mainSkin.fontSize
        color: mainSkin.inputColor
    }
    Row {
        id: horizontal
        visible :mainModel.isHorizontal
        Repeater {
            model: mainModel.candidateWords
            Text {
                id: candidateWord
                text: "<font style='color:" + mainSkin.indexColor + "'>" + cddLabel+ "</font>" +
                         "<font style='color:" + ((index == 0) ? mainSkin.firstCandColor :
                            mainSkin.otherColor) + "'>" + cddText + "</font>" + "  "
                font.pointSize : mainSkin.candFontSize != 0 ? mainSkin.candFontSize : mainSkin.fontSize
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                    }
//                }
            }
        }
    }

    Column {
        id: vertical
        visible : !mainModel.isHorizontal
        Repeater {
            model: mainModel.candidateWords
            Text {
                id: candidateWordVertical
                text: "<font style='color:" + mainSkin.indexColor + "'>" + cddLabel + "</font>" +
                         "<font style='color:" + ((index == 0) ? mainSkin.firstCandColor :
                            mainSkin.otherColor) + "'>" + cddText + "</font>" + "  "
                font.pointSize : mainSkin.candFontSize != 0 ? mainSkin.candFontSize : mainSkin.fontSize
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                    }
//                }
            }
        }
    }

    Image {
        id: prev_page
        source: mainSkin.backArrowImg
        opacity: 0.5
        MouseArea {
            anchors.fill: parent
            onClicked: {
            }
        }
    }
    
    Image {
        id: next_page
        source: mainSkin.forwardArrowImg

        MouseArea {
            anchors.fill: parent
            onClicked: {
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

        if (mainSkin.backArrowPosX == 0)
            mainSkin.backArrowPosX = - prev_page.width - next_page.width - 5 - 10;

        if (mainSkin.backArrowPosY == 0)
            mainSkin.backArrowPosY = mainSkin.inputStringPosY;
            
        clearAllAnchors(prev_page);
        setObjAbsolutePosition(prev_page, mainSkin.backArrowPosX, mainSkin.backArrowPosY);

        if (mainSkin.forwardArrowPosX == 0)
            mainSkin.forwardArrowPosX = - next_page.width - 10;
            
        if (mainSkin.forwardArrowPosY == 0)
            mainSkin.forwardArrowPosY = mainSkin.inputStringPosY;
            
        clearAllAnchors(next_page);
        setObjAbsolutePosition(next_page, mainSkin.forwardArrowPosX, mainSkin.forwardArrowPosY);

    }
    
    function max(x, y) { return x > y ? x : y; }


    Connections {
        target: mainModel   
        onQmlMainWindowSizeChanged: {

            var tmp;
            var width, width1;
            var height, height1;           

            width = mainSkin.marginLeft;
            width1 = 0;
            height = mainSkin.marginTop;
            height1 = 0;
                
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


                if (mainSkin.outputCandPosX > 0) {
                    if (mainModel.isHorizontal)
                        tmp = horizontal.x + horizontal.width;
                    else
                        tmp = vertical.x + vertical.width;
                    width = max(width, tmp);
//                    console.log(width)
                } else {
                    width1 = max(width1, -mainSkin.outputCandPosX);
                }

                if (mainSkin.outputCandPosY > 0) {
                    if (mainModel.isHorizontal)
                        tmp = horizontal.y + horizontal.height;
                    else
                        tmp = vertical.y + vertical.height;
                    height = max(height, tmp);
//                    console.log(height);
                } else {
                    height1 = max(height1, -mainSkin.outputCandPosY);
                }
            
                if (mainSkin.backArrowPosX > 0) {
                    tmp = prev_page.x + prev_page.width;
                    width = max(width, tmp);
                } else {
                    width1 = max(width1, -mainSkin.backArrowPosX);
                }
    
                if (mainSkin.forwardArrowPosX > 0) {
                    tmp = next_page.x + next_page.width;
                    width = max(width, tmp);
                } else {
                    width1 = max(width1, -mainSkin.forwardArrowPosX);
                }

                if (mainSkin.backArrowPosY > 0) {
                    tmp = prev_page.y + prev_page.height;
                    height = max(height, tmp);
                } else {
                    height1 = max(height1, -mainSkin.backArrowPosY);
                }
    
                if (mainSkin.forwardArrowPosY > 0) {
                    tmp = next_page.y + next_page.height;
                    height = max(height, tmp);
                } else {
                    height1 = max(height1, -mainSkin.forwardArrowPosY);
                }
            
            mainWindow.width = width + width1 + mainSkin.marginRight + mainSkin.adjustWidth;
            mainWindow.height = height + height1 + mainSkin.marginBottom + mainSkin.adjustHeight;

        }
    }
}
