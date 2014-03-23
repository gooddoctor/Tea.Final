#ifndef __T_LINE_EDIT_H
#define __T_LINE_EDIT_H

#include <vector>

#include <QLineEdit>
#include <QStringListModel>

class TLineEdit : public QLineEdit { Q_OBJECT
public:
  TLineEdit();
private slots:
  TLineEdit* return_handler();
  TLineEdit* text_handler(const QString& value);
private:
  QStringListModel values;
signals:
  void complete(const QString& value, QStringList& values);
  void select(const QString& value);
};

#endif
