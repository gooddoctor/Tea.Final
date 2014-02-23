#ifndef __FACE_PLAYLIST_H
#define __FACE_PLAYLIST_H

#include "../face_playlist.hpp"

namespace face {
  class Playlist : public TWidget { Q_OBJECT
  public:
    Playlist(int argc, char** argv);
  public slots:
    Playlist* previous_slot();
    Playlist* next_slot();
  private:
    TList* entries_list;
  signals:
    void play_signal(const QString& entry);
  };
}

#endif
