#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <vector>
#include <math.h>

using namespace sf;
class Pacman;
class Ghost;
class Blinky;
class Pinky;
class Inky;
class Clyde;

class GameSettings {
private:
    std::string windowTitle;
    sf::Color pacmanColor;
    sf::Color squareColor;
    sf::Color smallCircleColor;
    sf::Color biglCircleColor;
    sf::Color blinkyColor;
    sf::Color pinkyColor;
    sf::Color inkyColor;
    sf::Color clydeColor;
    int gridSize;
    int pacmanStartX;
    int pacmanStartY;

public:
    ~GameSettings() {};
    int getPacmanStartX() const { return pacmanStartX; }
    int getPacmanStartY() const { return pacmanStartY; }
    GameSettings() {}
    GameSettings(std::string windowTitle, int gridSize,
        int pacmanStartX, int pacmanStartY,
        sf::Color pacmanColor, sf::Color squareColor, sf::Color smallCircleColor,
        sf::Color biglCircleColor, sf::Color blinkyColor, sf::Color pinkyColor,
        sf::Color inkyColor, sf::Color clydeColor) : windowTitle(windowTitle), gridSize(gridSize),
        pacmanStartX(pacmanStartX), pacmanStartY(pacmanStartY), pacmanColor(pacmanColor), squareColor(squareColor), smallCircleColor(smallCircleColor),
        biglCircleColor(biglCircleColor), blinkyColor(blinkyColor), pinkyColor(pinkyColor), inkyColor(inkyColor), clydeColor(clydeColor) {};
    std::string getWindowTitle() const { return windowTitle; }
    int getGridSize() const { return gridSize; }
    sf::Color getPacmanColor() const { return pacmanColor; }
    sf::Color getSquareColor() const { return squareColor; }
    sf::Color getCircleColor() const { return smallCircleColor; }
    sf::Color getCircle2Color() const { return biglCircleColor; }
    sf::Color getBlinkyColor() const { return blinkyColor; }
    sf::Color getPinkyColor() const { return pinkyColor; }
    sf::Color getInkyColor() const { return inkyColor; }
    sf::Color getClydeColor() const { return clydeColor; }
};

class Food {
private:
    int count;
    int point;
    char type;
public:
    ~Food() {};
    Food() {};
    Food(int count, int point, char type) : count(count), point(point), type(type) {};
    int getCount() { return count; }
    int getPoint() { return point; }
    char getType() { return type; }
    void decreaseCount() { count--; }
    void increaseCount() { count++; }
};

class Map {
private:
    int H, W;
    Food smallFood;
    Food bigFood;
    std::vector<std::string> maze;
public:
    ~Map() {};
    Map(int H, int W, Food smallFood, Food bigFood) : H(H), W(W), smallFood(smallFood), bigFood(bigFood) { maze.resize(H); }
    int getH() const { return H; }
    int getW() const { return W; }
    char getTile(int y, int x) const { return  maze[y][x]; }
    void setTile(int y, int x, char tile) { maze[y][x] = tile; }
    Food& getSmallFood() { return smallFood; }
    Food& getBigFood() { return bigFood; }

