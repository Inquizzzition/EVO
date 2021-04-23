#include "gui.h"


Gui::Gui(int X, int Y):
	window(sf::VideoMode(X*10, Y*10), "EVOLUTION"),
	ob(sf::Vector2f(10.f, 10.f))
{}

void Gui::draw(int x, int y, Obj o) {
	ob.setPosition(x * 10, y * 10);
	switch (o)
	{
	case Obj::null:
		ob.setFillColor(sf::Color(169, 169, 169));
		window.draw(ob);
		break;
	case Obj::robot:
		ob.setFillColor(sf::Color(255, 0, 255));
		window.draw(ob);
		break;
	case Obj::wall:
		ob.setFillColor(sf::Color(0, 0, 0));
		window.draw(ob);
		break;
	case Obj::food:
		ob.setFillColor(sf::Color(34, 139, 34));
		window.draw(ob);
		break;
	case Obj::toxic:
		ob.setFillColor(sf::Color(139, 0, 0));
		window.draw(ob);
		break;
	default:
		break;
	}
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Gui::display() {
	window.display();
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Gui::clear() {
	window.clear();
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

