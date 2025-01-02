#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	this->_window = window;
	this->init();
}

void Game::update()
{

	this->updateMousePos();
	this->pollEvents();

	if (!this->_gameEnd)
	{
		this->updateGame();
	}
	else
	{
		std::cout << "Game End ";
	}
}

void Game::render()
{
	this->_window->clear(sf::Color(84, 173, 232));

	for (size_t objR = 0; objR < this->_gameMatrix.size(); objR++)
	{
		for (size_t objC = 0; objC < this->_gameMatrix[objR].size(); objC++) {
			auto value = this->_gameMatrix[objR][objC];
			this->_window->draw(value);
		}
	}

	//this->_window->draw(this->_ex);

	//this->_window->draw(this->_zero);

	this->_window->display();
}

bool Game::runningWindow()
{
	if (this->_window->isOpen())
	{
		return true;
	}
	return false;
}

void Game::updateMousePos()
{
	sf::Vector2i mouseWindow = sf::Mouse::getPosition(*this->_window);
	this->_mousePos = this->_window->mapPixelToCoords(mouseWindow);
}

void Game::pollEvents()
{
	sf::Event event;

	while (this->_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			this->_window->close();
		}
		if (sf::Keyboard::Escape == event.key.code)
		{
			this->_window->close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			/*if (this->_shape.getGlobalBounds().contains(this->_mousePos) || this->_isDragging) {
				this->_isDragging = true;
				this->_shape.setPosition(this->_mousePos.x - 25.0f, this->_mousePos.y - 20.0f);
			}*/
		}
		else {
			this->_isDragging = false;
		}
	}
}

void Game::updateGame()
{
	sf::RectangleShape player;
	
	switch (this->_turn)
	{
	case 0:
		player.setTexture(&this->_ex_texture);
		break;
	case 1:
		player.setTexture(&this->_zero_texture);
		break;
	}

	for (size_t objR = 0; objR < this->_gameMatrix.size(); objR++) {
		for (size_t objC = 0; objC < this->_gameMatrix.size(); objC++) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (this->_gameMatrix[objR][objC].getGlobalBounds().contains(this->_mousePos) &&
					this->_gameMatrix[objR][objC].getTexture() == nullptr)
				{
					this->_gameMatrix[objR][objC].setTexture(player.getTexture());
					switch (this->_turn)
					{
					case 0:
						this->_turn = 1;
						break;
					case 1:
						this->_turn = 0;
						break;
					}
				}
			}
		}
	}

	for (size_t objR = 0; objR < this->_gameMatrix.size(); objR++) {
		// HORIZONTAL
		if (this->_gameMatrix[0][0].getTexture() != nullptr &&
			this->_gameMatrix[0][1].getTexture() != nullptr &&
			this->_gameMatrix[0][2].getTexture() != nullptr)
		{
			if (this->_gameMatrix[0][0].getTexture() ==
				this->_gameMatrix[0][1].getTexture() &&
				this->_gameMatrix[0][0].getTexture() ==
				this->_gameMatrix[0][2].getTexture())
			{
				this->_gameEnd = true;
				return;
			}
		}
		if (this->_gameMatrix[2][0].getTexture() != nullptr &&
			this->_gameMatrix[2][1].getTexture() != nullptr &&
			this->_gameMatrix[2][2].getTexture() != nullptr)
		{
			if (this->_gameMatrix[2][0].getTexture() ==
				this->_gameMatrix[2][1].getTexture() &&
				this->_gameMatrix[2][0].getTexture() ==
				this->_gameMatrix[2][2].getTexture())
			{
				this->_gameEnd = true;
				return;
			}
		}
		if (this->_gameMatrix[1][0].getTexture() != nullptr &&
			this->_gameMatrix[1][1].getTexture() != nullptr &&
			this->_gameMatrix[1][2].getTexture() != nullptr)
		{
			if (this->_gameMatrix[1][0].getTexture() ==
				this->_gameMatrix[1][1].getTexture() &&
				this->_gameMatrix[1][0].getTexture() ==
				this->_gameMatrix[1][2].getTexture())
			{
				this->_gameEnd = true;
				return;
			}
		}

		// VERTICAL
		if (this->_gameMatrix[0][0].getTexture() != nullptr &&
			this->_gameMatrix[1][0].getTexture() != nullptr &&
			this->_gameMatrix[2][0].getTexture() != nullptr)
		{
			if (this->_gameMatrix[0][0].getTexture() ==
				this->_gameMatrix[1][0].getTexture() &&
				this->_gameMatrix[0][0].getTexture() ==
				this->_gameMatrix[2][0].getTexture())
			{
				this->_gameEnd = true;
				return;
			}
		}
		if (this->_gameMatrix[0][1].getTexture() != nullptr &&
			this->_gameMatrix[1][1].getTexture() != nullptr &&
			this->_gameMatrix[2][1].getTexture() != nullptr)
		{
			if (this->_gameMatrix[0][1].getTexture() ==
				this->_gameMatrix[1][1].getTexture() &&
				this->_gameMatrix[0][1].getTexture() ==
				this->_gameMatrix[2][1].getTexture())
			{
				this->_gameEnd = true;
				return;
			}
		}
		if (this->_gameMatrix[0][2].getTexture() != nullptr &&
			this->_gameMatrix[1][2].getTexture() != nullptr &&
			this->_gameMatrix[2][2].getTexture() != nullptr)
		{
			if (this->_gameMatrix[0][2].getTexture() ==
				this->_gameMatrix[1][2].getTexture() &&
				this->_gameMatrix[0][2].getTexture() ==
				this->_gameMatrix[2][2].getTexture())
			{
				this->_gameEnd = true;
				return;
			}
		}
	}
}

void Game::init()
{
	this->_x = this->_window->getSize().x / 2.0f;
	this->_y = this->_window->getSize().y / 2.0f;

	this->_turn = 0;

	this->_gameMatrix.resize(matrixSize, std::vector<sf::RectangleShape>(matrixSize));
	float objSize = 130.0f;
	float distance = objSize + 5.0f;

	for (size_t objR = 0; objR < this->_gameMatrix.size(); objR++) {
		for (size_t objC = 0; objC < this->_gameMatrix.size(); objC++) {
			sf::RectangleShape obj;

			obj.setFillColor(sf::Color::White);
			obj.setSize(sf::Vector2f(objSize, objSize));
			obj.setOutlineColor(sf::Color::Black);
			obj.setOutlineThickness(5.0f);
			obj.setPosition(sf::Vector2f((this->_x - 200.0f) + objC * distance, (this->_y - 200.0f) + objR * distance));
			this->_gameMatrix[objR][objC] = obj;
		}
	}

	if (!this->_ex_texture.loadFromFile("src/x.png")) {
		return;
	}

	if (!this->_zero_texture.loadFromFile("src/zero.png")) {
		return;
	}
}