    void createMap() {
        std::string tempmaze[] = {
            "                              ",
            "                              ",
            "                              ",
            " XXXXXXXXXXXXXXXXXXXXXXXXXXXX ",
            " XooooooooooooXXooooooooooooX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XOXXXXoXXXXXoXXoXXXXXoXXXXOX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XooooooooooooooooooooooooooX ",
            " XoXXXXoXXoXXXXXXXXoXXoXXXXoX ",
            " XoXXXXoXXoXXXXXXXXoXXoXXXXoX ",
            " XooooooXXooooXXooooXXooooooX ",
            " XXXXXXoXXXXX XX XXXXXoXXXXXX ",
            " nnnnnXoXXXXX XX XXXXXoXnnnnn ",
            " nnnnnXoXX          XXoXnnnnn ",
            " nnnnnXoXX XXXXXXXX XXoXnnnnn ",
            " XXXXXXoXX XnnnnnnX XXoXXXXXX ",
            "       o   XnnnnnnX   o       ",
            " XXXXXXoXX XnnnnnnX XXoXXXXXX ",
            " nnnnnXoXX XXXXXXXX XXoXnnnnn ",
            " nnnnnXoXX          XXoXnnnnn ",
            " nnnnnXoXX XXXXXXXX XXoXnnnnn ",
            " XXXXXXoXX XXXXXXXX XXoXXXXXX ",
            " XooooooooooooXXooooooooooooX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XOooXXooooooooooooooooXXooOX ",
            " XXXoXXoXXoXXXXXXXXoXXoXXoXXX ",
            " XXXoXXoXXoXXXXXXXXoXXoXXoXXX ",
            " XooooooXXooooXXooooXXooooooX ",
            " XoXXXXXXXXXXoXXoXXXXXXXXXXoX ",
            " XoXXXXXXXXXXoXXoXXXXXXXXXXoX ",
            " XooooooooooooooooooooooooooX ",
            " XXXXXXXXXXXXXXXXXXXXXXXXXXXX ",
            "                              ",
        };
        for (int i = 0; i < H; ++i) {
            maze[i] = tempmaze[i];
        }
        // подсчет еды после создания
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (maze[i][j] == smallFood.getType()) {
                    smallFood.increaseCount();
                }
                else if (maze[i][j] == bigFood.getType()) {
                    bigFood.increaseCount();
                }
            }
        }
    }

    void MazePaint(GameSettings& settings, RenderWindow& window, Sprite fruitShape, Sprite pacman);

};

class Fruit {
private:
    int x;       //координата X на карте
    int y;       //координата Y на карте
    int points;  //количество очков за съедение
    Sprite sprite; //графическое представление
    static bool isActive;  //активен ли фрукт
public:
    Fruit() {};
    Fruit(int points, Sprite sprite) : points(points), sprite(sprite) {}
    int getX() const { return x; }
    int getY() const { return y; }
    int getPoints() const { return points; }
    Sprite getSprite() const { return sprite; }
    static void setIsActive(bool active) { Fruit::isActive = active; }
    bool getIsActive() { return Fruit::isActive; }

    void createFruit(GameSettings& settings, Map& map, RenderWindow& window) {
        int sum = (map.getSmallFood()).getCount() + (map.getBigFood()).getCount();
        if ((sum == 176 || sum == 76) && !isActive)  //когда Пакман съел первые 70 или 170 точек
        {
            int randY, randX;
            do {                                           //выбор случайных координат
                randY = rand() % 30 + 4;
                randX = rand() % 23 + 4;
            } while (map.getTile(randY, randX) != ' ' && map.getTile(randY, randX) != 'b');
            x = randX;
            y = randY;
            sprite.setPosition(randX * settings.getGridSize(), randY * settings.getGridSize());
            isActive = true;
        }
        if (isActive)                                 //если фрукт активен, добавляем его на карту
        {
            map.setTile(y, x, 'F');
        }
    }
};
bool Fruit::isActive = false;



