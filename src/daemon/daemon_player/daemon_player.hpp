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
    Player* thumb_up_slot();
    Player* thumb_down_slot();
    Player* pause_slot();
    Player* play_slot();
    Player* position_slot(int value);
    Player* volume_slot(int value);
    Player* favorite_slot();
    Player* complete_slot(const QString value, QStringList& values);
    Player* comment_slot(const QString& name, const QString& content);
  private slots:
    Player* duration_changed(qint64 value);
    Player* metadata_changed();
    Player* position_changed(qint64 value);
    Player* state_changed(QMediaPlayer::State value);
  private:
    QString path();
    QString title();
    Player* emit_comments_signal();
  private:
    bool terminated = false;
    QMediaPlayer* player;
  signals:
    void thumb_up_signal(int value);
    void thumb_down_signal(int values);
    void done_signal(bool terminated);
    void duration_signal(int value);
    void tick_signal(int value);
    void title_signal(const QString& value);
    void favorite_signal(bool value);
    void comments_signal(const QStringList& names, const QStringList& contents);
  };
}

#endif
