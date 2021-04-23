#ifndef FIELD_H
#define FIELD_H

#include <sstream>
#include <iostream>
#include "robot.h"
#include "gui.h"
#include <fstream>

class Field {
private:
	Gui gui;
	std::vector<std::vector<Obj>> field;
	std::vector<Robot> robots;
	std::vector<std::vector<int>> best_programm;
	std::vector<Vec2> tree;
	std::vector<Vec2> pool;
	std::vector<int> dx = { 1, -1, 0, 0, 1, 1, -1, -1 };
	std::vector<int> dy = { 0, 0, 1, -1, 1, -1, 1, -1 };
	std::vector<int> dxa = { 2, 2, -2, -2, 0, 0, 2, -2 };
	std::vector<int> dya = { 2, -2, 2, -2, 2, -2, 0, 0 };
	std::vector<int> dwx = { 2, 2, 1, 1, -1, -1, -2, -2 };
	std::vector<int> dwy = { 1, -1, 2, -2, 2, -2, 1, -1 };
	int size; int day;
	int robo_n; int food;
	int food_n; int wall;
	int wall_n; int toxic;
	int toxic_n; int robo;
	int dop_tox; 
	int era;
	bool f, true_generation;
	void add_fwt();
	void add_trpo();
	void heal_trpo();
	std::fstream fout;
public:
	void chF();
	void new_era();
	void next_day();
	void seetocons();
	Field(int size, int robo_n, int food_n,	int wall_n,	int toxic_n, int tree_n, int pool_n, int dop_tox, bool gen);
};

#endif //FIELD_H
/*
TREE
W W T W W
W F F F W
T F W F F
W F F F W
W W T W W
---------
POOL
W W F W W
W T T T W
F T W T F
W T T T W
W W F W W
*/