class Pacman {
private:
    int x, y, nextX, nextY, score, nextDirection, lives, speed;
    int highScore;
    int animationFrame; // Текущий кадр анимации рта
    int animationSpeed;//Скорость анимации
    int animationDirection; //Направление анимации
    sf::Sprite pacmanSprite;
   sf::Texture pacmanTextures[4][3];
public:
    ~Pacman() {};
    Pacman(int x, int y, int nextX, int nextY, int speed, int nextDirection, int lives, int score) : x(x), y(y), nextX(nextX),
        nextY(nextY), speed(speed), nextDirection(nextDirection), lives(lives), score(score), animationFrame(0), animationSpeed(0) {
        highScore = 0;
    }
    int getX() const { return x; }
    int getY() const { return y; }
    int getScore() const { return score; }
    int getLives() const { return lives; }
    int getNextDirection() const { return nextDirection; }
    void setX(int a) { x = a; }
    void setY(int a) { y = a; }
    void setNextX(int a) { nextX = a; }
    void setNextY(int a) { nextY = a; }
    void setSpeed(int a) { speed = a; }
    void setLives(int a) { lives = a; }
    void setScore(int a) { score = a; }
    void setNextDirection(int a) { nextDirection = a; }
    void setSprite(sf::Sprite a) { pacmanSprite = a; }
   void setTextures(sf::Texture(*textures)[3]) {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
                pacmanTextures[i][j] = textures[i][j];
        }
    }
    void loseLife() { lives--; }
    void addScore(int p) { score += p; }
    int getHighScore() const { return highScore; }
    void updateHighScore(int newScore) {
        if (newScore > highScore)
            highScore = newScore;
    }

    void setGhostsFrightened(Ghost** ghost, int duration);

    int Collision(Ghost** ghost);

    void updateAnimation() {
        animationSpeed++;
        if (animationSpeed >= 30)
        {
            //if (animationDirection == 0)
                animationFrame = (animationFrame + 1) % 3;
            animationSpeed = 0;
        }
    }

   sf::Sprite getSprite()
    {

        pacmanSprite.setTexture(pacmanTextures[nextDirection][animationFrame]);
        //pacmanSprite.setPosition(x * 25, y * 25);
        return pacmanSprite;
    }

    void move(Map& map, Fruit& fruit, Ghost** ghost) {
        if (Keyboard::isKeyPressed(Keyboard::Up) && map.getTile(nextY - 1, nextX) != 'X' && !(nextY == 17 && nextX == 0 || nextY == 17 && nextX == map.getW() - 1)) {
            nextDirection = 0;
            animationDirection = 0; // Сбрасываем направление анимации
            nextX = x;
            nextY = y;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) && map.getTile(nextY + 1, nextX) != 'X' && !(nextY == 17 && nextX == 0 || nextY == 17 && nextX == map.getW() - 1)) {
            nextDirection = 1;
            animationDirection = 0; // Сбрасываем направление анимации
            nextX = x;
            nextY = y;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && (map.getTile(nextY, nextX - 1) != 'X')) {
            nextDirection = 2;
            animationDirection = 0; // Сбрасываем направление анимации
            nextX = x;
            nextY = y;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) && (map.getTile(nextY, nextX + 1) != 'X')) {
            nextDirection = 3;
            animationDirection = 0; // Сбрасываем направление анимации
            nextX = x;
            nextY = y;
        }
        speed++;
        if (speed >= 60)
        {
            switch (nextDirection)
            {
            case 0:
                if (map.getTile(nextY - 1, nextX) != 'X' && nextY - 1 >= 0)
                    nextY--;
                break;
            case 1:
                if (map.getTile(nextY + 1, nextX) != 'X' && nextY + 1 <= 35)
                    nextY++;
                break;
            case 2:
                if (nextY == 17 && nextX == 1)
                    nextX = map.getW() - 2;
                else if (map.getTile(nextY, nextX - 1) != 'X' && nextX - 1 >= 0)
                    nextX--;
                break;
            case 3:
                if (nextY == 17 && nextX == map.getW() - 2)
                    nextX = 1;
                else if (map.getTile(nextY, nextX + 1) != 'X' && nextX + 1 <= 35)
                    nextX++;
                break;
            }
            speed = 0;
        }
        if (map.getTile(nextY, nextX) != 'X')
        {
            if (map.getTile(nextY, nextX) == (map.getSmallFood()).getType())
            {
                addScore((map.getSmallFood()).getPoint());
                (map.getSmallFood()).decreaseCount();
            }
            if (map.getTile(nextY, nextX) == (map.getBigFood()).getType())
            {
                addScore((map.getBigFood()).getPoint());
                (map.getBigFood()).decreaseCount();
                setGhostsFrightened(ghost, 3000);
            }
            if (map.getTile(nextY, nextX)=='F')
            {
                addScore(fruit.getPoints());
                fruit.setIsActive(false);
            }
            map.setTile(y, x, 'b');
            map.setTile(nextY, nextX, 'P');
            x = nextX;
            y = nextY;
        }
    }

    int WonOrLost(Food smallFood, Food bigFood, Text& Result)
    {
        int f = 0;
        if (smallFood.getCount() == 0 && bigFood.getCount() == 0)
        {
            Result.setString("You won! ");
            f = 1;
        }
        else if (!getLives())
        {
            Result.setString("You lost! ");
            f = 2;
        }
        return f;
    }
};

