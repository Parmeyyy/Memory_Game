#pragma once

#include "Tile.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <algorithm>

class GameBoard
{
private:
	sf::RenderWindow* window;//указатель на окно отрисовки
	std::vector <Tile*> tilesVec;//Хранит указатели на все плитки на доске
	std::vector <int> activeTilesVec;//Хранит индексы активных плиток, которые показываются в начале
	std::vector <int> selectionVec;//Индексы плиток, которые игрок выбрал в текущей попытке
	float keyTime, keyTimeMax;//счётчик задержки между нажатиями,максимальное время между действиями
	sf::Vector2f mousePosView;//текущая позиция мыши в координатах окна
	float tileSize;//размер одной плитки
	bool exitGame;//флаг,указывающий выход из игры
	int tilesSelected;
	int nrOfActiveTiles;//кол-во активных плиток, которые надо запомнить
	bool restarting;//флаг, указывающий, что игра перезапускается
	float displayTimer;//таймер на скок сек показываются плитки в начале
	int correct;
	int incorrect;
	sf::Font font;
	sf::Text scoreText;//текст для отображения очков
	int score; 
	sf::Text messageText;//текст вывода ответа
	float messageTimer;
	bool exitToMenu;//флаг на выход в меню

	void createBoard(const int board_width, const int board_height);//Создаёт доску указанного размера
	void randomizeBoard();//Случайным образом выбирает кол-во актв плиток, чтобы игрок их запомнил
	void displayOrder();//Включает отображение выбранных активных плиток
	const bool checkSelection();//Проверяет, правильно ли игрок выбрал плитки
	void updateKeyTime();//Обновляет таймер между нажатиями клавиш
	void updateBoard();//Общая логика обновления состояния доски
	inline const bool checkKeyTime() const { return this->keyTime >= this->keyTimeMax; }//проверка, прошло ли достаточно времени для нового действия
	inline void resetKeyTime() { this->keyTime = 0.f; }//сброс таймера после действия

public:
	GameBoard();
	GameBoard(sf::RenderWindow* window, float tile_size = 100.f, int board_width = 5, int board_height = 5, int nr_active = 4);
	~GameBoard();

	
	bool checkExit() const;

	void restart();
	void update(sf::RenderWindow& window); // Обновляет все внутренние состояния
	void render(sf::RenderTarget& target);// Рисует все плитки, текст, счёт, сообщения
};
