#ifndef __STAFF_STORAGE_H
#define __STAFF_STORAGE_H

#include <QDomDocument>
#include <QDomElement>
#include <QFile>

namespace staff {
  class Storage {
  public:
    Storage();
    static Storage& comming_in_fast() {
      static Storage instance;
      return instance;
    }
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