void Map::MazePaint(GameSettings& settings, RenderWindow& window, Sprite fruitShape, Sprite pacman) {
    RectangleShape square(Vector2f(settings.getGridSize(), settings.getGridSize()));
    square.setFillColor(settings.getSquareColor());
       RectangleShape square2(Vector2f(settings.getGridSize()+20, settings.getGridSize()+20));
       square2.setFillColor(Color::Black);
    CircleShape smallCircle(3);
    smallCircle.setFillColor(settings.getCircleColor());
    CircleShape biglCircle(6);
    biglCircle.setFillColor(settings.getCircle2Color());
    // RectangleShape pacman(Vector2f(settings.getGridSize(), settings.getGridSize()));
 //    pacman.setFillColor(settings.getPacmanColor());
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            if (maze[i][j] == 'X')
            {
                square.setPosition(j * settings.getGridSize(), i * settings.getGridSize());
                window.draw(square);
            }
        }
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            if (maze[i][j] != 'X')
            {
                square2.setPosition(j * settings.getGridSize(), i * settings.getGridSize());
                window.draw(square2);
            }
        }

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            if (maze[i][j] == smallFood.getType())
            {
                
                smallCircle.setPosition(j * settings.getGridSize() + 16.5, i * settings.getGridSize() + 16.5f);
                // int pacmanX = static_cast<int>(pacman.getPosition().y / settings.getGridSize());
             //    int pacmanCol = static_cast<int>(pacman.getPosition().x / settings.getGridSize());
                window.draw(smallCircle);
            }
            else if (maze[i][j] == bigFood.getType())
            {
                
                biglCircle.setPosition(j * settings.getGridSize() + 14.5f, i * settings.getGridSize() + 14.5f);
                window.draw(biglCircle);
            }
            else if (maze[i][j] == 'F')
            {
                fruitShape.setPosition(j * settings.getGridSize() + 10.5f, i * settings.getGridSize() + 10.5f);
                window.draw(fruitShape);
            }
          
            
            else if (maze[i][j] == 'P')
            {
               
                pacman.setPosition(j * settings.getGridSize() + 5.5f, i * settings.getGridSize() + 5.5f);
                window.draw(pacman);
            }
        }

};

class Ghost {
public:
    enum GhostState {
        NORMAL,
        FRIGHTENED,
        EATEN
    };
    protected:
    int x, y, score, direction, lastDirection;
    int frightenedTimer;  // таймер для режима испуга
    GhostState currentState;
public:
    Ghost() {};
    ~Ghost() {};
    Ghost(int x, int y, int score, int direction, int lastDirection) : x(x), y(y), score(score), direction(direction), lastDirection(lastDirection) {};
    int getX() const { return x; }
    int getY() const { return y; }
    int getScore() const { return score; }
    int getDirection() const { return direction; }
    int getLastDirection() const { return lastDirection; }
    void setAll(int a, int b, int c, int d, int e) { x = a, y = b, score = c, d = direction, e = lastDirection; }

    GhostState getCurrentState() { return currentState; }
    void setGhostState(GhostState state, int duration) {
        currentState = state;
        frightenedTimer = duration;
    }

    float distance(int x1, int y1, int x2, int y2) {
        return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
    }
    void ghostDraw(sf::Color color, RenderWindow& window, GameSettings settings)
    {
        RectangleShape ghostShape(Vector2f(settings.getGridSize(), settings.getGridSize()));
        if (currentState == FRIGHTENED)
        {
            ghostShape.setFillColor(sf::Color::White); //Белый цвет для испуганного состояния
        }
        else
            ghostShape.setFillColor(color);
        ghostShape.setPosition(getX() * settings.getGridSize(), getY() * settings.getGridSize());
        window.draw(ghostShape);
    }

    void move(Map map, int goalX, int goalY, Ghost** ghost);
                       
};

void Pacman::setGhostsFrightened(Ghost** ghost, int duration) {
    for (int i = 0; i < 4; ++i)
    {
        ghost[i]->setGhostState(Ghost::FRIGHTENED, duration);
    }
}

