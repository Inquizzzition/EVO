#include "field.h"
#include <conio.h>

int main() {
	Field f(64, 64, 1000, 300, 500, 10, 40, 100, false);
	while (true) {
		f.next_day();
		if (_kbhit()) {
			char k = _getch();
			f.chF();
		}
	}
}