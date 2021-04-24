#include "field.h";

Field::Field(int size, int robo_n, int food_n, int wall_n, int toxic_n, int tree_n, int pool_n, int dop_tox, bool gen) :
	field(size, std::vector<Obj>(size, Obj::wall)),
	best_programm(0),
	robots(robo_n),
	dop_tox(dop_tox),
	day(0),
	era(1),
	size(size), 
	robo_n(robo_n), robo(robo_n),
	food_n(food_n), food(0),
	wall_n(wall_n), wall(0),
	toxic_n(toxic_n), toxic(0),
	gui(size, size), f(true),
	true_generation(gen),
	tree(tree_n), pool(pool_n)
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
			if (true_generation)
				robots[temp - 1].f = true;
			robots[temp - 1].set_rand_programm();
			temp--;
		}
	}
	fout.open("inp.csv", std::ios::out | std::ios::app);
	if (!true_generation)
		add_fwt();
	else
		add_trpo();
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
	while (food < food_n) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::food;
			food++;
		}
	}
	while (wall < wall_n) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::wall;
			wall++;
		}
	}
	while (toxic < toxic_n) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::toxic;
			toxic++;
		}
	}
}

void Field::add_trpo() {
	int t = 0;
	while (t < tree.size()) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::wall;
			for (int i = 0; i < dx.size(); i++) {
				if (x + dx[i] >= 0 && x + dx[i] < size && y + dy[i] >= 0 && y + dy[i] < size &&  field[x + dx[i]][y + dy[i]] == Obj::null)
					field[x + dx[i]][y + dy[i]] = Obj::food;
			}
			for (int i = 0; i < dwx.size(); i++) {
				if (x + dwx[i] >= 0 && x + dwx[i] < size && y + dwy[i] >= 0 && y + dwy[i] < size && field[x + dwx[i]][y + dwy[i]] == Obj::null)
					field[x + dwx[i]][y + dwy[i]] = Obj::wall;
			}
			for (int i = 0; i < dxa.size(); ++i) {
				if (x + dxa[i] >= 0 && x + dxa[i] < size && y + dya[i] >= 0 && y + dya[i] < size && field[x + dxa[i]][y + dya[i]] == Obj::null)
					field[x + dxa[i]][y + dya[i]] = Obj::toxic;
			}
			tree[t] = Vec2(x, y);
			t++;
		}
	}
	t = 0;
	while (t < pool.size()) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::wall;
			for (int i = 0; i < dx.size(); i++) {
				if (x+dx[i] >= 0 && x + dx[i] < size && y + dy[i] >= 0 && y + dy[i] < size && field[x + dx[i]][y + dy[i]] == Obj::null)
					field[x + dx[i]][y + dy[i]] = Obj::toxic;
			}
			for (int i = 0; i < dwx.size(); i++) {
				if (x + dwx[i] >= 0 && x + dwx[i] < size && y + dwy[i] >= 0 && y + dwy[i] < size && field[x + dwx[i]][y + dwy[i]] == Obj::null)
					field[x + dwx[i]][y + dwy[i]] = Obj::wall;
			}
			for (int i = 0; i < dxa.size(); ++i) {
				if (x + dxa[i] >= 0 && x + dxa[i] < size && y + dya[i] >= 0 && y + dya[i] < size && field[x + dxa[i]][y + dya[i]] == Obj::null)
					field[x + dxa[i]][y + dya[i]] = Obj::food;
			}
			pool[t] = Vec2(x, y);
			t++;
		}
	}
	t = 0;
	while (t < dop_tox) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::toxic;
			t++;
		}
	}
}

