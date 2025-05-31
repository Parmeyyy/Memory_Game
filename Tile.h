#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Tile
{
private:
    sf::RectangleShape shape;       // Графическое представление плитки
    sf::Color colorInactive;        // Цвет неактивной плитки
    sf::Color colorActive;          // Цвет активной плитки
    sf::Uint8 alphaIdle;           // Прозрачность в обычном состоянии
    sf::Uint8 alphaHover;          // Прозрачность при наведении
    sf::Uint8 alphaPressed;        // Прозрачность при нажатии
    bool active;                   // Активна ли плитка 
    bool pressed;                  // Нажата ли плитка в данный момент

public:
    Tile();                       
    Tile(sf::Vector2f position, float size, bool active); // создание плитки 
    ~Tile();                      

    
    inline const bool isPressed() const { return this->pressed; }//нажата ли мышка в данный момент
    inline const bool isActive() const { return this->active; }//активна ли плитка 

    //устанавливаем состояние и цвет зависит от него
    inline void setActive(const bool active) { this->active = active; }
    inline void setColorInactive() { this->shape.setFillColor(this->colorInactive); }
    inline void setColorActive() { this->shape.setFillColor(this->colorActive); }

    void update(sf::Vector2f& mousePosView, const bool lmb_pressed); // Обновление состояния
    void render(sf::RenderTarget& target);                           // Отрисовка
};