int Pacman::Collision(Ghost** ghost)
{
    int result = 0;
    if (getX() == ghost[0]->getX() && getY() == ghost[0]->getY()) {
        if (ghost[0]->getCurrentState() == Ghost::FRIGHTENED)
        {
            ghost[0]->setAll(13, 16, 0, 3, 3);
            addScore(300);
        }
        else
        {
            loseLife();
            result = 1;
        }
    }
    else if (getX() == ghost[1]->getX() && getY() == ghost[1]->getY()) {
        if (ghost[1]->getCurrentState() == Ghost::FRIGHTENED)
        {
            ghost[1]->setAll(16, 16, 0, 3, 3);
            addScore(300);
        }
        else
        {
            loseLife();
            result = 1;
        }
    }
    else if (getX() == ghost[2]->getX() && getY() == ghost[2]->getY()) {
        if (ghost[2]->getCurrentState() == Ghost::FRIGHTENED)
        {
            ghost[2]->setAll(13, 18, 0, 3, 3);
            addScore(300);
        }
        else
        {
            loseLife();
            result = 1;
        }
    }
    else if (getX() == ghost[3]->getX() && getY() == ghost[3]->getY()) {
        if (ghost[3]->getCurrentState() == Ghost::FRIGHTENED)
        {
            ghost[3]->setAll(16, 18, 0, 3, 3);
            addScore(300);
        }
        else
        {
            loseLife();
            result = 1;
        }
    }
    return result;
}

class Blinky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    ~Blinky() {};
    Blinky() {};
    Blinky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void BlinkyMove(Pacman pacman, Map map, GameSettings settings, RenderWindow& window, Ghost** ghost) {
        move(map, pacman.getX(), pacman.getY(), ghost);
        ghostDraw(settings.getBlinkyColor(), window, settings);
    }
};

class Pinky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    ~Pinky() {};
    Pinky() {};
    Pinky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void PinkyMove(Pacman pacman, Map map, GameSettings settings, RenderWindow& window, Ghost** ghost) {
        int a = pacman.getX(), b = pacman.getY();
        switch (pacman.getNextDirection())
        {
        case 0:
            b = b - 4;
            break;
        case 1:
            b = b + 4;
            break;
        case 2:
            a = a - 4;
            break;
        case 3:
            a = a + 4;
            break;
        }
        move(map, a, b, ghost);
        ghostDraw(settings.getPinkyColor(), window, settings);
    }
};

class Inky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    ~Inky() {};
    Inky() {};
    Inky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void InkyMove(Pacman pacman, Map map, Ghost blinky, GameSettings settings, RenderWindow& window, Ghost** ghost) {
        int a = pacman.getX(), b = pacman.getY();
        switch (pacman.getNextDirection())
        {
        case 0:
            b = b - 2;
            break;
        case 1:
            b = b + 2;
            break;
        case 2:
            a = a - 2;
            break;
        case 3:
            a = a + 2;
            break;
        }
        a = blinky.getX() + 2 * (a - blinky.getX());
        b = blinky.getY() + 2 * (b - blinky.getY());
        move(map, a, b, ghost);
        ghostDraw(settings.getInkyColor(), window, settings);
    }
};

