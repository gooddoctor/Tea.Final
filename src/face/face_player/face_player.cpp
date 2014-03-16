#include <QFileDialog>

#include "face_player.hpp"

using namespace face;

const int TOP_MARGIN = 3;
const int LEFT_MARGIN = 5;

const char* THUMB_UP_LABEL_STYLE = 
  "QLabel { "
    "color : #000000;"
    "font: 15px mono;"
  "}";
const char* THUMB_DOWN_LABEL_STYLE =
  "QLabel { "
    "color : #000000;"
    "font: 15px mono;"
  "}";
const char* SEARCH_WIDGET_STYLE = 
  "QWidget { "
    "background-color : #000000;"
  "}";
const char* SEARCH_LINE_EDIT_STYLE = 
  "QLineEdit { "
    "background-color: #FFFFFF;"
    "color: #000000;"
    "border: 2px solid #213d6c;"
  "}";
const char* VOLUME_SLIDER_STYLE =
  "QSlider::groove:horizontal {"
    "border: 1px solid #000000;"
    "height: 10px;"
    "background: #cecece;"
  "}"
  "QSlider::handle:horizontal {"
    "background: #0069a2; "
    "width: 10px;"
  "}";
const char* CONTENT_WIDGET_STYLE =
  "QWidget { "
    "background-color: #000000;"
    "border-radius: 10px;"
  "}";
const char* SONG_LABEL_STYLE =
  "QLabel { "
    "color : #ffffff;"
    "font: 18px mono;"
  "}";
const char* CURRENT_LABEL_STYLE =
  "QLabel { "
    "color : #FFFFFF;"
    "font: 18px mono;"
  "}";
const char* POSITION_SLIDER_STYLE =
  "QSlider::groove:horizontal {"
    "border: 1px solid #000000;"
    "height: 10px;"
    "background: #0069a2;"
  "}"
  "QSlider::handle:horizontal {"
    "background: #cecece; "
    "width: 10px;"
  "}";
const char* DURATION_LABEL_STYLE = 
  "QLabel { "
    "color : #848484;"
    "font: 18px monospace;"
  "}";

