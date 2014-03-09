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

Storage* Storage::comment(const QString& title, const QString& path,
                          const QString& name,  const QString& content) {
  QDomElement entry = find(title, path);
  if (!entry.isNull()) {
    QDomElement comment_entry = storage.createElement("comment");
    comment_entry.setAttribute("name", name);
    comment_entry.appendChild(storage.createTextNode(content));
    entry.appendChild(comment_entry);
    save();
  }
  return this;
}

Storage::Comments Storage::comments(const QString& title, const QString& path) {
  Comments comments;
  QDomElement entry = find(title, path);
  if (!entry.isNull()) {
    for (QDomElement comment = entry.firstChildElement(); !comment.isNull(); 
	 comment = comment.nextSiblingElement()) {
      comments.push_back({comment.attribute("name"), comment.firstChild().toText().data()});
    }
  }
  return comments;
}

Storage::Entries Storage::select(const QString& query) {
  Entries entries;
  for (QDomElement entry = storage.documentElement().firstChildElement(); !entry.isNull();
       entry = entry.nextSiblingElement()) {
    if (entry.attribute("title").contains(query, Qt::CaseInsensitive) ||
        entry.attribute("path").contains(query, Qt::CaseInsensitive))
      entries.push_back({entry.attribute("title"), entry.attribute("path")});
  }
  return entries;
}

int Storage::down(const QString& title, const QString& path) {
  return inc(title, path, "hates");
}

int Storage::up(const QString& title, const QString& path) {
  return inc(title, path, "loves");
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

int Storage::inc(const QString& title, const QString& path, const QString attr) {
  QDomElement entry = find(title, path);
  if (!entry.isNull()) {
    QString attr_value = entry.attribute(attr);
    if (attr_value.isEmpty())
      entry.setAttribute(attr, 1);
    else
      entry.setAttribute(attr, attr_value.toInt() + 1);
    save();
    return entry.attribute(attr).toInt();
  } else {
    return -1;
  }
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
