#include "GameBoard.h"
#include "Menu.h"
#include <cstdlib>
#include <ctime>


//Добро пожаловать, это мой код игры Memory, надеюсь ты искал то что хотел и получишь хорошую отметку или респект!


int main()
{
    //Создание окна и установка фпс
    sf::RenderWindow window(sf::VideoMode(800, 700), "Memory Game");
    window.setFramerateLimit(60);

    Menu menu;//Создается меню и проверка на загрузку шрифта
    if (!menu.loadFont())
    {
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            return EXIT_FAILURE;
        }
    }
    menu.initMenuItems(window);

    GameBoard* gameBoard = nullptr;
    bool inGame = false;//флаг показываем меню или играем 
    srand(static_cast<unsigned>(time(nullptr)));//генератор случаныйх плиток для выбора плиток

    while (window.isOpen())//главный цикл работает пока открыто окно
    {
        sf::Event event;
        while (window.pollEvent(event))
        {                                             //обработка событий и если пользователь нажимает на крестик, то закрываем
            if (event.type == sf::Event::Closed)
                window.close();

            if (!inGame) // Обработка событий меню
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                        menu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down)
                        menu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int selectedItem = menu.getSelectedItem();//если нажат Enter,то получаем индекс выбраного пункта
                        if (selectedItem == 3) // Exit
                        {
                            window.close();
                        }
                        else // Start Game
                        {
                            inGame = true;
                            int boardSize, activeTiles;
                            float tileSize;

                            switch (selectedItem)
                            {
                            case 0: // Easy
                                boardSize = 4;
                                activeTiles = 3;
                                tileSize = 100.f;
                                break;
                            case 1: // Medium
                                boardSize = 5;
                                activeTiles = 4;
                                tileSize = 100.f;
                                break;
                            case 2: // Hard
                                boardSize = 6;
                                activeTiles = 6;
                                tileSize = 100.f;
                                break;
                            default:
                                boardSize = 4;
                                activeTiles = 3;
                                tileSize = 100.f;
                            }

                            gameBoard = new GameBoard(&window, tileSize, boardSize, boardSize, activeTiles);//динамически создается игровая доска(игровое поле)
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);//очистка экрана

        if (!inGame)//если в игре 
        {
            menu.draw(window);//рисуем окно
        }
        else if (gameBoard)//если в игре то обновляем доску
        {
            gameBoard->update(window);

            if (gameBoard->checkExit())//проверка на выход, если завершается, то удаляем игровое поле, сбрасвыем флаг и возврат в меню
            {
                delete gameBoard;
                gameBoard = nullptr;
                inGame = false;
                continue;
            }

            gameBoard->render(window);

            if (gameBoard->checkExit())
            {
                delete gameBoard;
                gameBoard = nullptr;
                inGame = false;
            }
        }

        window.display();
    }

    if (gameBoard) delete gameBoard;//очистка всех элементов 
    return EXIT_SUCCESS;
}