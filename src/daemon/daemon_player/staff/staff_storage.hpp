#ifndef __STAFF_STORAGE_H
#define __STAFF_STORAGE_H

#include <utility>
#include <vector>

#include <QDomDocument>
#include <QDomElement>
#include <QFile>

namespace staff {
  class Storage {
  public:
    typedef std::pair<QString, QString> Entry;
    typedef std::vector<Entry> Entries;
    typedef Entries Comments;
    Storage();
    static Storage& comming_in_fast() {
      static Storage instance;
      return instance;
    }
    Storage* comment(const QString& title, const QString& path,
		     const QString& name,  const QString& content);
    Comments comments(const QString& title, const QString& path);
    Entries select(const QString& query);
    int down(const QString& title, const QString& path);
    int up(const QString& title, const QString& path);
    bool is_mark(const QString& title, const QString& path);
    Storage* mark(const QString& title, const QString& path);
    Storage* unmark(const QString& title, const QString& path);
  private:
    int inc(const QString& title, const QString& path, const QString attr);
    QDomElement find(const QString& title, const QString& path);
    Storage* save();
  private:
    QDomDocument storage;
    QFile data_file;
  };
}

#endif
