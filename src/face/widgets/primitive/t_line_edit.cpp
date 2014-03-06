#include <QCompleter>

#include "t_line_edit.hpp"

TLineEdit::TLineEdit() {
  QCompleter* completer = new QCompleter(&values);
  completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  setCompleter(completer);
  QObject::connect(this, SIGNAL(textEdited(const QString&)), 
		   this, SLOT(text_handler(const QString&)));
}

TLineEdit* TLineEdit::text_handler(const QString& value) {
  QStringList variants;
  emit complete(value, variants);
  values.setStringList(variants);
  completer()->complete();
  return this;
}
