#ifndef __T_SLIDER_H
#define __T_SLIDER_H

#include <QSlider>

class TSlider : public QSlider {
public:
  using QSlider::QSlider;
  bool is_hover();
private:
  bool hover = false;
protected:
  void enterEvent(QEvent* event) override;
  void leaveEvent(QEvent* event) override;
};

#endif
