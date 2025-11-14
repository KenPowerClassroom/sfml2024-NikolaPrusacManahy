#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// CONSTANTS
const int SCREEN_WIDTH = 520;
const int SCREEN_HEIGHT = 450;
const int TARGET_FPS = 60;


void setupBlock(Sprite* blocks, Texture block_txr)
{
    int n = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            blocks[n].setTexture(block_txr);
            blocks[n].setPosition(i * 43, j * 20);
            n++;
        }
}

int arkanoid()
{
    srand(time(0));

    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid!");
    app.setFramerateLimit(TARGET_FPS);

    Texture block_txr,background_txr,ball_txr,paddle_txr;
    block_txr.loadFromFile("images/arkanoid/block01.png");
    background_txr.loadFromFile("images/arkanoid/background.jpg");
    ball_txr.loadFromFile("images/arkanoid/ball.png");
    paddle_txr.loadFromFile("images/arkanoid/paddle.png");

    Sprite backgroundSprite(background_txr), ballSprite(ball_txr), paddleSprite(paddle_txr);
    paddleSprite.setPosition(300,440);

    const int MAX_BLOCKS = 1000;
    Sprite blocks[MAX_BLOCKS];

    setupBlock(blocks, block_txr);
    

    float dx=6, dy=5;
    float x=300, y=300;

    while (app.isOpen())
    {
       Event e;
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();
       }

    x+=dx;
    for (int i=0;i<n;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(blocks[i].getGlobalBounds()) ) 
             {blocks[i].setPosition(-100,0); dx=-dx;}

    y+=dy;
    for (int i=0;i<n;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(blocks[i].getGlobalBounds()) ) 
             {blocks[i].setPosition(-100,0); dy=-dy;}

    if (x<0 || x>520)  dx=-dx;
    if (y<0 || y>450)  dy=-dy;

    if (Keyboard::isKeyPressed(Keyboard::Right)) paddleSprite.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) paddleSprite.move(-6,0);

    if ( FloatRect(x,y,12,12).intersects(paddleSprite.getGlobalBounds()) ) dy=-(rand()%5+2);

    ballSprite.setPosition(x,y);

    app.clear();
    app.draw(backgroundSprite);
    app.draw(ballSprite);
    app.draw(paddleSprite);

    for (int i=0;i<n;i++)
     app.draw(blocks[i]);

    app.display();
    }

  return 0;
}
