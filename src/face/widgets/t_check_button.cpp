#include <QPainter>

#include "t_check_button.hpp"

TCheckButton::TCheckButton(const QPixmap& look) : TPushButton(look), 
				                  check_pixmap(":face_widgets/resource/check.png") {
  Q_ASSERT(!check_pixmap.isNull());
  setCheckable(true);
}

void TCheckButton::paintEvent(QPaintEvent* event) {
  TPushButton::paintEvent(event);
  if (isChecked()) {
    QPainter painter(this);
    painter.drawPixmap(0, height() - check_pixmap.height(), check_pixmap);
  }
}


  
