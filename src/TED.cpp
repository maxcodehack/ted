#include "terminal.cpp"
#include "keyboard.cpp"
#include "basic_graph.cpp"
#include <fstream>
using namespace std;



bool CREATE(string filename) {
	ofstream file(filename);
	if (!file.is_open()) return false;
	file.close();
	return true;
}


void SAVE(string txt, string filename, bool *saved) {
	ofstream file(filename);
	file << txt;
	file.close();
	*saved = true;
}

int main() {
	
	string txt = ""; //input text
	string filename = "noname.txt";
	bool saved = true;
	char c;

	system("wmctrl -r :ACTIVE: -N \"TED\"");
	
	
	
	if (!CREATE(filename)) {cout<<"Unable to create file!"; getchar();} else {
	init_terminal_nocanon();
	while(1) {
		
		clrscr();
		
		init_titlebar(filename, saved);
		
		cout<<txt;
		
		if (kbhit()) {
		c = getchar();
		if (c == 127) {if (txt.size() > 0) txt.erase(txt.size() - 1, 1);saved = false;} else //backspace
		if (c == 27) { //if echo - esc
			if (kbhit()) { 
				c = getchar();	
				if (c == '[') {
					c = getchar();
					if (not_arrow(c)) {txt += c; saved = false;} //arrow
					switch(c) {
						case '3': {c = getchar(); if (c == '~') {txt.erase(txt.size() - 1, 1); SAVE(txt, filename, &saved);}} //del 
							break;
						case '2': {c = getchar(); if (c == '~') {txt.erase(txt.size() - 1, 1); txt+="INSERT";}} //insert 
							break;
						case '5': {c = getchar(); if (c == '~') {txt.erase(txt.size() - 1, 1); txt+="PGUP";}} //pgup 
							break;
						case '6': {c = getchar(); if (c == '~') {txt.erase(txt.size() - 1, 1); txt+="PGDOWN";}} //pgdown 
							break;
					}
				}
			} else break;
		}
			else {txt += c; saved = false;}
		} else system("sleep 0.1");
	}
	}
	
	init_terminal_canon();
	clrscr();
	system("wmctrl -r :ACTIVE: -N \"TERMINAL\"");

	return 0;
}
