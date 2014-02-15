#include <QMouseEvent>

#include "t_moveable_widget.hpp"

TMoveableWidget::TMoveableWidget(const QPixmap& background) : TWidget(background) { }

void TMoveableWidget::mousePressEvent(QMouseEvent* event) {
    TWidget::mousePressEvent(event);
    x_offset = event->x();
    y_offset = event->y();
}

void TMoveableWidget::mouseReleaseEvent(QMouseEvent* event) {
    TWidget::mouseReleaseEvent(event);
    x_offset = 0;
    y_offset = 0;
}

void TMoveableWidget::mouseMoveEvent(QMouseEvent* event) {
    TWidget::mouseMoveEvent(event);
    if (x_offset > 0 && y_offset > 0) 
        move(event->globalX() - x_offset, event->globalY() - y_offset);
}

