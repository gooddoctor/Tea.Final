#include <QMediaMetaData>

#include "daemon_player.hpp"

using namespace daemon;

const int DEFAULT_VOLUME = 25;

Player::Player(int, char**) {
  player = new QMediaPlayer();
  player->setVolume(DEFAULT_VOLUME);
  QObject::connect(player, SIGNAL(durationChanged(qint64)), 
		   this, SLOT(duration_changed(qint64)));
  QObject::connect(player, SIGNAL(metaDataChanged()), 
		   this, SLOT(metadata_changed()));
  QObject::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
		   this, SLOT(state_changed(QMediaPlayer::State)));
}

Player* Player::open_slot(const QUrl& file_path, bool) {
  Q_ASSERT(!file_path.isEmpty());
  if (player->state() == QMediaPlayer::PlayingState ||
      player->state() == QMediaPlayer::PausedState) {
    terminated = true;
    player->stop();
  }
  player->setMedia(file_path);
  return this;
}

Player* Player::play_slot() {
  player->play();
  return this;
}

Player* Player::pause_slot() {
  player->pause();
  return this;
}
  
Player* Player::volume_slot(int value) {
  player->setVolume(value);
  return this;
}

Player* Player::duration_changed(qint64 value) {
  emit duration_signal(value / 1000);
  return this;
}

Player* Player::metadata_changed() {
  if (player->isMetaDataAvailable())
    emit title_signal(QString("%1:%2").arg(player->metaData(QMediaMetaData::AlbumArtist).toString())
				      .arg(player->metaData(QMediaMetaData::Title).toString()));
  return this;
}

Player* Player::state_changed(QMediaPlayer::State value) {
  if (value == QMediaPlayer::StoppedState) {
    emit done_signal(terminated);
    terminated = false;
  }
  return this;
}
