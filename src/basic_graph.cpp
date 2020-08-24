#include <iostream>

using namespace std;

void init_titlebar(string name, bool saved) {
	if (saved) cout<<"\033[0;40;97m"; else cout<<"\033[3;40;34m";//cout<<"\033[3;40;91m";
	int len = ((term_c() / 2) - (name.size() / 2));
	for (int i = 0; i<len; i++) cout<<' ';
	cout<<name;
	for (int i = 0; i<int(term_c() - (len + name.size())); i++) cout<<' ';
	cout<<"\033[0m\n";
}

void clrscr() {
	cout<<"\033c";
}
