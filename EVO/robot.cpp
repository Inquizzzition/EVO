#include "robot.h";

Robot::Robot(Vec2 coord, int hp) :
	coord(coord),
	hp(hp),
	iter(0),
	programm(32),
	dir(rand()%4),
	live(true)
{}

Robot::Robot() :
	coord(Vec2(0,0)),
	hp(0),
	iter(0),
	programm(32),
	dir(rand() % 4),
	live(false)
{}

Action Robot::update() {
	int act = programm[iter];
	iter++;
	if (hp <= 0)
		return Action::death;
	hp--;
	if (iter >= programm.size())
		iter -= programm.size();
	switch (act) {
	case 0:
		return Action(dir);
	case 1:
		return Action(dir + 4);
	case 2:
		return Action(dir + 8);
	case 3:
		dir++;
		if (dir >= 4)
			dir = 0;
		return Action::stay;
	case 4:
		dir--;
		if (dir < 0)
			dir = 3;
		return Action::stay;
	case 5:
		iter++;
		if (iter >= programm.size())
			iter -= programm.size();
		return Action::stay;
	case 6:
		iter += 2;
		if (iter >= programm.size())
			iter -= programm.size();
		return Action::stay;
	case 7:
		iter += 3;
		if (iter >= programm.size())
			iter -= programm.size();
		return Action::stay;
	}
	return Action::stay;
}

std::vector<int> Robot::get_programm() {
	return programm;
}

void Robot::set_programm(std::vector<int> p) {
	programm = p;
}

void Robot::set_mutate_programm(std::vector<int> p, int k) {
	for (int i = 0; i < k; ++i) {
		int t = rand() % programm.size();
		p[t] = rand() % 8;

	}
	programm = p;
}

void Robot::set_rand_programm() {
	for (int i = 0; i < programm.size(); ++i) {
		programm[i] = rand() % 8;
	}
}

void Robot::addhp(int h) {
	hp += h;
	//if (hp > 120)
	//	hp = 120;
}

void Robot::setCoord(Vec2 v) {
	coord = v;
}

int Robot::getx() {
	return coord.x;
}

int Robot::gety() {
	return coord.y;
}

void Robot::see(Obj b) {
	switch (b) {
	case Obj::toxic:
	case Obj::food:
		iter += 1;
		if (iter >= programm.size())
			iter -= programm.size();

	case Obj::wall:
		iter += 2;
		if (iter >= programm.size())
			iter -= programm.size();

	case Obj::robot:
		iter += 3;
		if (iter >= programm.size())
			iter -= programm.size();
	case Obj::null:
		iter += 4;
		if (iter >= programm.size())
			iter -= programm.size();
	}
}


