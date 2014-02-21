#include <QApplication>

#include "face/face_player/face_player.hpp"
#include "face/face_playlist/face_playlist.hpp"
#include "face/face_talk/face_talk.hpp"

int main(int argc, char** argv) {
  QApplication tea(argc, argv);

  face::Player* face_player = new face::Player(argc, argv);
  face_player->show();

  face::Playlist* face_playlist = new face::Playlist(argc, argv);
  face_playlist->show();

  face::Talk* face_talk = new face::Talk(argc, argv);
  face_talk->show();

  return tea.exec();
}
