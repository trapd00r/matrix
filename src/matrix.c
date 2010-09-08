/*  matrix.c
*  author: Floff, trapd00r
*
*  compiler flags: gcc -D_POSIX_C_SOURCE=199309L -ansi -pedantic
*  compiler libs: -lm
*/

/* includes
*/
#include <stdlib.h>    /*atexit()*/
#include <stdio.h>     /*putchar()*/
#include <time.h>      /*time()*/
#include <math.h>      /*pow()*/

#include <unistd.h>    /*usleep()*/

#include "./matrix.h"  /* application custom constants and functions */


/* extern global variables imported from matrix.h
*/
extern int *matrix;
extern int matrix_cnt;
extern int columns_per_char;

extern const char *charset;
extern int charset_len;

extern const int *colorset;
extern int colorset_len;

extern int rowset_max;
extern double char_gap_chance;
extern int row_delay;

void init(void)
{
  srand((unsigned int)time(NULL));

  hide_cursor();
  atexit(cleanup);
  atexit(show_cursor);
}

int main(int argc, char *argv[])
{
  int row, column;
  parse_args(argv, argc);
  init();

  row = 0;
  while(1) {
    if(row % rowset_max == 0) {
      clear_screen();
      fill_array(matrix, matrix_cnt, columns_per_char);
      bubble_sort(matrix, matrix_cnt);
    }

    for(column=0; column<matrix_cnt; column++) {
      print_nchars(' ', *(matrix + column) - (column * (columns_per_char - 1)));

      if(rand() % (int)percent_to_chance(char_gap_chance) <= 100.0) {
        print_row(charset[rand() % charset_len], colorset[rand() % colorset_len]);
      }
      else {
        putchar(' ');
      }
    }

    putchar('\n');
    usleep(row_delay);
    row++;
  }

  exit(EXIT_SUCCESS);
}