class Clyde : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    ~Clyde() {};
    Clyde() {};
    Clyde(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void ClydeMove(Pacman pacman, Map map, GameSettings settings, RenderWindow& window, Ghost** ghost) {
        int a, b;
        float mainDistance = distance(pacman.getX(), pacman.getY(), x, y);
        if (mainDistance > 8)
        {
            a = pacman.getX();
            b = pacman.getY();
        }
        else
        {
            a = 0;
            b = map.getH();
        }
        move(map, a, b, ghost);
        ghostDraw(settings.getClydeColor(), window, settings);
    }
};


   
void Ghost::move(Map map, int goalX, int goalY, Ghost** ghost) {
    float distanceUp, distanceDown, distanceLeft, distanceRight;
    double minDistance = INFINITY;
    int change = 0;
    int f = 0;

    if (currentState == FRIGHTENED) {
        //случайное движение
        frightenedTimer--;
        if (frightenedTimer <= 0) {
            currentState = NORMAL;
            ghost[0]->setAll(11, 14, 0, 3, 3);
            ghost[1]->setAll(13, 14, 0, 3, 3);
            ghost[2]->setAll(15, 14, 0, 3, 3);
            ghost[3]->setAll(17, 14, 0, 3, 3);
        }
        score++;
        if (score >= 400)
        {
            change = 1;
            int newDirection;
            do {
                newDirection = rand() % 4;
                f = 0; // Начинаем с предположения, что направление недопустимо

                if (newDirection == 0) { // Вверх
                    if (map.getTile(y - 1, x) != 'X' && lastDirection != 1 && !(y == 17 && x == 0 || y == 17 && x == map.getW() - 1)) {
                        f = 1; // Установим f в 1, если направление подходит
                    }
                }
                else if (newDirection == 1) { // Вниз
                    if (map.getTile(y + 1, x) != 'X' && lastDirection != 0 && !(y == 17 && x == 0 || y == 17 && x == map.getW() - 1)) {
                        f = 1; // Установим f в 1, если направление подходит
                    }
                }
                else if (newDirection == 2) { // Влево
                    if (map.getTile(y, x - 1) != 'X' && lastDirection != 3) {
                        f = 1; // Установим f в 1, если направление подходит
                    }
                }
                else if (newDirection == 3) { // Вправо
                    if (map.getTile(y, x + 1) != 'X' && lastDirection != 2) {
                        f = 1; // Установим f в 1, если направление подходит
                    }
                }
                // Если f равно нулю, то цикл должен повторится
            } while (f == 0);
            direction = newDirection;
            switch (direction) {
            case 0: //Движение вверх
                y--;
                break;
            case 1: //Движение вниз
                y++;
                break;
            case 2: //Движение влево
                if (y == 17 && x == 1)
                    x = map.getW() - 2;
                else
                    x--;
                break;
            case 3: //Движение вправо
                if (y == 17 && x == map.getW() - 2)
                    x = 1;
                else
                    x++;
                break;
            default:
                break;
            }
            score = 0;
        }
        if (lastDirection != direction && change)
            lastDirection = direction;
    }
    else
    {
        distanceUp = distance(goalX, goalY, x, y - 1);
        distanceDown = distance(goalX, goalY, x, y + 1);
        if (y == 17 && x == 1)
            distanceLeft = distance(goalX, goalY, map.getW() - 1, y);
        else distanceLeft = distance(goalX, goalY, x - 1, y);
        if (y == 17 && x == map.getW() - 1)
            distanceRight = distance(goalX, goalY, 0, y);
        else distanceRight = distance(goalX, goalY, x + 1, y);

        if (distanceRight <= minDistance && map.getTile(y, x + 1) != 'X' && lastDirection != 2) {
            minDistance = distanceRight;
            direction = 3;
        }
        if (distanceUp <= minDistance && map.getTile(y - 1, x) != 'X' && lastDirection != 1 && !(y == 17 && x == 0 || y == 17 && x == map.getW() - 1)) {
            minDistance = distanceUp;
            direction = 0;
        }
        if (distanceLeft <= minDistance && map.getTile(y, x - 1) != 'X' && lastDirection != 3) {
            minDistance = distanceLeft;
            direction = 2;
        }
        if (distanceDown <= minDistance && map.getTile(y + 1, x) != 'X' && lastDirection != 0 && !(y == 17 && x == 0 || y == 17 && x == map.getW() - 1)) {
            minDistance = distanceDown;
            direction = 1;
        }

        score++;
        if (score >= 60)
        {
            change = 1;
            // Двигаемся в выбранном направлении
            switch (direction) {
            case 0: //Движение вверх
                y--;
                break;
            case 1: //Движение вниз
                y++;
                break;
            case 2: //Движение влево
                if (y == 17 && x == 1)
                    x = map.getW() - 2;
                else
                    x--;
                break;
            case 3: //Движение вправо
                if (y == 17 && x == map.getW() - 2)
                    x = 1;
                else
                    x++;
                break;
            default:
                break;
            }
            score = 0;
        }

        if (lastDirection != direction && change)
            lastDirection = direction;
    }
}

