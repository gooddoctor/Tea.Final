#ifndef __T_WIDGET_H
#define __T_WIDGET_H

#include <QPixmap>
#include <QWidget>

class TWidget : public QWidget { Q_OBJECT
public:
    TWidget(const QPixmap& background);
    QSize sizeHint() const override;
private:
    QPixmap background;
protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif
