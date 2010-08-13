/*  matrix.h
*  author: Floff, trapd00r
*
*  included in matrix.c
*/

#ifndef __MATRIX_H__
#define __MATRIX_H__

/* info constants */
const char APPLICATION_NAME[] = "matrix";
const char APPLICATION_VERSION[] = "0.3.2";
const char APPLICATION_CREDITS[] = "Floff & trapd00r";

/*
*  0.1.x  - first version(beta)                                     - Floff, trapd00r
*  0.2.0  - second version                                          - Floff
*  0.2.1  - getopt() argument parsing                               - Floff, trapd00r
*  0.2.2  - added more argument options(-r, -R)                     - Floff
*  0.3.2  - better code structure(added matrix.h) and optimization  - Floff
*/


/* bash commands
*/
const char CMD_BASH_CLEAR_SCREEN[]  = "\033[2;J";
const char CMD_BASH_HIDE_CURSOR[]   = "\033[?25l";
const char CMD_BASH_SHOW_CURSOR[]   = "\033[?25h\033[0m\n";


/* arguments
*/
const char ARGFLAG_ALL[]            = "hc:C:r:R:";

const char ARGFLAG_HELP             = 'h';
const char ARGFLAG_CHARSET          = 'c';
const char ARGFLAG_COLORNAME        = 'C';
const char ARGFLAG_ROWSET_MAX       = 'r';
const char ARGFLAG_CHAR_GAP_CHANCE  = 'R';


/* dimensions
*/
#define TERM_COLUMNS        178  /*80*/
#define TERM_ROWS           54   /*24*/

#define MATRICES_MAX        10
#define COLUMNS_PER_CHAR    (TERM_COLUMNS / MATRICES_MAX)

#define DEFAULT_ROWSET_MAX  250
#define DEFAULT_GAP_CHANCE  0.5
#define ROW_DELAY           75000  /* usleep() sleeps in microseconds(us)*/


/* characters and colors
*/
#define DEFAULT_CHARSET                            "0123456789abcdefABCDEF"

#define COLOR_SIZE_RED                             6
const int COLOR_ARRAY_RED[COLOR_SIZE_RED]        = {52, 88, 124, 160, 196, 202};
const char COLORNAME_RED[]                       = "red";

#define COLOR_SIZE_YELLOW                          7
const int COLOR_ARRAY_YELLOW[COLOR_SIZE_YELLOW]  = {142, 148, 184, 190, 191, 220, 226};
const char COLORNAME_YELLOW[]                    = "yellow";

#define COLOR_SIZE_GREEN                           10
const int COLOR_ARRAY_GREEN[COLOR_SIZE_GREEN]    = {22, 28, 34, 40, 41, 42, 34, 35, 46, 47};
const char COLORNAME_GREEN[]                     = "green";

#define COLOR_SIZE_BLUE                            10
const int COLOR_ARRAY_BLUE[COLOR_SIZE_BLUE]      = {17, 18, 19, 20, 21, 25, 26, 27, 31, 32};
const char COLORNAME_BLUE[]                      = "blue";


/* global variables
*/
int matrix[MATRICES_MAX] = {0};

const char *charset = DEFAULT_CHARSET;
int charset_len = 0;

const int *colorset = COLOR_ARRAY_GREEN;
int colorset_len = COLOR_SIZE_GREEN;

int rowset_max = DEFAULT_ROWSET_MAX;
double char_gap_chance = DEFAULT_GAP_CHANCE;


/* functions
*/
void help(void)
{
  printf("%s v%s by %s", APPLICATION_NAME, APPLICATION_VERSION, APPLICATION_CREDITS);

  printf("\nusage: %s [FLAGS] ...", APPLICATION_NAME);
  printf("\n\t-%c <STRING>\tspecifies a custom charset to use", ARGFLAG_CHARSET);
  printf("\n\t-%c <STRING>\tspecifies the color to use; %s, %s, %s, %s", ARGFLAG_COLORNAME, COLORNAME_RED, COLORNAME_YELLOW, COLORNAME_GREEN, COLORNAME_BLUE);
  printf("\n\t-%c <INTEGER>\tspecifies maximum rows to print before clearing screen and starts a new matrix", ARGFLAG_ROWSET_MAX);
  printf("\n\t-%c <FLOAT>\tspecifies the chance for gaps in the matrix; 0.0 < x < 1.0", ARGFLAG_CHAR_GAP_CHANCE);
}

void parse_args(char *argv[], int argc)
{
  int opt;
  while((opt = getopt(argc, argv, ARGFLAG_ALL)) != -1) {
    switch(opt) {
      case 'h':
	help();
	exit(EXIT_SUCCESS);

      case 'c':
        charset = optarg;

        break;

      case 'C':
        if(strcmp(optarg, COLORNAME_RED) == 0) {
          colorset = COLOR_ARRAY_RED;
          colorset_len = COLOR_SIZE_RED;
        }
        else if(strcmp(optarg, COLORNAME_YELLOW) == 0) {
          colorset = COLOR_ARRAY_YELLOW;
          colorset_len = COLOR_SIZE_YELLOW;
        }
        else if(strcmp(optarg, COLORNAME_GREEN) == 0) {
          colorset = COLOR_ARRAY_GREEN;
          colorset_len = COLOR_SIZE_GREEN;

        }
        else if(strcmp(optarg, COLORNAME_BLUE) == 0) {
          colorset = COLOR_ARRAY_BLUE;
          colorset_len = COLOR_SIZE_BLUE;
        }
        else {
          printf("error: invalid color \'%s\'", optarg);
          exit(EXIT_FAILURE);
        }

        break;

      case 'r':
        rowset_max = atoi(optarg);
        if(rowset_max == 0) {
          printf("error: invalid integer value \'%s\'", optarg);
          exit(EXIT_FAILURE);
        }

	break;

      case 'R':
	
        char_gap_chance = atof(optarg);
        if(char_gap_chance == 0.0) {
          printf("error: invalid float value \'%s\'", optarg);
          exit(EXIT_FAILURE);
        }

        break;

      default:
        help();
        exit(EXIT_SUCCESS);
    }
  }

  charset_len = strlen(charset);
}

void clear_screen(void)
{
  printf(CMD_BASH_CLEAR_SCREEN);
}

void hide_cursor(void)
{
  printf(CMD_BASH_HIDE_CURSOR);
}

void show_cursor(void)
{
  printf(CMD_BASH_SHOW_CURSOR);
}

void print_nchars(const char ch, const int cnt)
{
  int i;
  for(i=0; i<cnt; i++) {
    putchar(ch);
  }
}

void print_row(const char ch, const int color)
{
  printf("\033[38;5;%dm%c", color, ch);
}

void print_array(const int array[], const int array_size)
{
  int i;
  for(i=0; i<array_size; i++) {
    printf("array[%d] = %d\n", i, array[i]);
  }
}

void fill_array(int array[], const int matrice_cnt)
{
  int i;
  for(i=0; i<matrice_cnt; i++) {
    array[i] = (rand() % COLUMNS_PER_CHAR) + (i * COLUMNS_PER_CHAR);
  }
}


void bubble_sort(int array[], const int size)
{
  int i, j, swap;
  for(i=0; i<size; i++) {
    for(j=i+1; j<size; j++) {
      if(array[i] > array[j]) {
        swap = array[j];
        array[j] = array[i];
        array[i] = swap;
      }
    }
  }
}

double percent_to_chance(const double percent)
{
  return pow((percent), -1.0) * 100.0;
}

#endif /*__MATRIX_H__*/

