/*  matrix.c
*  author: Floff, trapd00r
*
*  compiler flags: gcc -D_POSIX_C_SOURCE=199309L -ansi -pedantic
*  compiler libs: -lm
*/


#include <stdlib.h> /*atexit()*/
#include <string.h> /*strlen()*/
#include <stdio.h> /*printf(), putchar()*/
#include <math.h> /*pow()*/

#include <unistd.h> /*usleep()*/
#include <getopt.h> /*getopt(), optarg, optind*/


/* dimensions */
#define TERM_COLUMNS 178 /*80*/
#define TERM_ROWS 54 /*24*/

#define MATRICES_MAX 10

#define COLUMNS_PER_CHAR (TERM_COLUMNS / MATRICES_MAX)

#define CHAR_PAUSE_CHANCE 0.684 /* = (19/20) * (9/10) * (4/5)*/

#define ROW_DELAY 75000 /* usleep() sleeps in microseconds(us)*/

#define CLEAR_COUNT 250
#define CLEAR_COMMAND "clear"

int char_pos[MATRICES_MAX] = {0};

/* characters and colors */
#define DEFAULT_CHARSET "0123456789abcdefABCDEF"

#define COLOR_RED_SIZE 6
const int COLORS_RED[COLOR_RED_SIZE] = {52, 88, 124, 160, 196, 202};

#define COLOR_YELLOW_SIZE 7
const int COLORS_YELLOW[COLOR_YELLOW_SIZE] = {142, 148, 184, 190, 191, 220, 226};

#define COLOR_GREEN_SIZE 10
const int COLORS_GREEN[COLOR_GREEN_SIZE] = {22, 28, 34, 40, 41, 42, 34, 35, 46, 47};

#define COLOR_BLUE_SIZE 10
const int COLORS_BLUE[COLOR_BLUE_SIZE] = {17, 18, 19, 20, 21, 25, 26, 27, 31, 32};


void clear_screen(void)
{
  printf("\033[2;J");
}

void hide_cursor(void)
{
  printf("\033[?25l");
}

void show_cursor(void)
{
  printf("\033[?25h\033[0m\n");
}

void bubble_sort(int array[], int size)
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

void fill_array(void)
{
  int i, temp_rand;
  for(i=0; i<MATRICES_MAX; i++) {
    temp_rand = rand() % COLUMNS_PER_CHAR;
    char_pos[i] = temp_rand + (i * COLUMNS_PER_CHAR);
  }
}

void print_array(void)
{
  int i;
  for(i=0; i<MATRICES_MAX; i++) {
    printf("char_pos[%d] = %d\n", i, char_pos[i]);
  }
}

void print_nchars(char ch, int cnt)
{
  int i;
  for(i=0; i<cnt; i++) {
    putchar(ch);
  }
}

void print_row(char ch, int color)
{
  printf("\033[38;5;%dm%c", color, ch);
}

double percent_to_chance(double percent)
{
  return pow((percent), -1.0) * 100.0;
}

const char ARGFLAG_HELP[] = "-h";
const char ARGFLAG_LONG_HELP[] = "--help";
const char ARGFLAG_CHARSET[] = "-c";
const char ARGFLAG_COLORNAME[] = "-C";

const char COLORNAME_RED[] = "red";
const char COLORNAME_YELLOW[] = "yellow";
const char COLORNAME_GREEN[] = "green";
const char COLORNAME_BLUE[] = "blue";

const char *charset = NULL;
int charset_len = 0;

const int *colorset = NULL;
int colorset_len = 0;

const char APPLICATION_NAME[] = "matrix";
const char APPLICATION_VERSION[] = "1.0";

void help(void)
{
  printf("%s v%s", APPLICATION_NAME, APPLICATION_VERSION);

  printf("\nusage: %s [FLAGS] ...", APPLICATION_NAME);
  printf("\n\t%s <STRING>\tspecifies a custom charset to use", ARGFLAG_CHARSET);
  printf("\n\t%s <STRING>\tspecifies the color to use; %s, %s, %s, %s", ARGFLAG_COLORNAME, COLORNAME_RED, COLORNAME_YELLOW, COLORNAME_GREEN, COLORNAME_BLUE);
}

