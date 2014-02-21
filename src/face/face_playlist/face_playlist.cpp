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
  entries_list->setGeometry(LEFT_MARGIN, TOP_MARGIN, entries_list->sizeHint().width(),
			    entries_list->sizeHint().height());
}
