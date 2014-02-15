#include "face_player.hpp"

using namespace face;

const int ICON_HEIGHT = 32;
const int LEFT_MARGIN = 5;
const int TOP_MARGIN = 3;

const char* UP_DOWN_LABEL_STYLE = 
    "QLabel { "
    "color : #000000;"
    "font: 15px mono;"
    "}";

const char* SONG_LABEL_STYLE = 
    "QLabel { "
    "color : #ffffff;"
    "font: 18px mono;"
    "}";

const char* SEARCH_LINE_STYLE =
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


Player::Player(int, char**) : TMoveableWidget(QPixmap(":face/resource/player_background.png")) {
    open_button = new TPushButton(QPixmap(":face/resource/open.png"));
    open_button->setParent(this);
    open_button->setGeometry(LEFT_MARGIN, TOP_MARGIN, open_button->sizeHint().width(), 
                             open_button->sizeHint().height());

    thumb_up_button = new TPushButton(QPixmap(":face/resource/thumb_up.png"));
    thumb_up_button->setParent(this);
    thumb_up_button->setGeometry(74, TOP_MARGIN, thumb_up_button->sizeHint().width(), 
                                 thumb_up_button->sizeHint().height());

    thumb_up_label = new QLabel("0");
    thumb_up_label->setParent(thumb_up_button);
    thumb_up_label->setStyleSheet(UP_DOWN_LABEL_STYLE);
    thumb_up_label->setGeometry(15, 13, thumb_up_label->sizeHint().width(),
                                thumb_up_label->sizeHint().height());

    thumb_down_button = new TPushButton(QPixmap(":face/resource/thumb_down.png"));
    thumb_down_button->setParent(this);
    thumb_down_button->setGeometry(107, TOP_MARGIN, thumb_down_button->sizeHint().width(), 
                                   thumb_down_button->sizeHint().height());

    thumb_down_label = new QLabel("0");
    thumb_down_label->setParent(thumb_down_button);
    thumb_down_label->setStyleSheet(UP_DOWN_LABEL_STYLE);
    thumb_down_label->setGeometry(15, 2, thumb_down_label->sizeHint().width(),
                                  thumb_down_label->sizeHint().height());

    talk_button = new TPushButton(QPixmap(":face/resource/talk.png"));
    talk_button->setParent(this);
    talk_button->setGeometry(157, TOP_MARGIN, talk_button->sizeHint().width(), 
                             talk_button->sizeHint().height());

    search_widget = new TWidget(QPixmap(":face/resource/search_background.png"));
    search_widget->setParent(this);
    search_widget->setGeometry(189, TOP_MARGIN, search_widget->sizeHint().width(), 
                               search_widget->sizeHint().height());

    search_line_edit = new QLineEdit();
    search_line_edit->setParent(search_widget);
    search_line_edit->setAutoFillBackground(true);
    search_line_edit->setStyleSheet(SEARCH_LINE_STYLE);
    search_line_edit->setGeometry(4, 4, 135, 21);

    search_button = new TPushButton(QPixmap(":face/resource/search.png"));
    search_button->setParent(search_widget);
    search_button->setGeometry(140, 4, search_button->sizeHint().width(), 
                               search_button->sizeHint().height());

    minimize_button = new TPushButton(QPixmap(":face/resource/minimize.png"));
    minimize_button->setParent(this);
    minimize_button->setGeometry(355, TOP_MARGIN, minimize_button->sizeHint().width(), 
                                 minimize_button->sizeHint().height());

    close_button = new TPushButton(QPixmap(":face/resource/close.png"));
    close_button->setParent(this);
    close_button->setGeometry(387, TOP_MARGIN, close_button->sizeHint().width(), 
                              close_button->sizeHint().height());

    playlist_button = new TPushButton(QPixmap(":face/resource/playlist.png"));
    playlist_button->setParent(this);
    playlist_button->setGeometry(LEFT_MARGIN, TOP_MARGIN + ICON_HEIGHT, 
                                 playlist_button->sizeHint().width(), 
                                 playlist_button->sizeHint().height());

    previous_button = new TPushButton(QPixmap(":face/resource/previous.png"));
    previous_button->setParent(this);
    previous_button->setGeometry(41, TOP_MARGIN + ICON_HEIGHT, previous_button->sizeHint().width(), 
                                 previous_button->sizeHint().height());

    play_button = new TPushButton(QPixmap(":face/resource/play.png"));
    play_button->setParent(this);
    play_button->setGeometry(74, TOP_MARGIN + ICON_HEIGHT, play_button->sizeHint().width(), 
                             play_button->sizeHint().height());

    next_button = new TPushButton(QPixmap(":face/resource/next.png"));
    next_button->setParent(this);
    next_button->setGeometry(107, TOP_MARGIN + ICON_HEIGHT, next_button->sizeHint().width(), 
                             next_button->sizeHint().height());

    volume_button = new TPushButton(QPixmap(":face/resource/volume_high.png"));
    volume_button->setParent(this);
    volume_button->setGeometry(157, TOP_MARGIN + ICON_HEIGHT, volume_button->sizeHint().width(), 
                               volume_button->sizeHint().height());

    volume_slider = new QSlider(Qt::Horizontal);
    volume_slider->setParent(this);
    volume_slider->setMinimum(0);
    volume_slider->setMaximum(100);
    volume_slider->setValue(25);
    volume_slider->setStyleSheet(VOLUME_SLIDER_STYLE);
    volume_slider->setGeometry(189, TOP_MARGIN + ICON_HEIGHT + ICON_HEIGHT / 2 - 5, 93, 10);

    repeat_button = new TPushButton(QPixmap(":face/resource/repeat.png"));
    repeat_button->setParent(this);
    repeat_button->setGeometry(297, TOP_MARGIN + ICON_HEIGHT, repeat_button->sizeHint().width(), 
                               repeat_button->sizeHint().height());

    shuffle_button = new TPushButton(QPixmap(":face/resource/shuffle.png"));
    shuffle_button->setParent(this);
    shuffle_button->setGeometry(330, TOP_MARGIN + ICON_HEIGHT, shuffle_button->sizeHint().width(), 
                                shuffle_button->sizeHint().height());

    content_widget = new TWidget(QPixmap(":face/resource/player_content.png"));
    content_widget->setParent(this);
    content_widget->setGeometry(LEFT_MARGIN, TOP_MARGIN + 2 * ICON_HEIGHT + 2, 
                                content_widget->sizeHint().width(), 
                                content_widget->sizeHint().height());

    song_label = new QLabel("");
    song_label->setParent(content_widget);
    song_label->setStyleSheet(SONG_LABEL_STYLE);
    song_label->setGeometry(13, 5, 356, song_label->sizeHint().height());

    current_label = new QLabel("00:00");
    current_label->setParent(content_widget);
    current_label->setStyleSheet(CURRENT_LABEL_STYLE);
    current_label->setGeometry(4, 23, current_label->sizeHint().width(),
                               current_label->sizeHint().height());

    position_slider = new QSlider(Qt::Horizontal);
    position_slider->setParent(content_widget);
    position_slider->setMinimum(0);
    position_slider->setMaximum(100);
    position_slider->setValue(0);
    position_slider->setStyleSheet(POSITION_SLIDER_STYLE);
    position_slider->setGeometry(69, 34 -  5, 223, 10);

    duration_label = new QLabel("00:00");
    duration_label->setParent(content_widget);
    duration_label->setStyleSheet(DURATION_LABEL_STYLE);
    duration_label->setGeometry(295, 23, duration_label->sizeHint().width(),
                                duration_label->sizeHint().height());

    favorite_button = new TPushButton(QPixmap(":face/resource/favorite.png"));
    favorite_button->setParent(content_widget);
    favorite_button->setGeometry(352, 26, favorite_button->sizeHint().width(), 
                                 favorite_button->sizeHint().height());

}