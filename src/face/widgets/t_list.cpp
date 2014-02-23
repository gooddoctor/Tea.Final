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

int TList::get_selected_index() {
  return entries_list->get_selected_index();
}

TList* TList::set_selected_index(int index) {
  entries_list->set_selected_index(index);
  return this;
}

int TList::size() {
  return entries_list->size();
}

TList* TList::entry_select(const QString& entry) {
  emit select(format_mapping[entry]);
  return this;
}
