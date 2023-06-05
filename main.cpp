#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <cstdlib>


using namespace sf;

int getRandomNum(int min, int max, bool oddMake = false)
{
    int num = min + rand() % (max - min + 1);

    if (oddMake == true && num%2 == 0 && num != 0) num--;

    return num;
}


class Grid
{
    Sprite sprite;
public:
    Grid(Texture& texture)
    {
        sprite.setTexture(texture);
    }

    void draw(RenderWindow& window)
    {
        for (int i=0; i<30; i++)
        {
            for (int j=0; j<40; j++)
            {
                sprite.setPosition(Vector2f(j*20, i*20));
                window.draw(sprite);
            }
        }
    }
};

class Snake;

class Apple
{;
public:

    Sprite* sprite;
    int scoreGiving;
    bool applesOnScreen = false;
    int appleMaxStack;

    Apple(Texture& texture, int appleMaxStack)
    {
        this->appleMaxStack = appleMaxStack;

        sprite = new Sprite[appleMaxStack];
        std::cout << "sprite's array has been created with size of " << appleMaxStack << std::endl;

        for (int i=0; i<appleMaxStack; i++){
            sprite[i].setTexture(texture);
            sprite[i].setOrigin(Vector2f(10, 10));
            std::cout << "apple " << i << " got texture" << std::endl;
        }

        scoreGiving = 5;
        applesOnScreen = false;
    }

    ~Apple()
    {
        delete [] sprite;
    }

    void updateApple(int appleID)
    {
        sprite[appleID].setPosition(Vector2f(10*getRandomNum(1, 80, true), 10*getRandomNum(1, 60, true)));
    }

    void spawn(RenderWindow& window, Snake& snake)
    {
        for (int i=0; i<appleMaxStack; i++){
            sprite[i].setPosition(Vector2f(10*getRandomNum(1, 80, true), 10*getRandomNum(1, 60, true)));
            std::cout << "apple " << i << " was positioned at ( " << sprite[i].getPosition().x << ";" << sprite[i].getPosition().y << " )" << std::endl;
        }
    }

    void draw(RenderWindow& window)
    {
        for (int i=0; i<appleMaxStack; i++)
            window.draw(sprite[i]);
    }
};

enum class Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

struct Coords
{
    float x;
    float y;

    Coords(){x=0; y=0;}

    Coords(float val1, float val2)
    {
        x = val1;
        y = val2;
    }
};

struct SnakeBody
{
    Sprite sprite;
    //Direction moveDirect;
    Coords nextsegment; // координаты следующего сегмента тела предположительные.

    SnakeBody(){}
    SnakeBody(Texture& texture)
    {
        sprite.setTexture(texture);
        sprite.setOrigin(Vector2f(10,10));
    }
};

class Snake
{
public:
    std::vector<SnakeBody*> bodyparts;
private:
    bool increaseSnakeSpeed = false;
    SnakeBody head;
    Texture* texturebody;
    int snakeLength;
    int score;
    int snakeGrowMultiplier;
    Apple* apple;
public:
    bool inputlock = false;
private:
    Direction direction;
public:

    Snake(Texture& texturebody, Texture& texturehead, Apple& apple, int snakeGrowMultiplier=1)
    {
        this->apple = &apple;

        this->texturebody = &texturebody;

        head.sprite.setTexture(texturehead);

        head.sprite.setOrigin(Vector2f(10, 10));

        direction = Direction::RIGHT;

        score = 0;

        snakeLength = 0;

        this->snakeGrowMultiplier = snakeGrowMultiplier;

        head.sprite.setPosition(Vector2f(390, 290));

        grow();

        bodyparts[0]->nextsegment.x = head.sprite.getPosition().x;
        bodyparts[0]->nextsegment.y = head.sprite.getPosition().y;
        for (int i=1; i<snakeLength; i++)
        {
            bodyparts[i]->nextsegment.x = bodyparts[i-1]->sprite.getPosition().x;
            bodyparts[i]->nextsegment.y = bodyparts[i-1]->sprite.getPosition().y;
        }

    }

    ~Snake()
    {

    }

    SnakeBody getHead(){return head;}
    SnakeBody* getBodyPart(int val1){return bodyparts[val1];}

    int getScore()
    {
        return score;
    }

