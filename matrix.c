/*
 * gcc -D_POSIX_C_SOURCE=199309L -ansi -pedantic
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

#define GREEN_MAX 7
#define UNICODE

void hide_cursor(void) {
  printf("\033[?25l");
}

void show_cursor(void) {
 printf("\033[?25h\033[0m\n");
}

void set_matrix_font(void) {
  printf("\033]710;5x7\007\033]711;6x13\007");
}

int main(int argc, wchar_t *argv[]) {
  int actual_color, charslen;
  wchar_t *charptr = NULL;
  int green[GREEN_MAX] = {22, 28, 34, 40, 41, 34, 35};
  wchar_t tokens[] = L"\vabcdefABCDEF0123456789;«¸­³½§Ì¬±ÊÏ¶¿ÃÌÅ¦;(){}[]";
  char *tab_or_not = NULL;

  /* calls show_cursor() at program exit, even if terminated by a SIGINT */
  atexit(show_cursor);
  setlocale(LC_ALL,"");

  charptr = (argc > 1) ? argv[1] : tokens;
  charslen = wcslen(charptr);

  set_matrix_font();
  hide_cursor();
  while(1) {
    actual_color = green[rand() % GREEN_MAX];
    tab_or_not   = (actual_color % 80 == 0) ? "\n" : "\t";

    printf(
        "%s \033[38;5;%dm%c\033[38;5;%dm%c\033[38;5;%dm%c",
        tab_or_not,
        green[rand() % GREEN_MAX], *(charptr + (rand() % charslen)),
        green[rand() % GREEN_MAX], *(charptr + (rand() % charslen)),
        green[rand() % GREEN_MAX], *(charptr + (rand() % charslen))
        );
  }
  return(0);
}

