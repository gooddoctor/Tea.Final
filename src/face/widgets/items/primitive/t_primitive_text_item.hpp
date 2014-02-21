#ifndef __T_SIMPLE_TEXT_ITEM_H
#define __T_SIMPLE_TEXT_ITEM_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QObject>

#include "objects/t_object.hpp"

class TPrimitiveTextObject;

class TPrimitiveTextItem : public QGraphicsTextItem,
			   public TObject<TPrimitiveTextItem, 
					  TPrimitiveTextObject, 
					  TPrimitiveTextObject> {
  public:
    TPrimitiveTextItem(const QString& text);
    TPrimitiveTextItem* highlight();
    TPrimitiveTextItem* reset();
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

class TPrimitiveTextObject : public QObject { Q_OBJECT
  public:
    TPrimitiveTextObject(TPrimitiveTextItem* owner);
    TPrimitiveTextObject* emit_select(TPrimitiveTextItem* source);
  private:
    TPrimitiveTextItem* owner;
  signals:
    void select(TPrimitiveTextItem* source);
};

#endif