    void movement(float t, float dt)
    {
        switch (direction)
        {
            case Direction::UP:
            {
                bodyparts[0]->nextsegment.x = head.sprite.getPosition().x;
                bodyparts[0]->nextsegment.y = head.sprite.getPosition().y;
                for (int i=1; i<snakeLength; i++)
                {
                    bodyparts[i]->nextsegment.x = bodyparts[i-1]->sprite.getPosition().x;
                    bodyparts[i]->nextsegment.y = bodyparts[i-1]->sprite.getPosition().y;
                }
                head.sprite.move(Vector2f(0,-20));
                break;
            }
            case Direction::DOWN:
            {
                bodyparts[0]->nextsegment.x = head.sprite.getPosition().x;
                bodyparts[0]->nextsegment.y = head.sprite.getPosition().y;
                for (int i=1; i<snakeLength; i++)
                {
                    bodyparts[i]->nextsegment.x = bodyparts[i-1]->sprite.getPosition().x;
                    bodyparts[i]->nextsegment.y = bodyparts[i-1]->sprite.getPosition().y;
                }
                head.sprite.move(Vector2f(0,20));
                break;
            }
            case Direction::RIGHT:
            {
                bodyparts[0]->nextsegment.x = head.sprite.getPosition().x;
                bodyparts[0]->nextsegment.y = head.sprite.getPosition().y;
                for (int i=1; i<snakeLength; i++)
                {
                    bodyparts[i]->nextsegment.x = bodyparts[i-1]->sprite.getPosition().x;
                    bodyparts[i]->nextsegment.y = bodyparts[i-1]->sprite.getPosition().y;
                }
                head.sprite.move(Vector2f(20,0));
                break;
            }
            case Direction::LEFT:
            {
                bodyparts[0]->nextsegment.x = head.sprite.getPosition().x;
                bodyparts[0]->nextsegment.y = head.sprite.getPosition().y;
                for (int i=1; i<snakeLength; i++)
                {
                    bodyparts[i]->nextsegment.x = bodyparts[i-1]->sprite.getPosition().x;
                    bodyparts[i]->nextsegment.y = bodyparts[i-1]->sprite.getPosition().y;
                }
                head.sprite.move(Vector2f(-20,0));
                break;
            }
            default: break;
        }
        for (int i=0; i<snakeLength; i++)
        {
            //bodyparts[i]->sprite.move(Vector2f(bodyparts[i]->sprite.getPosition().x-bodyparts[i]->nextsegment.x, bodyparts[i]->sprite.getPosition().y-bodyparts[i]->nextsegment.y));
            bodyparts[i]->sprite.setPosition(Vector2f(bodyparts[i]->nextsegment.x, bodyparts[i]->nextsegment.y));
        }
    }

