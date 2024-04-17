#include "CustomGraphicsView.hpp"


void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if (mode == RecordClicks) {
        //recalculate the position of the click in scene coordinates
        QPointF scenePos = mapToScene(event->pos());
        qDebug() << "Mouse event position in scene coordinates: " << scenePos;

        lastClickPosition = std::make_pair(scenePos.x(), scenePos.y());
        //sending signal
        emit mouseClick(lastClickPosition.first, lastClickPosition.second);
    } else {
        QGraphicsView::mousePressEvent(event);
    }

}