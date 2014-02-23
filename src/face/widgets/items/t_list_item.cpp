#include <QFont>
#include <QList>
#include <QMimeData>
#include <QPainter>
#include <QUrl>

#include "t_list_item.hpp"

const int WIDTH = 283;
const int HEIGHT = 220;

const QFont TEXT_FONT("mono", 12, QFont::Bold);

TListItem::TListItem(const callback& format) : TObject(this) {
  this->format = format;
  
  down = new TPrimitiveTextItem("Вниз");
  down->setParentItem(this);
  down->setPos((WIDTH - down->boundingRect().width()) / 2, 200);
  down->setFont(TEXT_FONT);
  QObject::connect(down->signal(), SIGNAL(select(TPrimitiveTextItem*)), 
		   slot(), SLOT(down_select()));
  up = new TPrimitiveTextItem("Вверх");
  up->setParentItem(this);
  up->setPos((WIDTH - up->boundingRect().width()) / 2, 0);
  up->setFont(TEXT_FONT);
  QObject::connect(up->signal(), SIGNAL(select(TPrimitiveTextItem*)), 
		   slot(), SLOT(up_select()));
  
  setAcceptDrops(true);
}

void TListItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
  painter->setPen([]() {
    QPen pen(QColor(213, 213, 213));
    pen.setWidth(1);
    return pen;
  }());
  painter->setBrush(QBrush(QColor(213, 213, 213)));
  painter->drawRoundedRect(0, 0, WIDTH, HEIGHT, 10, 10);

  painter->setPen([]() {
    QPen pen(QColor(0, 0, 0));
    pen.setWidth(2);
    return pen;
  }());
  for (int i = 1; i <= 10; i++)
    painter->drawLine(1, i * 20 + 2, WIDTH, i * 20 + 2);
}

QRectF TListItem::boundingRect() const {
  return QRectF(0, 0, WIDTH, HEIGHT);
}

TListItem* TListItem::add(const QString& entry) {
  TPrimitiveTextItem* item = new TPrimitiveTextItem(format(entry));
  item->setParentItem(this);
  item->setFont(TEXT_FONT);
  item->setToolTip(format(entry)); 
  QObject::connect(item->signal(), SIGNAL(select(TPrimitiveTextItem*)), 
		   slot(), SLOT(entry_select(TPrimitiveTextItem*)));
  entries.push_back(item);
  calculate();
  return this;
}

TListItem* TListItem::entry_is_selected(TPrimitiveTextItem* entry) {
  Q_ASSERT(std::find(entries.begin(), entries.end(), entry) != entries.end());
  current_index = std::find(entries.begin(), entries.end(), entry) - entries.begin();
  return this;
}

TListItem* TListItem::reset() {
  for (auto it = entries.begin(); it != entries.end(); it++)
    (*it)->reset();
  return this;
}

TListItem* TListItem::scroll_down() {
  if ((entries.size() - start) > 9) {
    start++;
    calculate();
  }
  return this;
}

TListItem* TListItem::scroll_up() {
  if (start > 0) {
    start--;
    calculate();
  }
  return this;
}

TListItem* TListItem::set_selected_index(int index) {
  Q_ASSERT(index >= 0 && index < entries.size());
  entries[index]->select();
  return this;
}

int TListItem::get_selected_index() {
  return current_index;
}

int TListItem::size() {
  return entries.size();
}

TListItem* TListItem::calculate() {
  int i = 0;
  for (auto it = entries.begin(); it != entries.end(); it++, i++)
    if (i >= start && i < start + 9) {
      (*it)->setPos(0, (i - start + 1) * 20);
      (*it)->show();
    } else {
      (*it)->hide();
    }
  return this;
}

void TListItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
  if (event->mimeData()->hasUrls())
    event->accept();
}

void TListItem::dropEvent(QGraphicsSceneDragDropEvent* event) {
  QList<QUrl> urls = event->mimeData()->urls();
  for (auto it = urls.begin(); it != urls.end(); it++)
    add(it->path());
}

void TListItem::wheelEvent(QGraphicsSceneWheelEvent* event) {
  if (event->delta() > 0)
    scroll_up();
  else
    scroll_down();
}

/* TListObject next */

TListObject::TListObject(TListItem* owner) {
  this->owner = owner;
}

TListObject* TListObject::down_select() {
  owner->scroll_down();
  return this;
}

TListObject* TListObject::entry_select(TPrimitiveTextItem* entry) {
  owner->reset();
  owner->entry_is_selected(entry);
  owner->signal()->emit_select(entry->toPlainText());
  entry->highlight();
  return this;
}

TListObject* TListObject::up_select() {
  owner->scroll_up();
  return this;
}

TListObject* TListObject::emit_select(const QString& entry) {
  emit select(entry);
  return this;
}
