#include "GameBoard.h"

void GameBoard::createBoard(const int board_width, const int board_height)
{
    //начальные координаты
    float x = 0.f;
    float y = 0.f;
    for (size_t i = 0; i < board_height; i++)//цикл создания плиток и добавление ее в вектор
    {
        for (size_t k = 0; k < board_width; k++)
        {
            this->tilesVec.push_back(new Tile(sf::Vector2f(x, y), this->tileSize, false));
            x += this->tileSize;
        }
        y += this->tileSize;
        x = 0.f;
    }
}
//Проверка, должен ли игрок выйти в меню
bool GameBoard::checkExit() const {   
    return this->exitToMenu;
}

// функция отвечает за случацный выбор активных плиток \
// (очистка,деактиваация,выбор индекса из списка, активация и запоминание акт плиток и убирает их из списка)
void GameBoard::randomizeBoard()
{
    this->activeTilesVec.clear();

    for (size_t i = 0; i < this->tilesVec.size(); i++)
    {
        this->tilesVec[i]->setActive(false);
        this->tilesVec[i]->setColorInactive();
    }

    std::vector<int> index_vector;
    for (size_t i = 0; i < this->tilesVec.size(); i++)
    {
        index_vector.push_back(i);
    }

    int tiles_added = 0;
    int index = -1;
    while (tiles_added != this->nrOfActiveTiles)
    {
        index = rand() % index_vector.size();
        this->tilesVec[index_vector[index]]->setActive(true);
        this->tilesVec[index_vector[index]]->setColorActive();
        this->activeTilesVec.push_back(index_vector[index]);
        index_vector.erase(index_vector.begin() + index);
        tiles_added++;
    }
}
 //Функция отвечает за временное отображение порядка активных плиток в начале раунда
//делает все плитки неактив, потом подсвечивает нужные и снова неактивные
void GameBoard::displayOrder()
{
   
    if (this->displayTimer < 50.f)
    {
        for (size_t i = 0; i < this->tilesVec.size(); i++)
        {
            this->tilesVec[i]->setColorInactive();
        }
    }
    else if (this->displayTimer >= 50.f && this->displayTimer < 100.f)
    {
        for (size_t i = 0; i < this->tilesVec.size(); i++)
        {
            if (this->tilesVec[i]->isActive())
                this->tilesVec[i]->setColorActive();
        }
    }
    else if (this->displayTimer >= 100.f && this->displayTimer < 150.f)
    {
        for (size_t i = 0; i < this->tilesVec.size(); i++)
        {
            this->tilesVec[i]->setColorInactive();
        }
    }
    else
    {
        this->restarting = false;
    }

    this->displayTimer += 1.f;
}
//Сортировка и сравнение выбранных плиток с правильным порядком
const bool GameBoard::checkSelection()
{
    std::sort(this->activeTilesVec.begin(), this->activeTilesVec.end());
    std::sort(this->selectionVec.begin(), this->selectionVec.end());

    return this->activeTilesVec == this->selectionVec;
}

void GameBoard::updateKeyTime()      //Обновление таймера для защиты от слишком быстрого нажатия мыши
{
    if (this->keyTime < this->keyTimeMax)
        this->keyTime += 1.f;
}

