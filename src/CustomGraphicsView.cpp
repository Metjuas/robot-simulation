#include "CustomGraphicsView.hpp"


void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if (mode == RecordClicks) {
        qDebug() << "Recorded click at" << event->pos();
        lastClickPosition = std::make_pair(event->pos().x(), event->pos().y());
    } else {
        QGraphicsView::mousePressEvent(event);
    }

}