#ifndef __FACE_PLAYER_H
#define __FACE_PLAYER_H

#include <QLabel>
#include <QLineEdit>
#include <QSlider>

#include "../face_player.hpp"

namespace face {
  class Player : public TWidget { Q_OBJECT
  public:
    Player(int argc, char** argv);
  public slots:
    Player* play_slot(const QString& entry);
  private slots:
    Player* open_button_click_handler();
    Player* play_button_click_handler();
  private:
    TPushButton* open_button;
    TPushButton* thumb_up_button;
    QLabel* thumb_up_label;
    TPushButton* thumb_down_button;
    QLabel* thumb_down_label;
    TPushButton* talk_button;

    QWidget* search_widget;
    QLineEdit* search_line_edit;
    TPushButton* search_button;

    TPushButton* minimize_button;

    TPushButton* playlist_button;
    TPushButton* previous_button;
    TPushButton* play_button;
    TPushButton* next_button;
    TPushButton* volume_button;
    QSlider* volume_slider;
    TPushButton* repeat_button;
    TPushButton* shuffle_button;

    QWidget* content_widget;
    QLabel* song_label;
    QLabel* current_label;
    QSlider* position_slider;
    QLabel* duration_label;
    TPushButton* favorite_button;

    bool is_play = false;
  signals:
    void open_signal(const QUrl& file_path, bool by_user);
    void previous_signal();
    void play_signal();
    void pause_signal();
    void next_signal();
    void volume_signal(int value);
  };
}

#endif
