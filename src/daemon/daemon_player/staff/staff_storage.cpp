#include <QDir>
#include <QStandardPaths>
#include <QTextStream>

#include "staff_storage.hpp"

using namespace staff;

Storage::Storage() : storage("likes") {
  QDir data_dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
  if (!data_dir.exists())
    data_dir.mkpath(".");
  data_file.setFileName(data_dir.filePath("storage.xml"));
  if (!data_file.exists()) {
    data_file.open(QIODevice::ReadWrite);
    storage.appendChild(storage.createElement("likes"));
    save();
  } else {
    data_file.open(QIODevice::ReadWrite);
    storage.setContent(&data_file);
  }
}

bool Storage::is_mark(const QString& title, const QString& path) {
  return !find(title, path).isNull();
}

Storage* Storage::mark(const QString& title, const QString& path) {
  QDomElement entry = storage.createElement("song");
  entry.setAttribute("title", title);
  entry.setAttribute("path", path);
  storage.documentElement().appendChild(entry);
  save();
  return this;
}

Storage* Storage::unmark(const QString& title, const QString& path) {
  QDomElement entry = find(title, path);
  if (!entry.isNull()) {
    storage.documentElement().removeChild(entry);
    save();
  }
  return this;
}

QDomElement Storage::find(const QString& title, const QString& path) {
  QDomElement entry = storage.documentElement().firstChildElement();
  for (QDomElement entry = storage.documentElement().firstChildElement(); !entry.isNull();
       entry = entry.nextSiblingElement()) 
    if (entry.attribute("title").contains(title, Qt::CaseInsensitive) &&
	entry.attribute("path").contains(path, Qt::CaseInsensitive))
      return entry;
  return QDomElement();
}

Storage* Storage::save() {
  data_file.seek(0);
  QTextStream out(&data_file);
  storage.save(out, 4);
  data_file.resize(data_file.pos());
  return this;
}