class Game {
public:
    Game() {};
    ~Game() {};
    void resetGame(Map& map, Pacman& pacman, Ghost** ghostArray, GameSettings& settings, Text& Result, Fruit& fruit, int f) {
        // сброс еды
        Food smallFood(-2, 5, 'o');
        Food bigFood(0, 10, 'O');
        // сброс карты
        map = Map(35, 30, smallFood, bigFood);
        map.createMap();
        map.setTile(pacman.getY(), pacman.getX(), ' ');
        map.setTile(settings.getPacmanStartY(), settings.getPacmanStartX(), 'P');
     
        // сброс фрукта
        fruit.setIsActive(false);

        // сброс Pacman
        pacman.setX(settings.getPacmanStartX());
        pacman.setY(settings.getPacmanStartY());
        pacman.setNextX(settings.getPacmanStartX());
        pacman.setNextY(settings.getPacmanStartY());
        if (f == 2)  //если Пакман проиграл
        {
            pacman.setLives(3);
            pacman.updateHighScore(pacman.getScore());
            pacman.setScore(0);
        }
        pacman.setNextDirection(3);
        pacman.setSpeed(0);

        // сброс призраков
        Blinky& blinky = *static_cast<Blinky*>(ghostArray[0]);
        Pinky& pinky = *static_cast<Pinky*>(ghostArray[1]);
        Inky& inky = *static_cast<Inky*>(ghostArray[2]);
        Clyde& clyde = *static_cast<Clyde*>(ghostArray[3]);
        blinky.setAll(11, 14, 0, 3, 3);
        pinky.setAll(13, 14, 0, 3, 3);
        inky.setAll(15, 14, 0, 3, 3);
        clyde.setAll(17, 14, 0, 3, 3);

        //убираем результат
        Result.setString(" ");
    }
};


