#include "t_slider.hpp"

bool TSlider::is_hover() {
  return hover;
}

void TSlider::enterEvent(QEvent* event) {
  QSlider::enterEvent(event);
  hover = true;
}

void TSlider::leaveEvent(QEvent* event) {
  QSlider::leaveEvent(event);
  hover = false;
}
