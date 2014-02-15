#ifndef __T_LIST_ITEM_H
#define __T_LIST_ITEM_H

#include <functional>
#include <cassert>

#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsTextItem>

#include "t_simple_text_item.hpp"

class TListObject;

class TListItem : public QGraphicsItem, public TObject<TListObject> {
typedef std::function<QString(const QString&)> callback;

public:
  TListItem(const callback& format);

  QRectF boundingRect() const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget);

  TListItem* add(const QString& entry);
  
  TListItem* scroll_up();
  TListItem* scroll_down();

  TListItem* reset();
private:
  TListItem* calculate();
private:
  callback format;

  std::vector<TSimpleTextItem*> text_entries;

  TSimpleTextItem* up;
  TSimpleTextItem* down;

  int start = 0;
protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
  void dropEvent(QGraphicsSceneDragDropEvent* event) override;
  void wheelEvent(QGraphicsSceneWheelEvent* event) override;
};

class TListObject : public QObject { Q_OBJECT
public:
  TListObject* set_parent(TListItem* parent) {
    this->parent = parent;
    return this;
  }
public slots:
  TListObject* up_select() {
    assert(parent);

    parent->scroll_up();
    
    return this;
  }

  TListObject* down_select() {
    assert(parent);

    parent->scroll_down();

    return this;
  }

  TListObject* entry_select(TSimpleTextItem* entry) {
    assert(parent);

    parent->reset();
    entry->highlight();

    emit select(entry->toPlainText());

    return this;
  }
private:
  TListItem* parent = 0;
signals:
  void select(const QString& entry);
};

#endif
  
