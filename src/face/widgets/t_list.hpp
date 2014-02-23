#ifndef __T_LIST_H
#define __T_LIST_H

#include <functional>
#include <map>

#include <QGraphicsView>

#include "items/t_list_item.hpp"

class TList : public QGraphicsView { Q_OBJECT
typedef std::function<QString(const QString&)> callback;
public:
  TList(const callback& format);
  int get_selected_index();
  TList* set_selected_index(int index);
  int size();
private slots:
  TList* entry_select(const QString& entry);
private:
  QGraphicsScene* scene;
  TListItem* entries_list;
  std::map<QString, QString> format_mapping;
  callback format;
signals:
  void select(const QString& entry);
};

#endif
