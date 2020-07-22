#include "pch.h"
#include "Game.h"

int main() {
	srand(time(NULL));

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((3 << 4) | 15));

	while (true) {
		play();
		cout << "\tONE MORE?\n\tTAP ANY KEY TO PLAY AGAIN.\t\n" << endl;
		_getch();
	}
}