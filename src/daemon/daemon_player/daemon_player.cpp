#include "daemon_player.hpp"

using namespace daemon;

const int DEFAULT_VOLUME = 25;

Player::Player(int, char**) {
  player = new QMediaPlayer();
  player->setVolume(DEFAULT_VOLUME);
}

Player* Player::open_slot(const QUrl& file_path, bool) {
  Q_ASSERT(!file_path.isEmpty());
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