/*void parse_args(char *argv[], int argc)
{
  int i;
  for(i=1; i<argc; i++)
  {
    if(strcmp(argv[i], ARGFLAG_HELP) == 0 || strcmp(argv[i], ARGFLAG_LONG_HELP) == 0) {
      help();
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(argv[i], ARGFLAG_CHARSET) == 0) {
      if(i + 1 < argc) {
        charset = argv[i + 1];
      }
      else {
        printf("error: no charset specified");
        exit(EXIT_FAILURE);
      }
    }
    else if(strcmp(argv[i], ARGFLAG_COLORNAME) == 0) {
      if(i + 1 < argc) {
        if(strcmp(argv[i + 1], COLORNAME_RED) == 0) {
          colorset = COLORS_RED;
          colorset_len = COLOR_RED_SIZE;
        }
        else if(strcmp(argv[i + 1], COLORNAME_YELLOW) == 0) {
          colorset = COLORS_YELLOW;
          colorset_len = COLOR_YELLOW_SIZE;
        }
        else if(strcmp(argv[i + 1], COLORNAME_GREEN) == 0) {
          colorset = COLORS_GREEN;
          colorset_len = COLOR_GREEN_SIZE;
        }
        else if(strcmp(argv[i + 1], COLORNAME_BLUE) == 0) {
          colorset = COLORS_BLUE;
          colorset_len = COLOR_BLUE_SIZE;
        }
        else {
          printf("error: invalid colorname");
          exit(EXIT_FAILURE);
        }
      }
      else {
        printf("error: no colorname specified");
        exit(EXIT_FAILURE);
      }
    }
  }

  if(charset == NULL) {
    charset = DEFAULT_CHARSET;
  }

  charset_len = strlen(charset);

  if(colorset == NULL) {
    colorset = COLORS_GREEN;
    colorset_len = COLOR_GREEN_SIZE;
  }
}*/

void parse_args(char *argv[], int argc)
{
  int opt;
  while((opt = getopt(argc, argv, "hc:C:")) != -1) {
    switch(opt) {
      case 'h':
	help();
	exit(EXIT_SUCCESS);

      case 'c':
        charset = optarg;

        break;

      case 'C':
        if(strcmp(optarg, COLORNAME_RED) == 0) {
          colorset = COLORS_RED;
          colorset_len = COLOR_RED_SIZE;
        }
        else if(strcmp(optarg, COLORNAME_YELLOW) == 0) {
          colorset = COLORS_YELLOW;
          colorset_len = COLOR_YELLOW_SIZE;
        }
        else if(strcmp(optarg, COLORNAME_GREEN) == 0) {
          colorset = COLORS_GREEN;
          colorset_len = COLOR_GREEN_SIZE;

        }
        else if(strcmp(optarg, COLORNAME_GREEN) == 0) {
          colorset = COLORS_BLUE;
          colorset_len = COLOR_BLUE_SIZE;
        }
        else {
          printf("error: invalid color \'%s\'", optarg);
          exit(EXIT_FAILURE);
        }

        break;

      default:
        help();
        exit(EXIT_SUCCESS);
    }
  }

  if(charset == NULL) {
    charset = DEFAULT_CHARSET;
  }

  charset_len = strlen(charset);

  if(colorset == NULL) {
    colorset = COLORS_GREEN;
    colorset_len = COLOR_GREEN_SIZE;
  }
}

int main(int argc, char *argv[])
{
  int row, column;

  atexit(show_cursor);
  parse_args(argv, argc);

  srand(time(NULL));
  hide_cursor();

  row = 0;
  while(1/*row<TERM_ROWS*/) {
    if(row % CLEAR_COUNT == 0) {
      /*system(CLEAR_COMMAND);*/
      clear_screen();
      fill_array();
      bubble_sort(char_pos, MATRICES_MAX);
    }

    for(column=0; column<MATRICES_MAX; column++) {
      print_nchars(' ', char_pos[column] - (column * (COLUMNS_PER_CHAR - 1)));

      if(rand() % (int)percent_to_chance(CHAR_PAUSE_CHANCE) <= 100.0) {
        print_row(charset[rand() % charset_len], colorset[rand() % colorset_len]);
      }
      else {
        putchar(' ');
      }
    }

    putchar('\n');
    usleep(ROW_DELAY);
    row++;
  }

  exit(EXIT_SUCCESS);
}

