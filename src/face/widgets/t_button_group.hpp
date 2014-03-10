#ifndef __T_BUTTON_GROUP_H
#define __T_BUTTON_GROUP_H

#include <vector>

#include "primitive/t_push_button.hpp"

class TButtonGroup : public QObject { Q_OBJECT
  typedef std::vector<TPushButton*> Buttons;
public:
  TButtonGroup* add_button(TPushButton* button);
private slots:
  TButtonGroup* button_toggled(bool value);
private:
  Buttons buttons;
};

#endif
