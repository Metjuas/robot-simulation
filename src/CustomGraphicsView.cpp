#include "CustomGraphicsView.hpp"


void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if (mode == RecordClicks) {
        QPointF scenePos = mapToScene(event->pos());
        qDebug() << "Mouse event position in scene coordinates: " << scenePos;
        lastClickPosition = std::make_pair(scenePos.x(), scenePos.y());
        emit mouseClick(lastClickPosition.first, lastClickPosition.second);
    } else {
        QGraphicsView::mousePressEvent(event);
    }

}