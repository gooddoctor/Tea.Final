#ifndef __FACE_PLAYLIST_H
#define __FACE_PLAYLIST_H

#include "../face_playlist.hpp"

namespace face {
  class Playlist : public TWidget { Q_OBJECT
  enum State {NORMAL, REPEAT, SHUFFLE};
  public:
    Playlist(int argc, char** argv);
  public slots:
    Playlist* open_slot(const QUrl& file_path, bool by_user);
    Playlist* done_slot(bool terminated);
    Playlist* search_slot(const QUrl& file_path);
    Playlist* previous_slot();
    Playlist* next_slot();
    Playlist* normal_slot();
    Playlist* repeat_slot();
    Playlist* shuffle_slot();
  private:
    TList* entries_list;
    State what_next = NORMAL;
  signals:
    void play_signal(const QString& entry);
  };
}

#endif
