#ifndef ROBOT_H
#define ROBOT_H

#include "struct.h";
#include <vector>;

class Robot{
private:
	Vec2 coord;
	std::vector<int> programm;
	int hp;
	int iter;
	int dir;
public:
	bool live;
	Robot();
	Robot(Vec2 coord, int hp);
	Action update();
	void see(Obj b);
	void set_rand_programm();
	void set_programm(std::vector<int> p);
	void set_mutate_programm(std::vector<int> p, int k);
	std::vector<int> get_programm();
	int getx();
	int gety();
	void setCoord(Vec2 v);
	void addhp(int h);
};

#endif //ROBOT_H


/*
0 - go
1 - eat
2 - see
3 - turn rigth
4 - turn left
5 - goto
6 - goto
7 - goto
*/
