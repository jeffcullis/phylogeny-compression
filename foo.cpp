#include <iostream>

class Foo {
 protected:
  int x, y;

 public:
  Foo (int x_val = 0, int y_val = 0) {
    x = x_val;
    y = y_val;
  }

  int sum() {
    return x + y;
  }
};

