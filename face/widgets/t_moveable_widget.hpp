#ifndef __T_MOVEABLE_WIDGET_H
#define __T_MOVEABLE_WIDGET_H

#include "t_widget.hpp"

class TMoveableWidget : public TWidget { Q_OBJECT
public:
    TMoveableWidget(const QPixmap& background);
private:
    int x_offset = 0;
    int y_offset = 0;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif
