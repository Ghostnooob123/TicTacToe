// TicTacToe.cpp : Defines the entry point for the application.
//

#include "TicTacToe.h"

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1200, 700), "TicTacToe.Io");
	window->setFramerateLimit(60);

	Game game(window);
	while (game.runningWindow()) {

		game.update();
		game.render();
	}

	delete window;
	window = nullptr;

	return 0;
}
