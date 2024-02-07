#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <unistd.h>

#include "colors.h"

struct winsize sz;

void draw_line(char *cc) {
  int s = 0;
  printf("\n");
  while(s <= (sz.ws_col - 1)) {
    printf(cc);
    printf(" ");
    s++;
  }
}

void draw_flag(int f) {
  switch(f) {
    case 1:
      draw_line(FUCHSIA);
      draw_line(FUCHSIA);
      draw_line(PURPLE);
      draw_line(BLUE);
      draw_line(BLUE);
    break;

    case 2:
      draw_line(LBLUE);
      draw_line(HPINK);
      draw_line(WHITE);
      draw_line(HPINK);
      draw_line(LBLUE);
    break;

    case 3:
      draw_line(RED);
      draw_line(ORANGE);
      draw_line(WHITE);
      draw_line(PINK);
      draw_line(DPINK);
    break;

    default:
      draw_line(RED);
      draw_line(ORANGE);
      draw_line(YELLOW);
      draw_line(GREEN);
      draw_line(BLUE);
      draw_line(PURPLE);
  }
  printf("\n\n");
}

int main(int argc, char *argv[]) {
  const char *flags[4] = {"gay", "bi", "trans", "lesbian"};

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &sz); 
  
  int a;
  if (argv[1] == NULL) {
    a = 0;
  } else {
    for(int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
      if (strcmp(argv[1], flags[i]) == 0) {
        a = i;
      }
    }
  }
  draw_flag(a);
  return 0;
}
