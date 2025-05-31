#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
//Класс Menu представляет графическое меню для игры или программы, 
// в котором можно перемещаться по пунктам (например, "Start Game", "Options", "Exit") 
// с помощью клавиш и отображать его на окне.
class Menu
{
private:
    sf::Font font;
    std::vector<sf::Text> menuItems;
    int selectedItemIndex;
    sf::Text titleText;

public:
    Menu();
    bool loadFont();
    void initMenuItems(sf::RenderWindow& window);//инициализирует пункты меню и заголовок
    void draw(sf::RenderWindow& window);//отрисовывает все элементы меню
    void moveUp();
    void moveDown();
    int getSelectedItem() const;//возвращает индекс выбранного пункта меню
};