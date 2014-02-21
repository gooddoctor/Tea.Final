#include <cassert>

#include <QPainter>

#include "t_push_button.hpp"

const int SCALE_FACTOR = 2;

TPushButton::TPushButton(const QPixmap& look) {
  set_look(look);
}

QSize TPushButton::sizeHint() const {
  return look.size();
}

TPushButton* TPushButton::set_look(const QPixmap& look) {
  assert(!look.isNull());
  this->look = look;
  scaled_look = look.scaled(look.width() - SCALE_FACTOR, look.height() - SCALE_FACTOR,
			    Qt::KeepAspectRatio, Qt::SmoothTransformation);
  return this;
}

void TPushButton::enterEvent(QEvent*) {
  hover = true;
  update();
}

void TPushButton::leaveEvent(QEvent*) {
  hover = false;
  update();
}

void TPushButton::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  if (hover)
    painter.drawPixmap(0, 0, look);
  else
    painter.drawPixmap(SCALE_FACTOR / 2, SCALE_FACTOR / 2, scaled_look);
}
