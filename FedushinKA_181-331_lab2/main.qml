import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtMultimedia 5.14
import QtQuick.Dialogs 1.0
import QtMultimedia 5.0
import QtQuick 2.12
import QtWebView 1.14
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtMultimedia 5.9
import QtGraphicalEffects 1.12
import QtQuick.Window 2.0
import Qt.labs.platform 1.1
import QtCharts 2.0
import QtWebSockets 1.5



ApplicationWindow {
    Popup {
        id: popup
        parent: Overlay.overlay
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 300
        height: 150
        modal: true
        background:
            Rectangle{
            anchors.fill: parent
            color: "white"
            border.color: "black"
            radius: 10
        }
        ColumnLayout{
            Layout.fillWidth: true
            anchors.fill: parent
            TextField{
                id: popuppin
                placeholderText: "Введите пин"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                Layout.margins: 20
                color: "black"
                font.pixelSize: 20
                background:
                    Rectangle{
                    anchors.fill: parent
                    color: "white"
                    border.color: "black"
                    radius: 10
                }
            }

            Label {
                id: indexField
                text: ""
                visible: false
            }

            Label {
                id: typeField
                text: ""
                visible: false
            }

            Button {
                id: popupClose
                Layout.alignment: Qt.AlignCenter
                contentItem: Text {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("<b>Скопировать<b>")
                    font.pixelSize: 20
                    color: "white"
                }
                background: Rectangle {
                    implicitWidth: 80 //абсолютная ширина
                    implicitHeight: 35
                    color: auth.down ? "#079d4d" : "green" //смена цвета при нажатии
                    radius: 10
                }
                onClicked: {
                    labbock.copyToClipboard(indexField.text, typeField.text, popuppin.text)
                    popup.close()
                    popuppin.clear()
                    indexField.text = ""
                    typeField.text = ""
                    tmr.stop()
                    tmr.start()
                }
            }
        }
    }

    signal parseJson(string pin)

    visible: true
    width: 800
    height: 700
    title: qsTr("PassManager")



    background: Rectangle {
        color: "white"
    }
    header: Rectangle {
        id: rectengle315

        color: "#f0fff3"
        //border.color: "purple"
        height: 50
        radius: 10
        Image {
            id: png225
            x: 10
            y: 9
            width: 30
            height: 30
            source: "img/back.jpg"
        }

        Column {
            anchors.fill: parent
            anchors.topMargin: 5
            Text {
                text: qsTr("Менеджер паролей")

                font.family: "Helvetica"
                font.pointSize: 11
                color: "#079d4d"
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {

                text: qsTr("Добро пожаловать")

                font.pointSize: 9
                color: "#f59c31"

                anchors.horizontalCenter: parent.horizontalCenter
            }
        }


    }


    ColumnLayout{


        Layout.fillWidth: true
        anchors.fill: parent
        Label {
            id: proverca
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 20
            text: "<b>УСПЕШНО<b>"
            color: "green"
            visible: false
        }
        Label {
            id: proverc1a
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 50
            text: "<b>НЕ УСПЕШНО<b>"
            color: "red"
            visible: false
        }

        Label {
            id: tosik
            visible: true
            font.pixelSize: 12
            Layout.alignment: Qt.AlignCenter
        }

        Label {
            id: labelauth
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 20
            text: "<b>Введите пин:<b>"
        }


        TextField{
            id: key

            visible: true
            cursorVisible: false
            placeholderText: "Введите пин"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.margins: 20
            color: "black"
            background:
                Rectangle{

                anchors.fill: parent
                color: "white"
                border.color: "black"
                radius: 10
            }

        }

        Button {
            id: auth
            Layout.alignment: Qt.AlignCenter
            contentItem: Text {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("<b>Вход<b>")
                font.pixelSize: 15
                color: "white"
            }

            background: Rectangle {
                implicitWidth: 80 //абсолютная ширина
                implicitHeight: 35
                color: auth.down ? "#079d4d" : "green" //смена цвета при нажатии
                radius: 10
            }
            onClicked: {
                if(labbock.parseJson(key.text, "") === false){
                    proverc1a.visible = true
                }
                else {
                    proverc1a.visible = false
                    key.visible = false
                    labelauth.visible = false
                    scrollpop.visible = true
                    auth.visible = false
                    listView.visible = true
                }
            }
        }

    }





    ScrollView{
        id: scrollpop
        anchors.fill: parent
        visible: false

        Layout.fillWidth: true
        Item {}

        ColumnLayout{

            anchors.fill: parent

            TextField{
                id: search_1

                Layout.fillWidth: true
                visible: true
                cursorVisible: false
                placeholderText: "Поиск.."
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter


                Layout.margins: 20
                color: "black"
                onEditingFinished: {
                    labbock.parseJson(key.text, search_1.text)
//                    listView.model.roleNames().forEach(el => console.log(el))
                }
                background:
                    Rectangle{

                    anchors.fill: parent
                    color: "white"
                    border.color: "black"
                    radius: 10
                }

            }

            Item {
                id: name1233
                Layout.preferredWidth: 300
                Layout.preferredHeight: 20
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle {
                    Timer {
                        id: tmr
                        interval: 1500
                    }
                    id: soedinenie
                    visible: true
                    anchors.fill: parent
                    //Layout.margins: -10
                    color: "green"
                    opacity: tmr.running ? 1.0 : 0.0
                    Behavior on opacity {
                        PropertyAnimation { duration: 800 }
                    }
                    radius: 10
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("Скопированно в буфер")
                        font.bold: true
                        font.pixelSize: 15
                        color: "white"
                    }

                }


            }




            ListView{
                id: listView
                Layout.margins: 20
                visible: false
                Layout.fillHeight: true
                Layout.fillWidth: true
                enabled: true

                model: records_modal


                spacing: 10
                anchors.margins: 5
                //Layout.margins: 10

                delegate: Rectangle{
                    color: "#f0fff3"
                    anchors.margins: 5
                    width: listView.width
                    //Layout.margins: 10
                    height: 120
                    border.color: "green"
                    radius: 10


                    GridLayout{
                        anchors.fill: parent
                        columns: 4

                        Image{
                            source: "img/back.jpg"

                            Layout.rowSpan: 3
                            Layout.fillHeight: true
                            Layout.preferredWidth: 100
                            Layout.margins: 5
                            fillMode: Image.PreserveAspectFit
                            Layout.alignment: Qt.AlignCenter
                        }
                        Label{
                            color: "black"
                            text: surname
                            Layout.alignment: Qt.AlignVCenter
                            Layout.rowSpan: 3
                            Layout.preferredWidth: 120
                        }

                        Button {
                            id: pocazlogin
                            Layout.alignment: Qt.AlignVCenter
                            Layout.rowSpan: 3
                            Layout.preferredWidth: 170
                            hoverEnabled: true
                                ToolTip.visible: hovered
                                ToolTip.text: qsTr("Нажмите, чтобы скопировать логин")

                            contentItem: Text {
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: qsTr("<b>•••••••<b>")
                                font.pixelSize: 15
                                color: "black"
                            }

                            background: Rectangle {
                                implicitWidth: 80 //абсолютная ширина
                                implicitHeight: 35
                                color: "#f0fff3"
                                //color: pocazlogin.down ? "#079d4d" : "green" //смена цвета при нажатии
                                radius: 10
                            }
                            onClicked: {

////                                if(search_1.text.length >= 3){

//                                    console.log("2222222222222222222")
//                                //}




                                popup.open()
                                indexField.text = index
                                typeField.text = "friend_id"
                            }
                        }


                        Button {
                            id: pocazpassword
                            Layout.alignment: Qt.AlignVCenter
                            Layout.rowSpan: 3
                            Layout.preferredWidth: 170
                            hoverEnabled: true
                                ToolTip.visible: hovered
                                ToolTip.text: qsTr("Нажмите, чтобы скопировать пароль")
                            contentItem: Text {
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: qsTr("<b>•••••••<b>")
                                font.pixelSize: 15
                                color: "black"
                            }

                            background: Rectangle {
                                implicitWidth: 80 //абсолютная ширина
                                implicitHeight: 35
                                color: "#f0fff3"
                                //color: pocazpassword.down ? "#079d4d" : "green" //смена цвета при нажатии
                                radius: 10
                            }
                            onClicked: {
                                popup.open()
                                indexField.text = index
                                typeField.text = "photo"
                            }
                        }


                    }
                }
            }

            Button {
                id: auth1
                visible: false
                Layout.alignment: Qt.AlignCenter
                contentItem: Text {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("<b>Назад<b>")
                    font.pixelSize: 15
                    color: "white"
                }

                background: Rectangle {
                    implicitWidth: 80 //абсолютная ширина
                    implicitHeight: 35
                    color: auth1.down ? "#079d4d" : "red" //смена цвета при нажатии
                    radius: 10
                }
                onClicked: {

                    proverca.visible = false
                    key.visible = true
                    labelauth.visible = true
                    scrollpop.visible = false
                    auth.visible = true
                    listView.visible = false




                }
            }


        }
    }






}









