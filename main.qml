import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0
ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Zbuffer")

    FileDialog {
        id: fileDialog
        title: "Please choose a obj file"
        //folder: shortcuts.pictures
        onAccepted: {
            var url=fileDialog.fileUrl
            console.log("You chose: " + url)
            
            obj_loader.loadObj(url)
            // var str =url.toString()
            // var array=str.split('/')
            // var name = array[array.length-1]

            var source = "image://ip/"+"12"
            // console.log(source)
            form.imageToShow.source=source
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
            MenuItem { text: "Close" }
        }

        Menu {
            title: "Edit"
            MenuItem { text: "Cut" }
            MenuItem { text: "Copy" }
            MenuItem { text: "Paste" }
        }
    }
    MainForm {
        id:form
        anchors.fill: parent
        mouseArea.onClicked: {
            Qt.quit();
        }
        focus:true
        Keys.onPressed: {
        if (event.key == Qt.Key_Left) {
            console.log("move left");
            event.accepted = true;
        }
    }
    }
}
