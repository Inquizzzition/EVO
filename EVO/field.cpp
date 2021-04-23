#include "field.h";

Field::Field(int size, int robo_n, int food_n, int wall_n, int toxic_n) :
	field(size, std::vector<Obj>(size, Obj::wall)),
	best_programm(0),
	robots(robo_n),
	day(0),
	era(1),
	size(size),
	robo_n(robo_n), robo(robo_n),
	food_n(food_n), food(0),
	wall_n(wall_n), wall(0),
	toxic_n(toxic_n), toxic(0),
	gui(size, size), f(true)
{
	for (int i = 1; i < size-1; ++i) {
		for (int j = 1; j < size-1; ++j) {
			field[i][j] = Obj::null;
		}
	}
	int temp = robo_n;
	while (temp > 0) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::robot;
			robots[temp-1] = Robot(Vec2(x,y),50);
			robots[temp - 1].set_rand_programm();
			temp--;
		}
	}
	fout.open("inp.csv", std::ios::out | std::ios::app);
	add_fwt();
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			gui.draw(i, j, field[i][j]);
		}
	}
	gui.display();
}

void Field::chF() {
	if (f)
		f = false;
	else
		f = true;
}

void Field::add_fwt() {
	while (food != food_n) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::food;
			food++;
			gui.draw(x, y, Obj::food);
		}
	}
	while (wall != wall_n) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::wall;
			wall++;
			gui.draw(x, y, Obj::wall);
		}
	}
	while (toxic != toxic_n) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::toxic;
			toxic++;
			gui.draw(x, y, Obj::toxic);
		}
	}
}

void Field::seetocons() {
	std::string s = "";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (field[i][j] == Obj::null) {
				s += "   ";
			}
			if (field[i][j] == Obj::food) {
				s += " F ";
			}
			if (field[i][j] == Obj::wall) {
				s += " W ";
			}
			if (field[i][j] == Obj::toxic) {
				s += " T ";
			}
			if (field[i][j] == Obj::robot) {
				s += " R ";
			}
		}
		s += "\n";
	}
	system("cls");
	std::cout << s;
}

