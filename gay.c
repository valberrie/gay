#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <unistd.h>

#include "colors.h"

struct winsize sz;

uint ml;

const char *flags[] = {"pride", "bi", "trans", "lesbian", "nb", "ace", "aro", "pan", "queer", "mlm"};

struct flag { char *fl[10]; };
struct flag pride =   { {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE} };
struct flag bi =      { {FUCHSIA, FUCHSIA, PURPLE, BLUE, BLUE} };
struct flag trans =   { {LBLUE, LPINK, WHITE, LPINK, LBLUE} };
struct flag lesbian = { {RED, ORANGE, LORANGE, WHITE, PINK, MPINK, DPINK} };
struct flag nb =      { {YELLOW, WHITE, PURPLE, BLACK} };
struct flag ace =     { {BLACK, GRAY, WHITE, PURPLE} };
struct flag aro =     { {GREEN, LGREEN, WHITE, GRAY, BLACK} };
struct flag pan =     { {FUCHSIA, YELLOW, LBLUE} };
struct flag queer =   { {PURPLE, WHITE, GREEN} };
struct flag mlm =     { {DCYAN, CYAN, LCYAN, WHITE, LBLUE, CERUL, PURBLUE} };

void draw_line(char *cc) {
  int s = 0; 
  printf("\n");
  while(s <= (sz.ws_col - 1)) {
    printf(cc); printf(" "); s++; } 
}

void draw_flag(struct flag sf) {
  for(int i = 0; i < sizeof(sf.fl) / sizeof(sf.fl[0]); i++) {
    if (sf.fl[i] != NULL) { 
      for(int j = 0; j < ml; j++) {
        draw_line(sf.fl[i]); } } } 
  printf("\n\n");
}

int main(int argc, char *argv[]) {
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &sz);

  if (argv[2] != NULL) {
    int tml = atoi(argv[2]);
    if(tml >= 1 && tml <= 3) { ml = tml; }
    else { ml = 1; }
  } else { ml = 1; }
  
  int fnd;
  if (argv[1] == NULL || strcmp(argv[1], "pride") == 0) { draw_flag(pride); } 
  else {
    for(int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
      if (strcmp(argv[1], flags[i]) == 0) {
        switch(i) {
          case 1:   draw_flag(bi);      break;
          case 2:   draw_flag(trans);   break;
          case 3:   draw_flag(lesbian); break;
          case 4:   draw_flag(nb);      break;
          case 5:   draw_flag(ace);     break;
          case 6:   draw_flag(aro);     break;
          case 7:   draw_flag(pan);     break;
          case 8:   draw_flag(queer);   break;
          case 9:   draw_flag(mlm);     break;
          default:  draw_flag(pride);
        }
        return 0;
        fnd = 1;
      } else { fnd = 0; }
    }
    if (fnd == 0) { draw_flag(pride); }
  } 
  return 0;
}
