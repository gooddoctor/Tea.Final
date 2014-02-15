#include <cassert>

#include <QPainter>

#include "t_widget.hpp"

TWidget::TWidget(const QPixmap& background) : QWidget(nullptr, Qt::FramelessWindowHint) {
    assert(!background.isNull());
    this->background = background;
}

QSize TWidget::sizeHint() const {
    return background.size();
}

void TWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);
}

