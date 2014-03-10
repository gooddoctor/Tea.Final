#ifndef __T_CHECK_BUTTON_H
#define __T_CHECK_BUTTON_H

#include "primitive/t_push_button.hpp"

class TCheckButton : public TPushButton { Q_OBJECT
public:
  TCheckButton(const QPixmap& look);
private:
  QPixmap check_pixmap;
protected:
  void paintEvent(QPaintEvent* event) override;
};  

#endif
