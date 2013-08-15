//提示信息
import QtQuick 1.1

Rectangle {
    width: tipsString.width + 10
    height: tipsString.height + 5
    id: mainWindow
    objectName: "mainWindowQml"

    border.color: "#0080FF"
    border.width: 1
    
    Text {
        x: 5
        y: 2
        id: "tipsString"
        text: mainModel.tipsString
        color: "#FF0080"
    }
}
