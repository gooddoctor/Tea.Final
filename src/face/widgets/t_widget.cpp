#include <cassert>

#include <QPainter>

#include "t_widget.hpp"

const int TOP_MARGIN = 3;
const int RIGHT_MARGIN = 3;

TWidget::TWidget(const QPixmap& background) : QWidget(nullptr, Qt::FramelessWindowHint) {
  assert(!background.isNull());
  this->background = background;

  close_button = new TPushButton(QPixmap(":face_widgets/resource/close.png"));
  close_button->setParent(this);
  close_button->setGeometry(sizeHint().width() - close_button->sizeHint().width() - RIGHT_MARGIN, 
			    TOP_MARGIN, 
			    close_button->sizeHint().width(), close_button->sizeHint().height());
}

QSize TWidget::sizeHint() const {
  return background.size();
}

TWidget* TWidget::show_it(bool value, int x, int y) {
  if (value) {
    show();
    move(x, y);
  } else {
    hide();
  }
  return this;
}

void TWidget::mouseMoveEvent(QMouseEvent* event) {
  QWidget::mouseMoveEvent(event);
  if (x_offset > 0 && y_offset > 0) 
    move(event->globalX() - x_offset, event->globalY() - y_offset);
}

void TWidget::mousePressEvent(QMouseEvent* event) {
  QWidget::mousePressEvent(event);
  x_offset = event->x();
  y_offset = event->y();
}

void TWidget::mouseReleaseEvent(QMouseEvent* event) {
  QWidget::mouseReleaseEvent(event);
  x_offset = 0;
  y_offset = 0;
}

void TWidget::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, background);
}




