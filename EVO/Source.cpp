#include "field.h";

int main() {
	Field f(64, 64, 1000, 300, 500);
	while (true) {
		f.next_day();
	}
}