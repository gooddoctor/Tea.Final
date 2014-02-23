#ifndef __DAEMON_PLAYER_H
#define __DAEMON_PLAYER_H

#include <QMediaPlayer>
#include <QObject>
#include <QUrl>

namespace daemon {
  class Player : public QObject { Q_OBJECT
  public:
    Player(int argc, char** argv);
  public slots:
    Player* open_slot(const QUrl& file_path, bool by_user);
    Player* play_slot();
    Player* pause_slot();
    Player* volume_slot(int value);
  private:
    QMediaPlayer* player;
  };
}

#endif
