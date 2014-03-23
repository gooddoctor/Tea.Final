#ifndef __FACE_PLAYER_H
#define __FACE_PLAYER_H

#include <QLabel>
#include <QLineEdit>
#include <QSlider>

#include "../face_player.hpp"

namespace face {
  class Player : public TWidget { Q_OBJECT
  enum State {NORMAL, REPEAT, SHUFFLE};
  public:
    Player(int argc, char** argv);
  public slots:
    Player* thumb_up_slot(int value);
    Player* thumb_down_slot(int value);
    Player* play_slot(const QString& entry);
    Player* title_slot(const QString& value);
    Player* tick_slot(int value);
    Player* duration_slot(int value);
    Player* favorite_slot(bool value);
  private slots:
    Player* open_button_click_handler();
    Player* talk_button_toggle_handler(bool value);
    Player* playlist_button_toggle_handler(bool value);
    Player* play_button_click_handler();
    Player* repeat_button_click_handler();
    Player* shuffle_button_click_handler();
    Player* position_slider_value_handler(int value);
  private:
    TPushButton* open_button;
    TPushButton* thumb_up_button;
    QLabel* thumb_up_label;
    TPushButton* thumb_down_button;
    QLabel* thumb_down_label;
    TCheckButton* talk_button;

    QWidget* search_widget;
    TLineEdit* search_line_edit;
    TPushButton* search_button;

    TPushButton* minimize_button;

    TCheckButton* playlist_button;
    TPushButton* previous_button;
    TPushButton* play_button;
    TPushButton* next_button;
    TPushButton* volume_button;
    QSlider* volume_slider;
    TCheckButton* repeat_button;
    TCheckButton* shuffle_button;

    QWidget* content_widget;
    QLabel* song_label;
    QLabel* current_label;
    TSlider* position_slider;
    QLabel* duration_label;
    TCheckButton* favorite_button;

    bool is_play = false;
    State what_next = NORMAL;
  signals:
    void open_signal(const QUrl& file_path, bool by_user);
    void thumb_up_signal();
    void thumb_down_signal();
    void talk_signal(bool value, int x, int y);
    void search_signal(const QString& value);
    void playlist_signal(bool value, int x, int y);
    void previous_signal();
    void play_signal();
    void pause_signal();
    void next_signal();
    void volume_signal(int value);
    void normal_signal();
    void repeat_signal();
    void shuffle_signal();
    void position_signal(int value);
    void favorite_signal();
    void complete_signal(const QString& value, QStringList& values);
  };
}

#endif
