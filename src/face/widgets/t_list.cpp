#include "t_list.hpp"

const int WIDTH = 283;
const int HEIGHT = 220;

TList::TList(const callback& format) {
  this->format = format;
  entries_list = new TListItem([this](const QString& entry) {
    format_mapping.insert({this->format(entry), entry});
    return this->format(entry);
  });
  entries_list->setPos(0, 0);
  QObject::connect(entries_list->signal(), SIGNAL(select(const QString&)),
		   this, SLOT(entry_select(const QString&)));

  scene = new QGraphicsScene();
  scene->addItem(entries_list);
  scene->setSceneRect(0, 0, 283, 220);

  setScene(scene);
  setAcceptDrops(true);
}

TList* TList::entry_select(const QString&) {
  return this;
}
