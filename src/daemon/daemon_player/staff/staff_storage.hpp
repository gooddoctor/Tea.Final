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
    typedef std::vector<std::pair<QString, QString> > Entries;
    Storage();
    static Storage& comming_in_fast() {
      static Storage instance;
      return instance;
    }
    Entries select(const QString& query);
    bool is_mark(const QString& title, const QString& path);
    Storage* mark(const QString& title, const QString& path);
    Storage* unmark(const QString& title, const QString& path);
  private:
    QDomElement find(const QString& title, const QString& path);
    Storage* save();
  private:
    QDomDocument storage;
    QFile data_file;
  };
}

#endif
