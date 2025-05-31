#include "Menu.h"

Menu::Menu() : selectedItemIndex(0) {}

bool Menu::loadFont()//Метод для загрузки шрифта 
{
    if (font.loadFromFile("arial.ttf")) return true;
    if (font.loadFromFile("fonts/arial.ttf")) return true;
    return font.loadFromFile("C:/Windows/Fonts/arial.ttf"); 
}

void Menu::initMenuItems(sf::RenderWindow& window)//Инициализирует заголовок и пункты меню, размещая их относительно размеров окна
{
    titleText.setFont(font);
    titleText.setString("MEMORY");
    titleText.setCharacterSize(80); 
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);

    // Центрируем заголовок
    titleText.setPosition(
        window.getSize().x / 2 - titleText.getGlobalBounds().width / 2,
        50.f 
    );

    std::vector<std::string> items = 
    {
        "Easy (4x4, 3 tiles)",
        "Medium (5x5, 4 tiles)",
        "Hard (6x6, 6 tiles)",
        "Exit"
    };

    for (size_t i = 0; i < items.size(); i++)//цикл по всем пунктам от создания до выбора
    {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(40);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(
            window.getSize().x / 2 - text.getGlobalBounds().width / 2,
            200 + i * 70
        );
        menuItems.push_back(text);
    }
}

void Menu::draw(sf::RenderWindow& window)//Рисует заголовок и каждый пункт меню в переданное окно
{
    window.draw(titleText);
    for (auto& item : menuItems)
    {
        window.draw(item);
    }
}

void Menu::moveUp()//Метод ВВЕРХ, срабатывает при нажатии клавиши и меняет цвета и заголовков
{
    if (selectedItemIndex > 0)
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown()//аналогичный метод ВНИЗ, работает, если это не последний пункт 
{
    if (selectedItemIndex < menuItems.size() - 1)
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedItem() const//возвращает индекс, применяется в главном цикле при нажатии ENTER
{
    return selectedItemIndex;
}