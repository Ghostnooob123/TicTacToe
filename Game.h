#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

constexpr int matrixSize = 3;

class Game {
public:
	Game(sf::RenderWindow* window);

	void update();
	void render();

	bool runningWindow();
private:
	sf::RenderWindow* _window;
	sf::Vector2f _mousePos;

	float _x;
	float _y;

	void updateMousePos();
	void pollEvents();
	void updateGame();

	bool _isDragging = false;
	bool _gameEnd = false;
	std::vector<std::vector<sf::RectangleShape>> _gameMatrix;

	sf::Texture _ex_texture;
	sf::Texture _zero_texture;

	int _turn;

	void init();
};
#endif // !GAME_H

