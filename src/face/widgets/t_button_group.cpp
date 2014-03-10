#include "t_button_group.hpp"

TButtonGroup* TButtonGroup::add_button(TPushButton* button) {
  buttons.push_back(button);
  QObject::connect(button, SIGNAL(toggled(bool)), this, SLOT(button_toggled(bool)));
  return this;
}

TButtonGroup* TButtonGroup::button_toggled(bool value) {
  if (value) {
    TPushButton* toggled = static_cast<TPushButton*>(sender());
    for (auto it = buttons.begin(); it != buttons.end(); it++)
      if (toggled != (*it))
	(*it)->setChecked(false);
  }
  return this;
}
