#include <cassert>

#include <QFile>

#include "face_talk.hpp"

using namespace face;

const int LEFT_MARGIN = 3;
const int TOP_MARGIN = 3;
const char* TITLE_LABEL_STYLE = 
  "QLabel { "
    "color : #000000;"
    "font: 25px mono;"
  "}";
const char* NAME_LABEL_STYLE =
  "QLabel { "
    "color : #000000;"
    "font: 20px mono;"
  "}";
const char* NAME_LINE_EDIT_STYLE =
  "QLineEdit { "
    "background-color: #FFFFFF;"
    "color: #000000;"
    "border: 2px solid #213d6c;"
  "}";
const char* MESSAGE_TEXT_EDIT_STYLE =
  "QTextEdit { "
    "background-color: #FFFFFF;"
    "color: #000000;"
    "border: 2px solid #213d6c;"
  "}";

QString read(const char* path) {
  QFile file(path);
  assert(file.exists());
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  return file.readAll();
}

Talk::Talk(int, char**) : TWidget(QPixmap(":face_talk/resource/background.png")) {
  title_label = new QLabel("Bon Jovi - its my life");
  title_label->setParent(this);
  title_label->setStyleSheet(TITLE_LABEL_STYLE);
  title_label->setGeometry(LEFT_MARGIN, TOP_MARGIN, 370, 32);
  
  name_label = new QLabel("Имя");
  name_label->setParent(this);
  name_label->setStyleSheet(NAME_LABEL_STYLE);
  name_label->setGeometry(LEFT_MARGIN, 43, name_label->sizeHint().width(),
			  name_label->sizeHint().height());

  name_line_edit = new QLineEdit();
  name_line_edit->setParent(this);
  name_line_edit->setStyleSheet(NAME_LINE_EDIT_STYLE);
  name_line_edit->setGeometry(50 + LEFT_MARGIN, 40 + TOP_MARGIN, 220, 21);

  send_button = new TPushButton(QPixmap(":face_talk/resource/send.png"));
  send_button->setParent(this);
  QObject::connect(send_button, SIGNAL(clicked()), this, SLOT(send_button_handler()));
  send_button->setGeometry(280 + LEFT_MARGIN, 40 + TOP_MARGIN, send_button->sizeHint().width(),
			   send_button->sizeHint().height());

  message_text_edit = new QTextEdit();
  message_text_edit->setParent(this);
  message_text_edit->setAutoFillBackground(true);
  message_text_edit->setStyleSheet(MESSAGE_TEXT_EDIT_STYLE);
  message_text_edit->setGeometry(LEFT_MARGIN, 67 + TOP_MARGIN, 410, 90);
}

Talk* Talk::title_slot(const QString& value) {
  title_label->setText(value);
  return this;
}

Talk* Talk::send_button_handler() {
  QString name = name_line_edit->text();
  QString content = message_text_edit->toPlainText();
  if (!name.isEmpty() && !content.isEmpty())
    emit comment_signal(name, content);
  return this;
}
