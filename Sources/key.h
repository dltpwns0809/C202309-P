#include<stdio.h>

void keyboard_control(int* cursur_position_y, int max_scroll_num, int* select) {
  int key;
  key = _getch();
  if (key == 224) {
    key = _getch();
    switch (key) {
      case 72:
        if (*cursur_position_y > 0) {
          *cursur_position_y -= 1;
        }
        break;
      case 80:
        if (*cursur_position_y < max_scroll_num - 1) {
          *cursur_position_y += 1;
        }
    }
  } else if (key == 13) {
    *select = *cursur_position_y;
  }
}
