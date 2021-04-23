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
	int size; int day;
	int robo_n; int food;
	int food_n; int wall;
	int wall_n; int toxic;
	int toxic_n; int robo;
	int era;
	bool f;
	void add_fwt();
	std::fstream fout;
public:
	void chF();
	void new_era();
	void next_day();
	void seetocons();
	Field(int size, int robo_n, int food_n,	int wall_n,	int toxic_n);
};

#endif //FIELD_H
