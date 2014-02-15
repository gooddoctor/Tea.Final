#ifndef __T_OBJECT_H
#define __T_OBJECT_H

template <typename T> class TObject {
public:
  TObject() {
    object = new T();
  }

  T* tobject() {
    return object;
  }
private:
  T* object;
};

#endif
