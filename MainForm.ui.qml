import QtQuick 2.5

Rectangle {
    property alias mouseArea: mouseArea
    property alias imageToShow: imageToShow
    width: 800
    height: 600

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Image {
        id:imageToShow
        anchors.fill: parent
    }
}