Player::Player(int, char**) : TWidget(QPixmap(":face_player/resource/background.png")) {
  open_button = new TPushButton(QPixmap(":face_player/resource/open.png"));
  open_button->setParent(this);
  QObject::connect(open_button, SIGNAL(clicked()), this, SLOT(open_button_click_handler()));
  open_button->setGeometry(LEFT_MARGIN, TOP_MARGIN, open_button->sizeHint().width(),
			   open_button->sizeHint().height());

  thumb_up_button = new TPushButton(QPixmap(":face_player/resource/thumb_up.png"));
  thumb_up_button->setParent(this);
  QObject::connect(thumb_up_button, SIGNAL(clicked()), this, SIGNAL(thumb_up_signal()));
  thumb_up_button->setGeometry(74, TOP_MARGIN, thumb_up_button->sizeHint().width(), 
                               thumb_up_button->sizeHint().height());
  					
  thumb_up_label = new QLabel("0");			
  thumb_up_label->setParent(thumb_up_button);
  thumb_up_label->setStyleSheet(THUMB_UP_LABEL_STYLE);
  thumb_up_label->setGeometry(15, 13, thumb_up_label->sizeHint().width(),
                              thumb_up_label->sizeHint().height());

  thumb_down_button = new TPushButton(QPixmap(":face_player/resource/thumb_down.png"));
  thumb_down_button->setParent(this);
  QObject::connect(thumb_down_button, SIGNAL(clicked()), this, SIGNAL(thumb_down_signal()));
  thumb_down_button->setGeometry(107, TOP_MARGIN, thumb_down_button->sizeHint().width(), 
                                 thumb_down_button->sizeHint().height());

  thumb_down_label = new QLabel("0");
  thumb_down_label->setParent(thumb_down_button);
  thumb_down_label->setStyleSheet(THUMB_DOWN_LABEL_STYLE);
  thumb_down_label->setGeometry(15, 2, thumb_down_label->sizeHint().width(),
                                thumb_down_label->sizeHint().height());

  talk_button = new TCheckButton(QPixmap(":face_player/resource/talk.png"));
  talk_button->setParent(this);
  QObject::connect(talk_button, SIGNAL(toggled(bool)),
		   this, SLOT(talk_button_toggle_handler(bool)));
  talk_button->setGeometry(157, TOP_MARGIN, talk_button->sizeHint().width(), 
                           talk_button->sizeHint().height());
  
  search_widget = new QWidget();
  search_widget->setParent(this);
  search_widget->setStyleSheet(SEARCH_WIDGET_STYLE);
  search_widget->setGeometry(189, TOP_MARGIN, 165, 28);

  search_line_edit = new TLineEdit();
  search_line_edit->setParent(search_widget);
  search_line_edit->setAutoFillBackground(true);
  search_line_edit->setStyleSheet(SEARCH_LINE_EDIT_STYLE);
  QObject::connect(search_line_edit, SIGNAL(complete(const QString&, QStringList&)),
		   this, SIGNAL(complete_signal(const QString&, QStringList&)), Qt::DirectConnection);
  search_line_edit->setGeometry(4, 4, 135, 21);

  search_button = new TPushButton(QPixmap(":face_player/resource/search.png"));
  search_button->setParent(search_widget);
  search_button->setGeometry(140, 4, search_button->sizeHint().width(), 
                             search_button->sizeHint().height());
  minimize_button = new TPushButton(QPixmap(":face_player/resource/minimize.png"));
  minimize_button->setParent(this);
  minimize_button->setGeometry(355, TOP_MARGIN, minimize_button->sizeHint().width(), 
                               minimize_button->sizeHint().height());

  playlist_button = new TCheckButton(QPixmap(":face_player/resource/playlist.png"));
  playlist_button->setParent(this);
  QObject::connect(playlist_button, SIGNAL(toggled(bool)),
		   this, SLOT(playlist_button_toggle_handler(bool)));
  playlist_button->setGeometry(LEFT_MARGIN, TOP_MARGIN + 32, 
                               playlist_button->sizeHint().width(), 
                               playlist_button->sizeHint().height());

  previous_button = new TPushButton(QPixmap(":face_player/resource/previous.png"));
  previous_button->setParent(this);
  QObject::connect(previous_button, SIGNAL(clicked()), this, SIGNAL(previous_signal()));
  previous_button->setGeometry(41, TOP_MARGIN + 32, previous_button->sizeHint().width(), 
                               previous_button->sizeHint().height());

  play_button = new TPushButton(QPixmap(":face_player/resource/play.png"));
  play_button->setParent(this);
  QObject::connect(play_button, SIGNAL(clicked()), this, SLOT(play_button_click_handler()));
  play_button->setGeometry(74, TOP_MARGIN + 32, play_button->sizeHint().width(), 
                           play_button->sizeHint().height());

  next_button = new TPushButton(QPixmap(":face_player/resource/next.png"));
  next_button->setParent(this);
  QObject::connect(next_button, SIGNAL(clicked()), this, SIGNAL(next_signal()));
  next_button->setGeometry(107, TOP_MARGIN + 32, next_button->sizeHint().width(), 
                           next_button->sizeHint().height());

  volume_button = new TPushButton(QPixmap(":face_player/resource/volume_high.png"));
  volume_button->setParent(this);
  volume_button->setGeometry(157, TOP_MARGIN + 32, volume_button->sizeHint().width(), 
                             volume_button->sizeHint().height());

  volume_slider = new QSlider(Qt::Horizontal);
  volume_slider->setParent(this);
  volume_slider->setMinimum(0);
  volume_slider->setMaximum(100);
  volume_slider->setValue(25);
  volume_slider->setStyleSheet(VOLUME_SLIDER_STYLE);
  QObject::connect(volume_slider, SIGNAL(valueChanged(int)), this, SIGNAL(volume_signal(int)));
  volume_slider->setGeometry(189, TOP_MARGIN + 32 + 32 / 2 - 5, 93, 10);

  repeat_button = new TCheckButton(QPixmap(":face_player/resource/repeat.png"));
  repeat_button->setParent(this);
  QObject::connect(repeat_button, SIGNAL(clicked()), this, SLOT(repeat_button_click_handler()));
  repeat_button->setGeometry(297, TOP_MARGIN + 32, repeat_button->sizeHint().width(), 
                             repeat_button->sizeHint().height());

  shuffle_button = new TCheckButton(QPixmap(":face_player/resource/shuffle.png"));
  shuffle_button->setParent(this);
  QObject::connect(shuffle_button, SIGNAL(clicked()), this, SLOT(shuffle_button_click_handler()));
  shuffle_button->setGeometry(330, TOP_MARGIN + 32, shuffle_button->sizeHint().width(), 
                              shuffle_button->sizeHint().height());

  TButtonGroup* button_group = new TButtonGroup();
  button_group->add_button(repeat_button);
  button_group->add_button(shuffle_button);

  content_widget = new QWidget();
  content_widget->setParent(this);
  content_widget->setStyleSheet(CONTENT_WIDGET_STYLE);
  content_widget->setGeometry(LEFT_MARGIN, TOP_MARGIN + 66, 381, 47);

  song_label = new QLabel("");
  song_label->setParent(content_widget);
  song_label->setStyleSheet(SONG_LABEL_STYLE);
  song_label->setGeometry(13, 5, 356, song_label->sizeHint().height());

  current_label = new QLabel("00:00");
  current_label->setParent(content_widget);
  current_label->setStyleSheet(CURRENT_LABEL_STYLE);
  current_label->setGeometry(4, 23, current_label->sizeHint().width(),
                             current_label->sizeHint().height());

  position_slider = new TSlider(Qt::Horizontal);
  position_slider->setParent(content_widget);
  position_slider->setMinimum(0);
  position_slider->setMaximum(100);
  position_slider->setValue(0);
  position_slider->setStyleSheet(POSITION_SLIDER_STYLE);
  QObject::connect(position_slider, SIGNAL(valueChanged(int)),
		   this, SLOT(position_slider_value_handler(int)));
  position_slider->setGeometry(69, 29, 223, 10);

  duration_label = new QLabel("00:00");
  duration_label->setParent(content_widget);
  duration_label->setStyleSheet(DURATION_LABEL_STYLE);
  duration_label->setGeometry(295, 23, duration_label->sizeHint().width(),
                              duration_label->sizeHint().height());

  favorite_button = new TCheckButton(QPixmap(":face_player/resource/favorite.png"));
  favorite_button->setParent(content_widget);
  QObject::connect(favorite_button, SIGNAL(clicked()), this, SIGNAL(favorite_signal()));
  favorite_button->setGeometry(352, 26, favorite_button->sizeHint().width(), 
                               favorite_button->sizeHint().height());
}

