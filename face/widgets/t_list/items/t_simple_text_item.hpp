#ifndef __T_SIMPLE_TEXT_ITEM_H
#define __T_SIMPLE_TEXT_ITEM_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

#include "t_object.hpp"

class TSimpleTextObject;  

class TSimpleTextItem : public QGraphicsTextItem, public TObject<TSimpleTextObject> {
public:
  TSimpleTextItem(const QString& text, QGraphicsItem* parent);
  TSimpleTextItem* highlight();
  TSimpleTextItem* reset();
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

class TSimpleTextObject : public QObject { Q_OBJECT
  public:
  TSimpleTextObject* emit_select(TSimpleTextItem* source) {
    emit select(source);
    return this;
  }
signals:
  void select(TSimpleTextItem* source);
};  

#endif
