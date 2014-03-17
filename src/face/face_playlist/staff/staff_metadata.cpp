#include <QCoreApplication>
#include <QMediaMetaData>
#include <QMediaPlayer>

#include "staff_metadata.hpp"

using namespace staff;

Metadata::Metadata() {
  player = new QMediaPlayer();
}

QString Metadata::title(const QUrl& path) {
  if (cache.find(path) == cache.end()) {
    player->setMedia(path);
    while (true) {
      if (player->isMetaDataAvailable() && !player->metaData(QMediaMetaData::Title).isNull()) {
	cache.insert({path, player->metaData(QMediaMetaData::Title).toString()});
	break;
      }
      QCoreApplication::processEvents();
    }
  }
  return cache[path];
}
