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

Player* Player::thumb_up_slot() {
  QString title_value = title();
  if (!title_value.isEmpty()) {
    int count = staff::Storage::comming_in_fast().up(title_value, 
						     player->media().canonicalUrl().path());
    emit thumb_up_signal(count);
  }
  return this;
}

Player* Player::thumb_down_slot() {
  QString title_value = title();
  if (!title_value.isEmpty()) {
    int count = staff::Storage::comming_in_fast().down(title_value, 
						       player->media().canonicalUrl().path());
    emit thumb_down_signal(count);
  }
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
  QString title_value = title();
  if (!title_value.isEmpty()) {
    QString path_value = player->media().canonicalUrl().path();
    if (staff::Storage::comming_in_fast().is_mark(title_value, path_value))
      staff::Storage::comming_in_fast().unmark(title_value, path_value);
    else
      staff::Storage::comming_in_fast().mark(title_value, path_value);
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

Player* Player::comment_slot(const QString& name, const QString& content) {
  QString title_value = title();
  if (!title_value.isEmpty()) {
    QString path_value = player->media().canonicalUrl().path();
    staff::Storage::comming_in_fast().comment(title_value, path_value, name, content);
  }
  return this;
}

Player* Player::duration_changed(qint64 value) {
  emit duration_signal(value / 1000);
  return this;
}

Player* Player::metadata_changed() {
  QString value = title();
  if (!value.isEmpty())
    emit title_signal(value);
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

QString Player::title() {
  if (player->isMetaDataAvailable())
    return QString("%1:%2").arg(player->metaData(QMediaMetaData::AlbumArtist).toString())
			   .arg(player->metaData(QMediaMetaData::Title).toString());
  else
    return "";
}
