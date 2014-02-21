#ifndef __FACE_PLAYLIST_H
#define __FACE_PLAYLIST_H

#include "../face_playlist.hpp"

namespace face {
  class Playlist : public TWidget { Q_OBJECT
  public:
    Playlist(int argc, char** argv);
  private:
    TList* entries_list;
  };
}

#endif
