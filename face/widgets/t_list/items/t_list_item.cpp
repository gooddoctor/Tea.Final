#include <QList>
#include <QPainter>
#include <QUrl>
#include <QMimeData>
#include <QFont>

#include "t_list_item.hpp"

const int WIDTH = 283;
const int HEIGHT = 220;

const QFont TEXT_FONT("mono", 12, QFont::Bold);

TListItem::TListItem(const callback& format) {
  this->format = format;

  tobject()->set_parent(this);
  up = new TSimpleTextItem("Вверх", this);
  up->setPos((WIDTH - up->boundingRect().width()) / 2, 0);
  up->setFont(TEXT_FONT);
  QObject::connect(up->tobject(), SIGNAL(select(TSimpleTextItem*)), 
		  tobject(), SLOT(up_select()));
    
  down = new TSimpleTextItem("Вниз", this);
  down->setPos((WIDTH - down->boundingRect().width()) / 2, 200);
  down->setFont(TEXT_FONT);
  QObject::connect(down->tobject(), SIGNAL(select(TSimpleTextItem*)), 
		  tobject(), SLOT(down_select()));

  setAcceptDrops(true);
}

QRectF TListItem::boundingRect() const {
  return QRectF(0, 0, WIDTH, HEIGHT);
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

TListItem* TListItem::add(const QString& entry) {
  TSimpleTextItem* text_entry = new TSimpleTextItem(format(entry), this);
  text_entry->setFont(TEXT_FONT);
  text_entry->setToolTip(format(entry)); 

  QObject::connect(text_entry->tobject(), SIGNAL(select(TSimpleTextItem*)), 
		   tobject(), SLOT(entry_select(TSimpleTextItem*)));

  text_entries.push_back(text_entry);
    
  return calculate();
}

TListItem* TListItem::scroll_up() {
  if (start > 0) {
    start--;
    calculate();
  }
  return this;
}

TListItem* TListItem::scroll_down() {
  if ((text_entries.size() - start) > 9) {
    start++;
    calculate();
  }
  return this;
}

TListItem* TListItem::calculate() {
  int i = 0;
  for (auto it = text_entries.begin(); it != text_entries.end(); it++, i++)
    if (i >= start && i < start + 9) {
      (*it)->setPos(0, (i - start + 1) * 20);
      (*it)->show();
    } else {
      (*it)->hide();
    }
  return this;
}

TListItem* TListItem::reset() {
  for (auto it = text_entries.begin(); it != text_entries.end(); it++)
    (*it)->reset();
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
