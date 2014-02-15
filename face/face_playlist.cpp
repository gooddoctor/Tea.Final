#include "face_playlist.hpp"

using namespace face;

const int LEFT_MARGIN = 8; 
const int TOP_MARGIN = 8;

const char* SONG_LIST_STYLE = "border: 0px";

Playlist::Playlist(int, char**) : 
    TMoveableWidget(QPixmap(":face/resource/playlist_background.png")) {
  song_list = new TList([](const QString& entry) {
    return entry.toUpper();
  });
  song_list->setParent(this);
  song_list->setStyleSheet(SONG_LIST_STYLE);
  song_list->setGeometry(LEFT_MARGIN, TOP_MARGIN, song_list->sizeHint().width(),
			 song_list->sizeHint().height());


  close_button = new TPushButton(QPixmap(":face/resource/close.png"));
  close_button->setParent(this);
  close_button->setGeometry(387, 3, close_button->sizeHint().width(), 
                            close_button->sizeHint().height());
}

