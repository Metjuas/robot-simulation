#include "CustomGraphicsView.hpp"


void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if (mode == RecordClicks) {
        // QPointF scenePos = mapToScene(event->pos());
        qDebug() << "Mouse event position: " << event->pos();
        // qDebug() << "Scene position: " << scenePos;
        lastClickPosition = std::make_pair(event->pos().x(), event->pos().y());
        qDebug() << "Click recorded at: " << lastClickPosition.first << ", " << lastClickPosition.second;

        emit mouseClick(lastClickPosition.first, lastClickPosition.second);
    } else {
        QGraphicsView::mousePressEvent(event);
    }

}