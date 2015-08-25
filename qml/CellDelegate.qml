import QtQuick 2.4

Item {
    id: delegate
    width: chessGrid.cellWidth; height: chessGrid.cellHeight;

    Rectangle {
        anchors.fill: parent
        antialiasing : true
        color: (Math.floor(model.index / 8) + model.index)%2 == 0 ? "#B58763" : "#F0DAB5"
        anchors.horizontalCenter: parent.horizontalCenter

		Rectangle {
		        id: innerRect
				anchors.margins: boardModel.getRectMargin()
				anchors.fill: parent
				antialiasing : true
				color: 
				{
				   if (chessGrid.currentIndex !== index)
				      unselect();
				   boardModel.isMovePossible(chessGrid.currentIndex,index) ? "#FF4242" : parent.color
				}
				anchors.horizontalCenter: parent.horizontalCenter
				function select() {
					anchors.margins = 0;
				}
				function unselect() {
					anchors.margins = boardModel.getRectMargin();
				}
				    Image {
					    anchors.fill: parent
						fillMode: Image.PreserveAspectFit
					    source: image ? image : ""
                          }
			    }
    }
    
    MouseArea {
        id: frameMouseArea
        anchors {
            fill: parent
        }
        onClicked: {
		    
            if(chessGrid.currentIndex === index) {
                chessGrid.currentIndex = -1;
				innerRect.unselect();
            } else if(chessGrid.currentIndex === -1 && boardModel.isSelectionPosible(index)) {
			    boardModel.select(index); 
				innerRect.select();
                chessGrid.currentIndex = index;
            } else if(chessGrid.currentIndex !== -1 && boardModel.isMovePossible(chessGrid.currentIndex, index)) { 
                boardModel.move(chessGrid.currentIndex, index); 
                chessGrid.currentIndex = -1;
            }
        }
    }
}
