// TicTacToe.cpp : Defines the entry point for the application.
//

#include "TicTacToe.h"

using namespace std;

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1200, 700), "TicTacToe.Io");
	window->setFramerateLimit(60);

	Game game(window);
	while (game.runningWindow()) {

		game.update();
		game.render();
	}

	return 0;
}
