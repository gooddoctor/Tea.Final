#include <cassert>

#include <QPainter>

#include "t_push_button.hpp"

const int SCALE = 2;

TPushButton::TPushButton(const QPixmap& look) {
    set_look(look);
}

TPushButton* TPushButton::set_look(const QPixmap& look) {
    assert(!look.isNull());

    original_look = look;
    scaled_look = original_look.scaled(original_look.width() - SCALE,
                                       original_look.height() - SCALE,
                                       Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return this;
}

QSize TPushButton::sizeHint() const {
    return original_look.size();
}

void TPushButton::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    if (hover)
        painter.drawPixmap(0, 0, original_look);
    else
        painter.drawPixmap(SCALE / 2, SCALE / 2, scaled_look);
}

void TPushButton::enterEvent(QEvent*) {
    hover = true;
    update();
}

void TPushButton::leaveEvent(QEvent*) {
    hover = false;
    update();
}
