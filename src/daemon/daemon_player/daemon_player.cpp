#include <QMediaMetaData>

#include "staff/staff_storage.hpp"
#include "daemon_player.hpp"

using namespace daemon;

const int DEFAULT_NOTIFY = 200;
const int DEFAULT_VOLUME = 25;

Player::Player(int, char**) {
  player = new QMediaPlayer();
  player->setVolume(DEFAULT_VOLUME);
  player->setNotifyInterval(DEFAULT_NOTIFY);
  QObject::connect(player, SIGNAL(durationChanged(qint64)), 
		   this, SLOT(duration_changed(qint64)));
  QObject::connect(player, SIGNAL(metaDataChanged()), 
		   this, SLOT(metadata_changed()));
  QObject::connect(player, SIGNAL(positionChanged(qint64)),
		   this, SLOT(position_changed(qint64)));
  QObject::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
		   this, SLOT(state_changed(QMediaPlayer::State)));
}

Player* Player::open_slot(const QUrl& file_path, bool by_user) {
  if (by_user) { //nothing todo
    return this;
  }
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

Player* Player::position_slot(int value) {
  player->setPosition(value * 1000);
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

Player* Player::favorite_slot() {
  if (player->isMetaDataAvailable()) {
    QString title = QString("%1:%2").arg(player->metaData(QMediaMetaData::AlbumArtist).toString())
				    .arg(player->metaData(QMediaMetaData::Title).toString());
    QString path = player->media().canonicalUrl().path();
    if (staff::Storage::comming_in_fast().is_mark(title, path))
      staff::Storage::comming_in_fast().unmark(title, path);
    else
      staff::Storage::comming_in_fast().mark(title, path);
  }
  return this;
}

Player* Player::complete_slot(const QString value, QStringList& values) {
  staff::Storage::Entries entries = staff::Storage::comming_in_fast().select(value);
  std::transform(entries.begin(), entries.end(), std::back_inserter(values),
		 [](std::pair<QString, QString> entry) {
		   return entry.first;
		 });
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

Player* Player::position_changed(qint64 value) {
  emit tick_signal(value / 1000);
  return this;
}

Player* Player::state_changed(QMediaPlayer::State value) {
  if (value == QMediaPlayer::StoppedState) {
    emit done_signal(terminated);
    terminated = false;
  }
  return this;
}