int main()
{
    Game game;
    int f = 0;  //проигрыш или победа
    GameSettings settings = GameSettings("Pac-Man 1", 25, 14, 26, sf::Color::Yellow, sf::Color::Blue, sf::Color::White, sf::Color::White, sf::Color::Red, sf::Color(255, 185, 193),
        sf::Color::Cyan, sf::Color(255, 165, 0));
    sf::Texture pacmanTextures[4][3]; //4 направления, 3 кадра анимации рта



    Pacman pacman(settings.getPacmanStartX(), settings.getPacmanStartY(), settings.getPacmanStartX(), settings.getPacmanStartY(), 0, 3, 3, 0);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::string filename = "images/pacman_" + std::to_string(i) + "_" + std::to_string(j) + ".png";
            pacmanTextures[i][j].loadFromFile(filename);
             
        }
    }
    pacman.setTextures(pacmanTextures);
    sf::Sprite pacmanSprite;
    pacmanSprite.setTexture(pacmanTextures[3][0]);//По умолчанию смотрим вправо
    pacmanSprite.setScale(0.21f, 0.21f); //уменьшим размер
   pacman.setSprite(pacmanSprite);

    Food smallFood(0, 5, 'o');
    Food bigFood(0, 10, 'O');
    Map map(35, 30, smallFood, bigFood);
    map.createMap();
    //cпрайт вишенок
    sf::Texture cherryTexture;
    cherryTexture.loadFromFile("images/cherry.png");
    sf::Sprite cherryShape;
    cherryShape.setTexture(cherryTexture);
    cherryShape.setScale(0.12f, 0.12f);
    //спрайт яблока
    sf::Texture appleTexture;
    appleTexture.loadFromFile("images/apple.png");
    sf::Sprite appleShape;
    appleShape.setTexture(appleTexture);
    appleShape.setScale(0.022f, 0.022f);
    //спрайт груши
    sf::Texture pearTexture;
    pearTexture.loadFromFile("images/pear.png");
    sf::Sprite pearShape;
    pearShape.setTexture(pearTexture);
    pearShape.setScale(0.12f, 0.12f);
    //спрайт апельсина
    sf::Texture orangeTexture;
    orangeTexture.loadFromFile("images/orange.png");
    sf::Sprite orangeShape;
    orangeShape.setTexture(orangeTexture);
    orangeShape.setScale(0.12f, 0.12f);
    //спрайт арбуза
    sf::Texture watermelonTexture;
    watermelonTexture.loadFromFile("images/watermelon.png");
    sf::Sprite watermelonShape;
    watermelonShape.setTexture(watermelonTexture);
    watermelonShape.setScale(0.032f, 0.032f);
    //массив фруктов
    Fruit fruitArray[5];
    fruitArray[0] = Fruit(20, cherryShape);
    fruitArray[1] = Fruit(30, appleShape);
    fruitArray[2] = Fruit(40, pearShape);
    fruitArray[3] = Fruit(50, orangeShape);
    fruitArray[4] = Fruit(60, watermelonShape);
    int randFruit = 0;
    //массив призраков
    Ghost** ghostArray = new Ghost *[4];
    ghostArray[0] = new Blinky(11, 14, 0, 3, 3);
    ghostArray[1] = new Pinky(13, 14, 0, 3, 3);
    ghostArray[2] = new Inky(15, 14, 0, 3, 3);
    ghostArray[3] = new Clyde(17, 14, 0, 3, 3);
    Blinky& blinky = *static_cast<Blinky*>(ghostArray[0]);
    Pinky& pinky = *static_cast<Pinky*>(ghostArray[1]);
    Inky& inky = *static_cast<Inky*>(ghostArray[2]);
    Clyde& clyde = *static_cast<Clyde*>(ghostArray[3]);
    //загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("Unformital Medium.ttf")) {
        return EXIT_FAILURE;
    }
    //текущий счёт
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(1 * settings.getGridSize(), 1 * settings.getGridSize());
    //число жизней
    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(40);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(24 * settings.getGridSize(), 1 * settings.getGridSize());
    //результат - проигрыш или победа
    sf::Text Result;
    Result.setFont(font);
    Result.setCharacterSize(80);
    Result.setFillColor(sf::Color::White);
    Result.setPosition(5 * settings.getGridSize(), 10 * settings.getGridSize());
    sf::Text highScore;
    highScore.setFont(font);
    highScore.setCharacterSize(40);
    highScore.setFillColor(sf::Color::White);
    highScore.setPosition(11 * settings.getGridSize(), 1 * settings.getGridSize());

    RenderWindow window(VideoMode(settings.getGridSize() * map.getW(), settings.getGridSize() * map.getH()), settings.getWindowTitle(), sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                game.resetGame(map, pacman, ghostArray, settings, Result, fruitArray[0], f);
            }
        }
        if (!fruitArray[0].getIsActive())
        {
            randFruit = rand() % 5 ;
        }
        randFruit = 4;
        window.clear(Color::Black);
        fruitArray[randFruit].createFruit(settings, map, window);
        map.MazePaint(settings, window, fruitArray[randFruit].getSprite(), pacman.getSprite());
        if (f = pacman.WonOrLost(map.getSmallFood(), map.getBigFood(), Result))
        {
            blinky.ghostDraw(settings.getBlinkyColor(), window, settings);
            pinky.ghostDraw(settings.getPinkyColor(), window, settings);
            inky.ghostDraw(settings.getInkyColor(), window, settings);
            clyde.ghostDraw(settings.getClydeColor(), window, settings);
            sf::FloatRect textBounds = Result.getLocalBounds();
            sf::Vector2u windowSize = window.getSize();
            Result.setPosition((windowSize.x - textBounds.width) / 2, (windowSize.y - textBounds.height) / 2 - 50);
            window.draw(Result);
        }
        else
        {
            pacman.move(map, fruitArray[randFruit], ghostArray);
            pacman.updateAnimation();
            if (pacman.Collision(ghostArray))
            {
                if (pacman.getLives())
                {
                    blinky.setAll(11, 14, 0, 3, 3);
                    pinky.setAll(13, 14, 0, 3, 3);
                    inky.setAll(15, 14, 0, 3, 3);
                    clyde.setAll(17, 14, 0, 3, 3);
                    map.setTile(pacman.getY(), pacman.getX(), 'b');
                    map.setTile(settings.getPacmanStartY(), settings.getPacmanStartX(), 'P');
                    pacman.setX(settings.getPacmanStartX());
                    pacman.setY(settings.getPacmanStartY());
                    pacman.setNextX(settings.getPacmanStartX());
                    pacman.setNextY(settings.getPacmanStartY());
                    pacman.setSpeed(0);
                    pacman.setNextDirection(3);
                }
            }
            else {
               blinky.BlinkyMove(pacman, map, settings, window, ghostArray);
               pinky.PinkyMove(pacman, map, settings, window, ghostArray);
                inky.InkyMove(pacman, map, blinky, settings, window, ghostArray);
                clyde.ClydeMove(pacman, map, settings, window, ghostArray);
            }
        }
        scoreText.setString("Score " + std::to_string(pacman.getScore()));
        livesText.setString("Lives " + std::to_string(pacman.getLives()));
        highScore.setString("High score " + std::to_string(pacman.getHighScore()));
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(highScore);
        window.display();
    }
    for (int i = 0; i < 4; ++i)
        delete ghostArray[i];
    delete[] ghostArray;
    return 0;
}
