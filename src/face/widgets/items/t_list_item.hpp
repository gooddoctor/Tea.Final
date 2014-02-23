#ifndef __T_LIST_ITEM_H
#define __T_LIST_ITEM_H

#include <cassert>
#include <functional>
#include <vector>

#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsTextItem>
#include <QObject>

#include "primitive/t_primitive_text_item.hpp"

class TListObject;

class TListItem : public QGraphicsItem, public TObject<TListItem, TListObject, TListObject> {
typedef std::function<QString(const QString&)> callback;
public:
  TListItem(const callback& format);
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget);
  QRectF boundingRect() const;
  TListItem* add(const QString& entry);
  TListItem* entry_is_selected(TPrimitiveTextItem* entry);
  TListItem* reset();
  TListItem* scroll_down();
  TListItem* scroll_up();
  TListItem* set_selected_index(int index);
  int get_selected_index();
  int size();
private:
  TListItem* calculate();
private:
  callback format;
  int current_index = -1;
  int start = 0;
  std::vector<TPrimitiveTextItem*> entries;

  TPrimitiveTextItem* down;
  TPrimitiveTextItem* up;
protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
  void dropEvent(QGraphicsSceneDragDropEvent* event) override;
  void wheelEvent(QGraphicsSceneWheelEvent* event) override;
};

class TListObject : public QObject { Q_OBJECT
public:
  TListObject(TListItem* owner);
public slots:
  TListObject* down_select();
  TListObject* entry_select(TPrimitiveTextItem* entry);
  TListObject* up_select();
  TListObject* emit_select(const QString& entry);
private:
  TListItem* owner = 0;
signals:
  void select(const QString& entry);
};
#endif
