#ifndef __FACE_TALK_H
#define __FACE_TALK_H

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include "../face_talk.hpp"

namespace face {
  class Talk : public TWidget { Q_OBJECT
  public:
    Talk(int argc, char** argv);
  private:
    QLabel* title_label;
    QLabel* name_label;
    QLineEdit* name_line_edit;
    TPushButton* send_button;
    QTextEdit* message_text_edit;
  };
}

#endif