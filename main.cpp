#include <QApplication>

#include "face/face_player.hpp"
#include "face/face_playlist.hpp"
#include "face/face_talk.hpp"

int main(int argc, char** argv) {
  QApplication tea(argc, argv);

  face::Player* player = new face::Player(argc, argv);
  player->show();

  face::Playlist* playlist = new face::Playlist(argc, argv);
  playlist->show();

  face::Talk* talk = new face::Talk(argc, argv);
  talk->show();

  return tea.exec();
}
