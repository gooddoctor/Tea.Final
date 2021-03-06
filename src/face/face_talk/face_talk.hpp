#ifndef __FACE_TALK_H
#define __FACE_TALK_H

#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QTextEdit>

#include "../face_talk.hpp"

namespace face {
  class Talk : public TWidget { Q_OBJECT
  public:
    Talk(int argc, char** argv);
  public slots:
    Talk* title_slot(const QString& value);
    Talk* comments_slot(const QStringList& names, const QStringList& contents);
  private slots:
    Talk* send_button_handler();
  private:
    QLabel* title_label;
    QLabel* name_label;
    QLineEdit* name_line_edit;
    TPushButton* send_button;
    QTextEdit* message_text_edit;
    QScrollArea* chat_scroll_area;
  signals:
    void comment_signal(const QString& name, const QString& content);
  };
}

#endif
