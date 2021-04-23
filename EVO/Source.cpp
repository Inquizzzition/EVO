#include "field.h"
#include <conio.h>

int main() {
	Field f(65, 64, 1000, 300, 500);
	while (true) {
		f.next_day();
		if (_kbhit()) {
			char k = _getch();
			f.chF();
		}
	}
}