void Field::next_day() {
	day++;
	for (int i = 0; i < robots.size(); ++i) {
		if (!robots[i].live)
			continue;
		Action act = robots[i].update();
		int x = robots[i].getx();
		int y = robots[i].gety();
		switch (act) {
		case Action::death:
			robo--;
			robots[i].live = false;
			field[x][y] = Obj::null;
			best_programm.emplace_back(robots[i].get_programm());
			break;
		case Action::stay:
			break;
		case Action::go_forward:
			if (field[x + 1][y] == Obj::null) {
				field[x + 1][y] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x + 1, y));
			}
			if (field[x + 1][y] == Obj::food) {
				field[x + 1][y] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x + 1, y));
				robots[i].addhp(5);
				food--;
			}
			if (field[x + 1][y] == Obj::toxic) {
				field[x + 1][y] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x + 1, y));
				robots[i].addhp(-5);
				toxic--;
			}
			break;
		case Action::go_left:
			if (field[x][y - 1] == Obj::null) {
				field[x][y - 1] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x, y - 1));
			}
			if (field[x][y - 1] == Obj::food) {
				field[x][y - 1] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x, y - 1));
				robots[i].addhp(5);
				food--;
			}
			if (field[x][y - 1] == Obj::toxic) {
				field[x][y - 1] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x, y - 1));
				robots[i].addhp(-5);
				toxic--;
			}
			break;
		case Action::go_back:
			if (field[x - 1][y] == Obj::null) {
				field[x - 1][y] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x - 1, y));
			}
			if (field[x - 1][y] == Obj::food) {
				field[x - 1][y] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x - 1, y));
				robots[i].addhp(5);
				food--;
			}
			if (field[x - 1][y] == Obj::toxic) {
				field[x - 1][y] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x - 1, y));
				robots[i].addhp(-5);
				toxic--;
			}
			break;
		case Action::go_right:
			if (field[x][y + 1] == Obj::null) {
				field[x][y + 1] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x, y + 1));
			}
			if (field[x][y + 1] == Obj::food) {
				field[x][y + 1] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x, y + 1));
				robots[i].addhp(5);
				food--;
			}
			if (field[x][y + 1] == Obj::toxic) {
				field[x][y + 1] = Obj::robot;
				field[x][y] = Obj::null;
				robots[i].setCoord(Vec2(x, y + 1));
				robots[i].addhp(-5);
				toxic--;
			}
			break;
		case Action::eat_forward:
			if (field[x + 1][y] == Obj::food || field[x + 1][y] == Obj::toxic) {
				if (field[x + 1][y] == Obj::food)
					food--;
				else
					toxic--;
				field[x + 1][y] = Obj::null;
				robots[i].addhp(10);
			}
			break;
		case Action::eat_back:
			if (field[x - 1][y] == Obj::food || field[x - 1][y] == Obj::toxic) {
				if (field[x - 1][y] == Obj::food)
					food--;
				else
					toxic--;
				field[x - 1][y] = Obj::null;
				robots[i].addhp(10);
			}
			break;
		case Action::eat_left:
			if (field[x][y - 1] == Obj::food || field[x][y - 1] == Obj::toxic) {
				if (field[x][y - 1] == Obj::food)
					food--;
				else
					toxic--;
				field[x][y - 1] = Obj::null;
				robots[i].addhp(10);
			}
			break;
		case Action::eat_rigth:
			if (field[x][y + 1] == Obj::food || field[x][y + 1] == Obj::toxic) {
				if (field[x][y + 1] == Obj::food)
					food--;
				else
					toxic--;
				field[x][y + 1] = Obj::null;
				robots[i].addhp(10);
			}
			break;
		case Action::see_forward:
			robots[i].see(field[x+1][y]);
			break;
		case Action::see_back:
			robots[i].see(field[x-1][y]);
			break;
		case Action::see_left:
			robots[i].see(field[x][y-1]);
			break;
		case Action::see_right:
			robots[i].see(field[x][y+1]);
			break;
		}
	}
	if (f) {
		gui.clear();
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				gui.draw(i, j, field[i][j]);
			}
		}
		gui.display();
	}
	add_fwt();
	if (robo == 0) {
		new_era();
	}
}

void Field::new_era() {
	int bs = best_programm.size();
	std::cout << era << " " << day << std::endl;
	fout << era << "," << day << "\n";
	era++;
	day = 0;
	field = std::vector<std::vector<Obj>>(size, std::vector<Obj>(size, Obj::wall));
	
	for (int i = 1; i < size - 1; ++i) {
		for (int j = 1; j < size - 1; ++j) {
			field[i][j] = Obj::null;
		}
	}
	robo = robo_n;
	int temp = robo_n;
	while (temp > robo_n - 8) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::robot;
			robots[temp - 1] = Robot(Vec2(x, y), 50);
			robots[temp - 1].set_programm(best_programm[bs-1]);
			temp--;
		}
	}
	while (temp > robo_n - 16) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::robot;
			robots[temp - 1] = Robot(Vec2(x, y), 50);
			robots[temp - 1].set_mutate_programm(best_programm[bs-1], 1);
			temp--;
		}
	}
	while (temp > robo_n - 32) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::robot;
			robots[temp - 1] = Robot(Vec2(x, y), 50);
			robots[temp - 1].set_mutate_programm(best_programm[bs - 1], 2);
			temp--;
		}
	}
	while (temp > robo_n - 58) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::robot;
			robots[temp - 1] = Robot(Vec2(x, y), 50);
			robots[temp - 1].set_mutate_programm(best_programm[bs - 1], 3);
			temp--;
		}
	}
	while (temp > 0) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::robot;
			robots[temp - 1] = Robot(Vec2(x, y), 50);
			robots[temp - 1].set_rand_programm();
			temp--;
		}
	}
	food = 0; wall = 0; toxic = 0;
	add_fwt();
}

