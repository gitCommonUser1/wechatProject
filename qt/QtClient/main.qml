import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    id:root
    width: 900
    height: 600
    visible: true
    title: qsTr("Hello World")

    //排名  姓名  手机号  热度
    Row{
        spacing: 50
        Text{
            text:qsTr("排名")
        }
        Text{
            text:qsTr("姓名")
        }
        Text{
            text:qsTr("手机号")
        }
        Text{
            text:qsTr("热度")
        }
    }

    ListView{
//        anchors.fill: parent
        id:m_listView
        width:parent.width
        y:50
        height:300
        model: tableModel
        delegate:myDelegate

        ScrollBar.vertical: ScrollBar {
                        id: scrollBar
                        onActiveChanged: {
                            console.log("onActiveChanged========================")
                            active = true;
                        }
                        Component.onCompleted: {
        //                    scrollBar.handle.color = "yellow"
        //                    scrollBar.active = true;
        //                    scrollBar.handle.width = 10;
                            console.log("Component.onCompleted========================")
                        }
                    }
    }


    Component{
        id: myDelegate
        Rectangle {
            Row{
                Text{
                    text:index+1
                }
                Text{
                    text:name
                }
                Text{
                    text:telephone
                }
                Text{
                    text:fire
                }
                spacing: 50
            }
            width: ListView.view.width
            height: 40
            color: ListView.isCurrentItem?"#157efb":"#FFFFFF" //选中颜色设置
            MouseArea {
                anchors.fill: parent
                onClicked: m_listView.currentIndex = index  //实现item切换
            }
        }
    }


    Row{
        y:400
        spacing: 50
        Button{
            text:"删除"
            onClicked: {
                if(m_listView.currentIndex != -1){
                    client.remove(m_listView.currentIndex)
                }
            }
        }
        TextField{
            id:changeFire
            focus: true
        }
        Button{
            text:"修改"
            onClicked: {
                if(m_listView.currentIndex != -1){
                    client.update(m_listView.currentIndex,changeFire.text)
                }
            }
        }
    }

    Row{
        //姓名 手机号  热度
        y:450
        spacing: 20
//        Rectangle{
            Text {
//                anchors.centerIn: parent
                text: qsTr("姓名")
            }
//        }
        TextField{
            id:name
            focus: true
        }
//        Rectangle{
            Text {
//                anchors.centerIn: parent
                text: qsTr("手机号")
            }
//        }
        TextField{
            id:phone
            focus: true
        }
//        Rectangle{
            Text {
//                anchors.centerIn: parent
                text: qsTr("热度")
            }
//        }
        TextField{
            id:fire
            focus: true
        }
        Button{
            text:"新增"  //删除  修改
            onClicked: {
                client.newData(name.text,phone.text,fire.text)
            }
        }
    }

//    TextInput{
//        x:100
//        y:350
////        text:"修改"  //删除  修改
//    }



}
