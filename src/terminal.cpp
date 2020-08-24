#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

int term_l() {
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_row;
}

int term_c() {
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}

struct termios newt, oldt;
void init_terminal_nocanon() {
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void init_terminal_canon() {
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
