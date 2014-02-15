#ifndef __FACE_TALK_H
#define __FACE_TALK_H

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QWebView>

#include "../widgets/t_moveable_widget.hpp"
#include "../widgets/t_push_button.hpp"

namespace face {
  class Talk : public TMoveableWidget { Q_OBJECT
  public:
    Talk(int argc, char** argv);
  private:
    QLabel* title_label;
    TPushButton* close_button;

    QLabel* name_label;
    QLineEdit* name_line_edit;
    TPushButton* send_button;

    QTextEdit* message_text_edit;

    QWebView* talk_web_view;
  };
}
#endif
