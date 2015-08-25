import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQml.StateMachine 1.0

ApplicationWindow {
    title: qsTr("Chess")
    width:  640
    height: 640
    visible: true

    toolBar:ToolBar {
            RowLayout {
                anchors.fill: parent
                ToolButton {
                    id: startGameToolButton
                    text: "Start"
                    onClicked: 
					{
						boardModel.startGame()
						startGameToolButton.visible = false;
                        loadGameToolButton.visible = false;
						stopGameToolButton.visible = true;
                        saveGameToolButton.visible = true;
						prevGameToolButton.visible = false;
						nextGameToolButton.visible = false;
					}
                }
                ToolButton {
                    id: stopGameToolButton
                    text: "Stop"
                    onClicked: 
					{
						boardModel.stopGame()
						startGameToolButton.visible = true;
                        loadGameToolButton.visible = true;
						stopGameToolButton.visible = false;
                        saveGameToolButton.visible = false;
					}
                    visible: false
                }
                ToolButton {
                    id: loadGameToolButton
                    text: "Load"
                    onClicked:
					{
						boardModel.loadGame()
						startGameToolButton.visible = true;
                        loadGameToolButton.visible = true;
						stopGameToolButton.visible = false;
                        saveGameToolButton.visible = false;
						prevGameToolButton.visible = true;
						prevGameToolButton.enabled = !boardModel.isFirstStep();
						nextGameToolButton.visible = true;
				    }
                }
                ToolButton {
                    id: saveGameToolButton
                    text: "Save"
                    visible: false
                    onClicked: boardModel.saveGame()
                }
                ToolButton {
                    id: prevGameToolButton
                    text: "Prev"
                    visible: false
                    onClicked:
					{
					 prevGameToolButton.enabled = !boardModel.isFirstStep();
					 boardModel.prevStep()
					 nextGameToolButton.enabled = !boardModel.isLastStep();
					}
                }
                ToolButton {
                    id: nextGameToolButton
                    text: "Next"
                    visible: false
                    onClicked: 
					{
						boardModel.nextStep()
						prevGameToolButton.enabled = !boardModel.isFirstStep();
					    nextGameToolButton.enabled = !boardModel.isLastStep();
				    }
                }

                Item { Layout.fillWidth: true }
            }
        }
    Rectangle {
        anchors.fill: parent
        color: "Brown"
    }

    ChessBoard {
        id: chessBoard
        anchors {
            centerIn: parent
        }
        height: parent.height > parent.width ? parent.width : parent.height
        width: chessBoard.height
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("Chess game")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }

    Connections {
        target: boardModel

        onGameFinished: {
            messageDialog.show("Player " + player + " won!");
        }
    }
}
