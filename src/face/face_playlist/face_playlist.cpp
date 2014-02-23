#include "face_playlist.hpp"

using namespace face;

const int TOP_MARGIN = 8;
const int LEFT_MARGIN = 8; 

const char* ENTRIES_LIST_STYLE = "border: 0px";

Playlist::Playlist(int, char**) : TWidget(QPixmap(":face_playlist/resource/background.png")) {
  entries_list = new TList([](const QString& entry) {
    return entry.toUpper();
  });
  entries_list->setParent(this);
  entries_list->setStyleSheet(ENTRIES_LIST_STYLE);
  QObject::connect(entries_list, SIGNAL(select(const QString&)), 
		   this, SIGNAL(play_signal(const QString&)));
  entries_list->setGeometry(LEFT_MARGIN, TOP_MARGIN, entries_list->sizeHint().width(),
			    entries_list->sizeHint().height());
}

Playlist* Playlist::previous_slot() {
  int size = entries_list->size();
  if (size == 0)
    return this;
  int index = entries_list->get_selected_index() - 1;
  if (index < 0)
    index = entries_list->size() - 1;
  entries_list->set_selected_index(index);
  return this;
}

Playlist* Playlist::next_slot() {
  int size = entries_list->size();
  if (size == 0)
    return this;
  int index = entries_list->get_selected_index() + 1;
  if (index == entries_list->size())
    index = 0;
  entries_list->set_selected_index(index);
  return this;
}
