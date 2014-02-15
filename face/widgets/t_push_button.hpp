#ifndef __T_PUSH_BUTTON_H
#define __T_PUSH_BUTTON_H

#include <QAbstractButton>
#include <QPixmap>

class TPushButton : public QAbstractButton { Q_OBJECT
public:
    TPushButton(const QPixmap& look);
    TPushButton* set_look(const QPixmap& look);
    QSize sizeHint() const override;
private:
    QPixmap original_look;
    QPixmap scaled_look;

    bool hover = false;
protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
};

#endif
