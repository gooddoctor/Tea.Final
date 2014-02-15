#include "t_simple_text_item.hpp"

const QColor DEFAULT_COLOR(0, 0, 0);
const QColor HIGHLIGHT_COLOR(255, 255, 255);

TSimpleTextItem::TSimpleTextItem(const QString& text, QGraphicsItem* parent) :
  QGraphicsTextItem(text, parent) {
  setDefaultTextColor(DEFAULT_COLOR);
}

TSimpleTextItem* TSimpleTextItem::highlight() {
  setDefaultTextColor(HIGHLIGHT_COLOR);
  return this;
}

TSimpleTextItem* TSimpleTextItem::reset() {
  setDefaultTextColor(DEFAULT_COLOR);
  return this;
}

void TSimpleTextItem::mousePressEvent(QGraphicsSceneMouseEvent*) {
  tobject()->emit_select(this);
}
