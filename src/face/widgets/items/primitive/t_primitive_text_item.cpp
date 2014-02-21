#include <QColor>

#include "t_primitive_text_item.hpp"

const QColor DEFAULT_COLOR(0, 0, 0);
const QColor HIGHLIGHT_COLOR(255, 255, 255);

TPrimitiveTextItem::TPrimitiveTextItem(const QString& text) : QGraphicsTextItem(text),
							      TObject(this) {
  setDefaultTextColor(DEFAULT_COLOR);
}

TPrimitiveTextItem* TPrimitiveTextItem::highlight() {
  setDefaultTextColor(HIGHLIGHT_COLOR);
  return this;
}

TPrimitiveTextItem* TPrimitiveTextItem::reset() {
  setDefaultTextColor(DEFAULT_COLOR);
  return this;
}

void TPrimitiveTextItem::mousePressEvent(QGraphicsSceneMouseEvent*) {
  signal()->emit_select(this);
}

/* TPrimitiveTextObject next */

TPrimitiveTextObject::TPrimitiveTextObject(TPrimitiveTextItem* owner) {
  this->owner = owner;
}

TPrimitiveTextObject* TPrimitiveTextObject::emit_select(TPrimitiveTextItem* source) {
  emit select(source);
  return this;
}
