// Řešení ICP, 2.5.2024
// Autor: Matej Olexa xolexa03, Dominik Sajko xsajko01, FIT
// Přeloženo: g++ 11.4.0

#include "CustomGraphicsView.hpp"


/// @brief records mouse click events, saves them into last_click_pos attribute
/// @param event 
void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if (mode == RecordClicks) {
        //recalculate the position of the click in scene coordinates
        QPointF scene_pos = mapToScene(event->pos());
        
        last_click_pos = std::make_pair(scene_pos.x(), scene_pos.y());
        //sending signal
        emit mouseClick(last_click_pos.first, last_click_pos.second);
    } else {
        QGraphicsView::mousePressEvent(event);
    }

}
/// @brief resizes the view to fit the scene
/// @param event 
void CustomGraphicsView::resizeEvent(QResizeEvent *event)
{
    fitInView(sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}