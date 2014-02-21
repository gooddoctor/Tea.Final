#ifndef __T_PUSH_BUTTON_H
#define __T_PUSH_BUTTON_H

#include <QAbstractButton>
#include <QPixmap>

class TPushButton : public QAbstractButton { Q_OBJECT
public:
  TPushButton(const QPixmap& look);
  QSize sizeHint() const override;
  TPushButton* set_look(const QPixmap& look);
private:
  QPixmap look;
  QPixmap scaled_look;
  bool hover = false;
protected:
  void enterEvent(QEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
};

#endif
