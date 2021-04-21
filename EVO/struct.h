#ifndef STRUCTH_H
#define STRUCTH_H

struct Vec2
{
	int x, y;
	Vec2(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Vec2() {
		x = 0; y = 0;
	}
};

enum class Action { go_forward, go_right, go_back, go_left, eat_forward, eat_rigth, eat_back, eat_left, see_forward, see_right, see_back, see_left, stay, death};
enum class Obj { null, robot, wall, food, toxic};

#endif //STRUCTH_H
