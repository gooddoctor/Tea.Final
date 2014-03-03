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
    Player* pause_slot();
    Player* play_slot();
    Player* position_slot(int value);
    Player* volume_slot(int value);
    Player* favorite_slot();
  private slots:
    Player* duration_changed(qint64 value);
    Player* metadata_changed();
    Player* position_changed(qint64 value);
    Player* state_changed(QMediaPlayer::State value);
  private:
    bool terminated = false;
    QMediaPlayer* player;
  signals:
    void done_signal(bool terminated);
    void duration_signal(int value);
    void tick_signal(int value);
    void title_signal(const QString& value);
  };
}

#endif