    void handleInput(RenderWindow& window, float& movetimetochange)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code== Keyboard::W || event.key.code == Keyboard::Up && direction != Direction::DOWN && inputlock == false)
                {
                    head.sprite.setRotation(270);
                    direction = Direction::UP;

                    inputlock = true;
                }
                if (event.key.code== Keyboard::A || event.key.code == Keyboard::Left && direction != Direction::RIGHT && inputlock == false)
                {
                    head.sprite.setRotation(180);
                    direction = Direction::LEFT;
                    inputlock = true;
                }
                if (event.key.code== Keyboard::S || event.key.code == Keyboard::Down && direction != Direction::UP && inputlock == false)
                {
                    head.sprite.setRotation(90);
                    direction = Direction::DOWN;

                    inputlock = true;
                }
                if (event.key.code== Keyboard::D || event.key.code == Keyboard::Right && direction != Direction::LEFT && inputlock == false)
                {
                    head.sprite.setRotation(0);
                    direction = Direction::RIGHT;

                    inputlock = true;
                }
                if (event.key.code== Keyboard::Equal)
                {
                    movetimetochange-= 0.025;
                }
                if (event.key.code== Keyboard::Dash)
                {
                    movetimetochange+= 0.025;
                }
                if (event.key.code== Keyboard::M)
                {
                    if (increaseSnakeSpeed == false) increaseSnakeSpeed = true;
                    else increaseSnakeSpeed = false;
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();

        }
    }

    void restartGame()
    {
        for (int i=0; i<apple->appleMaxStack; i++)
        {
            apple->updateApple(i);
        }

        head.sprite.setPosition(Vector2f(390, 290));

        score = 0;

        destroySnakeBodyParts();

        snakeLength = 0;

        grow();

        std::cout << "num of bodyparts in vector: " << bodyparts.size() << std::endl;
    }

    void headCrush()
    {
        for (int i=0; i<snakeLength; i++)
        {
            if (head.sprite.getPosition().x == bodyparts[i]->sprite.getPosition().x && head.sprite.getPosition().y == bodyparts[i]->sprite.getPosition().y)
            {
                restartGame();
            }
            if (head.sprite.getPosition().x < 0 || head.sprite.getPosition().y < 0 || head.sprite.getPosition().x > 800 || head.sprite.getPosition().y > 600 )
            {
                restartGame();
            }
        }
    }

    void draw(RenderWindow& window)
    {
        window.draw(head.sprite);
        for (int i=0; i<snakeLength; i++)
        {
            window.draw(bodyparts[i]->sprite);
        }
    }

    void destroySnakeBodyParts()
    {
        bodyparts.clear();
    }

    void grow()
    {
        snakeLength += snakeGrowMultiplier;
        for (int i=0; i<snakeGrowMultiplier; i++)
        {
            bodyparts.push_back(new SnakeBody(*texturebody));
            switch (direction){
                case Direction::UP:
                {
                    bodyparts[snakeLength-1]->sprite.setPosition(Vector2f(head.sprite.getPosition().x, head.sprite.getPosition().y+20));
                    std::cout << "body part " << snakeLength << " was created at ( " << head.sprite.getPosition().x << ";" << head.sprite.getPosition().y+20 << " )" << std::endl;
                    break;
                }
                case Direction::DOWN:
                {
                    bodyparts[snakeLength-1]->sprite.setPosition(Vector2f(head.sprite.getPosition().x, head.sprite.getPosition().y-20));
                    std::cout << "body part " << snakeLength << " was created at ( " << head.sprite.getPosition().x << ";" << head.sprite.getPosition().y-20 << " )" << std::endl;
                    break;
                }
                case Direction::RIGHT:
                {
                    bodyparts[snakeLength-1]->sprite.setPosition(Vector2f(head.sprite.getPosition().x-20, head.sprite.getPosition().y));
                    std::cout << "body part " << snakeLength << " was created at ( " << head.sprite.getPosition().x-20 << ";" << head.sprite.getPosition().y << " )" << std::endl;
                    break;
                }
                case Direction::LEFT:
                {
                    bodyparts[snakeLength-1]->sprite.setPosition(Vector2f(head.sprite.getPosition().x+20, head.sprite.getPosition().y));
                    std::cout << "body part " << snakeLength << " was created at ( " << head.sprite.getPosition().x+20 << ";" << head.sprite.getPosition().y << " )" << std::endl;
                    break;
                }
            }
        }
    }

    void eatApple(float movetimetochange)
    {
        for (int i=0; i<apple->appleMaxStack; i++)
        {
            if (head.sprite.getPosition().x == apple->sprite[i].getPosition().x && head.sprite.getPosition().y == apple->sprite[i].getPosition().y)
            {
                if (increaseSnakeSpeed == true) movetimetochange -= 0.002;
                score += apple->scoreGiving;
                apple->updateApple(i);
                grow();
                std::cout << "score: " << score << std::endl;
                std::cout << "snake length: " << snakeLength << std::endl;
            }
        }
    }
};

int main()
{
    srand(time(NULL));

    sf::RenderWindow app(sf::VideoMode(800, 600), "Snake Game", Style::Close);

    sf::Texture gridtexture;
    gridtexture.loadFromFile("media/Tile.png");
    sf::Texture snakebody;
    snakebody.loadFromFile("media/SnakeBody.png");
    sf::Texture snakehead;
    snakehead.loadFromFile("media/SnakeHead.png");
    sf::Texture appletexture;
    appletexture.loadFromFile("media/Apple.png");

    Image icon;
    if (!icon.loadFromFile("media/SnakeHead.png")) return 1;
    app.setIcon(20,20,icon.getPixelsPtr());

    Font font;
    font.loadFromFile("media/sfns-display-bold.ttf");

    std::string scorestring;
    scorestring = "Score: " + std::to_string(0);
    Text text(scorestring, font, 20);
    text.setPosition(Vector2f(0,0));
    text.setColor(Color::Black);

    Grid grid(gridtexture);

    Apple apple(appletexture, 5);

    Snake snake(snakebody, snakehead, apple);

    Clock clock;
    Clock movementClock;

    apple.spawn(app, snake);

    static float movetime = 0.2;

    while (app.isOpen())
    {
        Time elapsed = clock.restart();
        Time time = movementClock.getElapsedTime();
        float t = time.asSeconds();
        float dt = elapsed.asSeconds();

        if (t > movetime){
            snake.inputlock = false;
            snake.movement(t, dt);
            movementClock.restart();
        }

        snake.headCrush();

        snake.handleInput(app, movetime);

        snake.eatApple(movetime);

        scorestring = "Score: " + std::to_string(snake.getScore());
        text.setString(scorestring);

        app.clear();

        grid.draw(app);

        snake.draw(app);

        apple.draw(app);

        app.draw(text);

        app.display();
    }

    return EXIT_SUCCESS;
}
