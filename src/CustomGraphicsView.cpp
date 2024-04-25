#include "CustomGraphicsView.hpp"


void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if (mode == RecordClicks) {
        //recalculate the position of the click in scene coordinates
        QPointF scene_pos = mapToScene(event->pos());
        qDebug() << "Mouse event position in scene coordinates: " << scene_pos;

        last_click_pos = std::make_pair(scene_pos.x(), scene_pos.y());
        //sending signal
        emit mouseClick(last_click_pos.first, last_click_pos.second);
    } else {
        QGraphicsView::mousePressEvent(event);
    }

}

void CustomGraphicsView::resizeEvent(QResizeEvent *event)
{
    fitInView(sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}