#ifndef __T_WIDGET_H
#define __T_WIDGET_H

#include <QMouseEvent>
#include <QPixmap>
#include <QWidget>

#include "primitive/t_push_button.hpp"

class TWidget : public QWidget { Q_OBJECT
public:
  TWidget(const QPixmap& background);
  QSize sizeHint() const override;
public slots:
  TWidget* show_it(bool value, int x, int y);
private:
  QPixmap background;
  TPushButton* close_button;
  int x_offset = 0;
  int y_offset = 0;
protected:
  void mouseMoveEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
signals:
  void clos();
};

#endif
