#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// CONSTANTS
const int SCREEN_WIDTH = 520;
const int SCREEN_HEIGHT = 450;
const int TARGET_FPS = 60;

int arkanoid()
{
    srand(time(0));

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid!");
    window.setFramerateLimit(TARGET_FPS);

    Texture block_txr,background_txr,ball_txr,paddle_txr;
    block_txr.loadFromFile("images/arkanoid/block01.png");
    background_txr.loadFromFile("images/arkanoid/background.jpg");
    ball_txr.loadFromFile("images/arkanoid/ball.png");
    paddle_txr.loadFromFile("images/arkanoid/paddle.png");

    Sprite backgroundSprite(background_txr), ballSprite(ball_txr), paddleSprite(paddle_txr);
    paddleSprite.setPosition(300,440);

    const int MAX_BLOCKS = 1000;
    Sprite blocks[MAX_BLOCKS];

    int blockCount = 0;
    setupBlock(blocks, block_txr,blockCount);
    
    while (window.isOpen())
    {
       Event event;
       while (window.pollEvent(event))
       {
         if (event.type == Event::Closed)
             window.close();
       }
        float ballVelocityX=6, ballVelocityY=5;
        float xPos=300, yPos=300;

        xPos+=ballVelocityX;
        for (int i=0;i<blockCount;i++)
            if ( FloatRect(xPos+3,yPos+3,6,6).intersects(blocks[i].getGlobalBounds()) ) 
                {blocks[i].setPosition(-100,0); ballVelocityX=-ballVelocityX;}

        yPos+=ballVelocityY;
        for (int i=0;i<blockCount;i++)
            if ( FloatRect(xPos+3,yPos+3,6,6).intersects(blocks[i].getGlobalBounds()) ) 
                {blocks[i].setPosition(-100,0); ballVelocityY=-ballVelocityY;}

        if (xPos<0 || xPos>520)  ballVelocityX=-ballVelocityX;
        if (yPos<0 || yPos>450)  ballVelocityY=-ballVelocityY;

        if (Keyboard::isKeyPressed(Keyboard::Right)) paddleSprite.move(6,0);
        if (Keyboard::isKeyPressed(Keyboard::Left)) paddleSprite.move(-6,0);

        if ( FloatRect(xPos,yPos,12,12).intersects(paddleSprite.getGlobalBounds()) ) ballVelocityY=-(rand()%5+2);

        ballSprite.setPosition(xPos,yPos);

        drawWindow(window, backgroundSprite, ballSprite, paddleSprite, blocks, blockCount);
    }

  return 0;
}

void drawWindow(RenderWindow& window, Sprite& backgroundSprite, Sprite& ballSprite, Sprite& paddleSprite, Sprite* t_blocks, int& blockCount)
{
    window.clear();
    window.draw(backgroundSprite);
    window.draw(ballSprite);
    window.draw(paddleSprite);

    for (int i = 0; i < blockCount; i++)
    {
        window.draw(t_blocks[i]);
    }
    window.display();
}

void setupBlock(Sprite* t_blocks, Texture& t_block_txr, int& t_blockCount)
{
    const float BLOCK_SPACING_X = 43.f;
    const float BLOCK_SPACING_Y = 20.f;
    const int ROWS = 10;
    const int COLS = 10;

    for (int i = 1; i <= COLS; i++)
    {
        for (int j = 1; j <= ROWS; j++)
        {
            t_blocks[t_blockCount].setTexture(t_block_txr);
            t_blocks[t_blockCount].setPosition(i * BLOCK_SPACING_X, j * BLOCK_SPACING_Y);
            t_blockCount++;
        }
    }
}