void Field::heal_trpo() {
	for (int j = 0; j < tree.size(); ++j) {
		int x = tree[j].x;
		int y = tree[j].y;
		for (int i = 0; i < dx.size(); i++) {
			if (x + dx[i] >= 0 && x + dx[i] < size && y + dy[i] >= 0 && y + dy[i] < size && field[x + dx[i]][y + dy[i]] == Obj::null)
				field[x + dx[i]][y + dy[i]] = Obj::food;
		}
		for (int i = 0; i < dxa.size(); ++i) {
			if (x + dxa[i] >= 0 && x + dxa[i] < size && y + dya[i] >= 0 && y + dya[i] < size && field[x + dxa[i]][y + dya[i]] == Obj::null)
				field[x + dxa[i]][y + dya[i]] = Obj::toxic;
		}
	}
	for (int j = 0; j < pool.size(); ++j) {
		int x = pool[j].x;
		int y = pool[j].y;
		for (int i = 0; i < dx.size(); i++) {
			if (x + dx[i] >= 0 && x + dx[i] < size && y + dy[i] >= 0 && y + dy[i] < size && field[x + dx[i]][y + dy[i]] == Obj::null)
				field[x + dx[i]][y + dy[i]] = Obj::toxic;
		}
		for (int i = 0; i < dxa.size(); ++i) {
			if (x + dxa[i] >= 0 && x + dxa[i] < size && y + dya[i] >= 0 && y + dya[i] < size && field[x + dxa[i]][y + dya[i]] == Obj::null)
				field[x + dxa[i]][y + dya[i]] = Obj::food;
		}
	}
	int t = 0;
	int itr = 0;
	while (t < 2) {
		itr++;
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::toxic;
			t++;
		}
		if (itr > 1e3 / 2)
			break;
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
				if (field[x + 1][y] == Obj::food) {
					food--;
					field[x + 1][y] = Obj::null;
					robots[i].addhp(10);
				}
				else {
					toxic--;
					food++;
					field[x + 1][y] = Obj::food;
				}
			}
			break;
		case Action::eat_back:
			if (field[x - 1][y] == Obj::food || field[x - 1][y] == Obj::toxic) {
				if (field[x - 1][y] == Obj::food) {
					food--;
					field[x - 1][y] = Obj::null;
					robots[i].addhp(10);
				}
				else {
					toxic--;
					food++;
					field[x - 1][y] = Obj::food;
				}
			}
			break;
		case Action::eat_left:
			if (field[x][y - 1] == Obj::food || field[x][y - 1] == Obj::toxic) {
				if (field[x][y - 1] == Obj::food) {
					food--;
					field[x][y - 1] = Obj::null;
					robots[i].addhp(10);
				}
				else {
					toxic--;
					food++;
					field[x][y - 1] = Obj::food;
				}
			}
			break;
		case Action::eat_rigth:
			if (field[x][y + 1] == Obj::food || field[x][y + 1] == Obj::toxic) {
				if (field[x][y + 1] == Obj::food) {
					food--;
					field[x][y + 1] = Obj::null;
					robots[i].addhp(10);
				}
				else {
					toxic--;
					food++;
					field[x][y + 1] = Obj::food;
				}
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
	if (!true_generation)
		add_fwt();
	else if(day % 5 == 0)
			heal_trpo();
	if (day > 50000) {
		robo = 0;
		for (auto& i : robots) {
			if(i.live)
				best_programm.emplace_back(i.get_programm());
		}
	}
	if (robo < 5) {
		robo = 0;
		for (auto& i : robots) {
			if (i.live)
				best_programm.emplace_back(i.get_programm());
		}
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
	if (!true_generation) {
		food = 0; wall = 0; toxic = 0;
		add_fwt();
	}
	else {
		add_trpo();
	}
	robo = robo_n;
	int temp = robo_n;
	while (temp > robo_n - 10) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::robot;
			robots[temp - 1] = Robot(Vec2(x, y), 50);
			robots[temp - 1].set_programm(best_programm[bs-1]);
			if (true_generation)
				robots[temp - 1].f = true;
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
			if (true_generation)
				robots[temp - 1].f = true;
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
			if (true_generation)
				robots[temp - 1].f = true;
			temp--;
		}
	}
	while (temp > 0) {
		int x = rand() % size;
		int y = rand() % size;
		if (field[x][y] == Obj::null) {
			field[x][y] = Obj::robot;
			robots[temp - 1] = Robot(Vec2(x, y), 50);
			if (true_generation)
				robots[temp - 1].f = true;
			robots[temp - 1].set_rand_programm();
			temp--;
		}
	}
}

