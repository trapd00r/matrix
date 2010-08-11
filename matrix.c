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
	printf("\033[?25h");
}

void set_matrix_font(void) {
	printf("\033]710;5x8\007\033]711;6x13\007");
}

int main(int argc, char *argv[]) {
	int actual_color, charslen;
	char *charptr = NULL;
	int green[GREEN_MAX] = {22, 28, 34, 40, 41, 34, 35};
	char tokens[] = "01";
	char *tab_or_not = NULL;
	wchar_t paraply[] = L"Ϩ";

	atexit(show_cursor); /* calls show_cursor() at program exit, even if terminated with ctrl+c */
	setlocale(LC_ALL,"");

	charptr = (argc > 1) ? argv[1] : tokens;
	charslen = strlen(charptr);

	set_matrix_font();
	hide_cursor();
	while(1) {
		actual_color = green[rand() % GREEN_MAX];
		tab_or_not = (actual_color % 40 == 0) ? "\n\033[3m" : "\t\033[1m";

		printf("%s\033[38;5;%dm%c\033[0m\033[38;5;%dm%ls",
		tab_or_not, actual_color, *(charptr + (rand() % charslen)),actual_color+2,paraply
	);

	usleep(800);
	}
	return(0);
}