Player* Player::play_slot(const QString& entry) {
  Q_ASSERT(!entry.isEmpty());
  emit open_signal(QUrl::fromLocalFile(entry), false);
  if (is_play)
    emit play_signal();
  return this;
}

Player* Player::title_slot(const QString& value) {
  song_label->setText(value);
  return this;
}

Player* Player::tick_slot(int value) {
  current_label->setText(QString("%1:%2")
			 .arg(value / 60, 2, 10, QChar('0'))
			 .arg(value % 60, 2, 10, QChar('0')));
  if (!position_slider->is_hover())
    position_slider->setValue(value);
  return this;
}

Player* Player::duration_slot(int value) {
  position_slider->setMaximum(value);
  duration_label->setText(QString("%1:%2")
			  .arg(value / 60, 2, 10, QChar('0'))
			  .arg(value % 60, 2, 10, QChar('0')));
  return this;
}

Player* Player::favorite_slot(bool value) {
  favorite_button->setChecked(value);
  return this;
}

Player* Player::open_button_click_handler() {
  QString local_file = QFileDialog::getOpenFileName(this);
  if (!local_file.isEmpty()) {
    emit open_signal(QUrl::fromLocalFile(local_file), true);
    if (is_play)
      emit play_signal();
  }
  return this;
}

Player* Player::talk_button_toggle_handler(bool value) {
  emit talk_signal(value, frameGeometry().x() + frameGeometry().width() + 2, frameGeometry().y());
  return this;
}

Player* Player::playlist_button_toggle_handler(bool value) {
  emit playlist_signal(value, frameGeometry().x(), frameGeometry().y() + frameGeometry().height() + 2);
  return this;
}

Player* Player::play_button_click_handler() {
  if (is_play) {
    play_button->set_look(QPixmap(":face_player/resource/play.png"));
    emit pause_signal();
  } else {
    play_button->set_look(QPixmap(":face_player/resource/pause.png"));
    emit play_signal();
  }
  is_play = !is_play;
  return this;
}

Player* Player::repeat_button_click_handler() {
  if (what_next == REPEAT) {
    what_next = NORMAL;
    emit normal_signal();
  } else {
    what_next = REPEAT;
    emit repeat_signal();
  }
  return this;
}

Player* Player::shuffle_button_click_handler() {
  if (what_next == SHUFFLE) {
    what_next = NORMAL;
    emit normal_signal();
  } else {
    what_next = SHUFFLE;
    emit shuffle_signal();
  }
  return this;
}

Player* Player::position_slider_value_handler(int value) {
  if (position_slider->is_hover())
    emit position_signal(value);
  return this;
}
