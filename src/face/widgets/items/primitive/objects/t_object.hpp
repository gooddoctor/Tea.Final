#ifndef __T_OBJECT_H
#define __T_OBJECT_H

template <typename Parent, typename Slot, typename Signal>
class TObject {
  public:
    TObject(Parent* owner) {
      this->slot_object = new Slot(owner);
      this->signal_object = new Signal(owner);
    }
    Slot* slot() {
      return slot_object;
    }
    Signal* signal() {
      return signal_object;
    }
  private:
    Slot* slot_object;
    Signal* signal_object;
};

#endif
