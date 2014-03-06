#include <QApplication>

#include "daemon/daemon_player/daemon_player.hpp"
#include "face/face_player/face_player.hpp"
#include "face/face_playlist/face_playlist.hpp"
#include "face/face_talk/face_talk.hpp"

int main(int argc, char** argv) {
  QApplication tea(argc, argv);

  daemon::Player* daemon_player = new daemon::Player(argc, argv);

  face::Player* face_player = new face::Player(argc, argv);
  face::Playlist* face_playlist = new face::Playlist(argc, argv);
  face::Talk* face_talk = new face::Talk(argc, argv);

  QObject::connect(daemon_player, SIGNAL(done_signal(bool)),
		   face_playlist, SLOT(done_slot(bool)));
  QObject::connect(daemon_player, SIGNAL(duration_signal(int)),
		   face_player, SLOT(duration_slot(int)));
  QObject::connect(daemon_player, SIGNAL(tick_signal(int)),
		   face_player, SLOT(tick_slot(int)));
  QObject::connect(daemon_player, SIGNAL(title_signal(const QString&)),
		   face_player, SLOT(title_slot(const QString&)));

  QObject::connect(face_player, SIGNAL(open_signal(const QUrl&, bool)),
 		   daemon_player, SLOT(open_slot(const QUrl&, bool)));
  QObject::connect(face_player, SIGNAL(open_signal(const QUrl&, bool)),
		   face_playlist, SLOT(open_slot(const QUrl&, bool)));
  QObject::connect(face_player, SIGNAL(play_signal()),
		   daemon_player, SLOT(play_slot()));
  QObject::connect(face_player, SIGNAL(pause_signal()),
		   daemon_player, SLOT(pause_slot()));
  QObject::connect(face_player, SIGNAL(volume_signal(int)),
		   daemon_player, SLOT(volume_slot(int)));
  QObject::connect(face_player, SIGNAL(previous_signal()),
		   face_playlist, SLOT(previous_slot()));
  QObject::connect(face_player, SIGNAL(next_signal()),
		   face_playlist, SLOT(next_slot()));
  QObject::connect(face_player, SIGNAL(normal_signal()),
		   face_playlist, SLOT(next_slot())); 
  QObject::connect(face_player, SIGNAL(repeat_signal()),
		   face_playlist, SLOT(repeat_slot())); 
  QObject::connect(face_player, SIGNAL(shuffle_signal()),
		   face_playlist, SLOT(shuffle_slot())); 
  QObject::connect(face_player, SIGNAL(position_signal(int)),
		   daemon_player, SLOT(position_slot(int))); 
  QObject::connect(face_player, SIGNAL(favorite_signal()),
		   daemon_player, SLOT(favorite_slot())); 
  QObject::connect(face_player, SIGNAL(complete_signal(const QString, QStringList&)),
		   daemon_player, SLOT(complete_slot(const QString, QStringList&)),
		   Qt::DirectConnection);
  QObject::connect(face_playlist, SIGNAL(play_signal(const QString&)),
		   face_player, SLOT(play_slot(const QString&)));

  face_player->show();
  face_playlist->show();
  face_talk->show();

  return tea.exec();
}
