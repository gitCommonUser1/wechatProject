import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    id:root
    width: 900
    height: 600
    visible: true
    title: qsTr("Hello World")

    TableView{
        anchors.fill: parent
        model: tableModel
        columnSpacing: 1
        rowSpacing: 1
        delegate: Rectangle {
            implicitWidth: 250
            implicitHeight: 50
              Text {
                  text: {
                      if(column == 0){
                          name
                      }else if(column == 1){
                          telephone
                      }else if(column == 2){
                          fire
                      }else if(column == 3){
                          row
                      }
                  }
                  font.pixelSize: 30
              }
        }
    }
}
