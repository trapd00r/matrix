/*  matrix.c
*  author: Floff, trapd00r
*
*  compiler flags: gcc -D_POSIX_C_SOURCE=199309L -ansi -pedantic
*  compiler libs: -lm
*/

/* includes
*/
#include <stdlib.h>    /*atexit(), atoi(), atof()*/
#include <string.h>    /*strlen()*/
#include <stdio.h>     /*printf(), putchar()*/
#include <math.h>      /*pow()*/

#include <unistd.h>    /*usleep(), getopt(), optarg, optind*/

#include "./matrix.h"  /* application custom constants and functions */


/* extern global variables imported from matrix.h
*/
extern int matrix[MATRICES_MAX];

extern const char *charset;
extern int charset_len;

extern const int *colorset;
extern int colorset_len;

extern int rowset_max;
extern double char_gap_chance;
extern int row_delay;

int main(int argc, char *argv[])
{
  int row, column;

  atexit(show_cursor);
  parse_args(argv, argc);

  srand(time(NULL));
  hide_cursor();

  row = 0;
  while(1/*row<TERM_ROWS*/) {
    if(row % rowset_max == 0) {
      /*system(CLEAR_COMMAND);*/
      clear_screen();
      fill_array(matrix, MATRICES_MAX);
      bubble_sort(matrix, MATRICES_MAX);
    }

    for(column=0; column<MATRICES_MAX; column++) {
      print_nchars(' ', matrix[column] - (column * (COLUMNS_PER_CHAR - 1)));

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

