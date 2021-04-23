#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "struct.h"

class Gui {
private:
	sf::RenderWindow window;
	sf::RectangleShape ob;
	sf::Event event;
public:
	Gui(int X, int Y);
	void draw(int x, int y, Obj o);
	void display();
	void clear();
};


#endif //GUI_H