//основная игровая логика(мозг)
//Управляет выбором плиток игроком;Проверяет, верно ли выбран порядок;Обновляет счёт;
//Показывает сообщение;Запускает перезапуск раунда
void GameBoard::updateBoard()  
{
    if (this->restarting)
    {
        this->displayOrder();
        
    }
    else
    {
        if (this->tilesSelected <= this->nrOfActiveTiles)// Проверка: сколько плиток уже выбрано
        {
            for (size_t i = 0; i < this->tilesVec.size(); i++)
            {
                this->tilesVec[i]->update(this->mousePosView, sf::Mouse::isButtonPressed(sf::Mouse::Left));

                if (this->tilesVec[i]->isPressed() && this->checkKeyTime())
                {
                    this->selectionVec.push_back(i);                // запоминаем выбор игрока
                    this->tilesVec[i]->setColorActive();            // плитка загорается
                    this->tilesSelected++;                          // считаем выбор
                    this->resetKeyTime();                           // не даём кликать слишком быстро
                }

            }
        }
        if(this->tilesSelected == this->nrOfActiveTiles)// проверка что нажато нужное кол-во плиток и вывод ответа
        {
            //Прописываем правильный выбор 
            if (this->checkSelection())
            {
                this->messageText.setString("Correct!");
                this->messageText.setFillColor(sf::Color::Green);
                this->messageTimer = 120.f; // показать на 2 секунды (при 60 FPS)
                this->score += 10;
                this->scoreText.setString("Score: " + std::to_string(this->score));
                std::cout << "Correct!" << "\n";
                this->correct++;
            }
            else
            {
                //Неправильный выбор плитки 
                this->messageText.setString("Incorrect!");
                this->messageText.setFillColor(sf::Color::Red);
                this->messageTimer = 120.f;
                this->score = std::max(0, score - 5);
                this->scoreText.setString("Score: " + std::to_string(this->score));
                std::cout << "Incorrect!" << "\n";
                this->incorrect++;
            }
            std::cout << "Correct/Incorrect: " << this->correct << "/" << this->incorrect << "\n";
            this->restart();
        }
    }
}
//конструктор создаёт объект игрового поля и инициализирует все переменные в безопасное начальное состояние по умолчанию
GameBoard::GameBoard() 
{
    this->window = nullptr;
    this->tileSize = 0.f;
    this->exitGame = false;
    this->keyTimeMax = 0.f;
    this->keyTime = 0.f;
    this->nrOfActiveTiles = 0;
    this->tilesSelected = 0;
    this->restarting = false;
    this->displayTimer = 0.f;
    this->correct = 0;
    this->incorrect = 0;
    this->exitToMenu = false;
}
//А все запускается во втором конструкторе
GameBoard::GameBoard(sf::RenderWindow* window, float tile_size, int board_width, int board_height, int nr_active)
    : window(window)
{
    this->tileSize = tile_size;
    this->exitGame = false;
    this->keyTimeMax = 10.f;
    this->keyTime = this->keyTimeMax;
    this->nrOfActiveTiles = nr_active;
    this->tilesSelected = 0;
    this->restarting = true;
    this->displayTimer = 0.f;
    this->correct = 0;
    this->incorrect = 0;
    this->exitToMenu = false;

    

    if (!this->font.loadFromFile("arial.ttf")) {
        std::cerr << "ERROR: Could not load font!" << std::endl;
    }

    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(45);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setPosition(610.f, 10.f); //позиция надписи
    this->scoreText.setString("Score: 0");

    this->messageText.setFont(this->font);
    this->messageText.setCharacterSize(40);
    this->messageText.setFillColor(sf::Color::Yellow);
    this->messageText.setPosition(620.f, 100.f); // центр верхней части окна
    this->messageText.setString("");
    this->messageTimer = 0.f;

    this->createBoard(board_width, board_height);
    this->randomizeBoard();

}

GameBoard::~GameBoard()//деструктор класса GameBoard, и он отвечает за освобождение памяти, которая была выделена вручную(через new) при создании плиток
{
    for (size_t i = 0; i < this->tilesVec.size(); i++)
    {
        delete this->tilesVec[i];
    }
}
//Метод restart() перезапускает раунд игры,
// сбрасывает выбор игрока, заново рандомизирует активные плитки и запускает режим показа порядка
void GameBoard::restart()
{
    this->tilesSelected = 0;
    this->restarting = true;
    this->displayTimer = 0.f;
    this->selectionVec.clear();
    this->randomizeBoard();
}
// Метод управляет результатом и вызывает игровую логику
void GameBoard::update(sf::RenderWindow& window)
{
    // Обработка выхода в меню
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->exitToMenu = true;
        return;
    }
    this->mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (this->messageTimer > 0.f)
    {
        this->messageTimer -= 1.f;
        if (this->messageTimer <= 0.f)
            this->messageText.setString("");
    }

    this->updateKeyTime();
    this->updateBoard();
}

//Метод отвечает за отрисовку всего, что отображается в игровом окне
void GameBoard::render(sf::RenderTarget& target)
{

    for (size_t i = 0; i < this->tilesVec.size(); i++)
    {
        this->tilesVec[i]->render(target);//вызываем метод для отрисовки плиток
    }
    target.draw(this->scoreText);//рисуем текмт с текущим счетом
    target.draw(this->messageText);//рисуем сообщения о результате

}
