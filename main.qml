import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: config.url?config.url:qsTr("21621170 李书楠")

    Dialog {
        title: "使用说明"
        id:help
        
        contentItem: Rectangle {
            implicitWidth: 400
            implicitHeight: 100
            Text {
                text: "方向键平移，wasd键旋转，zx键缩放"
                anchors.centerIn: parent
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a obj file"
        //folder: shortcuts.pictures
        onAccepted: {
            var url=fileDialog.fileUrl
            console.log("You chose: " + url)
            
            obj_loader.loadObj(url)
            form.imageToShow.refresh();
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem { 
                text: "Open..." 
                onTriggered: fileDialog.open()
            }
        }

        Menu {
            title: "Help"
            MenuItem { 
                text: "Help" 
                onTriggered: help.open()
            }
        }
    }
    MainForm {
        id:form
        anchors.fill: parent
        mouseArea.onClicked: {
            
        }
        focus:true
        Keys.onPressed: {
            if (event.key == Qt.Key_Left) {
                console.log("move left");
                obj_loader.moveLeft();
                form.imageToShow.refresh();
                event.accepted = true;
            }
            else if(event.key==Qt.Key_Up)
            {
                console.log("move up");
                obj_loader.moveUp();
                form.imageToShow.refresh();
                event.accepted=true;
            }
            else if(event.key==Qt.Key_Right)
            {
                obj_loader.moveRight();
                form.imageToShow.refresh();
                event.accepted=true;
            }
            else if(event.key==Qt.Key_Down)
            {
                obj_loader.moveDown();
                form.imageToShow.refresh();
                event.accepted=true;
            }
            else if(event.key==Qt.Key_A)
            {
                obj_loader.rotateLeft();
                form.imageToShow.refresh();
                event.accepted=true;
            }
            else if(event.key==Qt.Key_D)
            {
                obj_loader.rotateRight();
                form.imageToShow.refresh();
                event.accepted=true;
            }
            else if(event.key==Qt.Key_W)
            {
                obj_loader.rotateUp();
                form.imageToShow.refresh();
                event.accepted=true;
            }
            else if(event.key==Qt.Key_S)
            {
                obj_loader.rotateDown();
                form.imageToShow.refresh();
                event.accepted=true;
            }
            else if(event.key==Qt.Key_Z)
            {
                obj_loader.zoomIn();
                form.imageToShow.refresh();
                event.accepted=true;
            }
            else if(event.key==Qt.Key_X)
            {
                obj_loader.zoomOut();
                form.imageToShow.refresh();
                event.accepted=true;
            }
        }
    }

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label { text: "面数："+config.faceCount }
            Label{text:"用时："+config.time+"ms"}
        }
    }
}
