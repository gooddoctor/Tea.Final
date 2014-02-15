#ifndef __FACE_PLAYLIST_H
#define __FACE_PLAYLIST_H

#include "widgets/t_moveable_widget.hpp"
#include "widgets/t_push_button.hpp"
#include "widgets/t_list.hpp"

namespace face {
  class Playlist : public TMoveableWidget { Q_OBJECT
  public:
    Playlist(int argc, char** argv);
  private:
    TList* song_list;
    TPushButton* close_button;
  };
}

#endif
